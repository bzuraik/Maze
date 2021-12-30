# Auto-generating a maze

maze.c:
A progrma that creates a path through a two dimensional array. Program could run in a serial mode or in in parallel with four processors with OpenMP.

---------------------------------------
How to compile?
$ make


*after compiling, it will produce two exectuable programs:
- maze, which implements the serial maze generation.
- mazep, which implements the parallelized maze generation. 
---------------------------------------
How to run?

    serial version
    $ ./maze <-s> <-n grid size>

    Parrallel version
    $ ./mazep <-s> <-n grid size>
    
    The -s argument is used to seed the random number generator for determining the order in
    which the neighbours are visited. If no -s argument is used, it will seed the random number
    generator with 0.
    
    The program accept -n to indicate the size of the array.
    
    ex. 
      $ maze -n 21
    would create an array that is 21 by 21 elements. If no -n argument is used then make the array
    11 by 11.
