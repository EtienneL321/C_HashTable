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

  // Check if value at index i is 0
  if (*((int *)(map->val) + i) == 0)
  {
    map->count += 1;
    return i;
  }
  // Compare stored hash key to curernt hash at index i
  else if (*((map->key) + i) == h)
  {
    return i;
  }
  else
  {
    printf("Collision detected for hash %lu\n", h);
    return -1;
  }
}

/**
 * Return -1 if the current hash causes a collision
 * Return 0 if the current index is empty
 * Returns a correct index otherwize
 */
int search_collision(Hashtable *map, unsigned long h)
{
  // Get index from hash of key
  int i = (int)(h % (unsigned long)(map->size));

  // Compare stored hash key to curernt hash at index i
  if (*((map->key) + i) == h)
  {
    return i;
  }
  else if (*((int *)(map->val) + i) == 0)
  {
    return 0;
  }
  else
  {
    printf("Collision detected for hash %lu\n", h);
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

  // Use linear probing to iterate until i does not create a collision
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

int search_hashtable(Hashtable *map, void *key)
{
  // Calculate hash of key
  unsigned long h = hash(key);

  int i;
  while ((i = search_collision(map, h)) == -1)
  {
    h++;
  }

  if (i == 0)
  {
    printf("Key \"%s\" was not found.\n", (char *)key);
    return -1;
  }
  else
  {
    return *((int *)(map->val) + i);
  }
}

void print_hashtable(Hashtable *map)
{
  for (int i = 0; i < map->size; i++)
  {
    if (*((int *)(map->val) + i) != 0)
    {
      printf("index: %4d  ||  key: %20lu  || str_key: %16s  ||  value: %4d\n", i, *((map->key) + i), *((char **)(map->str_key) + (2 * i)), *((int *)(map->val) + i));
    }
  }
}