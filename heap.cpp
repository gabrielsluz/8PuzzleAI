#include "heap.hpp"
#include <vector>
#include "puzzle.hpp"

bool Heap::isSmallerThan(Puzzle A, Puzzle B){
  return A.pathCost() < B.pathCost();
}

int Heap::_parent(int i){
  return (i-1)/2;
}

int Heap::_leftChild(int i){
  return 2*i +1;
}

int Heap::_rightChild(int i){
  return 2*i +2;
}

void Heap::_heapifyDown(int i){
  int left = _leftChild(i);
  int right = _rightChild(i);

  Puzzle swapper;

  int min = i;

  if(left < _heap.size() && isSmallerThan(_heap[left],_heap[i]))
    min = left;

  if(right < _heap.size() && isSmallerThan(_heap[right],_heap[i]))
    min = right;

  if(min != i){
    swapper = _heap[min];
    _heap[min] = _heap[i];
    _heap[i] = swapper;

    _heapifyDown(min);
  }
}

void Heap::_heapifyUp(int i){
  if(i == 0)
    return;

  Puzzle swapper;

  if(isSmallerThan(_heap[i],_heap[_parent(i)])){
    swapper = _heap[_parent(i)];
    _heap[_parent(i)] = _heap[i];
    _heap[i] = swapper;

    _heapifyUp(_parent(i));
  }

}

Puzzle Heap::top(){
  return _heap.front();
}


void Heap::push(Puzzle node){
  _heap.push_back(node);

  _heapifyUp(_heap.size() - 1);

}

void Heap::pop(){
  if(isEmpty()) //Mistake
    return;

  _heap[0] = _heap.back();
  _heap.pop_back();

  _heapifyDown(0);


}


bool Heap::isEmpty(){
  return _heap.empty();
}


bool Heap::isPuzzleInHeap(Puzzle target){
  std::vector<Puzzle>::iterator it;
  for(it = _heap.begin(); it != _heap.end(); it++){
    if(target.compareBoard(*it)){
      return true;
    }
  }
  return false;

}
