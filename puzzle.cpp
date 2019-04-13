#include "puzzle.hpp"


Puzzle::Puzzle(int* vec){
  for(int i = 0; i < N; i++){
    _board[i] = vec[i];

    if(vec[i] == 0)
      _blank = i;
  }
}

Puzzle::isFinalState(){
  for(int i = 0; i < N-1; i++){
    if(_board[i] != i+1)
      return false;
  }

  return true;
}
