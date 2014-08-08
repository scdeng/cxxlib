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
#include <limits.h>
#include <deque>
#include <vector>
#include <queue>
#include <list>
#include <iostream>

using namespace std;

class Digraph;
std::ostream& operator<<(ostream&, const Digraph&);

/*	@brief Directed Graph 
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
		Digraph reverse()const;

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

/*	@brief given a digraph and source(one or more vertices)
 *	compute bfs tree
 */
class BFSDirectedPaths{
	private:
		//markev if visited
		vector<bool> marked;
		//no. of hop from source to this vertex
		vector<int> distTo;
		//breadth first search tree(forest)
		//parent index representation
		vector<int> edgeTo;
		
		/*	@brief check a vertex is a valid or not
		 *	v is valid if v < G.V() and v >= 0
		 */
		bool isValidVertex(int v)const{
			int sz = distTo.size();
			if( v < 0 || v >= sz ){
				return false;
			}
			return true;
		}

		/*	@brief breadth first search to compute bfs tree(forest)
		 *	@param g	digraph
		 *	@param v 	vertex to start	
		 */
		void bfs(const Digraph &g, int v);
		
		/*	@brief breadth first search to compute bfs tree(forest)
		 *	@param g	digraph
		 *	@param sources 	vertices to start
		 *
		 *	@note may be not the shortest path
		 */
		void bfs(const Digraph &g, const vector<int> &sources);


	public:

		/*	@brief constructor with a Digraph and a source s
		 *	compute breadth first search tree(forest) from s
		 *	@param dg	digraph 
		 *	@param s	source vertex
		 */
		BFSDirectedPaths(const Digraph &dg, int s);
	
		/*	@brief compute bfs forest start from a vector of sources
		 *	@param dg	digraph
		 *	@param sources	sources 
		 */
		BFSDirectedPaths(const Digraph &dg, const vector<int> &sources);

		/*	@brief is reachable
		 *		true if there exists a path from source(s) to v
		 *		false otherwise
		 *	@param v	vertex 
		 *				if v is not a valid vertex return false
		 */
		bool reachable(int v) const ;
		
		/*	@brief return a path from s to vertex v
		 *	@param v	vertex
		 */
		deque<int> pathTo(int v);

};

/*	@brief compute a DAG's topological order
 *		depth first search based
 */
class DFSOrder{
	private:
		//visited marks
		vector<bool> marked;
		//order of call a vertex
		//it's dependent on graph representation
		deque<int> __vertexCallOrder;
		//return order
		deque<int> __preOrder;
		//reverse of returning order
		deque<int> __reverseOrder;

		/*	@brief depth first search
		 */
		void dfs(const Digraph &dg, int v);
	
	public:
		/*	@brief topological sort of a Digraph
		 *	@param dg	Digraph
		 */
		DFSOrder(const Digraph &dg);
			
		/*	@brief return a const reference of deque invoke order
		 */
		deque<int> invokeOrder() const {
			return __vertexCallOrder;
		}
		/*	@brief return a const reference of deque returning order
		 */
		deque<int> preOrder() const {
			return __preOrder;
		}
		/*	@brief return a const reference deque of reverse returning order
		 */
		deque<int> reverseOrder() const {
			return __reverseOrder;
		}
};

/*	@brief compute topological order
 */
class TopologicalSort{
	private:
		//topological order
		deque<int> topOrder;
		bool dag;

	public:

		/*	@brief constructor with a Digraph
		 *		if Digraph is a DAG topological order is an empty deque
		 *		dag is false
		 *		else
		 *			dag is true
		 */
		TopologicalSort(const Digraph &dg){
			DirectedCycle cyc(dg);
			if( cyc.hasCycle() ){
				topOrder = deque<int>();
				dag = false;
			}else{
				DFSOrder order(dg);
				topOrder = order.reverseOrder();
				dag = true;
			}
		}
	
		/*	@brief check a digraph is a Directed acyclic graph
		 */
		bool isDAG() const {
			return dag;
		}

		/*	@brief if digraph is a DAG
		 *		return topological order
		 *		else
		 *			return an empty deque
		 */
		deque<int> topologicalOrder() const {
			return topOrder;
		}
};

/*	@brief Kosaraju Strongly Connected Component algorithm implementation
 */
class SCC{
	private:
		vector<bool> marked;
		vector<int> __id;
		int __count;

		/*	@brief check if a vertex is valid
		 */
		bool isValidVertex(int v) const {
			int sz = __id.size();
			return v < sz && v >= 0;
		}
	
		/*	@brief depth first search to compute __id
		 */
		void dfs(const Digraph &dg, int v);

	public:
		
		/*	@brief construct a SCC with a graph and compute 
		 *		strongly connected component
		 *	@param dg	Digraph
		 */
		SCC(const Digraph &dg);
		
		/*	@brief check if given two vertices u and v are strongly connected
		 *	@param	u	vertex
		 *	@param 	v	vertex
		 *	if one of these vertices is invalid return false;
		 */
		bool stronglyConnected(int u, int v){
			if( isValidVertex(u) && isValidVertex(v) ){
				return __id[u] == __id[v];
			}else{
				return false;
			}	
		}
		
		vector<deque<int> > components() const{
			vector<deque<int> > comp(__count);
			int sz = __id.size();
			for(int i=0; i< sz; ++i){
				comp[__id[i]].push_back(i);
			}
			return comp;
		}
		/*	@brief how many strongly connected components
		 */
		int numOfComponents() const {
			return __count;
		}
};


#endif
