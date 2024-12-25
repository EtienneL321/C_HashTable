#include <stdlib.h>
#include <stdio.h>

#include "hashtable.h"

#define DEFAULT_SIZE 16

/**
 * djb2 hash function
 */
unsigned long hash(unsigned char *str)
{
  unsigned long hash = 5381;
  int c;

  while ((c = *str++))
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
  if (*((int *)(map->val) + i) == 0)
  {
    return i;
  }
  else if (*((map->key) + i) == h)
  {
    return i;
  }
  else
  {
    return -1;
  }
}

void initialize_hashtable(Hashtable *map)
{
  map->val = (int *)calloc(DEFAULT_SIZE * sizeof(int), 0);
  map->key = malloc(DEFAULT_SIZE * sizeof(unsigned long));
  map->str_key = (char **)malloc(DEFAULT_SIZE * sizeof(char *));
  map->size = DEFAULT_SIZE;
  map->count = 0;

  if (map->val == NULL || map->key == NULL)
  {
    printf("Failed to initialize hashtable\n");
  }
}

void free_hashtable(Hashtable *map)
{
  free(map->val);
  free(map->key);
  free(map->str_key);

  map->size = 0;
  map->count = 0;

  // if (map->val != NULL || map->key != NULL)
  // {
  //   printf("Failed to free hashtable memory\n");
  // }
}

void add_to_hashtable(Hashtable *map, void *key)
{
  // Calculate hash of key
  unsigned long h = hash(key);

  // Iterate until i does not create a collision
  int i;
  while ((i = collision(map, h)) == -1)
  {
    h++;
  }

  // increment by 1
  *((int *)(map->val) + i) += 1;

  // store key
  *((map->key) + i) = h;

  // store string key
  // We times i by 2 because the size of a pointer is 8 bytes
  *((char **)(map->str_key) + (2 * i)) = (char *)key;
}

void print_hashtable(Hashtable *map)
{
  for (int i = 0; i < map->size; i++)
  {
    if (*((int *)(map->val) + i) != 0)
    {
      printf("index: %4d  ||  key: %8lu  || str_key: %8s  ||  value: %4d\n", i, *((map->key) + i), *((char **)(map->str_key) + (2 * i)), *((int *)(map->val) + i));
    }
  }
}