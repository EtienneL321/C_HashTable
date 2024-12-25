// Writting my own hashtable implementation

/**
 * Start with a static implementation with a size of 16
 * Step 1 - Use hash function to create hash of input key
 * Step 2 - Use modulo operator to get index of size 16 array
 * Step 3 - Use linear probing to fit the hash into the array
 *
 * Need to be able to create and remove a hashmap
 *
 *
 * Things that still need to be considered
 * - Test that linear probing works
 * - Add searching for value given a key
 * - Resize hashtable once count is 33% of the total size
 * - Add removal of key/value pair from hashmap
 *
 * - When storing the string key, we are simply passing the pointer
 * which means we are creating a shallow copy and not a deep copy.
 * This needs to be fixed by copying each character at a time and
 * allocating new memory for it so that it is immutable.
 *
 * Linear probing affects addition, searching, and deletion of keys in
 * the hashtable. More information can be found here
 * https://stackoverflow.com/questions/6338798/is-searching-a-hashtable-for-a-value-that-isnt-there-on-linear-probing
 *
 */

typedef struct Hashtable
{
  void *val;          // key value pair
  unsigned long *key; // hash key pair (used to check for collision)
  void *str_key;      // string key
  int size;           // size of hashtable
  int count;          // current number of items in hashtable
} Hashtable;

/**
 * Initializes void pointer of type Hashtable
 */
void initialize_hashtable(Hashtable *map);

/**
 * Free allocated space to hashtable
 */
void free_hashtable(Hashtable *map);

/**
 * Treat hashtable as a Counter and add 1 to current count of key
 */
void add_to_hashtable(Hashtable *map, void *key);

/**
 * Return the value of a key/value pair. Returns -1 if no key was found in the hashtable
 */
int search_hashtable(Hashtable *map, void *key);

/**
 * Remove the a key from a hashtable if it exists
 */
void remove_from_hashtable(Hashtable *map, void *key);

/**
 * Print the contents of the hashtable
 */
void print_hashtable(Hashtable *map);