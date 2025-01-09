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

  add_to_hashtable(map, "sport");
  // add_to_hashtable(map, "Sport");
  // add_to_hashtable(map, "sport");
  // add_to_hashtable(map, "train");
  // add_to_hashtable(map, "Hello World!");
  // add_to_hashtable(map, "Hello World!");
  // add_to_hashtable(map, "Hello World!");
  // add_to_hashtable(map, "Hello World!");
  // add_to_hashtable(map, "Hello World!");
  // add_to_hashtable(map, "Hello World");
  // add_to_hashtable(map, "Apple");

  print_hashtable(map);

  // char *key = "Hello World!";
  // int n = search_hashtable(map, key);
  // if (n != -1)
  // {
  //   printf("Key \"%s\" has a value of %d\n", key, n);
  // }

  /**
   * An intersting bug occurs here where just inputing the string "Hello World" as the
   * input causes a "No key found error" even if the key "Hello World" can be found.
   * This is probably caused by a key of type char * being different than the default type
   * given to the c string "Hello World".
   */
  // int c = search_hashtable(map, (char *)"Hello world");

  // key = "sport";
  // remove_from_hashtable(map, key);

  // add_to_hashtable(map, "tree");
  // add_to_hashtable(map, "Francais");
  // add_to_hashtable(map, "Fourmi");
  // add_to_hashtable(map, "Joe Dassin");
  // add_to_hashtable(map, "Duran Duran");
  // add_to_hashtable(map, "Queen");
  // add_to_hashtable(map, "View to a Kill");
  // add_to_hashtable(map, "Rio");
  // add_to_hashtable(map, "Hungry");

  // print_hashtable(map);

  free_hashtable(map);
  printf("\n");
  return 0;
}