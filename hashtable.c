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

/**
 * Double size of hashtable
 */
void resize_hashtable(Hashtable *map)
{
  Hashtable new_map;
  initialize_hashtable(&new_map);

  new_map.size = map->size * 2;

  new_map.val = (int *)calloc(new_map.size * sizeof(int), 0);
  new_map.key = malloc(new_map.size * sizeof(unsigned long));
  new_map.str_key = (char **)malloc(new_map.size * sizeof(char *));

  for (int i = 0; i < map->size; i++)
  {
    if ((*((int *)(map->val) + i) != 0) && (*((int *)(map->val) + i) != -1))
    {
      unsigned long h = *((map->key) + i);
      int j;
      while ((j = collision(&new_map, h)) == -1)
      {
        h++;
      }

      // Copy over values
      *((int *)(new_map.val) + j) = *((int *)(map->val) + i);

      // Copy over hash keys
      *((new_map.key) + j) = *((unsigned long *)(map->key) + i);

      // Copy over string keys
      *((char **)(new_map.str_key) + (2 * j)) = *((char **)(map->str_key) + (2 * i));
    }
  }

  // Free old memory
  free_hashtable(map);

  *map = new_map;
}

Hashtable *initialize_hashtable()
{
  Hashtable *map = malloc(sizeof(Hashtable));

  map->val = (int *)calloc(DEFAULT_SIZE * sizeof(int), 0);
  // Using calloc here instead of malloc breaks a lot of stuff and I should figure
  // out why
  map->key = malloc(DEFAULT_SIZE * sizeof(unsigned long));
  map->str_key = (char **)malloc(DEFAULT_SIZE * sizeof(char *));
  map->size = DEFAULT_SIZE;
  map->count = 0;

  if (map->val == NULL || map->key == NULL)
  {
    printf("Failed to initialize hashtable\n");
  }

  return map;
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

  // Increment by 1
  *((int *)(map->val) + i) += 1;

  // Store key
  *((map->key) + i) = h;

  // Store string key
  // We times i by 2 because the size of a pointer is 8 bytes
  *((char **)(map->str_key) + (2 * i)) = (char *)key;

  // Check for 33% capicity. If over, double the size of the hashtable
  if (((map->count * 100) / map->size) > 33)
  {
    resize_hashtable(map);
    printf("Size is now %d.\n", map->size);
  }
  printf("Count is now %d.\n", map->count);
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

void remove_from_hashtable(Hashtable *map, void *key)
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
    printf("Key \"%s\" was not found. Not removal needed.\n", (char *)key);
  }
  else
  {
    *((int *)(map->val) + i) = -1;
    *((map->key) + i) = 0;
    *((char **)(map->str_key) + (2 * i)) = NULL;

    map->count -= 1;
  }
}

void print_hashtable(Hashtable *map)
{
  for (int i = 0; i < map->size; i++)
  {
    // if ((*((int *)(map->val) + i) != 0) && (*((int *)(map->val) + i) != -1))
    // {
    printf("index: %4d  ||  key: %20lu  || str_key: %16s  ||  value: %4d\n", i, *((map->key) + i), *((char **)(map->str_key) + (2 * i)), *((int *)(map->val) + i));
    // }
  }
}