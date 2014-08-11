/*
 * =====================================================================================
 *
 *       Filename:  regex.h
 *
 *    Description:  pattern search
 *    		1. DFA for substring search
 *    		2. NFA for regular expression search
 *
 *        Version:  1.0
 *        Created:  08/11/2014 03:08:19 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */
#ifndef PATTERN_SEARCH_H
#define PATTERN_SEARCH_H
#include <vector>
#include <stack>
#include <string>
#include "digraph.h"
using namespace std;
const int R = 256;

/*	@brief DFA for substring search
 *		only ascii character string works
 */
class DFA{
	
	private:
		//string of pattern
		string pat;
		//dfa[i][j] = k
		//state j read a i your should go to state k
		vector<vector<int> > dfa;

	public:

		
		/*	@brief construct DFA with pattern 
		 */
		DFA( string pt ) ;
		
		/*	@brief search pattern in txt
		 *		if search hit return start index
		 *		return txt.length() otherwise
		 */
		int search(string txt);

		string pattern()const{
			return pat;
		}

};

class NFA{
	private:
		//regular expresion
		string regex;
		//no. of states
		int M;
		//epsilon transition graph
		Digraph epsilonTrans;

	public:

		/*	@brief construct a NFA recoginizer of regex
		 *		regex 
		 *		1. cancatenation	eg. AB 
		 *		2. closure	eg. A* 
		 *		2. or(with parentheses)	eg. (AC|AB) 
		 */
		NFA( string reg );

		/*	@brief recoginize a text
		 *		if matches return true
		 *		return false otherwise
		 */
		bool recoginize(string txt) const ;

		/*	@brief return regular expression
		 */
		string pattern() const {
			return regex;
		}
		
		/*	@brief return epsilon transition graph
		 */
		const Digraph& epsilonTransition() const {
			return epsilonTrans;
		}
};

#endif

