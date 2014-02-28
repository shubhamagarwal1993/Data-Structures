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
	if ((first == NULL) && (second == NULL))
		return NULL;

	if ((first == NULL) && (second != NULL))
		return second;

	if ((first != NULL) && (second == NULL))
		return first;
	
	ListNode * t;
	ListNode * t1 = first;
	ListNode * t2 = second;
	ListNode * marker;
	
	if (t1->data < t2->data)
	{
		t = t1;
		marker = t;
		t1 = split(t1,1);
	}
	else
	{
		t = t2;
		marker = t;
		t2 = split(t2,1);
	}		
	
		
	while((t1->next != NULL) && (t2->next != NULL))
	{
		if ((t1->data) < (t2->data))
		{
			t->next = t1;
			t1->prev = t;
			t1 = split(t1,1);
			t = t->next;
		}
		else
		{
			t->next = t2;
			t2->prev = t;
			t2 = split(t2,1);
			t = t->next;
		}
	}
	
//	if ((t1 == NULL) && (t2 == NULL))
//	{
//		return marker;
//	}

	if (t1->next == NULL)		//t2 is left
	{
		while ((t1->data) > (t2->data))
		{
			t->next = t2;
			t2->prev = t;
			if (t2->next != NULL)
				t2 = split(t2,1);
			t = t->next;
			return marker;
		}
		
			t->next = t1;
			t1->prev = t;
			t=t->next;
			t->next = t2;
			t2->prev = t;
			return marker;
	}
	
	else		//t2->next == NULL
	{
		while ((t2->data) > (t1->data))
		{
			t->next = t1;
			t1->prev = t;
			if (t1->next != NULL)
				t1 = split(t1,1);
			t = t->next;
			return marker;
		}
		
			t->next = t2;
			t2->prev = t;
			t=t->next;
			t->next = t1;
			t1->prev = t;
			return marker;	
	
	}
}		
	
		
/*		
	ListNode * temp1 = first;
	ListNode * temp2 = second;
	ListNode * marker;
	ListNode * newheader;
//checking which list' data has smallest data
	if(first->data < second->data)
	{
		marker = first;
		temp1 = temp1->next;
	//	marker->prev = NULL;
		newheader = first;	
	}		
	else		
	{
		marker = second;
		temp2 = temp2->next;
	//marker->prev = NULL;
		newheader = second;		
	}
	//we have a pointer to the list that we have to return

	// we have made temp4 = temp3;
	
	while ((temp1 != NULL) && (temp2 != NULL))
	{
		if(temp1->data<temp2->data)
		{
            marker->next=temp1;
            temp1->prev=marker;
            temp1=temp1->next;
            marker=marker->next;    
        }
        else
        {
            marker->next=temp2;
            temp2->prev=marker;
            temp2=temp2->next;
            marker=marker->next;
        }
    }
    
    if(temp1!=NULL)
    {
        marker->next=temp1;
        temp1->prev=marker;
    }
    
    if(temp2!=NULL)
    {
        marker->next=temp2;
        temp2->prev=marker;
    }
    temp1 = NULL;
    temp2 = NULL;
    marker = NULL;
    return newheader;
}
*/

/*{
    /// @todo Graded in MP3.2
 
 	//first = head of first node
 	//second = head of second node
 	if ((first == NULL) && (second == NULL))
		return NULL;

	if ((first == NULL) && (second != NULL))
		return second;

	if ((first != NULL) && (second == NULL))
		return first;
	if(first->data < second->data){
		ListNode * temp=first;
		first->next=merge(first->next,second);
		first->next->prev=first;
		return temp;	
	}
 	else{
 		ListNode * temp=second;
		second->next=merge(first,second->next);
		second->next->prev=second;
		return temp;	
 	}
}
*/ 	
 	
 	
 	
//********solving with recursion************* 
	/*if ((first == NULL) && (second == NULL))
		return NULL;

	if ((first == NULL) && (second != NULL))
		return second;

	if ((first != NULL) && (second == NULL))
		return first;

	else
	{
		
		if (second->data < first->data)
		{
			
			return marker;
		}
		else
		{
			ListNode *marker = first;
			return marker;
			merge(first->next, second);
			
			
		}
	}*/







