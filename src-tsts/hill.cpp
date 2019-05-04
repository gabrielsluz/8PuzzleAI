#include "puzzle.hpp"
#include <iostream>
#include <list>
#include <vector>
#include <chrono>
#include <cmath>
#include <fstream>



int hillClimbing(Puzzle *current, int max){
  std::vector <Puzzle*> *childNodes;
  int cont = 0;

  Puzzle *neighbor;

  if(current->isFinalState())
    return 0;


  while(true){
    childNodes = current->getNextStates();
    //std::cout << current.piecesInPlace() << " ";
    neighbor = *childNodes->begin();
    for(std::vector <Puzzle*>::iterator it = childNodes->begin(); it != childNodes->end(); it++){
      if((*it)->piecesInPlace() > neighbor->piecesInPlace()){
        neighbor = *it;
      }
    }

    if(neighbor->piecesInPlace() < current->piecesInPlace()){
      if(current->isFinalState())
        return current->pathCost();
      else
        return -2;
    }
    else if(neighbor->piecesInPlace() == current->piecesInPlace()){
      cont++;
      if(cont >= max){
        return -2;
      }
    }

    current = neighbor;

    if(current->isFinalState())
      return current->pathCost();

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

  solution = hillClimbing(input,100*100*100);

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
  outfile.open("./tst/hillClimbing.data", std::ios::app);

  outfile << solution << " " << AverageTime << " " << UpperTime << " " << LowerTime << std::endl;

  outfile.close();


  return 0;
}
