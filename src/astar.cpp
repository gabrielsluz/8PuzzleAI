#include "puzzle.hpp"
#include <iostream>
#include <list>
#include <unordered_set>

#include "heap.hpp"

bool isSmallerThan(Puzzle* A, Puzzle* B){
  return (A->pathCost() + A->astarH()) < (B->pathCost() + B->astarH());
}



int astar(Puzzle *initialState){
  Heap frontier(isSmallerThan);
  std::unordered_set <int> explored;
  std::unordered_set <int> frontierSet;
  std::vector <Puzzle*> *childNodes;

  bool isInFrontier = false;
  bool isInExplored = false;

  Puzzle *node;

  int id =0;

  frontier.push(initialState);
  frontierSet.insert(initialState->toNum());

  while(true){
    if(frontier.isEmpty())
      return -1;
/*
    std::cout << "Heap = ";
    frontier.printHeap();
    std::cout << std::endl;*/

    node = frontier.top();
    id = node->toNum();
    frontier.pop();
    frontierSet.erase(id);

    //std::cout << node->pathCost() + node->astarH() << std::endl;

    if(node->isFinalState()){
      node->printPath();
      return node->pathCost();
    }

    explored.insert(id);

    childNodes = node->getNextStates();

    for(std::vector<Puzzle*>::iterator it = childNodes->begin(); it != childNodes->end(); it++){
      id = (*it)->toNum();
      isInFrontier = frontierSet.find(id) != frontierSet.end();
      isInExplored = explored.find(id) != explored.end();

      if(!(isInFrontier) && !(isInExplored)){
      //  std::cout << "Child = " << (*it)->pathCost() + (*it)->astarH() << std::endl;
        frontier.push(*it);
        frontierSet.insert(id);

      }
      else if(isInFrontier){
        frontier.tryReplace(*it);
      }
    }
  }
}



int main(){
  int in[N];
  int solution=0;

  for(int i=0; i < N; i++){
    std::cin >> in[i];
  }

  Puzzle *input = new Puzzle(in,N);


  solution = astar(input);

  if(solution == -1)
    std::cout << "Nao tem solucao" << std::endl;

  std::cout << std::endl << solution << std::endl;

  input->purgeLeaks();


  return 0;
}
