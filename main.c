#include <stdio.h>

#include "hashtable.h"

int main()
{
  /**
   * Old way of initializaing a hashtable
   *
   * Hashtable map;
   * initialize_hashtable(&map);
   *
   * New way of initializing a hashtable
   *
   * Hashtable *map = initialize_hashtable();
   */
  Hashtable *map = initialize_hashtable();

  add_to_hashtable(&map, "sport");
  add_to_hashtable(&map, "Sport");
  add_to_hashtable(&map, "sport");
  add_to_hashtable(&map, "train");
  add_to_hashtable(&map, "Hello World!");
  add_to_hashtable(&map, "Hello World!");
  add_to_hashtable(&map, "Hello World!");
  add_to_hashtable(&map, "Hello World!");
  add_to_hashtable(&map, "Hello World!");
  add_to_hashtable(&map, "Hello World");
  add_to_hashtable(&map, "Apple");

  char *key = "Hello World!";
  int n = search_hashtable(map, key);
  if (n != -1)
  {
    printf("Key \"%s\" has a value of %d\n", key, n);
  }

  char *key1 = "Hello Worl";
  int n1 = search_hashtable(map, key1);
  if (n1 != -1)
  {
    printf("Key \"%s\" has a value of %d\n", key1, n1);
  }

  int c = search_hashtable(map, "Sport");
  if (c != -1)
  {
    printf("Key \"%s\" has a value of %d\n", "Sport", c);
  }

  key = "sport";
  remove_from_hashtable(map, key);
  print_hashtable(map);

  add_to_hashtable(&map, "tree");
  add_to_hashtable(&map, "Francais");
  add_to_hashtable(&map, "Fourmi");
  add_to_hashtable(&map, "Joe Dassin");
  add_to_hashtable(&map, "Duran Duran");
  add_to_hashtable(&map, "Queen");
  add_to_hashtable(&map, "View to a Kill");
  add_to_hashtable(&map, "Rio");
  add_to_hashtable(&map, "Hungry");

  print_hashtable(map);

  free_hashtable(&map);
  printf("\n");
  return 0;
}