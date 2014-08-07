/*
 * =====================================================================================
 *
 *       Filename:  digraph.h
 *
 *    Description:  directed graph implementation
 *
 *        Version:  1.0
 *        Created:  08/07/2014 07:26:41 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */

#ifndef DIGRAPH_H
#define DIGRAPH_H
#include <cassert>
#include <deque>
#include <vector>
#include <list>
#include <iostream>
using namespace std;

class Digraph;
std::ostream& operator<<(ostream&, const Digraph&);

/*	@brief Directed Graph 
 *
 */
class Digraph{
	friend std::ostream& operator<<(ostream&, const Digraph&);

	private:
		//no. of vertices
		int __V;
		//no. of directed edges
		int __E;
		//adjacent list
		vector<list<int> > __adj;
	
		/*	@brief 	check a given vertex is less than number of 
		 *			vertex and greater than or equal to 0
		 *	@return return true if v is a valid vertex in this graph
		 *			return false otherwise
		 */
		bool isValidVertex(int v)const{
			if( v < 0 || v >= __V){
				return false;
			}
			return true;
		}

	public:

		/*	@brief construt a digrap with N vertices and no adge
		 */
		Digraph(int N){
			__V = N;
			__E = 0;
			__adj = vector<list<int> >(N);
		}

		/*	@brief copy construtor
		 *			deep copy
		 */
		Digraph(const Digraph &G);
	
		/*	@brief return a directed graph of given graph
		 *	@param dg	a directed graph
		 */
		Digraph reverse();

		/*	@brief constuct a directed graph from an input stream
		 *	@param is  	input stream
		 */
		Digraph(istream &is);

		/*	@brief 	add an edge from u to v
		 *	@param	edge from
		 *	@param 	edge to
		 */
		void addEdge(int u, int v){
			//add edge from u to v
			//add to u's adjacent list
			assert ( isValidVertex(u) && isValidVertex(v) );
			__adj[u].push_back(v);
			//increase no. of edges by 1;
			++__E;
		}
		
		/*	@brief 	return vertex v's adjacent list
		 */
		const list<int>& adj(int v)const{
			assert ( isValidVertex(v) );
			return __adj[v];
		}

		/*	@brief return number of vertices
		 */
		int V() const {
			return __V;
		}
		/*	@brief return number of edges
		 */
		int E() const {
			return __E;
		}
};

/*	@brief Directed DFS detect reachability
 *	
 */
class DirectedDFS{
	private:
		//if vertex v is reachable
		//then marked[v] is true
		vector<bool> marked;
		
		//dfs tree
		//parent index representation
		//vertex v's parent is edgeTo[v]
		vector<int> edgeTo;
		
		//source
		int __s;

		/*	@brief depth first search a DG
		 */
		void dfs(const Digraph &dg, int s);

	public:
		/*	@brief constructor with a graph and a source s
		 *	@param dg	graph
		 *	@param s	source 
		 */
		DirectedDFS(const Digraph &dg, int s);
		
		/*	@brief return a path to vertex v
		 *	@param v	path from s to v
		 */
		deque<int> pathTo(int v);
	
		/*	@brief check vertex v is reachable from source
		 */
		bool reachable(int v) const {
			return marked[v];
		}
		

};

/*	@brief directed cycle
 */
class DirectedCycle{
	private:
		//vector
		vector<bool> marked;
		//v is searched when onStack[v] is true
		vector<bool> onStack;
		//return cycle
		deque<int> cyc;
		//dfs search tree
		//parent index representation
		vector<int> edgeTo;
		
		/*	@brief depth first search to detect cycle
		 */
		void dfs(const Digraph &dg, int v);

	public:
		/*	@brief construct a Directed Cycle objec with Digraph
		 *	composite design pattern
		 */
		DirectedCycle(const Digraph &dg);

		/*	@brief has a cycle in this DG
		 */
		bool hasCycle(){
			return (cyc.size() != 0);
		}
		/*	@brief return cycle
		 *			if there exists no cycle
		 *			return a empty cycle
		 */
		deque<int> cycle() const {
			return cyc;
		}
};

#endif
