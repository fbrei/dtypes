# dtypes
This is a collection of commonly used data types. It is hand implemented and still far from being complete. Available so far:

## DArray

A dynamically growing array (grows in chunks). It allocates multiple fixed size C arrays of void pointers, thus allowing to store any arbitrary data type. The size of such a static array can be configured by changing the value of DARRAY_PAGE_SIZE in config.h.

## HSet

A simple Hash Set. To use it you have to define two functions, a hash and an equals function, and provide it to the init method. It dynamically rehashes itself when growing too full, based on the HSET_MAX_RATIO in config.h

## PrQueue

A priority queue. You have to provide a compare_to method that returns a signed integer, based on the outcome of the comparison.

## Graph

work in progress, not to be used yet.

----

For all API methods I chose names that I would expect. I tried to be as consistent as possible, but I cannot guarantee that I made some errors here and there. For example:

All data structures have a *module*_init method. They all can be destroyed using *module*_destroy, always taking two arguments: the data structure itself and an optional destructor for the elements, accepting NULL as an indicator to use builtin free. Setters with an index are called *module*_set, setters without index are called *module*_add. And many more ...
