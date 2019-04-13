#include "puzzle.hpp"


void Puzzle::newPuzzle(int* vec, int lastBlank){
  for(int i = 0; i < N; i++){
    _board[i] = vec[i];

    if(vec[i] == 0)
      _blank = i;
  }
  _lastsBlank = lastBlank;
}

Puzzle::Puzzle(int* vec, int lastBlank){
  newPuzzle(vec,lastBlank);
}

Puzzle::Puzzle(){
  for(int i = 0; i < N; i++){
    _board[i] = 0;
  }
  _lastsBlank = 0;
  _blank = 0;
}

bool Puzzle::isFinalState(){
  for(int i = 0; i < N-1; i++){
    if(_board[i] != i+1)
      return false;
  }

  return true;
}


void Puzzle::getNextStates(std::list<Puzzle>* nextPuzzles){
  int nextVec[N];
  int swapper=0;
  Puzzle nextPuzzle;
  int nextBlank=0;

  if(_blank > COLUMNS-1 && _blank - COLUMNS != _lastsBlank){ //Not first row
    nextBlank = _blank - COLUMNS;

    for(int i = 0; i < N; i++){
      nextVec[i] = _board[i];
    }

    nextVec[_blank] = nextVec[nextBlank];
    nextVec[nextBlank] = 0;

    nextPuzzle.newPuzzle(nextVec,nextBlank);

    nextPuzzles->push_back(nextPuzzle);
  }

  if(_blank < N-COLUMNS && _blank + COLUMNS != _lastsBlank){ //Not last row
    nextBlank = _blank + COLUMNS;

    for(int i = 0; i < N; i++){
      nextVec[i] = _board[i];
    }

    nextVec[_blank] = nextVec[nextBlank];
    nextVec[nextBlank] = 0;

    nextPuzzle.newPuzzle(nextVec,nextBlank);

    nextPuzzles->push_back(nextPuzzle);
  }

  if(_blank % COLUMNS != 0  && _blank - 1 != _lastsBlank){ //Not first column
    nextBlank = _blank - 1;

    for(int i = 0; i < N; i++){
      nextVec[i] = _board[i];
    }

    nextVec[_blank] = nextVec[nextBlank];
    nextVec[nextBlank] = 0;

    nextPuzzle.newPuzzle(nextVec,nextBlank);

    nextPuzzles->push_back(nextPuzzle);
  }

  if(_blank % COLUMNS != COLUMNS-1  && _blank + 1 != _lastsBlank){ //Not last column
    nextBlank = _blank + 1;

    for(int i = 0; i < N; i++){
      nextVec[i] = _board[i];
    }

    nextVec[_blank] = nextVec[nextBlank];
    nextVec[nextBlank] = 0;

    nextPuzzle.newPuzzle(nextVec,nextBlank);

    nextPuzzles->push_back(nextPuzzle);
  }

}
