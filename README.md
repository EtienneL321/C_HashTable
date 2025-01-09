# C_HashTable

Implementation of a HashTable in C

# build c executable

`gcc -std=c99 -g -o build/main ./main.c ./hashtable.c`

# To-Do

I think I need to fix where I initialize the hashtable. Rn this is being done on the stack with the actual arrays initialized on the heap. I should be allocating memory for the whole hashtable on the heap with nothing on the stack.

- This can be achieved by having the function return a hashtable address that will be given to a hashtable pointer

With the constructor finished, I also need to create a destructor that will free all allocated memory

- I can also tackle allocating memory to the str_key at this stage or forget it for the time being since it does not add to the logic of the hashtable

Next I need to switch from creating a new hashtable when resizing to just creating a new array for the key, value, and str_key.

- To be more specific, if I have a constructor and destructor that workd exactly as expected, I need to figure out if using the const/destruct is better or using newly allocated arrays is better

Once the allocation is done better and all on the heap, I can debug some more

I will need to add a TON of error handling once the hashtable works as expected. That way using it in the wrong way does not crash or break an application.

Rather than use GDB to debug, I will switch over to LLDB since it seems to be more compatible with Apple's suite of technologies.

- As of Dec 31st, the allocation of memory for a hashtable is done all on the stack and is freed using the free_hashtable method. I am attempting to create a deep copy of the string key copy I am holding but am having buffer overflow issues I am having trouble understanding which is why I need to learn how to use lldb to look into memory what is being written where and why.
