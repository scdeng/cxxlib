/*
 * =====================================================================================
 *
 *       Filename:  digraph.cpp
 *
 *    Description:  directed graph implementation
 *
 *        Version:  1.0
 *        Created:  08/07/2014 09:55:42 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */

#include "digraph.h"


//====================Digraph====================//
Digraph::Digraph(const Digraph &G){
	__V = G.V();
	__adj = vector<list<int> >(G.V());
	for(int v=0; v<G.V(); ++v){
		for(list<int>::const_iterator it=G.__adj[v].begin();
					it != G.__adj[v].end(); ++it){
			addEdge(v,*it);	
		}
	}
}

std::ostream& operator<<(std::ostream &os, const Digraph &dg){
	os <<"===============Digraph===================" << std::endl;
	os << dg.V() << " vertice\t" << dg.E() << " edges" <<std::endl;
	for(int v=0; v<dg.__V; ++v){
		os << "vertex " << v << ":\t";
		for(list<int>::const_iterator it = dg.__adj[v].begin(); 
					it != dg.__adj[v].end(); ++it){
			os << *it << " ";
		}
		os << std::endl;
	}
	os <<"===============end of Digraph====================" << std::endl;
	return os;
}


/*	@brief return a directed graph of given graph
 *	@param dg	a directed graph
 */
Digraph Digraph::reverse()const{
	Digraph G(__V);
	for(int v=0; v<__V; ++v){
		for(list<int>::const_iterator it = __adj[v].begin();
					it != __adj[v].end(); ++it){
			G.addEdge(*it,v);
		}

	}
	return G;
}

Digraph::Digraph(istream &is){
	int V;
	int E;
	is >> V;
	is >> E;
	__V = V;
	__adj = vector<list<int> >(V);

	__E = 0;
	int u;
	int v;
	while (is >> u && is >> v){
		addEdge(u,v);
	}
}
//====================Digraph====================//


//====================DFS path====================//
/*	@brief construct DFS
 */
DirectedDFS::DirectedDFS(const Digraph &dg, int s){
	marked = vector<bool>(dg.V(), false);
	edgeTo = vector<int>(dg.V());
	__s = s;
	for(unsigned i=0; i<edgeTo.size(); ++i){
		edgeTo[i] = i;
	}
	dfs(dg,s);
}

/*	@brief depth first search a DG
*/
void DirectedDFS::dfs(const Digraph &dg, int v){
	marked[v] = true;
	list<int>::const_iterator it;
	for(it = (dg.adj(v)).begin(); it != (dg.adj(v)).end(); ++it){
		if( !marked[*it] ){
			edgeTo[*it] = v;
			dfs(dg,*it);
		}
	}
}

deque<int> DirectedDFS::pathTo(int v){
	deque<int> path;
	while( v != __s ){
		path.push_front(v);
		v = edgeTo[v];
	}
	path.push_front(__s);
	return path;
}
//====================DFS path====================//


//====================directed cycle================//
/*	@brief depth first search to detect cycle
 *
 */
void DirectedCycle::dfs(const Digraph &dg, int v){
	marked[v] = true;
	onStack[v] = true;
	list<int>::const_iterator it;
	for( it = (dg.adj(v)).begin(); it != dg.adj(v).end(); ++it){
		//there exists a cycle
		if( hasCycle() ){
			return ;
		}
		if( !marked[*it] ){
			edgeTo[*it] = v;
			dfs(dg, *it);
		}else{
			//cycle detected
			if( onStack[*it] ){
				for(int u = v; u != *it; u = edgeTo[u] ){
					cyc.push_front(u);
				}
				cyc.push_front(*it);
				cyc.push_front(v);
			}
		}
	}
	//v has been searched
	onStack[v] = false;
}
/*	@brief construct a Directed Cycle objec with Digraph
 *	composite design pattern
 */
DirectedCycle::DirectedCycle(const Digraph &dg){
	marked = vector<bool>(dg.V(), false);
	onStack = vector<bool>(dg.V(), false);
	cyc = deque<int>();
	edgeTo = vector<int>(dg.V());
	for(int v=0; v < dg.V(); ++v){
		if( !marked[v] ){
			dfs(dg, v);
		}
	}
}
//====================directed cycle====================//


//====================BFS directed path====================//

/*	@brief breadth first search to compute bfs tree(forest)
 *	@param g	digraph
 *	@param v 	vertex to start	
 */
void BFSDirectedPaths::bfs(const Digraph &g, int v){
	queue<int> q;
	marked[v] = true;
	distTo[v] = 0;
	edgeTo[v] = v;
	q.push(v);
	while( !q.empty() ){
		int w = q.front();
		list<int>::const_iterator it;
		for(it = g.adj(w).begin(); it != g.adj(w).end(); ++it){
			if( !marked[*it] ){
				q.push(*it);
				marked[*it] = true;
				edgeTo[*it] = w;
				distTo[*it] = distTo[w] + 1;
			}
		}
		q.pop();
	}
}

