# Programming Style

When making header one should use the #define guard
incase you are unaware the header guard looks something like this

#ifndef FOO_H
#define FOO_H

...

#endif 

When making header files one should only have the definition of a function within
it if it is succint. Meaning that one should only write definitions in header 
files if they are small. Otherwise the function should be in its own source file. 

When allocating memory immediately set where you are gonna deallocate it. 
Additionally do not deallocate or change inputted pointers within a function 
unless that is its main purpose. For example a free function for a 2D array is 
fine, however a functions who's purpose is something else should not change 
the input pointer.
