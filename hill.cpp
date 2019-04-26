#include "puzzle.hpp"
#include <iostream>
#include <list>



int hillClimbing(Puzzle current, int max){
  std::list <Puzzle> childNodes;
  int cont = 0;

  Puzzle neighbor;

  if(current.isFinalState())
    return 0;


  while(true){
    current.getNextStates(&childNodes);
    //std::cout << current.piecesInPlace() << " ";
    neighbor = *childNodes.begin();
    for(std::list<Puzzle>::iterator it = childNodes.begin(); it != childNodes.end(); it++){
      if(it->piecesInPlace() > neighbor.piecesInPlace()){
        neighbor = *it;
      }
    }

    if(neighbor.piecesInPlace() < current.piecesInPlace()){
      return current.pathCost();
    }
    else if(neighbor.piecesInPlace() == current.piecesInPlace()){
      cont++;
      if(cont >= max){
        return -1;
      }
    }

    current = neighbor;

    if(current.isFinalState())
      return current.pathCost();

  }
}




int main(){
  int in[N];
  int solution=0;

  for(int i=0; i < N; i++){
    std::cin >> in[i];
  }

  Puzzle input(in,N);

  solution = hillClimbing(input,100*100*100);

  if(solution == -1)
    std::cout << "Nao tem solucao" << std::endl;

  std::cout << std::endl << solution << std::endl;


  return 0;
}
