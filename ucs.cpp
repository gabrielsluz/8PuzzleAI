#include "puzzle.hpp"
#include <iostream>
#include <list>
#include "heap.hpp"
#include <unordered_set>


bool isSmallerThan(Puzzle A, Puzzle B){
  return A.pathCost() < B.pathCost();
}




int ucs(Puzzle initialState)  {
  Heap frontier(isSmallerThan);
  std::unordered_set <int> explored;
  std::unordered_set <int> frontierSet;
  std::list <Puzzle> childNodes;

  bool isInFrontier = false;
  bool isInExplored = false;

  Puzzle node;

  int id =0;

  frontier.push(initialState);
  frontierSet.insert(initialState.toNum());

  while(true){
    if(frontier.isEmpty())
      return -1;

    node = frontier.top();
    id = node.toNum();
    frontier.pop();
    frontierSet.erase(id);

    //std::cout << node.pathCost() << std::endl;

    if(node.isFinalState())
      return node.pathCost();

    explored.insert(id);

    node.getNextStates(&childNodes);

    for(std::list<Puzzle>::iterator it = childNodes.begin(); it != childNodes.end(); it++){
      id = it->toNum();
      isInFrontier = frontierSet.find(id) != frontierSet.end();
      isInExplored = explored.find(id) != explored.end();

      if(!(isInFrontier) && !(isInExplored)){
        frontier.push(*it);
        frontierSet.insert(id);
        //std::cout << "Child = " << it->pathCost() << std::endl;
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

  Puzzle input(in,N);

  solution = ucs(input);

  if(solution == -1)
    std::cout << "Nao tem solucao" << std::endl;

  std::cout << std::endl << solution << std::endl;


  return 0;
}
