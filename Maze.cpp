//
// Created by Jacques T. Sarraffe on 2020-09-3.
//

#include <iostream>
#include <fstream>
#include "Maze.hpp"
Maze::Maze(std::string inputFileName) {
    //constructs the maze, and the solved mazed.
    MazeStream.open(inputFileName);
    if (!MazeStream.is_open())  {
        std::cout<< "Could not open file" << std::endl;
        return;
    }
    std::string tempRow;
    while (getline(MazeStream, tempRow)){
        std::vector<char> Row;
        std::vector<bool> usedRow;
        for(int i = 0; i<tempRow.size(); i++)
        {
            usedRow.push_back(false);
            Row.push_back(tempRow.at(i));
        }
        MazeMatrix.push_back(Row);
        //the solution
        solvedMatrix.push_back(Row);
        used.push_back(usedRow);
    }
    isSolved = false;
    MazeStream.close();
}
Maze::~Maze() {
    // close the input stream if it was successfully opened.
    if(MazeStream.is_open())
        MazeStream.close();
}
void Maze::printMatrix(std::vector<std::vector<char>> Matrix) {
    //prints the maze

    for(int i = 0; i < Matrix.size(); i++){
        for(int j = 0; j < Matrix.at(i).size(); j++){
            std::cout<< Matrix.at(i).at(j)<<" ";
        }
        std::cout<< std::endl;
    }

}
void Maze::pathBetweenCells() {
    //generates a path between the cells, and shows the path with spaces in the solvedMatrix.
    startCellEndCells();
    int row = std::get<0>(startCell);
    int column = std::get<1>(startCell);
    used.at(row).at(column) = true;
    //MARK START AS SOLVED
    solvedMatrix.at(row).at(column) = ' ';
    pathStack.push(startCell);
    while(!pathStack.empty()){
        auto successorIndex = adjacentCells(std::get<0>(pathStack.top()),std::get<1>(pathStack.top()));
        row = std::get<0>(successorIndex);
        column =std::get<1>(successorIndex);

        int topOfStackRow = std::get<0>(pathStack.top());
        int topOfStackColumn = std::get<1>(pathStack.top());

        if(std::get<0>(successorIndex) == -1){
            //UNMARK CURRENT CELL, as unsolved.
            //BACK TRACK
            solvedMatrix.at(topOfStackRow).at(topOfStackColumn) = '0';
            pathStack.pop();
        }
        else{
            pathStack.push(successorIndex);
            solvedMatrix.at(row).at(column) = ' ';
            used.at(row).at(column) = true;
        }
        if(pathStack.empty()){
            std::cout<<"Error: their is no path"
            <<std::endl;
            break;
        }
        if(pathStack.top() == endCell){
            isSolved = true;
            printSolved();
            break;
        }
    }
}
std::tuple<int, int> Maze::adjacentCells (int row, int column){
    //if theirs a successor return it's index, otherwise return somthing invalid.

    std::tuple<int, int> NoSuccessor = std::make_tuple(-1,-1);
    if(row+1<MazeMatrix.size() && MazeMatrix.at(row+1).at(column) == '0'&& !used.at(row+1).at(column)) {
        return std::make_tuple(row+1, column);
        //checking vertical down
    }
    else if(row >= 1 && MazeMatrix.at(row-1).at(column) == '0' && !used.at(row-1).at(column)){
        return std::make_tuple(row-1, column);
        //checking vertical up
    }
    //
    else if(column >= 1 && MazeMatrix.at(row).at(column -1) == '0' && !used.at(row).at(column-1)){
        return std::make_tuple(row,column -1);
        //checking left
    }
    else if(column+1 < MazeMatrix.at(row).size() && MazeMatrix.at(row).at(column + 1) == '0' && !used.at(row).at(column + 1)){
        return std::make_tuple(row,column + 1);
        //checking right.
    }
    else{
        return NoSuccessor;
    }
}
void Maze::startCellEndCells() {
//looks for the start cell and the end cell.
//scans the edges, and picks the first one it comes accoss as the start cell. The next one
// would be the ending cell.


    bool startFound = false;
    for(int i = 0; i < MazeMatrix.size(); i++)
    {
        if(MazeMatrix.at(i).at(0) == '0'){
            if(!startFound){
                startCell = std::make_tuple (i,0);
                startFound = true;
            }
            else{
                endCell = std::make_tuple(i,0);
            }
        }
        if(MazeMatrix.at(i).at(MazeMatrix.at(i).size()-1) == '0'){
            if(!startFound){
                startCell = std::make_tuple (i,MazeMatrix.at(i).size()-1);
                startFound = true;
            }
            else{
                endCell = std::make_tuple(i,MazeMatrix.at(i).size()-1);
            }
        }
    }
    //checking top and bottom
    for(int i = 0; i < MazeMatrix.at(0).size(); i++){
        if(MazeMatrix.at(0).at(i) == '0'){
            if(!startFound){
                startCell = std::make_tuple (0, i);
                startFound = true;
            }
            else{
                endCell = std::make_tuple(0, i);
            }
        }
        if(MazeMatrix.at(MazeMatrix.size() -1).at(i) == '0'){
            if(!startFound){
                startCell = std::make_tuple(MazeMatrix.size()-1, i);
                startFound = true;
            }
            else {
                endCell = std::make_tuple(MazeMatrix.size() - 1, i);
            }

        }

    }
 }
void Maze::printSolved() {
    //prints the maze that is solved.
    if(isSolved){
        printMatrix(solvedMatrix);
    }
    else{
        std::cout <<"Not Solved"<<std::endl;
    }
}
void Maze::printMaze(){
    printMatrix(MazeMatrix);
}




