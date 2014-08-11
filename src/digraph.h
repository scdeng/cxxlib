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
#include <set>
#include <queue>
#include <list>
#include <iostream>
#include <cstdlib>
#include <cfloat>
using namespace std;

class Digraph;
std::ostream& operator<<(ostream&, const Digraph&);
class DirectedWeightedEdge;
class EdgeWeightedDigraph;

/*	@brief overload operator<<
*/
std::ostream& operator<<(ostream &os, const DirectedWeightedEdge &e);

/*	@brief overload operator<<
*/
std::ostream& operator<<(ostream &os, const EdgeWeightedDigraph &G);



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
		set<int> srcs;

		/*	@brief depth first search a DG
		 */
		void dfs(const Digraph &dg, int s);

	public:
		/*	@brief constructor with a graph and a source s
		 *	@param dg	graph
		 *	@param s	source 
		 */
		DirectedDFS(const Digraph &dg, int s);

		/*	@brief check reachability from sources
		 */
		DirectedDFS(const Digraph &dg, const vector<int> &sources);

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


//================Edge weighted Digraph=================//

class DirectedWeightedEdge{
	
	friend std::ostream& operator<<(ostream &os, const DirectedWeightedEdge &e);
	private:
		//start vertex
		int _u;
		//end vertex
		int _v;
		//weight of this edge
		double wt;

	public:
		/*	@brief default constructor
		 */
		DirectedWeightedEdge(): _u(-1), _v(-1), wt(DBL_MAX) { }
		
		/*	@brief construct with u->v with weight w
		 */
		DirectedWeightedEdge(int u, int v, double w):
			_u(u), _v(v), wt(w) { }

		/*	@brief return start vertex
		 */
		int from() const{
			return _u;
		}
	
		/*	@brief return end vertex
		 */
		int to() const{
			return _v;
		}
		
		/*	@brief return weight of edge
		 */
		double weight() const {
			return wt;
		}
};

/*	@brief edge weighted Digraph(EWD for short)
 */
class EdgeWeightedDigraph{
	

	friend std::ostream& operator<<(ostream &os, const EdgeWeightedDigraph &G);
	private:
		typedef DirectedWeightedEdge Edge;
		//no. of vertices
		int _V;
		//no. of edges
		int _E;
		//adjacent list
		vector<list<Edge> > _adj;
		
		/*	@brief check if a vertex is Valid for this EWD
		 */
		bool check_vertex(int v) const {
			if( v < _V && v >= 0){
				return true;
			}else{
				return false;
			}
		}


	public:
		/*	@brief construct a EWD vertices with no edges
		 */
		EdgeWeightedDigraph(int N):
			_V(N), _E(0), _adj( vector<list<Edge> >(N) ) { }

		/*	@brief construct a EWD with input stream
		 */
		EdgeWeightedDigraph(istream &is){
			int V;
			int E;
			is >> V;
			is >> E;
			_V = V;
			_E = 0;
			_adj = vector<list<Edge> >(V);
			int u, v;
			double w;
			while( is >> u && is >> v && is >> w){
				addEdge(u,v,w);
			}
		}

		/*	@brief copy constructor
		 */
		EdgeWeightedDigraph(const EdgeWeightedDigraph &ewd):
			_V(ewd._V), _E(ewd._E), _adj(ewd._adj){ }
	
		/*	@brief assignment operator
		 */
		EdgeWeightedDigraph& operator=(const EdgeWeightedDigraph &that){
			_V = that._V;
			_E = that._E;
			_adj = that._adj;
			return *this;
		}
		
		/*	@brief add an edge to EWD with no duplicate edge detection
		*/
		void addEdge(const Edge &e) {
			//get e's vertices
			int u = e.from();
			int v = e.to();
			//check if vertex is valid
			if ( !check_vertex(u) || !check_vertex(v) ){
				std::cerr<<"you made a mistake..."<<std::endl;
				std::cerr<<"please check your edge is correct..."<<std::endl;
				return ;
			}
			//push e to u's adjacent list
			_adj[u].push_back(e);
			++_E;
		}

		/*	@brief add an edge with two vertices and a weight
		 */
		void addEdge(int u, int v, double w){
			//construct an edge
			Edge e(u,v,w);
			addEdge(e);
		}

		/*	@brief return no. of vertices
		*/
		int V() const {
			return _V;
		}

		/*	@brief return no. of edges
		*/
		int E() const {
			return _E;
		}


		/*	@brief return a const reference of v's adjacent list
		*/
		const list<Edge> & adj(int v)const{
			if( !check_vertex(v) ){
				std::cerr<<"access non-vertex's adjacent..." <<std::endl;
				std::cerr<<"oops!!! crashed..."<<std::endl;
				exit(1);
			}
			return _adj[v];
		}

		/*	@brief check if EWD is empty
		 */
		bool empty(){
			return _V == 0;
		}
};

class EdgeWeightedDirectedCycle{

	private:
		typedef EdgeWeightedDigraph EWD;
		typedef DirectedWeightedEdge Edge;
		//vector
		vector<bool> marked;
		//v is searched when onStack[v] is true
		vector<bool> onStack;
		//return cycle
		deque<Edge> cyc;
		//dfs search tree
		//parent index representation
		vector<Edge> edgeTo;

		/*	@brief depth first search to detect cycle
		 *
		 */
		void dfs(const EWD &dg, int v){
			marked[v] = true;
			onStack[v] = true;
			list<Edge>::const_iterator it;
			for( it = (dg.adj(v)).begin(); it != dg.adj(v).end(); ++it){
				//there exists a cycle
				if( hasCycle() ){
					return ;
				}
				//to vertex	v->w
				int w = it->to();
				// w is not visited
				// recursively visit it
				if( !marked[w] ){
					edgeTo[w] = *it;
					dfs(dg, w);
				}else{
					//cycle detected
					if( onStack[w] ){
						cyc.push_front(*it);
						int x = it->from();
						while( edgeTo[x].from() != w ){
							cyc.push_front(edgeTo[x]);
							x = edgeTo[x].from();
						}
						cyc.push_front(edgeTo[x]);
					}
				}
			}
			//v has been searched
			onStack[v] = false;
		}

	public:

		/*	@brief construct a Directed Cycle objec with Digraph
		 *	composite design pattern
		 */
		EdgeWeightedDirectedCycle(const EWD &dg){
			//initialize members
			marked = vector<bool>(dg.V(), false);
			onStack = vector<bool>(dg.V(), false);
			cyc = deque<Edge>();
			edgeTo = vector<Edge>(dg.V());
			for(int v=0; v < dg.V(); ++v){
				if( !marked[v] ){
					dfs(dg, v);
				}
			}

		}

		/*	@brief has a cycle in this DG
		*/
		bool hasCycle(){
			return (cyc.size() != 0);
		}
		/*	@brief return cycle
		 *			if there exists no cycle
		 *			return a empty cycle
		 */
		const deque<Edge>& cycle() const {
			return cyc;
		}
};



#endif
