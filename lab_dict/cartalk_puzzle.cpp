/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of "StringTriples" (a typedef'd std::tuple, see top of 
 * cartalk_puzzle.h). Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector< StringTriple > cartalk_puzzle(PronounceDict d,
                                      const string& word_list_fname)
{
    /* Your code goes here! */

	vector< StringTriple > final;
	StringTriple st;
//	unsigned int i = 0;
	ifstream words(word_list_fname);
	string word;
	if(words.is_open())
	{
		while (getline(words,word))
		{
			if (word.length() > 1)
			{
				string temp1 = word.substr(1);
				string temp2 = word[0] + word.substr(2);
				bool val;
				val = /*PronounceDict::*/d.homophones(temp1, temp2);
				if (val == 1)
				{
					//final[i]->first = word;
					st = make_tuple(word, temp1, temp2);
					final.push_back(st);	
				}
			}
		}
	}
	
	
	if (final.empty())
		return vector< StringTriple >();
	else
		return final;
}		
