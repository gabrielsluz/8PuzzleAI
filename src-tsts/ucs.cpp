#include "puzzle.hpp"
#include <iostream>
#include <list>
#include <unordered_set>
#include <chrono>
#include <cmath>
#include <fstream>

#include "heap.hpp"


bool isSmallerThan(Puzzle *A, Puzzle *B){
  return A->pathCost() < B->pathCost();
}




int ucs(Puzzle *initialState){
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

    //std::cout << node->pathCost() << std::endl;

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
      //  std::cout << "Child = " << (*it)->pathCost()<< std::endl;
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

  double times[20];
  int count = 5;

  for(int i=0; i < N; i++){
    std::cin >> in[i];
  }

for(int i =0; i < count; i++){
  Puzzle *input = new Puzzle(in,N);

  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

  solution = ucs(input);

  std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();

  times[i] = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();

  if(solution == -1)
    std::cout << "Nao tem solucao" << std::endl;

  std::cout << std::endl << solution << std::endl;

  input->purgeLeaks();
}

  for(int i =0; i < count; i++){
    std::cout << times[i] << std::endl;
  }



  double UpperTime = 0;
  double LowerTime = 0;
  double AverageTime = 0;
  double stdDev = 0;
  double sum = 0;


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
  outfile.open("./tst/ucs.data", std::ios::app);

  outfile << solution << " " << AverageTime << " " << UpperTime << " " << LowerTime << std::endl;

  outfile.close();


  return 0;
}
