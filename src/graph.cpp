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
ostream& operator<<(ostream &os, const Graph &g){
	os << g.V() << " verices and " << g.E() << " edges" << endl;
	for(int i=0; i<g._v; i++){
		os << i << " : " ;
		for(list<int>::const_iterator it = (g.adj[i]).begin();
					it != (g.adj[i]).end(); ++it){
			os << *it << " ";
		}
		os << endl;
	}
	return os;
}

ostream& operator<<( ostream &os, const DepthFirstPaths &dfs){
	os << "marked is: " << endl;
	for(unsigned i=0; i<dfs.marked.size(); ++i){
		os << (dfs.marked)[i] << ", ";
	}
	os << endl;
	os << "count is: " << dfs.__count << endl;
	return os;
}



ostream& operator<<(ostream &os, const BreadthFirstPaths &bfs){
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



//==================edge weighted graph=================//

std::ostream& operator<<(std::ostream &os, const WeightEdge &e){
	os<< "{" <<e.oneVertex()<<"-"<<
		e.anotherVertex()<<", " << e.weight() << "}"<< std::endl;
	return os;
}

std::ostream& operator<<(std::ostream &os, const EdgeWeightGraph &g){
	os<<"---------------------------------"<<std::endl;
	os<<g._V<<" vertices and " << g._E << " edges"<<std::endl;
	for(int v=0; v<g._V; ++v){
		os<<v<<":\t";
		for(list<WeightEdge>::const_iterator it = g._adj[v].begin();
					it != g._adj[v].end(); ++it){
			os<<"[" << it->other(v) <<", "<<it->weight() << "] "; 
		}
		os<<std::endl;
	}
	os<<"--------------------------------"<<std::endl<<std::endl;
	return os;
}

/*	@brief construct with input stream
*/
EdgeWeightGraph::EdgeWeightGraph(istream &is){
	int V;
	int E;
	is >> V;
	is >> E;
	_V = V;
	_E = 0;
	_adj = vector<list<Edge> >(V);

	int u;
	int v;
	double w;
	while( is>>u && is>>v && is >> w ){
		addEdge(Edge(u,v,w));	
	}
}
/*	@brief add a weight edge
*/
void EdgeWeightGraph::addEdge(Edge e){
	//get vertex
	int u = e.oneVertex();
	int v = e.anotherVertex();
	//add vertex to adjacent list
	_adj[u].push_back(e);
	_adj[v].push_back(e);
	//increase no. of edge
	++_E;
}

/*	@brief dfs utility function
*/
void ArticPoint::articUtil(const Graph &G, int v, int &count){
	marked[v] = true;
	int children = 0;
	disc[v] = low[v] = ++count;
	list<int>::const_iterator it;
	for(it = G.adjacent(v).begin(); it != G.adjacent(v).end(); ++it){
		int w = *it;
		if( !marked[w] ){
			++children;
			//set parent of w to v
			parent[w] = v;
			//recursively find w
			articUtil(G, w, count);
			//after search w (one of v's children)
			//check if subtree rooted w has a back edge to a lowest vertex
			low[v] = min(low[w], low[v]);

			//case 1: if root of dfs tree has more than 1 childred
			//v is a articulation point
			if( parent[v] == INT_MAX && children > 1){
				isAP[v] = true;
			}
			//case 2:
			//if v is not a root of dfs tree
			//one of it's child has no back edge to v's parent
			//which indicats path to w shall contain v
			//
			//v is remove and this child of v is isolated
			if( parent[v] != INT_MAX && low[w] >= disc[v] ){
				isAP[v] = true;
			}
		}else if( w != parent[v] ){
			//low[v] is minimum of low[w] and low[v]
			low[v] = min(low[v], low[w]);
		}
	}	
}
/*	@brief constructor with a graph
*/
ArticPoint::ArticPoint(const Graph &G){
	marked = vector<bool>(G.V(), false);
	parent = vector<int>(G.V(), INT_MAX);
	isAP = vector<bool>(G.V(), false);
	low = vector<int>(G.V(), INT_MAX);
	disc = vector<int>(G.V(), INT_MAX);
	int count = 0;
	for( int v=0; v<G.V(); ++v){
		if( !marked[v]){
			articUtil(G, v, count);
		}
	}
}

