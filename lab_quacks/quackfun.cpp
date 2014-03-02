/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */

using namespace std;
#include <iostream>
#include <stack>
/**
 * Sums items in a stack.
 * @param s A stack holding values to sum.
 * @return The sum of all the elements in the stack, leaving the original
 *  stack in the same state (unchanged).
 *
 * @note You may modify the stack as long as you restore it to its original
 *  values.
 * @note You may use only two local variables of type T in your function.
 *  Note that this function is templatized on the stack's type, so stacks of
 *  objects overloading the + operator can be summed.
 * @note We are using the Standard Template Library (STL) stack in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint Think recursively!
 */
template <typename T>
T QuackFun::sum(stack<T> & s)
{
    // Your code here
    if (s.empty())
    {
    	return 0;	
    }
    
    T temp = s.top();
    T newsum = 0;
    s.pop();		
	newsum = temp + sum(s);
	s.push(temp);
	return newsum; // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
                
                
                  
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 * @param q A queue of items to be scrambled
 *
 * @note Any "leftover" numbers should be handled as if their block was complete.
 * @note We are using the Standard Template Library (STL) queue in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint You'll want to make a local stack variable.
 */
template <typename T>
void QuackFun::scramble(queue<T> & q)
{
    stack<T> temp_stack;
	queue<T> temp_queue;
	int length = q.size();
	unsigned int length_temp = q.size();
	int k = 1;
	int counter = 0;
	while(length != 0) 
	{
		for (int i = 0; i < k; i++)
		{
			
			if (length > 0)
			{
				temp_queue.push(q.front());
				q.pop();
				length = length - 1;
			}
		}
		k = k + 1;
		
		if (length > 0)
		{
			for (int i = 0; i < k; i ++)
			{
				
				if (length > 0)
				{	
					counter++;
					temp_stack.push(q.front());
					q.pop();
					length = length - 1;
				}	
									
			}
			for (int i = 0; i < counter; i++)
			{
				temp_queue.push(temp_stack.top());
				temp_stack.pop();
			}	
			counter = 0;
			k = k + 1;
		}
	}	

	
	for(unsigned int i=0; i<length_temp; i++ )
	{
		q.push(temp_queue.front());
		temp_queue.pop();
	} 	 
}

/**
 * @return true if the parameter stack and queue contain only elements of exactly
 *  the same values in exactly the same order; false, otherwise.
 *
 * @note You may assume the stack and queue contain the same number of items!
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in your return statement,
 *      and you may only declare TWO local variables of parametrized type T to use however you wish.
 *   No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be sure to comment your code VERY well.
 */
template <typename T>
bool QuackFun::verifySame(stack<T> & s, queue<T> & q)
{
    bool retval;
    T temp1; // rename me
    T temp2; // rename :)
    
    
    if (temp1 != temp2)
    {
    	retval = false;
    	return retval;
    }
    
    
    
    temp1 = s.top();
    temp2 = q.front();
    s.pop();
    q.pop();		
	retval = verifySame(s,q);
	s.push(temp1);
    q.push(temp2);
    retval = true;
    
    return retval;
}

