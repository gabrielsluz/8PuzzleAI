#include "puzzle.hpp"
#include <iostream>
#include <list>

bool isPuzzleInList(Puzzle target, std::list<Puzzle> list){
  std::list<Puzzle>::iterator it;

  for(it = list.begin(); it != list.end(); it++){
    if(target.compareBoard(*it)){
      return true;
    }
  }
  return false;
}




int bfs(Puzzle initialState){
  std::list <Puzzle> frontier;
  std::list <Puzzle> explored;
  std::list <Puzzle> childNodes;

  Puzzle node;

  if(initialState.isFinalState())
    return 0;

  frontier.push_back(initialState);

  while(true){
    if(frontier.empty())
      return -1;

    node = frontier.front();
    frontier.pop_front();
    explored.push_back(node);

    node.getNextStates(&childNodes);

    for(std::list<Puzzle>::iterator it = childNodes.begin(); it != childNodes.end(); it++){
      if(isPuzzleInList(*it,frontier) || isPuzzleInList(*it,explored))
        continue;

      if(it->isFinalState())
        return it->pathCost();

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
