/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */

#include "rgbapixel.h"
#include "list.h"
#include <iostream>
using namespace std;


/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List()
{
    /// @todo Graded in MP3.1
    clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{
    /// @todo Graded in MP3.1


	//if the linked list does not exist
	if ((head == NULL) && (tail == NULL))
	{
		length = 0;
		return;
	}
	
	else 
	{	
		ListNode * P;
		P = head;
	
		while (head->next != NULL)
		{
    		head = P->next;
    		P->next = NULL;
    		P->prev = NULL;
    		delete P;
    		P = head;
    	}
    
	    head->next = NULL;
    	head->prev = NULL;
    	delete head;
    	P = NULL;
		head = NULL;
		tail = NULL;
		
		length = 0;
	}
}		

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata)
{
    /// @todo Graded in MP3.1
    
    if ((head == NULL) && (tail == NULL))
    {
    	ListNode * P = new ListNode(ndata);		
    	P->prev = NULL;
    	P->next = NULL;
    	head = P;			   
    	tail = P;
    	P = NULL;
    	length++;
    }
    
    else 
    { 
		ListNode* P = new ListNode(ndata);
//		P->prev = NULL;
//		P->next = NULL;
		P->next = head;
		head->prev = P;
		head = P;	
		P = NULL;				//P is a local variable - will go out of scope
//		tail->next = NULL;
		length++;
	}
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack( const T & ndata )
{
    /// @todo Graded in MP3.1
    
  if ((head == NULL) && (tail == NULL))
    {
    	ListNode * P = new ListNode(ndata);		
    	P->prev = NULL;
    	P->next = NULL;
    	head = P;			   
    	tail = P;
    	P = NULL;
		length++;
    }
    
    //if there exists a list, we will create a new node
    else 
    {
    	ListNode *P = new ListNode(ndata);
    	P->next = NULL;
    	P->prev = NULL;
    	P->prev = tail;
    	tail->next = P;
    	tail = P;
    	P = NULL;
    	head->prev = NULL;
    	length++;
	}	     
}
    
/**
 * Reverses the current List.
 */
 

template <class T>
void List<T>::reverse()
{
    reverse(head, tail);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *.cpp:115: error: no matching function for call to ‘List<int>::revers
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */

template <class T>
void List<T>::reverse( ListNode * & startPoint, ListNode * & endPoint )
{
	if (startPoint == endPoint)
	{
		return;
	}

	/// @todo Graded in MP3.1
	ListNode* temp=startPoint;
	ListNode* tempstart=startPoint;
	ListNode* tempend=endPoint;
	while(temp!=endPoint)
	{
		ListNode* inTemp=temp->next;
		temp->next=temp->prev;
		temp->prev=inTemp;
		temp=inTemp;
		//cout<<"infinite Loop"<<endl;
	}
	ListNode* inTemp = temp->prev;
	temp->next=temp->prev;
	temp->prev=inTemp;
	endPoint=tempstart;
	startPoint=tempend;
	//cout<<"Exit"<<endl;
//
}	




/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */

template <class T>
void List<T>::reverseNth( int n )
{
    /// @todo Graded in MP3.1
	ListNode* temp = head;
	while(temp!=NULL)
	{
		int c = 0;
		ListNode* innertemp = temp;
		while(c<n-1&&innertemp->next!=NULL)
		{
			innertemp=innertemp->next;
			c++;
		}
		ListNode* tempprev = temp -> prev;
		ListNode* tempnext = innertemp->next;
		reverse(temp,innertemp);
		temp->prev=tempprev;
		innertemp->next=tempnext;
		if(tempprev!=NULL)
		{
			tempprev->next=temp;
		}
		else
		{
			head=temp;
		}
		if(tempnext!=NULL)
		{
			tempnext->prev=innertemp;
		}
		else
		{
			tail=innertemp;
			break;
		}
		temp=innertemp->next;
	}
/*	if (n <= length)
	{
		ListNode * S = head;
		ListNode * R = head;

		for (int i = 0; i < (length/n); i++)
		{
			for (int j = 0; j < n-1; j++)
			{
				R = R->next;
			}
			
			ListNode * save1 = S;
			if (S->prev != NULL)
				save1 = S->prev;
		  
					
			ListNode * save2 = R;	
			if (R->next != NULL)	
				save2 = R->next;
			
			S->prev = NULL;
			R->next = NULL;
	cout<<"calling reverse 1syt time"<<endl;
			reverse(S, R);
			
	cout<<"exited reversew"<<endl;		
			//if (save != NULL)
			
			save1->next = S;
			S->prev = save1;
			R->next = save2;
			save2->prev = R;
			
			
			S = R;
			
		cout<<5<<endl;
			if (S->next != NULL)
			{
				S = S->next;
				R = R->next;
			}
			else 
			{
				return;
			}			
		}	
	}	    
	
	int new_length = (length - ((length/n)*n));
	if (new_length == 0)
	{
		return;
	}	    
    else
    {
    	ListNode * R = head;
    	ListNode * S = head;
    	for (int i = 0; i < new_length; i++)
    	{
    		R = R->next;
    	}
    	
    	reverse(S, R);
    }
*/
}


/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */

template <class T>
void List<T>::waterfall()
{
    /// @todo Graded in MP3.1
    
    if (head == NULL)
    {
    	return;
    }
    
    ListNode * curr = head;
    ListNode * P = curr->next;
    
    while ((P != tail))
    {
    	curr = curr->next;
    	P = P->next;
    	curr->prev->next = P;
    	P->prev = curr->prev;
    	tail->next = curr;
    	curr->prev = tail;
    	curr->next=NULL;
    	tail = curr;
    	curr = P;
    	P = P->next;
    }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */

template <class T>
List<T> List<T>::split(int splitPoint)		
{
	if (splitPoint > length)				//invalid splitpoint
        return List<T>();

	
    if (splitPoint < 0)						
        splitPoint = 0;

    ListNode * secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head)
    {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    }
    else
    {
        // set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL)
    {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */

template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint)
{
    /// @todo Graded in MP3.2
    
    if (start == NULL)
    {
    	return 0;
    }
    
	else
	{
		ListNode * temp = start;
		
		for (int i = 0; i < splitPoint; i++)
		{
			if(temp->next != NULL)
			{
				temp = temp->next;
			}
		}
	
		ListNode * temp_marker = temp->prev;
		temp->prev = NULL;
		temp_marker->next = NULL;
		start = temp;
		return start;
	}    
    
    						//return NULL; // change me!
/*
	ListNode * temp = start;
	for (int i = 0; i < splitPoint; i++)
	{
		temp = temp->next
	}
	split();

*/
}
//*******************************************************************************************************
/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */

template <class T>
void List<T>::mergeWith(List<T> & otherList)
{
    // set up the current list
    head = merge(head, otherList.head);                            
    tail = head;

    // make sure there is a node in the new list
    if(tail != NULL)
    {
        while (tail->next != NULL)
            tail = tail->next;
    }
    length = length + otherList.length;

    // empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;

return;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */

template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode * second)
{
    /// @todo Graded in MP3.2
 
 	//first = head of first node
 	//second = head of second node
 	
 	if((first == NULL) && (second == NULL))
 	return NULL;
 	
 	if (first == NULL)
 	{
 		return second;
 	}
 	
 	else if (second == NULL)
 	{
 		return first;
 	}
 	else
 		return NULL;
	
// if both first and second have elements
 	else
 	{
	 	//***** we will return header*****
		ListNode * curr = first;
		ListNode * temp1 = first->next;
		ListNode * temp2 = second;
		
		while ((temp2 != NULL) || (temp1 != NULL))		
		{
			if (first->data < second->data)
			{
					
			}	
			if (second->data < first->data)	
		}	
		
		
/*		
		if (second->data < first->data)
		{
			first = second;
		}
		
		if (first->data)				 	
 		
 	}
 	
  	
 	
	ListNode * newhead;
	if (first->data == second->data)
	{
		newhead = first;
	} 	 
 	else if (first->data < second->data)
 	{
 		newhead = first;
 	}
 	else
 	{
 		newhead = second;
 	}
 	
 	ListNode * temp1 = newhead;
 	ListNode * curr = newhead;
 	ListNode * temp2;
 	ListNode * temp2_curr;
 	if (first == newhead)
 	{
 		temp2 = second;
 	}
 	else
 	{
 		temp2 = first;
 	}	
 	
 	if (temp2->next != NULL)
 	{
 		temp2_curr = temp2->next;
 	}
 	
 //we have head pointer to smallest data
 //we have temp1,curr pointing to head
 //we have temp2,temp2_curr pointing to other list
 
 	if (temp1->next != NULL)
 	{
 		temp1 = temp1->next;
   	}
   	
	while((temp1->next != NULL) && (temp2_curr->next != NULL))
	{ 
		if((temp2->data) < (temp1->data)) 
 		{
			curr->next = temp2;
 			temp2->prev = curr;
 			temp1->prev = NULL;
 			
 			while ((temp2_curr->data) < (temp1->data))
 			{
 				temp2 = temp2->next;
 				temp2_curr = temp2_curr->next;
 			}
 			
 			temp2->next = temp1;
 			temp1->prev = temp2;
 			temp2_curr->prev = NULL;
 			temp2 = temp2_curr;
 			
 			temp2_curr = temp2_curr->next;
 		}
 	}			
 			

	
 		if ((temp1->data) < (temp2->data))
 		{
 			temp1 = temp1->next;
 			curr = curr->next;
 		}
	
//temp 1 is null

	if (temp2 != NULL)
	{
		if (temp2->data < temp1->data)
		{
			curr = curr->next;
			temp1 = temp1->next;
		}	
	}
	
	if (temp2_curr != NULL)
	{
		temp1->next = temp2_curr;
		temp2_curr->prev = temp1;
	}
*/	
//    return newhead; // change me!

//*************************************************************************************************
/**
 * Sorts the current list by applying the Mergesort algorithm.
 */

template <class T>
void List<T>::sort()
{
/*    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
*/
return;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
 
template <class T>
typename List<T>::ListNode * List<T>::mergesort(ListNode * start, int chainLength)
{
    /// @todo Graded in MP3.2
    return NULL; // change me!
}

