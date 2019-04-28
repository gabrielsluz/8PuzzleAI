#include "puzzle.hpp"
#include <iostream>
#include <list>
#include <vector>



int hillClimbing(Puzzle *current, int max){
  std::vector <Puzzle*> *childNodes;
  int cont = 0;

  Puzzle *neighbor;

  if(current->isFinalState())
    return 0;


  while(true){
    childNodes = current->getNextStates();
    //std::cout << current.piecesInPlace() << " ";
    neighbor = *childNodes->begin();
    for(std::vector <Puzzle*>::iterator it = childNodes->begin(); it != childNodes->end(); it++){
      if((*it)->piecesInPlace() > neighbor->piecesInPlace()){
        neighbor = *it;
      }
    }

    if(neighbor->piecesInPlace() < current->piecesInPlace()){
      return current->pathCost();
    }
    else if(neighbor->piecesInPlace() == current->piecesInPlace()){
      cont++;
      if(cont >= max){
        return -1;
      }
    }

    current = neighbor;

    if(current->isFinalState())
      return current->pathCost();

  }
}



int main(){
  int in[N];
  int solution=0;

  for(int i=0; i < N; i++){
    std::cin >> in[i];
  }

  Puzzle *input = new Puzzle(in,N);

  solution = hillClimbing(input,100*100*100);

  if(solution == -1)
    std::cout << "Nao tem solucao" << std::endl;

  std::cout << std::endl << solution << std::endl;

  input->purgeLeaks();


  return 0;
}
