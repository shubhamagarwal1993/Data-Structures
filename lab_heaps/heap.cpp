/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

#include <iostream>
#include <vector>
#include <stdio.h>
#include <math.h>

using namespace std;

template <class T, class Compare>
size_t heap<T, Compare>::root() const {
    /// @todo Update to return the index you are choosing to be your root.

    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild( size_t currentIdx ) const {
    /// @todo Update to return the index of the left child.

	if((2*currentIdx) < _elems.size())
	{
		return (2*currentIdx);
	}		
		return -1;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild( size_t currentIdx ) const {
    /// @todo Update to return the index of the right child.
    if((2*currentIdx+1) < _elems.size())
	{
		return (2*currentIdx)+1;
	}
		return -1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent( size_t currentIdx ) const {
    /// @todo Update to return the index of the parent.
    return floor(currentIdx/2);	
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild( size_t currentIdx ) const {
    /// @todo Update to return whether the given node has a child

	if(2*currentIdx < _elems.size())
	{
		return true;
	}
	return false;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild( size_t currentIdx ) const {
    /// @todo Update to return the index of the child with highest priority
    ///   as defined by higherPriority()

	if(!hasAChild(currentIdx)) 
  		return -1;
      
	if(rightChild(currentIdx) == -1) 
		return leftChild(currentIdx);
      
	if(higherPriority(_elems[leftChild(currentIdx)], _elems[rightChild(currentIdx)])) 
       	return leftChild(currentIdx);
      
    return rightChild(currentIdx);
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown( size_t currentIdx ) {
    /// @todo Implement the heapifyDown algorithm.

	if(hasAChild(currentIdx))
	{
		size_t minChildIndex = maxPriorityChild(currentIdx);
		if(higherPriority(_elems[minChildIndex], _elems[currentIdx]))
		{
			std::swap(_elems[currentIdx], _elems[minChildIndex]);
			heapifyDown(minChildIndex);
		}
	}
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp( size_t currentIdx ) {
    if( currentIdx == root() )
        return;
    size_t parentIdx = parent( currentIdx );
    if( higherPriority( _elems[ currentIdx ], _elems[ parentIdx ] ) ) {
        std::swap( _elems[ currentIdx ], _elems[ parentIdx ] );
        heapifyUp( parentIdx );
    }
}

template <class T, class Compare>
heap<T, Compare>::heap() {
    /// @todo Depending on your implementation, this function may or may
    ///   not need modifying
    _elems.push_back(-1);		//why do we need this
}

template <class T, class Compare>
heap<T, Compare>::heap( const std::vector<T> & elems ) {
    /// @todo Construct a heap using the buildHeap algorithm
    _elems.push_back(0);
    for (int i = 0; i < elems.size(); i++)
    {
        _elems.push_back(elems[i]);
    }
    for (int i = parent(_elems.size()); i > 0; i--)
    {
        heapifyDown(i);
    }
}

template <class T, class Compare>
T heap<T, Compare>::pop() {
    /// @todo Remove, and return, the element with highest priority
    
    //replace the root with the last element on the last level
    
    T minval = _elems[1];
    _elems[1] = _elems[_elems.size()-1];
    _elems.pop_back();							//what is this exactly

    heapifyDown(1);
    return minval;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const {
    /// @todo Return, but do not remove, the element with highest priority
    return _elems[1];
}

template <class T, class Compare>
void heap<T, Compare>::push( const T & elem ) {
    /// @todo Add elem to the heap
    
//	if(size == capacity) growArray();
//	_elems[elems.size()+1] = elem;

    _elems.push_back(elem);
    heapifyUp(_elems.size()-1);
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const {
    /// @todo Determine if the heap is empty
    if(_elems.size() == 1)
    	return true;
    return false;	
}
