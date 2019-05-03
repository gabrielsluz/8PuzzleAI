#include "puzzle.hpp"
#include <cmath>
#include <vector>
#include <iostream>


Puzzle::Puzzle(int* vec, int lastBlank){
  for(int i = 0; i < N; i++){
    _board[i] = vec[i];

    if(vec[i] == 0)
      _blank = i;
  }
  _lastBlank = lastBlank;
  _pathCost = 0;
  _father = NULL;
}

Puzzle::Puzzle(){
  for(int i = 0; i < N; i++){
    _board[i] = 0;
  }
  _lastBlank = 0;
  _blank = 0;
  _pathCost = 0;
  _father = NULL;
}

bool Puzzle::isFinalState(){
  for(int i = 0; i < N-1; i++){
    if(_board[i] != i+1)
      return false;
  }

  return true;
}

void Puzzle::childPuzzleCreator(int* vec, int lastBlank, int lastPathCost, Puzzle *oldPuzzle){ //Creates child puzzle
  for(int i = 0; i < N; i++){
    _board[i] = vec[i];

    if(vec[i] == 0)
      _blank = i;
  }
  _lastBlank = lastBlank;

  _pathCost = lastPathCost + 1;
  _father = oldPuzzle;
}


Puzzle* Puzzle::getNextStateAux(int nextBlank){
  Puzzle* nextPuzzle = new Puzzle;
  int nextVec[N];

  for(int i = 0; i < N; i++){
    nextVec[i] = _board[i];
  }

  nextVec[_blank] = nextVec[nextBlank];
  nextVec[nextBlank] = 0;

  nextPuzzle->childPuzzleCreator(nextVec,_blank,_pathCost,this);

  //std::cout << nextPuzzle.pathCost() << std::endl;

  return nextPuzzle;
}


std::vector<Puzzle*> * Puzzle::getNextStates(){
  int nextBlank=0;
  _nextPuzzles.clear();

  if(_blank > COLUMNS-1 && _blank - COLUMNS != _lastBlank){ //Not first row
    nextBlank = _blank - COLUMNS;

    _nextPuzzles.push_back(getNextStateAux(nextBlank));
  }

  if(_blank < N-COLUMNS && _blank + COLUMNS != _lastBlank){ //Not last row
    nextBlank = _blank + COLUMNS;

    _nextPuzzles.push_back(getNextStateAux(nextBlank));
  }

  if(_blank % COLUMNS != 0  && _blank - 1 != _lastBlank){ //Not first column
    nextBlank = _blank - 1;

    _nextPuzzles.push_back(getNextStateAux(nextBlank));
  }

  if(_blank % COLUMNS != COLUMNS-1  && _blank + 1 != _lastBlank){ //Not last column
    nextBlank = _blank + 1;

    _nextPuzzles.push_back(getNextStateAux(nextBlank));
  }

  return &_nextPuzzles;
}

int Puzzle::pathCost(){
  return _pathCost;
}

void Puzzle::printPath(){
  Puzzle* aux;
  aux = this;
  while(aux != NULL){
    aux->printBoard();
    std::cout << std::endl;
    aux = aux->_father;
  }
}

void Puzzle::printBoard(){
  for(int i=0; i < N; i++){
    if(i%COLUMNS == 0)
      std::cout << std::endl;
    std::cout << _board[i] << " ";
  }
}


bool Puzzle::compareBoard(Puzzle *cmp){
  int *board = cmp->returnBoard();
  for(int i=0; i < N; i++){
    if(board[i] != _board[i])
      return false;
  }
  return true;
}

int* Puzzle::returnBoard(){
  return _board;
}


int Puzzle::getRow(int i){
  return i%COLUMNS;
}

int Puzzle::getColumn(int i){
  return i/COLUMNS;
}

int Puzzle::absoluteValue(int a){
  if(a < 0)
    return -a;
  return a;
}

int Puzzle::greedyH(){ //Returns the number of pieces out of place
  int sum=0;
  for(int i = 0; i < N; i++){
    if(_board[i] != i+1 && _board[i] != 0)
      sum++;
  }

  return sum;
}

int Puzzle::astarH(){ //Returns the sum of the Manhattan distances of the miss placed pieces
  int sum=0;
  for(int i = 0; i < N; i++){
    if(_board[i] != i+1 && _board[i] != 0){
      sum += absoluteValue(getRow(_board[i]-1) - getRow(i)) + absoluteValue(getColumn(_board[i]-1) - getColumn(i));
    }
  }

  return sum;
}

int Puzzle::piecesInPlace(){ //Returns the number of pieces in place
  int sum=0;
  for(int i = 0; i < N; i++){
    if(_board[i] == 0 && i == N-1)
      sum++;
    else if(_board[i] == i+1)
      sum++;
  }

  return sum;
}

//Int does not work with larger values of N
int Puzzle::toNum(){
  int id = 0;
  for(int i = 0; i < N; i++){
    id += _board[i]*(std::pow(10,i));
  }
  return id;
}

void Puzzle::purgeLeaks(){ //DFS to free memory
  std::vector<Puzzle *>::iterator it;
  for(it = _nextPuzzles.begin(); it != _nextPuzzles.end(); it++){
    (*it)->purgeLeaks();
  }
  delete this;
}

void Puzzle::purgeSubTree(){
  std::vector<Puzzle *>::iterator it;
  for(it = _nextPuzzles.begin(); it != _nextPuzzles.end(); it++){
    (*it)->purgeLeaks();
  }
  _nextPuzzles.clear();

}
