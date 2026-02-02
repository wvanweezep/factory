#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef void (*HashMapDestructor)(uint64_t key, uint64_t value);

typedef uint64_t (*HashFunc)(uint64_t key);

typedef enum EntryState {
    ENTRY_EMPTY = 0,
    ENTRY_OCCUPIED,
    ENTRY_TOMBSTONE
} EntryState;

typedef struct PairKV {
    uint64_t key;
    uint64_t value;
} PairKV;

// Collection for storing key-value pairs of a generic type.
typedef struct HashMap {
    PairKV* entries;            // Array containing the map entries
    EntryState* states;         // Array containing map entry states
    HashFunc hash;              // Function computing the hash of keys
    size_t capacity;            // The total capacity of the hashmap
    size_t count;               // Current entries in the hashmap
    float max_load;             // Max load before the entry array grows
} HashMap;

extern const HashFunc std_hash_func;

/**
 * Creates a new empty HashMap of an initial size.
 * @param initial_size initial size of the entry array (power of 2)
 * @param hash hashing function used
 * @return pointer to newly created HashMap
 */
HashMap* hashmap_create(size_t initial_size, HashFunc hash);

/**
 * Checks the HashMap for the existence of an entry with the provided key.
 * @param hm HashMap to search through
 * @param key key to search for
 * @return true, if there exists an entry in this HashMap with the provided key
 */
bool hashmap_contains(const HashMap* hm, uint64_t key);

/**
 * Retrieves the value in the HashMap with the provided key.
 * @param hm HashMap to search through
 * @param key key to search for
 * @param out buffer to put the value in
 * @return true, if the value with the provided key was found
 */
bool hashmap_get(const HashMap* hm, uint64_t key, uint64_t* out);

/**
 * Inserts the value in the HashMap for the provided key.
 * @param hm HashMap to insert the value to
 * @param key key to register the value to
 * @param value value to insert in the HashMap
 */
void hashmap_insert(HashMap* hm, uint64_t key, uint64_t value);

/**
 * Extracts the entry from the HashMap with the provided key.
 * @param hm HashMap to extract the entry from
 * @param key key of the entry to extract
 * @param out buffer to put the value of the extracted entry in
 * @return true, if the entry was found in the HashMap
 */
bool hashmap_extract(HashMap* hm, uint64_t key, uint64_t* out);

/**
 * Deletes the entry from the HashMap with the provided key.
 * @param hm HashMap to delete the entry from
 * @param key key of the entry to delete
 * @param destructor function to free any occupied memory by the entry
 * @return true, if the entry was found in the HashMap
 */
bool hashmap_delete(HashMap* hm, uint64_t key, HashMapDestructor destructor);

/**
 * Clears and destroys all entries in the HashMap
 * @param hm HashMap to clear
 * @param destructor function to free any occupied memory by an entry
 */
void hashmap_clear(HashMap* hm, HashMapDestructor destructor);

/**
 * Destroys the HashMap and its entries.
 * @param hm HashMap to destroy
 * @param destructor function to free any occupied memory by an entry
 */
void hashmap_free(HashMap* hm, HashMapDestructor destructor);
