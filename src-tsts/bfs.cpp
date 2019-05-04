#include "puzzle.hpp"
#include <iostream>
#include <unordered_set>
#include <list>
#include <vector>
#include <chrono>
#include <cmath>
#include <fstream>



int bfs(Puzzle *initialState){
  std::list <Puzzle*> frontier;
  std::unordered_set <int> explored;
  std::unordered_set <int> frontierSet;
  std::vector <Puzzle*> *childNodes;

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

    childNodes = node->getNextStates();

    for(std::vector<Puzzle*>::iterator it = childNodes->begin(); it != childNodes->end(); it++){
      id = (*it)->toNum();
      isInFrontier = frontierSet.find(id) != frontierSet.end();
      isInExplored = explored.find(id) != explored.end();

      if(isInFrontier || isInExplored){
        //Desaloca no
        continue;
      }

      if((*it)->isFinalState()){
        //Desaloca no
        (*it)->printPath();
        return (*it)->pathCost();
      }

      frontier.push_back(*it);
      frontierSet.insert(id);
    }
  }
}



int main(){
  int in[N];
  int solution=0;

  double times[20];

  for(int i=0; i < N; i++){
    std::cin >> in[i];
  }

for(int i =0; i < 20; i++){
  Puzzle *input = new Puzzle(in,N);

  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

  solution = bfs(input);

  std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();

  times[i] = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();

  if(solution == -1)
    std::cout << "Nao tem solucao" << std::endl;

  std::cout << std::endl << solution << std::endl;

  input->purgeLeaks();
}

  for(int i =0; i < 20; i++){
    std::cout << times[i] << std::endl;
  }



  double UpperTime = 0;
  double LowerTime = 0;
  double AverageTime = 0;
  double stdDev = 0;
  double sum = 0;

  int count = 20;

  for(int i=0; i < count; i++){
    sum += times[i];
  }
  AverageTime = sum/count;
  std::cout << AverageTime << std::endl;


  for(int i=0; i < count; i++){
    stdDev += std::pow(times[i] - AverageTime,2);
  }
  stdDev = std::sqrt(stdDev/count);

  UpperTime = AverageTime + 1.96*(stdDev/std::sqrt(count));
  LowerTime = AverageTime - 1.96*(stdDev/std::sqrt(count));


  std::ofstream outfile;
  outfile.open("./tst/bfs.data", std::ios::app);

  outfile << solution << " " << AverageTime << " " << UpperTime << " " << LowerTime << std::endl;

  outfile.close();


  return 0;
}
