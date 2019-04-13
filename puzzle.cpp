#include "puzzle.hpp"


Puzzle::Puzzle(){
  for(int i =0; i < N; i++){
    _board[i] = 0;
  }
  _blank = 0;
}
