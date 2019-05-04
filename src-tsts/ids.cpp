#include "puzzle.hpp"
#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <fstream>

int depthLimitedSearch(Puzzle *state, int limit){
  std::vector <Puzzle*> *childNodes;
  bool cutoffOccurred = false;

  //std::cout << "Limit = " << limit << std::endl;

  int result=0;

  if(state->isFinalState()){
    state->printPath();
    return state->pathCost();
  }
  else if(limit == 0)
    return -2; //cutoff

  childNodes = state->getNextStates();


  for(std::vector<Puzzle*>::iterator it = childNodes->begin(); it != childNodes->end(); it++){
    result = depthLimitedSearch(*it, limit-1);
    if(result == -2)
      cutoffOccurred = true;
    else if(result != -1)
      return result;
  }

  if(cutoffOccurred)
    return -2;
  else
    return -1;

}


int ids(Puzzle *initialState){ //Iterative deepening search
  int depth = 0;
  int result = 0;

  while(true){
    depth ++;

    result = depthLimitedSearch(initialState, depth);

    if(result != -2)
      return result;

    initialState->purgeSubTree();
  }
}





int main(){
  int in[N];
  int solution=0;

  double times[20];
  int count = 20;

  for(int i=0; i < N; i++){
    std::cin >> in[i];
  }

for(int i =0; i < count; i++){
  Puzzle *input = new Puzzle(in,N);

  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

  solution = ids(input);

  std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();

  times[i] = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();

  if(solution == -1)
    std::cout << "Nao tem solucao" << std::endl;

  std::cout << std::endl << solution << std::endl;

  input->purgeLeaks();
}

  for(int i =0; i < count ; i++){
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
  outfile.open("./tst/ids.data", std::ios::app);

  outfile << solution << " " << AverageTime << " " << UpperTime << " " << LowerTime << std::endl;

  outfile.close();


  return 0;
}

/*
#include "puzzle.hpp"
#include <iostream>
#include <list>


int depthLimitedSearch(Puzzle state, int limit){
  std::list <Puzzle> childNodes;
  bool cutoffOccurred = false;

  //std::cout << "Limit = " << limit << std::endl;

  int result=0;

  if(state.isFinalState())
    return state.pathCost();
  else if(limit == 0)
    return -2; //cutoff

  state.getNextStates(&childNodes);


  for(std::list<Puzzle>::iterator it = childNodes.begin(); it != childNodes.end(); it++){
    result = depthLimitedSearch(*it, limit-1);
    if(result == -2)
      cutoffOccurred = true;
    else if(result != -1)
      return result;
  }

  if(cutoffOccurred)
    return -2;
  else
    return -1;

}


int ids(Puzzle initialState){ //Iterative deepening search
  int depth = 0;
  int result = 0;

  while(true){
    depth ++;

    result = depthLimitedSearch(initialState, depth);

    if(result != -2)
      return result;
  }
}




int main(){
  int in[N];
  int solution=0;

  for(int i=0; i < N; i++){
    std::cin >> in[i];
  }

  Puzzle input(in,N);

  solution = ids(input);

  if(solution == -1)
    std::cout << "Nao tem solucao" << std::endl;

  std::cout << std::endl << solution << std::endl;



  return 0;
}
*/
