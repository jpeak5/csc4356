##2012-09-27
Nothing like the pressure of the last minute to squeeze the bugs out...  

1. using the -Wall flag on the compiler was a huge boon to my debugging effort.
2. with the compile warnings eliminated, and a clean refactoring done, reviewing the lecture slides revealed this gem:
`glDrawElements(GL_TRIANGLES, 3* S->num_tri, GL_UNSIGNED_SHORT, 0)`
3. now I was drawing real geonmetry to the window, but everything was skewed.
    1. icosa looked like a deflated beachball & 747 looked like the banner of this site
    2. I was sure that I had messed up the offset in the glBufferData() calls, but unfortunately, I had another hour or so of frustration ahead
    3. after refactoring my `struct triangle` a bit, I took a peek back at the lecture slides for the answer: __element buffer needs to be composed of GLushorts, _NOT_ ints!!__
4. using the example set in `viewing-tumble-5.c` verbatim without issue, going further is entirely within reach...
##2012-09-26
no progress, just alot of head scratching and copying and pasting things around
##2012-09-25
consult with Prof Kooima in office hours to clear up some issues with the C language...
##2012-09-23
Using the hello teapot example combined with lecture slides example code and with GL docs.

##2012-09-22
Have been grappling with C pointers and their use in arrays. 
Also coming to understand that the Util3D modules are exactly that: 
modules to be incorporated in a given project.

##2012-09-18
This is the first entry for this file. See below for a from-memory account of work done up to this point.  

Today's goal is to load geometry to the GPU and have it rendered on the screen. I have refactored my vertex struct to more closely follow the examples given in the lecture slides. Specifically, where I previously segregated point coordinates and normal values into separate structs, I have used only a single struct vert with member arrays for the point and normal values.  

One challenge in reaching this goal is obtaining the size of the data to be loaded.
before 
##pre-2012-09-18
__File IO__ in C looks alot like it does in PHP, so I was able to accomplish the simple task of opening a file fairly easily through reading the recommended documentation in the Wikibooks site. _fscanf_ was completely new, and it took some trial and error before understanding that newlines count when scanning; this is intuitive, but it wasn't obvious at first.  

[A Little C Primer/C File-IO Through Library Functions - Wikibooks, Open Books for an Open World](http://en.wikibooks.org/wiki/A_Little_C_Primer/C_File-IO_Through_Library_Functions)  
[C Printf and Scanf Reference](http://wpollock.com/CPlus/PrintfRef.htm)  
[C Programming Notes](http://www.eskimo.com/~scs/cclass/notes/top.html)  
[C Programming/Pointers and Arrays - Wikibooks, Open Books for an Open World](https://en.wikibooks.org/wiki/C_Programming/Pointers_and_arrays)  
[C Structure](http://cprogramminglanguage.net/c-structure.aspx)  
[Fscanf](http://pubs.opengroup.org/onlinepubs/7908799/xsh/fscanf.html)  
[Strings as Arrays, as Pointers, and String.h](http://www.cs.bu.edu/teaching/c/string/intro/)  
