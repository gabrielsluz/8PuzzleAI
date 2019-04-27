#include "puzzle.hpp"
#include <iostream>
#include <unordered_set>
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




int bfs(Puzzle *initialState){
  std::list <Puzzle*> frontier;
  std::unordered_set <int> explored;
  std::unordered_set <int> frontierSet;
  std::list <Puzzle> childNodes;

  Puzzle *node;
  int id = 0;

  bool isInFrontier = false;
  bool isInExplored = false;

  if(initialState->isFinalState())
    return 0;

  frontier.push_back(initialState);
  frontierSet.insert(initialState->toNum());

  while(true){
    if(frontier.empty())
      return -1;

    node = frontier.front();
    id = node->toNum();
    frontier.pop_front();
    frontierSet.erase(id);
    explored.insert(id);

    node->getNextStates(&childNodes);

    for(std::list<Puzzle>::iterator it = childNodes.begin(); it != childNodes.end(); it++){
      id = it->toNum();
      isInFrontier = frontierSet.find(id) != frontierSet.end();
      isInExplored = explored.find(id) != explored.end();

      if(isInFrontier || isInExplored)
        continue;

      if(it->isFinalState())
        return it->pathCost();

      frontier.push_back(&(*it));
      frontierSet.insert(id);
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

  solution = bfs(&input);

  if(solution == -1)
    std::cout << "Nao tem solucao" << std::endl;

  std::cout << std::endl << solution << std::endl;


  return 0;
}