//************************************ 	
 	
 	
/* 	if((first == NULL) && (second == NULL))
 	return NULL;
 	
 	else if ((first == NULL) && (second != NULL))
 	{
 		return second;
 	}
 	
 	else if ((second == NULL) && (first != NULL))
 	{
 		return first;
 	}
 	else
 	{
 	
// 	if list 2 elements are smaller than list 1 elements initially
 		ListNode * intlen = first;
 		ListNode * marker = first;
 		if (second->data < first->data)
 		{
 			intlen = second;
 			marker = second;
 			while((intlen->data < first->data) && (intlen->next->data < first->data))
 			{
 				if (intlen->next != NULL)
 				{
 					intlen = intlen->next;
 				}
 				else
 				{
 					return first;
 				}	
 					
 			}
 			//now intlen is at required positoin and second is at front of list.
 			
 //			if ()
 			second = intlen->next;
 			intlen->next = first;
 			first->prev = intlen;
 			intlen = first;
 			
 			
 			if (second == NULL)
 				return marker;
 				
 				
 			if (first->next != NULL)
 			{
 				intlen = intlen->next;
 			}
 			
 			else if (first->next == NULL)
 			{
 				first->next = second;
 				second->prev = first;
 				return marker;
 			}
//***************************************************************************************** 			
 		}
 		//second will be a valid list from here
 		
 		//if the first element's data is smaller than the 2nd elements data
 		if (first->data < second->data)
 		{
 			intlen = first;
 			marker = first;
 			if (intlen->next != NULL)
 			{
 				intlen = intlen->next;
 			}
 			else
 			{
 				first->next = second;
 				second->prev = first;
 				return marker;
 			}
 		}
 		
 		
 		while((intlen->next != NULL) && (second->next != NULL))
 		{
 			if ((first->data < second->data) &&(second->data < intlen->data))
 			{
 				//insert second between first and intlen
 				first->next = second;
 				second->prev = first;
 				intlen->prev = second;
 				if (second->next == NULL)
 				{
 					first->next = second;
 					second->prev = first;
 					second->next = intlen;
 					intlen->prev = second;
 					
// 					second->next = intlen;
 					return marker;
 				}
 				else if (second->next != NULL)
 				{
 					second = second->next;
 					second->prev->next = intlen;
 					second->prev = NULL;
 					first = first->next;
 				}
 			}	
 			else //if ((first->data < second->data) && (intlen->data < second->data))
 			{
 				intlen = intlen->next;
 				first = first->next;	
 			}	
 		}	
 		
 		
 		
 		if((intlen->next == NULL) && (second->next == NULL))
 		{
 			if ((first->data < second->data) &&(second->data < intlen->data))
 			{
 				first->next = second;
 				second->prev = first;
 				second->next = intlen;
 				intlen->prev = second;
 				return marker;
 			}
 			else
 			{
 				intlen->next = second;
 				second->prev = intlen;
 				second->next = NULL;
 				return marker;
 			}
 		}
 		
 		else if((intlen->next == NULL) && (second->next != NULL))
 		{
 			if ((first->data < second->data) && (second->data < intlen->data))
 			{
 				first->next = second;
 				second->prev = first;
 				intlen->prev = second;
 				second = second->next;
 				second->prev->next = intlen;
 				second->prev = NULL;
 				intlen->next = second;
 				second->prev = intlen;
 				return marker;
 			}
 			
 			else
 			{
 				intlen->next = second;
 				second->prev = intlen;
 				return marker;
 			}	
 		}
 		
 		else //((intlen->next != NULL) && (second->next == NULL))
 		{
 			while ((first->data < second->data) && (intlen->data < second->data))
 			{
 				if (intlen->next != NULL)
 				{
 					intlen = intlen->next;
 					first = first->next;	
 				}
 				else
 				{
 					intlen->next = second;
 					second->prev = intlen;
 				}
 			}
 			if ((first->data < second->data) && (second->data < intlen->data))
 			{
 				first->next = second;
 				second->prev = first;
 				intlen->prev = second;
 				second->next = intlen;
 				
 				return marker;
 			}
 		return marker;
 		}
 					
 			
 	}
}
*/
//*************************************************************************************************	
	//helper function for inserting between first and intlen	
	
	
	
//*************************************************************************************************
/**
 * Sorts the current list by applying the Mergesort algorithm.
 */

template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;

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
    
    if (chainLength == 1)
    {
    	return start;
    }
    
    else
    {
    	ListNode * temp = split(start, chainLength/2);
    	ListNode * ret1 = mergesort(start, chainLength/2);
    	ListNode * ret2 = mergesort(temp, chainLength - (chainLength/2));
    	
    	return merge(ret1, ret2);
     }
}

