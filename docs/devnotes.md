##2012-09-18
This is the first entry for this file. See below for a from-memory account of work done up to this point.  

Today's goal is to load geometry to the GPU and have it rendered on the screen. I have refactored my vertex struct to more closely follow the examples given in the lecture slides. Specifically, where I previously segregated point coordinates and normal values into separate structs, I have used only a single struct vert with member arrays for the point and normal values.  

One challenge in reaching this goal is obtaining the size of the data to be loaded.

##before 2012-09-18
__File IO__ in C looks alot like it does in PHP, so I was able to accomplish the simple task of opening a file fairly easily through reading the recommended documentation in the Wikibooks site. _fscanf_ was completely new, and it took some trial and error before understanding that newlines count when scanning; this is intuitive, but it wasn't obvious at first.  

[A Little C Primer/C File-IO Through Library Functions - Wikibooks, Open Books for an Open World](http://en.wikibooks.org/wiki/A_Little_C_Primer/C_File-IO_Through_Library_Functions)  
[C Printf and Scanf Reference](http://wpollock.com/CPlus/PrintfRef.htm)  
[C Programming Notes](http://www.eskimo.com/~scs/cclass/notes/top.html)  
[C Programming/Pointers and Arrays - Wikibooks, Open Books for an Open World](https://en.wikibooks.org/wiki/C_Programming/Pointers_and_arrays)  
[C Structure](http://cprogramminglanguage.net/c-structure.aspx)  
[Fscanf](http://pubs.opengroup.org/onlinepubs/7908799/xsh/fscanf.html)  
[Strings as Arrays, as Pointers, and String.h](http://www.cs.bu.edu/teaching/c/string/intro/)  
