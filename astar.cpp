#include "puzzle.hpp"
#include <iostream>
#include <list>
#include "heap.hpp"


bool isPuzzleInList(Puzzle target, std::list<Puzzle> list){
  std::list<Puzzle>::iterator it;

  for(it = list.begin(); it != list.end(); it++){
    if(target.compareBoard(*it)){
      return true;
    }
  }
  return false;
}



int ucs(Puzzle initialState){
  Heap frontier;
  std::list <Puzzle> explored;
  std::list <Puzzle> childNodes;

  Puzzle node;

  //if(initialState.isFinalState())
    //return 0;

  frontier.push(initialState);

  while(true){
    if(frontier.isEmpty())
      return -1;

    node = frontier.top();
    frontier.pop();

    if(node.isFinalState())
      return node.pathCost();

    explored.push_back(node);

    node.getNextStates(&childNodes);

    for(std::list<Puzzle>::iterator it = childNodes.begin(); it != childNodes.end(); it++){
      if(!(frontier.isPuzzleInHeap(*it)) && !(isPuzzleInList(*it,explored)))
        frontier.push(*it);
      else if(frontier.isPuzzleInHeap(*it))
        frontier.tryReplace(*it);
    }
  }
}



int main(){
  int in[N];
  int solution=0;

  for(int i=0; i < N; i++){
    std::cin >> in[i];
  }

  Puzzle input(in,N);

  solution = ucs(input);

  if(solution == -1)
    std::cout << "Nao tem solucao" << std::endl;

  std::cout << std::endl << solution << std::endl;


  return 0;
}
