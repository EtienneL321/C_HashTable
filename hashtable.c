#include <stdlib.h>
#include <stdio.h>

#include "hashtable.h"

#define DEFAULT_SIZE 16
#define RESIZE_PERCENTAGE 70

/**
 * Initialize hashtable
 */
Hashtable *initialize_hashtable()
{
  Hashtable *map = malloc(sizeof(Hashtable));
  printf("\nAddress of map value is %18p\n", &(map->val));
  printf("Address of map key is %20p\n", &(map->key));
  printf("Address of map string key is %13p\n", &(map->str_key));
  printf("Address of map size is %19p\n", &(map->size));
  printf("Address of map count is %18p\n\n", &(map->count));

  map->val = (int *)calloc(DEFAULT_SIZE, sizeof(int));
  // Using calloc here instead of malloc breaks a lot of stuff and I should figure out why
  map->key = (unsigned long *)calloc(DEFAULT_SIZE, sizeof(unsigned long));
  map->str_key = (char **)malloc(DEFAULT_SIZE * sizeof(char *));

  printf("Address of first map value is %18p\n", map->val);
  printf("Address of first map key is %20p\n", map->key);
  printf("Address of first map string key is %13p\n\n", map->str_key);

  printf("Pointer-to-pointer address is: %p\n", map->str_key);
  printf("Pointer-to-pointer second address is: %p\n", (map->str_key + 1));
  printf("Pointer-to-pointer second address is: %p\n", ((map->str_key) + 1));

  // We need to initialize the pointers to string to NULL
  for (int i = 0; i < DEFAULT_SIZE; i++)
  {
    *((map->str_key) + i) = NULL;
  }

  map->size = DEFAULT_SIZE;
  map->count = 0;

  if (map->val == NULL || map->key == NULL || map->str_key == NULL)
  {
    printf("Failed to initialize hashtable\n");
  }

  return map;
}

/**
 * Free up allocated memory from hashtable
 */
void free_hashtable(Hashtable **map)
{
  printf("Freeing memory!\n");
  free((*map)->val);
  (*map)->val = NULL;

  free((*map)->key);
  (*map)->key = NULL;

  free((*map)->str_key);
  (*map)->str_key = NULL;

  if ((*map)->val != NULL || (*map)->key != NULL || (*map)->str_key != NULL)
  {
    printf("Failed to free hashtable memory\n");
  }

  free((*map));
  (*map) = NULL;

  if ((*map) != NULL)
  {
    printf("Failed to free hashtable\n");
  }
}

/**
 * djb2 hash function
 */
unsigned long hash(char *str)
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
  int i = (int)(h % (map->size));

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
    printf("Collision detected for hash %lu. Returning -1\n", h);
    return -1;
  }
}

/**
 * Helper function for hashtable resize
 */
Hashtable *initialize_hashtable_for_resize(int size)
{
  Hashtable *map = malloc(sizeof(Hashtable));

  map->val = (int *)calloc(size, sizeof(int));
  map->key = (unsigned long *)calloc(size, sizeof(unsigned long));
  map->str_key = (char **)malloc(size * sizeof(char *));

  // We need to initialize the pointers to string to NULL
  for (int i = 0; i < size; i++)
  {
    *((map->str_key) + i) = NULL;
  }

  map->size = size;
  map->count = 0;

  if (map->val == NULL || map->key == NULL || map->str_key == NULL)
  {
    printf("Failed to initialize hashtable\n");
  }

  return map;
}

/**
 * Helper function for hashtable resize
 */
void add_to_hashtable_for_resize(Hashtable *map, char *key, int val)
{
  // Calculate hash of key
  unsigned long h = hash(key);
  // Use linear probing to iterate until i does not create a collision

  int i = 0;
  while ((i = collision(map, h)) == -1)
  {
    h++;
  }

  // Copy previous value
  *((map->val) + i) = val;

  // Store key
  *((map->key) + i) = h;

  // Store string key
  *((map->str_key) + i) = key;
}

/**
 * Double size of hashtable
 */
void resize_hashtable(Hashtable **map)
{
  Hashtable *new_map = initialize_hashtable_for_resize((*map)->size * 2);

  for (int i = 0; i < (*map)->size; i++)
  {
    if ((*(((*map)->val) + i) != 0) && (*(((*map)->val) + i) != -1))
    {
      add_to_hashtable_for_resize(new_map, *(((*map)->str_key) + i), *(((*map)->val) + i));
    }
  }

  // Free old memory
  free_hashtable(map);

  (*map) = new_map;
}

void add_to_hashtable(Hashtable **map, char *key)
{
  // Calculate hash of key
  unsigned long h = hash(key);
  // Use linear probing to iterate until i does not create a collision

  int i = 0;
  while ((i = collision((*map), h)) == -1)
  {
    h++;
  }

  // Increment by 1
  *(((*map)->val) + i) += 1;

  // Store key
  *(((*map)->key) + i) = h;

  // Store string key
  *(((*map)->str_key) + i) = key;

  // Check for 33% capicity. If over, double the size of the hashtable
  if ((((*map)->count * 100) / (*map)->size) > RESIZE_PERCENTAGE)
  {
    resize_hashtable(map);
    printf("Size is now %d.\n", (*map)->size);
  }
}

int search_hashtable(Hashtable *map, char *key)
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
    printf("Key \"%s\" was not found.\n", key);
    return -1;
  }
  else
  {
    return *((map->val) + i);
  }
}

void remove_from_hashtable(Hashtable *map, char *key)
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
    printf("Key \"%s\" was not found. Not removal needed.\n", key);
  }
  else
  {
    *((int *)(map->val) + i) = -1;
    *((map->key) + i) = 0;
    *((map->str_key) + i) = NULL;

    map->count -= 1;
  }
}

void print_hashtable(Hashtable *map)
{
  for (int i = 0; i < map->size; i++)
  {
    // if ((*((int *)(map->val) + i) != 0) && (*((int *)(map->val) + i) != -1))
    // {
    printf("index: %4d  ||  key: %20lu  || str_key: %16s  ||  value: %4d\n", i, *((map->key) + i), *((map->str_key) + i), *((map->val) + i));
    // }
  }
}