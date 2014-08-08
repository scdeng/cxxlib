/*
 * =====================================================================================
 *
 *       Filename:  graph.cpp
 *
 *    Description:  graph implementation
 *
 *        Version:  1.0
 *        Created:  08/05/2014 05:30:03 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */

#include "graph.h"

Graph::Graph(istream &is){
	int V;
	int E;
	is >> V;
	is >> E;
	_v = V;
	adj = vector<list<int> >(V);

	_e = 0;
//	for(int i=0; i<V; ++i){
//		adj.push_back(list<int>());
//	}

	int u;
	int v;
	while (is >> u && is >> v){
		addEdge(u,v);
	}
}
//check v 
bool Graph::check_vertex(int v)const{
	if( v >= _v || v < 0) {
		std::cerr<< "vertex index out of bounds..." << endl;
		return false;
	}
	return true;
}

//
void DepthFirstPaths::dfs(const Graph &g, int v){
	__count++;
	marked[v] = true;
	list<int> adj = g.adjacent(v);
	for(list<int>::iterator it = adj.begin();
				it != adj.end(); ++it){
		if( !marked[*it] ){
			edgeTo[*it] = v;
			dfs(g, *it);
		}
	}
}

/*	@brief return a path fron s(source) to v
 */
deque<int> DepthFirstPaths::pathTo(int v)const{
	deque<int> path;
	if( !hasPathTo(v) ){
		return path;
	}
	while( v != __s){
		path.push_front(v);
		v = edgeTo[v];
	}
	path.push_front(__s);
	return path;
}

#ifdef DEBUG_PRINT
ostream& operator<<(ostream &os, Graph &g){
	os << g.V() << " verices and " << g.E() << " edges" << endl;
	for(int i=0; i<g._v; i++){
		os << i << " : " ;
		for(list<int>::iterator it = (g.adj[i]).begin();
					it != (g.adj[i]).end(); ++it){
			os << *it << " ";
		}
		os << endl;
	}
	return os;
}

ostream& operator<<( ostream &os, DepthFirstPaths &dfs){
	os << "marked is: " << endl;
	for(unsigned i=0; i<dfs.marked.size(); ++i){
		os << (dfs.marked)[i] << ", ";
	}
	os << endl;
	os << "count is: " << dfs.__count << endl;
	return os;
}



ostream& operator<<(ostream &os, BreadthFirstPaths &bfs){
	os << "marked is: " << endl;
	for(unsigned i=0; i<bfs.marked.size(); ++i){
		os << (bfs.marked)[i] << ", ";
	}
	os << endl;
	return os;
}
#endif

/*	@brief breadth first search to construct a search tree
 */
void BreadthFirstPaths::bfs(const Graph &g, int s){
	queue<int> q;
	q.push(s);
	marked[s] = true;
	edgeTo[s] = s;
	distTo[s] = 0;
	while( !q.empty() ){
		int v = q.front();
		//search v's adjacents
		list<int> L = g.adjacent(v);
		for(list<int>::const_iterator it = L.begin(); 
					it != L.end(); ++it){
			int w = *it;
			if( !marked[w] ){
				marked[w] = true;
				distTo[w] = distTo[v] + 1;
				edgeTo[w] = v;
				q.push(w);
			}
		}
		//pop a vertex whose adjacents are searched
		q.pop();
	}
}

/*	@brief breadth first search to construct a search forest
 */
void BreadthFirstPaths::bfs(const Graph &g, const vector<int> &sources){
	queue<int> q;
	//enque all sources
	for(unsigned i=0; i<sources.size(); ++i){
		q.push( sources[i] );
		marked[ sources[i] ] = true;
		distTo[ sources[i] ] = 0;
	}
	while( !q.empty() ){
		int v = q.front();
		//search v's adjacent
		list<int> L = g.adjacent(v);
		for(list<int>::const_iterator it = L.begin(); 
					it != L.end(); ++it){
			int w = *it;
			if( !marked[w] ){
				marked[w] = true;
				distTo[w] = distTo[v] + 1;
				edgeTo[w] = v;
				q.push(w);
			}
		}
		//pop v
		q.pop();
	}

}
/*	@brief breadth first search path from s to v
 */
deque<int> BreadthFirstPaths::pathTo(int v)const{
	deque<int> path;
	if( !hasPathTo(v) ){
		return path;
	}
	while( distTo[v] != 0 ){
		path.push_front(v);
		v = edgeTo[v];
	}
	path.push_front(v);
	return path;
}

/*	@brief depth first search to compute connected component
 */
void CC::dfs(const Graph &g, int v){
	marked[v] = true;
	__id[v] = __count;
	++(sz[__count]);
	list<int> L = g.adjacent(v);
	for(list<int>::iterator it = L.begin(); it != L.end(); ++it){
		if( !marked[*it] ){
			dfs(g,*it);
		}
	}
}
/*	@brief Connect component constructor
 */
CC::CC(const Graph &g){
	marked = vector<bool>(g.V(), false);
	__id = vector<int>(g.V());
	sz = vector<int>(g.V());
	__count = 0;
	for( int w=0; w<g.V(); ++w){
		if( !marked[w] ){
			dfs(g,w);	
			__count++;
		}
	}
}

