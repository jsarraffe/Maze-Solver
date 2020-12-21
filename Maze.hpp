//
// Created by Ali A. Kooshesh on 2020-01-19.
//

#ifndef GENERALBACKBONEPROGRAMS_DICTIONARY_HPP
#define GENERALBACKBONEPROGRAMS_DICTIONARY_HPP

#include<iostream>
#include<fstream>
#include<vector>
#include<tuple>
#include<stack>

class Maze {
public:
    Maze(std::string inputFileName);
    void pathBetweenCells();
    ~Maze();
    void printSolved();
    void printMaze();
private:
    std::stack<std::tuple<int, int>> pathStack;
    bool isSolved;
    std::vector<std::vector<char> > MazeMatrix;
    std::vector<std::vector<char> > solvedMatrix;
    std::vector<std::vector<bool> > used;
    std::tuple<int, int> startCell;
    std::tuple<int, int> endCell;
    void printMatrix(std::vector<std::vector<char>> Matrix);
    void startCellEndCells();
    std::tuple<int, int> adjacentCells (int row, int column);
    std::ifstream MazeStream;  // use it to open the input file.

};
#endif //GENERALBACKBONEPROGRAMS_DICTIONARY_HPP
