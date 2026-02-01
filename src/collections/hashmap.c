#include "collections/hashmap.h"

#include <assert.h>
#include <stdlib.h>

uint64_t hash_uint64(uint64_t key) {
    key ^= key >> 33;
    key *= 0xff51afd7ed558ccdL;
    key ^= key >> 33;
    key *= 0xc4ceb9fe1a85ec53L;
    key ^= key >> 33;
    return key;
}

HashFunc std_hash_func = hash_uint64;

HashMap* hashmap_create(size_t initial_size, HashFunc hash) {
    assert(initial_size % 2 == 0);
    HashMap* hm = malloc(sizeof(HashMap));
    hm->entries = calloc(initial_size, sizeof(PairKV));
    hm->states = calloc(initial_size, sizeof(EntryState));
    hm->hash = hash;
    hm->capacity = initial_size;
    hm->count = 0;
    hm->max_load = 0.7f;
    return hm;
}

bool hashmap_contains(const HashMap* hm, uint64_t key) {
    uint64_t index = hm->hash(key) & (hm->capacity - 1);
    EntryState state = hm->states[index];
    while (state != ENTRY_EMPTY) {
        if (state == ENTRY_OCCUPIED && hm->entries[index].key == key)
            return true;
        index = (index + 1) & (hm->capacity - 1);
        state = hm->states[index];
    } return false;
}

bool hashmap_get(const HashMap* hm, uint64_t key, uint64_t* out) {
    if (!out) return false;
    uint64_t index = hm->hash(key) & (hm->capacity - 1);
    while (hm->states[index] != ENTRY_EMPTY) {
        const PairKV kv = hm->entries[index];
        if (hm->states[index] == ENTRY_OCCUPIED && kv.key == key) {
            *out = kv.value;
            return true;
        } index = (index + 1) & (hm->capacity - 1);
    } return false;
}

void hashmap_insert(HashMap* hm, uint64_t key, uint64_t value) {
    uint64_t index = hm->hash(key) & (hm->capacity - 1);
    size_t tomb_index = SIZE_MAX;
    while (hm->states[index] != ENTRY_EMPTY) {
        if (tomb_index == SIZE_MAX && hm->states[index] == ENTRY_TOMBSTONE)
            tomb_index = index;
        if (hm->entries[index].key == key) {
            hm->entries[index].value = value;
            return;
        } index = (index + 1) & (hm->capacity - 1);
    }
    const size_t insert_index = (tomb_index != SIZE_MAX) ? tomb_index : index;
    hm->entries[insert_index] = (PairKV){key, value};
    hm->states[insert_index] = ENTRY_OCCUPIED;
}

bool hashmap_extract(HashMap* hm, uint64_t key, uint64_t* out) {
    uint64_t index = hm->hash(key) & (hm->capacity - 1);
    while (hm->states[index] != ENTRY_EMPTY) {
        if (hm->states[index] == ENTRY_OCCUPIED && hm->entries[index].key == key) {
            *out = hm->entries[index].value;
            hm->states[index] = ENTRY_TOMBSTONE;
            return true;
        } index = (index + 1) & (hm->capacity - 1);
    } return false;
}

bool hashmap_delete(HashMap* hm, uint64_t key, HashMapDestructor destructor) {
    uint64_t index = hm->hash(key) & (hm->capacity - 1);
    while (hm->states[index] != ENTRY_EMPTY) {
        if (hm->states[index] == ENTRY_OCCUPIED && hm->entries[index].key == key) {
            destructor(hm->entries[index].key, hm->entries[index].value);
            hm->states[index] = ENTRY_TOMBSTONE;
            return true;
        } index = (index + 1) & (hm->capacity - 1);
    } return false;
}

void hashmap_clear(HashMap* hm, HashMapDestructor destructor) {
    for (size_t i = 0; i < hm->capacity; i++) {
        if (hm->states[i] != ENTRY_OCCUPIED) continue;
        const PairKV kv = hm->entries[i];
        destructor(kv.key, kv.value);
        hm->states[i] = ENTRY_EMPTY;
    }
}

void hashmap_free(HashMap* hm, HashMapDestructor destructor) {
    hashmap_clear(hm, destructor);
    free(hm);
}
