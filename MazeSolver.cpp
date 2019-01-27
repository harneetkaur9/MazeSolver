// Maze Solver.cpp
//
// Harneet Kaur
// CSCI 23500 - Professor Ligorio - PROJECT 4 - Nov 1
//
// This file will implement member functions of the class MazeSolver.
// The program will read an input file, from which it will create a 2D array.
// Based on the characters in the input file, a maze will be stimulated consisting of hallways and walls.
// If a dead end is reached, the program will backtrack to the a last postion till it can take a different route.
// The program has served its purpose once it has discovered a possible route out, or comes to the conclusion there is no way out.

#include "MazeSolver.h"

using std::cout;
using std::endl;

//Constructor to intialize Maze
//param: An input file containing the dimensions of the maze_
//Opens, checks, and closes input file.
MazeSolver::MazeSolver(std::string input_file){
    std::ifstream in_stream(input_file); 
    if(in_stream.fail()){
        cout << "Cannot read from " << input_file << endl;
    }
    else {
        in_stream >> maze_rows_ >> maze_columns_; //get number of maze rows and maze columns
        initializeMaze(maze_rows_, maze_columns_);
        fillMaze(in_stream);
        initializeSolution();
    }
    in_stream.close();
}

//Helper function called by the constructor.
//Creates a 2D array based on the input taken from input file.
void MazeSolver::initializeMaze(int rows, int columns){
    maze_ = new char *[rows]; //memory allocated for the amount of rows specified from the input file.
    for(int i = 0; i < rows; i++){
        maze_[i] = new char [columns]; //memory allocated for the amount of columns specified from input.
    }
}

//Helper function called by constructor.
//Will fill the 'maze' (2D array) with characters from the input file
void MazeSolver::fillMaze(std::ifstream& input_stream){
    for (int i = 0; i < maze_rows_; i++){
        for(int j = 0; j < maze_columns_; j++){
            input_stream >> maze_[i][j]; //inputs corresponding element from input file to the matrix.
        }
    }
}

//Helper function called by constructor.
//Intializes the solution matrix. Character from the maze_ are copied to soultion_.
//Marks the current position as visited using a '>' character.
void MazeSolver::initializeSolution(){
    solution_ = new char *[maze_rows_];
    for(int i = 0; i < maze_rows_; i++){
        solution_[i] = new char [maze_columns_];
    }
    copyMazetoSolution();
    solution_[0][0] = '>'; //places a '>' at the starting position.
}

//Helper function called by intializeSolution()
//solution_ gets a copy of the maze_ matrix.
//Pre: maze_ has been itialized properly.
//Post: solution_ gets the correct number of rows and columns.
void MazeSolver::copyMazetoSolution(){
    for(int i = 0; i < maze_rows_; i++){
        for(int j = 0; j < maze_columns_; j++){
            solution_[i][j] = maze_[i][j];
        }
    }
}

//Destructor
//Deletes and frees up dynamically allocated memory alloted maze_ and solution_
MazeSolver::~MazeSolver(){
    for(int i = maze_rows_-1; i >= 0; i--){
        delete[] maze_[i];
    }
    delete[] maze_;
    
    for(int i = maze_rows_-1; i >= 0; i--){
        delete[] solution_[i];
    }
    delete[] solution_;
}

//Checks if maze_ has been initialized.
//Return: True if maze_ in intialized, false if it was not intialized.
bool MazeSolver::mazeIsReady(){
    for(int i = 0; i < maze_rows_; i++){
        for(int j = 0; j < maze_columns_; j++){
            if(maze_[i][j] != '_' && maze_[i][j] != '*' && maze_[i][j] != '$') {
                cout << maze_[i][j] << i << j << endl;
                maze_ready = false;
                return maze_ready;
            }
        }
    }
    maze_ready = true;
    return true;
}

//Checks if a solution was found from the maze.
//Prints '>' on every space alomg the path to the exit.
bool MazeSolver::solveMaze(){
    Position pos;
    pos.row = 0;
    pos.column = 0;
    backtrack_stack_.push(pos);
    
    Position current_pos = pos;
    
    while(!backtrack_stack_.empty()){
        if(maze_[current_pos.row][current_pos.column] == '$'){
            cout << "Found the exit!!!" << endl;
            return true;
        }
        else if (extendPath(current_pos)) {
            solution_[current_pos.row][current_pos.column] = '>';
            current_pos = backtrack_stack_.top();
        }
        else {
            maze_[current_pos.row][current_pos.column] = 'X';
            solution_[current_pos.row][current_pos.column] = '@';
            backtrack_stack_.pop();
            if(!backtrack_stack_.empty()){
                current_pos = backtrack_stack_.top();
            }
            else{
                cout << "This maze has no solution." << endl;
                return false;
            }
        }
    }
    return false;
}

//Helper function called by solveMaze()
//Pushes all positions reachable from the current position on to backtrack stack.
//Return: True if path was extended, false otherwise.
bool MazeSolver::extendPath(Position current_position){
    if(isExtensible(current_position, SOUTH)){
        backtrack_stack_.push(getNewPosition(current_position, SOUTH));
        return true;
    }
    if(isExtensible(current_position, EAST)){
        backtrack_stack_.push(getNewPosition(current_position, EAST));
        return true;
    }
    return false;
}

//pre: old_position is a Position initialized with row and column to valid positions in maze_ and it is extensible in direction dir
//return: a new Position on the maze moving in direction dir from old_position
//called by extendPath()
Position MazeSolver::getNewPosition(Position old_position, direction dir){
    Position new_position;
    if(dir == SOUTH){
        new_position.row = old_position.row;
        new_position.column = old_position.column+1;
    }
    else if (dir == EAST){
        new_position.row = old_position.row+1;
        new_position.column = old_position.column;
    }
    return new_position;
}

//Helper function called by extendPath()
//Checks if the path can be extended in maze_ from position current_position in direction dir
//Return: true if path can be extended given current_position and dir, false otherwise
bool MazeSolver::isExtensible(Position current_position, direction dir){
    if(dir == EAST && current_position.row+1 < maze_rows_ && maze_[current_position.row+1][current_position.column] != 'X') {
        return maze_[current_position.row+1][current_position.column] != '*';
    }
    else if (dir == SOUTH && current_position.column+1 < maze_columns_ && maze_[current_position.row][current_position.column+1] != 'X') {
        return maze_[current_position.row][current_position.column+1] != '*';
    }
    else
        return false;
}

//Prints solution
//post: prints the solution to the standard output stream
//      with single space character between each maze character
//      and each maze row on a new line
void MazeSolver::printSolution(){
    cout << "The solution to this maze is: " << endl;
    for (int i = 0; i < maze_rows_; i++){
        for(int j = 0; j < maze_columns_; j++){
            cout << solution_[i][j] << " ";
        }
        cout << endl;
    }
}
