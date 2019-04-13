#include "bfs.hpp"
#include "puzzle.hpp"
#include <iostream>
#include <list>



int bfs(Puzzle initialState){
  std::list <Puzzle> frontier;
  std::list <Puzzle> explored;
  std::list <Puzzle> childNodes;

  int pathCost = 0;
  Puzzle node;

  if(initialState.isFinalState())
    return pathCost;


  frontier.push_back(initialState);

  while(true){
    if(frontier.empty())
      return -1;

    node = frontier.front();
    frontier.pop_front();
    explored.push_back(node);

    node.getNextStates(&childNodes);

    for(std::list<Puzzle>::iterator it = childNodes.begin(); it != childNodes.end(); it++){
      if(it->isFinalState())
        return pathCost;

      frontier.push_back(*it);
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

  solution = bfs(input);

  std::cout << std::endl << solution << std::endl;


  return 0;
}
