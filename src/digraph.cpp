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
Digraph Digraph::reverse(){
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





