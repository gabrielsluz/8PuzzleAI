#ifndef PUZZLE_H
#define PUZZLE_H

#define N 9
#define COLUMNS 3


#include <list>
#include <string>

class Puzzle{
  private:
    int _board[N];
    int _blank;
    int _lastBlank;
    std::list<int> _path;


    Puzzle getNextStateAux(int nextBlank);

  public:
    Puzzle(int* vec, int lastBlank);
    Puzzle();
    void childPuzzleCreator(int* vec, int lastBlank, std::list<int> path);
    bool isFinalState();
    void getNextStates(std::list<Puzzle> * nextPuzzles);
    int pathCost();
    void printPath();
    bool compareBoard(Puzzle cmp);
    int* returnBoard();
    int greedyH();
    int astarH();
    int piecesInPlace();
    int getRow(int i);
    int getColumn(int i);
    int absoluteValue(int a);
    int toNum();


};

#endif
