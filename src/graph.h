/*
 * =====================================================================================
 *
 *       Filename:  graph.h
 *
 *    Description:  undirected graph class
 *
 *        Version:  1.0
 *        Created:  08/05/2014 05:24:08 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */

#ifndef GRAPH_H
#define GRAPH_H
#include <deque> 
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits.h>
#include <list>
using namespace std;
#define DEBUG_PRINT

class Graph;
class DepthFirstPaths;
class BreadthFirstPaths;

ostream& operator<<(ostream &os, Graph &g);
ostream& operator<<( ostream &os, DepthFirstPaths &dfs);
ostream& operator<<(ostream &, BreadthFirstPaths &);

class Graph{
	
	friend ostream& operator<<(ostream &os, Graph &g);

	private:
		//no. of vertics
		int _v;
		//no. of edges
		int _e;
		//adjacent list
		vector<list<int> > adj;		
		
		//check v 
		bool check_vertex(int v);

	public:
		//create an empty graph
		Graph(): _v(0), _e(0), adj(vector<list<int> > () ){ }
		Graph(istream &is);
		Graph(int N){
			_v = N;
			_e = 0;
			adj = vector<list<int> >(N);
		}

		list<int> adjacent(int v){
			return adj[v];
		}

		//not check for duplicate edge
		void addEdge(int u, int v){
			adj[u].push_back(v);
			adj[v].push_back(u);
			++_e;
		}
		int V() const { return _v; }
		int E() const { return _e; }
	

};
//print graph
//	os << g.V() << " verices and " << g.E() << " edges" << endl;
//	for(int i=0; i<g._v; i++){
//		os << i << " : " ;
//		for(list<int>::iterator it = (g.adj[i]).begin();
//					it != (g.adj[i]).end(); ++it){
//			os << *it << " ";
//		}
//		os << endl;
//	}
//	return os;
//}


class DepthFirstPaths{
#ifdef DEBUG_PRINT
	friend ostream& operator<<(ostream&, DepthFirstPaths &);
#endif
	private:
		//visited mark
		vector<bool> marked;
		//edge to v
		vector<int> edgeTo;
		//no. of vertices connected to s
		int __count;
		//source vertex
		int __s;
		void dfs(Graph &g, int v);

	public:

		DepthFirstPaths(Graph &g, int s){
			__s = s;
			marked = vector<bool>(g.V(), false);
			edgeTo = vector<int>(g.V(),-1);
			__count = 0;
			dfs(g,s);
		}
	
		//return a path from s to v
		//depth first search path
		inline deque<int> pathTo(int v);
		
		bool connected(int v){
			return marked[v];
		}

		bool hasPathTo(int v){
			return marked[v];
		}
		int count(){
			return __count;
		}
};

/*
 *	breadth first search 
 */
class BreadthFirstPaths{
#ifdef DEBUG_PRINT
	friend ostream& operator<<(ostream&, BreadthFirstPaths &);
#endif
	private:
		//visited
		vector<bool> marked;
		//edge from 
		vector<int> edgeTo;
		//distance to vertex v
		vector<int> distTo;
		//...
		void bfs(Graph &g, int s);
		
		void bfs(Graph &g, const vector<int> &sources);

	public:
		BreadthFirstPaths(Graph &g, int s){
			marked = vector<bool>(g.V(), false);
			edgeTo = vector<int>(g.V());
			for(int i=0; i<g.V(); ++i){
				edgeTo[i] = i;
			}
			distTo = vector<int>(g.V(), INT_MAX);
			bfs(g,s);
		}

		

		BreadthFirstPaths(Graph &g, const vector<int> &sources){
			marked = vector<bool>(g.V(), false);
			edgeTo = vector<int>(g.V());
			for(int i=0; i<g.V(); ++i){
				edgeTo[i] = i;
			}
			distTo = vector<int>(g.V(), INT_MAX);
			bfs(g, sources);	
		}

		//return path fron source to v
		deque<int> pathTo(int v);
	
		//return true if there exists a path to v	
		bool hasPathTo(int v){
			return marked[v];
		}
		
		//distance from source to v
		int distanceTo(int v){
			return distTo[v];
		}
};

//connected component
class CC{
	private:
		//visited
		vector<bool> marked;
		//which connected component
		vector<int> __id;
		//sz of 
		vector<int> sz;
		//no. of connedted component
		int __count;

		void dfs(Graph &g, int v);
	public:
		CC(Graph &g);
		//return id of vertex v
		int id(int v)const {
			return __id[v];
		}

		//return no. of connected components
		int count(){
			return __count;
		}

		//u and v are connected ?
		bool connected(int u, int v){
			return __id[v] == __id[u];
		}
		//size of connected component of contains v
		int size(int v){
			return sz[ __id[v] ];
		}
};
#endif 
