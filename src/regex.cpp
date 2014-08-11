/*
 * =====================================================================================
 *
 *       Filename:  regex.cpp
 *
 *    Description:  substring search & regular expression implementation
 *    		1. DFA
 *    		2. NFA	regular expression 
 *    			1. cancatenation	eg. AB
 *    			2. closure  		eg. A*
 *    			3. or (parentheses) eg. (AC|DF)
 *
 *        Version:  1.0
 *        Created:  08/11/2014 09:21:35 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */


#include "regex.h"

/*	@brief construct DFA with pattern 
*/
DFA::DFA( string pt ) {
	//initialize member
	pat = pt;
	int LEN = pt.length();
	dfa = vector<vector<int> >( R, vector<int>(LEN, 0) );

	//construct dfa
	//colum 0 is OK, which means that 
	//all read goes to state 0 except read pat[0]
	dfa[pat[0]][0] = 1;
	//update column 1...LEN-1
	//x is the state which reads pattern [1...i-1]
	for(int x = 0, j=1; j<LEN; ++j){
		//compute dfa[][j]
		//copy dfa[][x] to dfa[][j] and then
		for( int c=0; c<R; ++c){
			dfa[c][j] = dfa[c][x];
		}
		//update it match state
		dfa[pat[j]][j] = j+1;
		//update restart state
		x = dfa[pat[j]][x];
	}
}

/*	@brief search pattern in txt
 *		if search hit return start index
 *		return txt.length() otherwise
 */
int DFA::search(string txt){
	//i is index of txt
	int i = 0;
	int N = txt.length();
	//j is current state
	int j = 0;
	int M = pat.length();
	//simulate dfa
	for( ; i<N && j<M; ++i ){
		if( txt[i] == pat[j] ){
			++j;
		}else{
			j = dfa[txt[i]][j];
		}
	}
	//search hit
	if( j == M ){
		return i-M;
	}else{
		//search miss
		return N;
	}
}





/*	@brief construct a NFA recoginizer of regex
 *		regex 
 *		1. cancatenation	eg. AB 
 *		2. closure	eg. A* 
 *		2. or(with parentheses)	eg. (AC|AB) 
 */
NFA::NFA( string reg ):regex(reg), M(reg.length()),
	epsilonTrans(Digraph(reg.length()+1)){

		stack<int> ops;
		for(int i=0; i<M; ++i){
			//left parentheses
			int lp = i;
			if( reg[i] == '(' || reg[i] == '|'){
				ops.push(i);
			}else if( reg[i] == ')' ){
				int opOR = ops.top();
				ops.pop();
				if( reg[opOR] == '|' ){
					lp = ops.top();
					ops.pop();
					epsilonTrans.addEdge(lp, opOR+1);
					epsilonTrans.addEdge(opOR, i);
				}else{
					lp = opOR;
				}
			}
			if( i < M-1 && reg[i+1] == '*' ){
				epsilonTrans.addEdge(lp, i+1);
				epsilonTrans.addEdge(i+1, lp);
			}
			if( reg[i] == '(' || reg[i] == ')' || reg[i] == '*' ){
				epsilonTrans.addEdge(i,i+1);
			}
		}
	}

/*	@brief recoginize a text
 *		if matches return true
 *		return false otherwise
 */
bool NFA::recoginize(string txt) const {
	//state is at some state s
	//your can reach some else states by epsilon transitions
	vector<int> states;
	
	//initialize states
	DirectedDFS *dfs = new DirectedDFS(epsilonTrans, 0);
	for(int v=0; v<epsilonTrans.V(); ++v){
		if( dfs->reachable(v) ){
			states.push_back(v);
		}
	}

	//recoginize each character a time
	for(size_t i=0; i<txt.length(); ++i){
		//read txt[i] you can move to next state for all state in states
		vector<int> matches;
		for(size_t index=0; index<states.size(); ++index){
			int v = states[index];
			if( regex[ v ] == txt[i] || regex[ v ] == '.' ){
				matches.push_back( v + 1 );
			}
		}

		delete dfs;
		if( matches.size() != 0 ){
			dfs = new DirectedDFS(epsilonTrans, matches);
		}else{
			//no matches
			//matches next character at begining of nfa 
			dfs = new DirectedDFS(epsilonTrans, 0);
		}
		//update next receivable states
		states.clear();
		for(int v=0; v<epsilonTrans.V(); ++v){
			if( dfs->reachable(v) ){
				states.push_back(v);
			}
		}
		//states are next reachable states
	}
	//if one of state in statets is acception state
	//search hit
	int numOfStates = states.size();
	for(int v=0; v<numOfStates; ++v){
		if( states[v] == M){
			return true;
		}
	}
	//delete dfs
	delete dfs;
	return false;
}
















