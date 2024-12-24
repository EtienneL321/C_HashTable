#include <stdlib.h>
#include <stdio.h>

#include "hashtable.h"

/**
 * djb2 hash function
 */
unsigned long hash(unsigned char *str)
{
  unsigned long hash = 5381;
  int c;

  while (c = *str++)
    hash = ((hash << 5) + hash) + c; // hash * 33 + c

  return hash;
}

/**
 * Return -1 if the current hash causes a collision
 * Returns a correct index otherwize
 */
int collision(Hashtable *map, unsigned long h)
{
  // Get index from hash of key
  int i = (int)(h % (unsigned long)(map->size));

  // Compare stored key to current hash at index i
  if (*((int *)(map->key) + i) == h)
  {
    return i;
  }
  else
  {
    return -1
  }
}

int initialize_hashtable(Hashtable *map)
{
  map->arr = (int *)calloc(16 * sizeof(int), 0);
  map->key = (int *)calloc(16 * sizeof(int), 0);
  map->size = 16;

  return map->arr != NULL && map->key != NULL;
}

int free_hashtable(Hashtable *map)
{
  free(map->arr);
  free(map->key);
  map->size = 0;
  map->count = 0;

  return map->arr == NULL && map->key == NULL;
}

void add_to_hashtable(Hashtable *map, void *key)
{
  // Calculate hash of key
  unsigned long h = hash(key);

  // Iterate until i does not create a collision
  int i;
  while (i = collision(&map, h) == -1)
  {
    h++;
  }

  // increment by 1
  *((int *)(map->arr) + i) += 1;
}

/**
 * Hashtable map;
 *
 * initialize_hashtable(map);
 *
 * add_to_hashtable(map, key, val, func)
 *
 */