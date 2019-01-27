#MazeSolver
Finds a solution to a maze from an input file and prints the solution.

A maze is simulated from an input text file. 
The first 2 numbers of the input text file specify the dimensions of the maze (rows and columns). The file is then parsed to create a maze of the specfied dimensions.
The program will then attempt to find an exit which is marked with a '$'. An underscore ( _ ) marks a path which is accessible and an asterisk ( * ) acts as a wall. 
Accessible paths are marked with a '>' and if the program needs to backtrack to the last viable track, that path is marked with an '@'.
The program keeps two dynamically allocated arrays. A maze and a solution maze.
If a path is not extendable from its position it will be marked with a 'X' on maze for future reference.
If a solution is found a maze will be printed with a series of '>' marking the way to the exit. Along with any '@' to show where backtracking had occured.
