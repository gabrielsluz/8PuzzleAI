#ifndef PUZZLE_H
#define PUZZLE_H

#define N 9
#define COLUMNS 3


#include <list>
#include <string>
#include <vector>

class Puzzle{
  private:
    int _board[N];
    int _blank;
    int _lastBlank;
    int _pathCost;



    Puzzle* getNextStateAux(int nextBlank);

  public:
    Puzzle *_father;
    std::vector<Puzzle*> _nextPuzzles;

    Puzzle(int* vec, int lastBlank);
    Puzzle();
    void childPuzzleCreator(int* vec, int lastBlank, int lastPathCost, Puzzle *oldPuzzle);
    bool isFinalState();
    std::vector<Puzzle*> * getNextStates();
    int pathCost();
    void printPath();
    void printBoard();
    bool compareBoard(Puzzle *cmp);
    int* returnBoard();
    int greedyH();
    int astarH();
    int piecesInPlace();
    int getRow(int i);
    int getColumn(int i);
    int absoluteValue(int a);
    int toNum();
    void purgeLeaks();
    void purgeSubTree();


};

#endif
