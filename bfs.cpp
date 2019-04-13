#include "bfs.hpp"
#include "puzzle.hpp"
#include <iostream>
#include <list>



int bfs(Puzzle initialState){
  std::list <Puzzle> frontier;
  std::list <Puzzle> explored;
  std::list <Puzzle> childNodes;

  int path_cost = 0;
  Puzzle node;

  if(initialState.isFinalState())
    return path_cost;


  frontier.push_back(initialState);

  while(true){
    if(frontier.empty())
      return -1;

    node = frontier.front();
    frontier.pop_front();
    explored.push_back(node);

    node.getNextStates(&childNodes);


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


  return 0;
}
