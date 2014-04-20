/**
 * @file word_counter.cpp
 * Implementation of the WordFreq class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Spring 2012
 */

using std::vector;
using std::pair;
using std::string;
using std::ifstream;
using std::istringstream;
using std::cout;
using std::endl;

template <template <class K, class V> class HT>
WordFreq<HT>::WordFreq( const string & infile ) : filename( infile ) { /* nothing */ }

template <template <class K, class V> class HT>
vector< pair<string, int> > WordFreq<HT>::getWords( int threshold ) const {
    TextFile infile( filename );
    vector< pair<string, int> > ret;
    
	HT<string, int> temp_table(256);
    
    while(infile.good())
    {
    	temp_table[infile.getNextWord()]++;
	}
    
//fill the ret vector to store the words that have to be returned    
        
    typename HT<string, int>::iterator i;
	for(i = temp_table.begin(); i != temp_table.end(); i++) 
	{
		if(i->second >= threshold)
		{
			ret.push_back(*i);
		}
	}		
	return ret;
}