/*	@brief breadth first search to compute bfs tree(forest)
 *	@param g	digraph
 *	@param sources 	vertices to start
 *
 *	@note may be not the shortest path
 */
void BFSDirectedPaths::bfs(const Digraph &g, const vector<int> &sources){
	queue<int> q;
	int sz = sources.size();
	for(int i=0; i<sz; ++i){
		int v = sources[i];
		marked[v] = true;
		distTo[v] = 0;
		edgeTo[v] = v;
		q.push(v);
	}
	while( !q.empty() ){
		int v = q.front();
		list<int>::const_iterator it;
		for(it = g.adj(v).begin(); it != g.adj(v).end(); ++it){
			int w = *it;
			if( !marked[w] ){
				marked[w] = true;
				distTo[w] = distTo[v] + 1;
				edgeTo[w] = v;
				q.push(w);
			}
		}
		//deque
		q.pop();
	}
}



/*	@brief constructor with a Digraph and a source s
 *	compute breadth first search tree(forest) from s
 *	@param dg	digraph 
 *	@param s	source vertex
 */
BFSDirectedPaths::BFSDirectedPaths(const Digraph &dg, int s){
	//initialize
	marked = vector<bool>(dg.V(), false);
	distTo = vector<int>( dg.V() );
	edgeTo = vector<int>( dg.V() );
	for(int i=0; i<dg.V(); ++i){
		distTo[i] = INT_MAX;
	}
	//breadth first search
	bfs(dg, s);
}

/*	@brief compute bfs forest start from a vector of sources
 *	@param dg	digraph
 *	@param sources	sources 
 */
BFSDirectedPaths::BFSDirectedPaths(const Digraph &dg, const vector<int> &sources){
	//initialize
	marked = vector<bool>(dg.V(), false);
	distTo = vector<int>( dg.V() );
	edgeTo = vector<int>( dg.V() );
	for(int i=0; i<dg.V(); ++i){
		distTo[i] = INT_MAX;
	}
	bfs(dg, sources);
}

/*	@brief is reachable
 *		true if there exists a path from source(s) to v
 *		false otherwise
 *	@param v	vertex 
 *				if v is not a valid vertex return false
 */
bool BFSDirectedPaths::reachable(int v) const {
	if( !isValidVertex(v) ){
		return false;
	}
	return distTo[v] < INT_MAX;
}

/*	@brief return a path from s to vertex v
 *	@param v	vertex
 */
deque<int> BFSDirectedPaths::pathTo(int v){
	deque<int> dc;
	if( !isValidVertex(v) ){
		return dc;
	}
	while( distTo[v] != 0 ){
		dc.push_front(v);
		v = edgeTo[v];
	}
	dc.push_front(v);
	return dc;
}
//====================BFS directed path====================//


//===========================DFS Order===========================//
/*	@brief depth first search
*/
void DFSOrder::dfs(const Digraph &dg, int v){
	marked[v] = true;
	__vertexCallOrder.push_back(v);
	list<int>::const_iterator it;
	for( it = dg.adj(v).begin(); it != dg.adj(v).end(); ++it){
		int w = *it;
		if( !marked[w] ){
			dfs(dg,w);
		}
	}
	__preOrder.push_back(v);
	__reverseOrder.push_front(v);
}

/*	@brief topological sort of a Digraph
 *	@param dg	Digraph
 */
DFSOrder::DFSOrder(const Digraph &dg){
	marked = vector<bool>(dg.V(), false);
	__vertexCallOrder = deque<int>();
	__preOrder = deque<int>();
	__reverseOrder = deque<int>();

	//depth first search
	for(int v=0; v<dg.V(); ++v){
		if( !marked[v] ){
			dfs(dg,v);
		}
	}
}
//===========================DFS Order===========================//


//===========kosaraju strongly connected componetn===========//
/*	@brief depth first search to compute __id
*/
void SCC::dfs(const Digraph &dg, int v){
	marked[v] = true;
	__id[v] = __count;
	list<int>::const_iterator it;
	for( it = dg.adj(v).begin(); it != dg.adj(v).end(); ++it){
		int w = *it;
		if(  !marked[w] ){
			dfs(dg, w);
		}
	}
}

/*	@brief construct a SCC with a graph and compute 
 *		strongly connected component
 *	@param dg	Digraph
 */
SCC::SCC(const Digraph &dg){
	//initialize private menber
	marked = vector<bool>(dg.V(),false);
	__id = vector<int>(dg.V());
	__count = 0;
	for(int i=0; i<dg.V(); ++i){
		__id[i] = i;
	}

	//dg's reverse graph
	const Digraph rdg = dg.reverse();
	//rdg's order
	DFSOrder order(rdg);
	//reverse order of dg's reverse graph
	deque<int> reverseOrder = order.reverseOrder();
	//depth first searh in reverseOrder 
	__count = 0;
	int num = reverseOrder.size();
	for(int i=0; i<num; ++i){
		int v = reverseOrder[i];
		if( !marked[v] ){
			dfs(dg,v);
			//search one strongly connected component
			++__count;
		}
	}
}
//===========kosaraju strongly connected componetn===========//

