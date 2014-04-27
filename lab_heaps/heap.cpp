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
//==========================================================================
template <class T, class Compare>
size_t heap<T, Compare>::leftChild( size_t currentIdx ) const 
{
    /// @todo Update to return the index of the left child.
 
	if((2*currentIdx) < _elems.size())
	{
		return (2*currentIdx)+1;
	}		

		return -1;
}
//==========================================================================
template <class T, class Compare>
size_t heap<T, Compare>::rightChild( size_t currentIdx ) const 
{
    /// @todo Update to return the index of the right child.

	if((2*currentIdx+1) < _elems.size())
	{
		return (2*currentIdx)+1;
	}

		return -1;
}
//==========================================================================
template <class T, class Compare>
size_t heap<T, Compare>::parent( size_t currentIdx ) const {
    /// @todo Update to return the index of the parent.

	size_t parent_index = floor(currentIdx/2);			//would it be int
	return parent_index;
}
//==========================================================================
template <class T, class Compare>
bool heap<T, Compare>::hasAChild( size_t currentIdx ) const {
    /// @todo Update to return whether the given node has a child
	
	if(2*currentIdx <= _elems.size())
	{
		return true;
	}
	
	return false;
}
//==========================================================================
template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild( size_t currentIdx ) const 
{
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
//================ heapifyDown ==============================
template <class T, class Compare>
void heap<T, Compare>::heapifyDown( size_t currentIdx ) 
{
    /// @todo Implement the heapifyDown algorithm.

	if(hasAChild(currentIdx))
	{
		int minChildIndex = maxPriorityChild(currentIdx);
		if(_elems[currentIdx] > _elems[minChildIndex])
		{
			std::swap(_elems[currentIdx], _elems[minChildIndex]);
			heapifyDown(minChildIndex);
		}
	}
}
//=================heapifyUP ==================================
template <class T, class Compare>
void heap<T, Compare>::heapifyUp( size_t currentIdx ) 
{
    if( currentIdx == root() )
        return;
    size_t parentIdx = parent( currentIdx );
    if( higherPriority( _elems[ currentIdx ], _elems[ parentIdx ] ) ) {
        std::swap( _elems[ currentIdx ], _elems[ parentIdx ] );
        heapifyUp( parentIdx );
    }
}
//============= empty heap ================================================
template <class T, class Compare>
heap<T, Compare>::heap() {
    /// @todo Depending on your implementation, this function may or may
    ///   not need modifying

    _elems.push_back(-1);
    
}
//=============== build heap =================================================
template <class T, class Compare>
heap<T, Compare>::heap( const std::vector<T> & elems ) {
    /// @todo Construct a heap using the buildHeap algorithm


	_elems.push_back(T());
	
	for(int i = 0; i < elems.size(); i++)
	{
		_elems.push_back(elems[i]);
	}
	
	for(int i = _elems.size()-1; i >= 1; i--)
	{
		heapifyDown(i);
	}
		
}
//================ pop =============================================================
template <class T, class Compare>
T heap<T, Compare>::pop() 
{
    /// @todo Remove, and return, the element with highest priority

	T minVal = _elems[1];
    _elems[1] = _elems[_elems.size()];
	heapifyDown(1);
	return minVal;
}
//================= Peek ===========================================================
template <class T, class Compare>
T heap<T, Compare>::peek() const {
    /// @todo Return, but do not remove, the element with highest priority
    return _elems[1];
}
//====================== insert =================================================
template <class T, class Compare>
void heap<T, Compare>::push( const T & elem ) {
    /// @todo Add elem to the heap
	
//	if(size == capacity) growArray();


//	_elems[elems.size()+1] = elem;
		
	_elems.push_back(elem);
	heapifyUp(_elems.size());
}
//=================================================================================
template <class T, class Compare>
bool heap<T, Compare>::empty() const {
	 /// @todo Determine if the heap is empty
	if(_elems.empty())
		return true;
	
	return false;
}
