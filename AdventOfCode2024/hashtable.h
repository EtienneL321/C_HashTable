// Writting my own hashtable implementation

/**
 * Start with a static implementation with a size of 16
 * Step 1 - Use hash function to create hash of input key
 * Step 2 - Use modulo operator to get index of size 16 array
 * Step 3 - Use linear probing to fit the hash into the array
 *
 * Need to be able to create and remove a hashmap
 *
 */

typedef struct Hashtable
{
  void *val; // key value pair
  void *key; // hash key pair (used to check for collision)
  int size;  // size of hashtable
  int count; // current number of items in hashtable
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
 * Print the contents of the hashtable
 */
void print_hashtable(Hashtable *map);