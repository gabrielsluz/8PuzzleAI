#include "puzzle.hpp"
#include <iostream>


void Puzzle::childPuzzleCreator(int* vec, int lastBlank, std::list<int> path){ //Creates child puzzle
  for(int i = 0; i < N; i++){
    _board[i] = vec[i];

    if(vec[i] == 0)
      _blank = i;
  }
  _lastBlank = lastBlank;

  _path = path;
  _path.push_front(_blank);
}

Puzzle::Puzzle(int* vec, int lastBlank){
  for(int i = 0; i < N; i++){
    _board[i] = vec[i];

    if(vec[i] == 0)
      _blank = i;
  }
  _lastBlank = lastBlank;
  _path.push_front(_blank);
}

Puzzle::Puzzle(){
  for(int i = 0; i < N; i++){
    _board[i] = 0;
  }
  _lastBlank = 0;
  _blank = 0;
}

bool Puzzle::isFinalState(){
  for(int i = 0; i < N-1; i++){
    if(_board[i] != i+1)
      return false;
  }

  return true;
}


Puzzle Puzzle::getNextStateAux(int nextBlank){
  Puzzle nextPuzzle;
  int nextVec[N];

  for(int i = 0; i < N; i++){
    nextVec[i] = _board[i];
  }

  nextVec[_blank] = nextVec[nextBlank];
  nextVec[nextBlank] = 0;

  nextPuzzle.childPuzzleCreator(nextVec,_blank,_path);

  //std::cout << nextPuzzle.pathCost() << std::endl;

  return nextPuzzle;
}


void Puzzle::getNextStates(std::list<Puzzle>* nextPuzzles){
  int nextBlank=0;

  if(_blank > COLUMNS-1 && _blank - COLUMNS != _lastBlank){ //Not first row
    nextBlank = _blank - COLUMNS;

    nextPuzzles->push_back(getNextStateAux(nextBlank));
  }

  if(_blank < N-COLUMNS && _blank + COLUMNS != _lastBlank){ //Not last row
    nextBlank = _blank + COLUMNS;

    nextPuzzles->push_back(getNextStateAux(nextBlank));
  }

  if(_blank % COLUMNS != 0  && _blank - 1 != _lastBlank){ //Not first column
    nextBlank = _blank - 1;

    nextPuzzles->push_back(getNextStateAux(nextBlank));
  }

  if(_blank % COLUMNS != COLUMNS-1  && _blank + 1 != _lastBlank){ //Not last column
    nextBlank = _blank + 1;

    nextPuzzles->push_back(getNextStateAux(nextBlank));
  }
}

int Puzzle::pathCost(){
  return _path.size()-1;
}

void Puzzle::printPath(){
  std::list<int>::iterator it;

  for(it = _path.begin(); it != _path.end(); it++){
    std::cout << *it << std::endl;
  }
}


bool Puzzle::compareBoard(Puzzle cmp){
  int *board = cmp.returnBoard();
  for(int i=0; i < N; i++){
    if(board[i] != _board[i])
      return false;
  }
  return true;
}

int* Puzzle::returnBoard(){
  return _board;
}
