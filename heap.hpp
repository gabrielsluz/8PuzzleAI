#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include "puzzle.hpp"

class Heap{
  private:
    std::vector<Puzzle> _heap;

    int _parent(int i);
    int _leftChild(int i);
    int _rightChild(int i);

    void _heapifyDown(int i);
    void _heapifyUp(int i);

    bool isSmallerThan(Puzzle A, Puzzle B);


  public:

    Puzzle top();
    void push(Puzzle node);
    void pop();

    bool isEmpty();

    bool isPuzzleInHeap(Puzzle target);


};



#endif
