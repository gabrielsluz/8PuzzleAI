#ifndef PUZZLE_H
#define PUZZLE_H

#define N 9
#define COLUMNS 3


#include <list>

class Puzzle{
  private:
    int _board[N];
    int _blank;
    int _lastsBlank;

  public:
    Puzzle(int* vec, int lastBlank);
    Puzzle();
    void newPuzzle(int* vec, int lastBlank);
    bool isFinalState();
    void getNextStates(std::list<Puzzle> * nextPuzzles);

};

#endif
