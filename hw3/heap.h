#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>


template <typename T, typename PComparator = std::less<T> >
class Heap
{
 public:
  /// Constructs an m-ary heap for any m >= 2
  Heap(int m, PComparator c = PComparator());

  /// Destructor as needed
  ~Heap();

  /// Adds an item
  void push(const T& item);

  /// returns the element at the top of the heap 
  ///  max (if max-heap) or min (if min-heap)
  T const & top() const;

  /// Removes the top element
  void pop();

  int size();


  /// returns true if the heap is empty
  bool empty() const;


//find size of it
  int size() const;


 private:
  /// Add whatever helper functions and data members you need below
     
     int _m;
     PComparator _c;
     //template <typename T>
     std::vector<T> _heap;
     
  
};

// Add implementation of member functions here


//create heap

template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c){
  _m = m;
  _c = c;
}


// destructor   ~Heap();
template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap(){

}



template <typename T, typename PComparator>
int Heap<T,PComparator>::size(){
  return _heap.size();
}


// if empty return true
template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const
{
  if(_heap.empty()){
    return true;
  }
  return false;

}


template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(_heap.empty()){
    throw std::underflow_error("can't top an empty heap");
  }

  return _heap[0];
}

// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T, PComparator>::pop()
{
  if(_heap.empty()){
    throw std::underflow_error("can't pop an empty heap");
  }

if(_heap.size() == 1){
  _heap.pop_back();
  return;
}
//put bottom at top
_heap[0] = _heap[_heap.size() - 1];
_heap.pop_back();
int item_location = 0;
//heapify function
int location = item_location;
while(true){
  
  if(item_location == (int(_heap.size())-1)){
    return;
  }
  T best = _heap[item_location];
  for(int i = 0; i < _m; i++){
    if(_m*item_location + i + 1 < int( _heap.size())){
    
    if(_c(_heap[_m*item_location + i + 1], best)){
      best = _heap[_m*item_location + i + 1];
      location = _m*item_location + i + 1;
    }
    }
    else{
      break;
    }
  }
    if(item_location == location){
      return;
    }
    else{
      T temp = _heap[item_location];
      _heap[item_location] = _heap[location];
      _heap[location] = temp;
      item_location = location;
    }


}

}



// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item)
{
  _heap.push_back(item);
  int location = _heap.size() - 1;
  while(true){
    if(_heap.size() == 1){
      return;
    }
    else if(_c(_heap[location], _heap[(location-1)/_m])){
      T temp = _heap[location];
     _heap[location] = _heap[(location-1)/_m];
      _heap[(location-1)/_m] = temp;
     location = (location - 1)/_m;
    }
  else{
    return;
  }
 
  }

}







#endif

