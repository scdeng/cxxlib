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
bool Graph::check_vertex(int v){

	if( v >= _v || v < 0) {
		std::cerr<< "vertex index out of bounds..." << endl;
		return false;
	}
	return true;
}


void DepthFirstPaths::dfs(Graph &g, int v){
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
//return a path from s to v
//depth first search path
deque<int> DepthFirstPaths::pathTo(int v){
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

//breadth first search
void BreadthFirstPaths::bfs(Graph &g, int s){
	queue<int> q;
	q.push(s);
	marked[s] = true;
	edgeTo[s] = s;
	distTo[s] = 0;
	while( !q.empty() ){
		int v = q.front();
		list<int> L = g.adjacent(v);
		for(list<int>::iterator it = L.begin(); 
					it != L.end(); ++it){
			if( !marked[*it] ){
				marked[*it] = true;
				distTo[*it] = distTo[v] + 1;
				edgeTo[*it] = v;
				q.push(*it);
			}
		}
		q.pop();
	}
}


void BreadthFirstPaths::bfs(Graph &g, const vector<int> &sources){
	queue<int> q;
	for(unsigned i=0; i<sources.size(); ++i){
		q.push( sources[i] );
		marked[ sources[i] ] = true;
		distTo[ sources[i] ] = 0;
	}
	while( !q.empty() ){
		int v = q.front();
		list<int> L = g.adjacent(v);
		for(list<int>::iterator it = L.begin(); 
					it != L.end(); ++it){
			if( !marked[*it] ){
				marked[*it] = true;
				distTo[*it] = distTo[v] + 1;
				edgeTo[*it] = v;
				q.push(*it);
			}
		}
		q.pop();
	}

}
//return a path from s to v
//depth first search path
deque<int> BreadthFirstPaths::pathTo(int v){
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




