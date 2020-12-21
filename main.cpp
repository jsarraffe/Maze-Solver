//
// Created by Jacques Sarraffe on 2020-09-3.
//

#include<iostream>

#include"Maze.hpp"

int main(int argc, char *argv[]) { // the main function.
    if( argc != 2) {
        std::cout << "usage: " << argv[0] << " inputFileNameThatContainsDictionary inputFileNameThatContainsPairsOfWords\n";
        exit(1);
    }
    std::ifstream MazeStream;
    MazeStream.open(argv[1]);
    if( !MazeStream.is_open()) {
        std::cout << "Unable to open input file ->" << argv[1] << "<-\n";
        exit(2);
    }
    MazeStream.close();

    Maze *thePuzzle = new Maze("sampleInputForMaze.txt");
    //thePuzzle->printMaze();
    //std::cout<<std::endl;
    thePuzzle->pathBetweenCells();
    delete thePuzzle;
}
