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
#include <cassert>
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
		
		/*	@brief check if v is a valid vertex
		 */
		bool check_vertex(int v)const;

	public:
		
		/*	@brief create an empyt graph
		 */
		Graph(): _v(0), _e(0), adj(vector<list<int> > () ){ }
		/*	@brief create a graph with input stream
		 */
		Graph(istream &is);

		/*	@brief create a graph with n vertices and no edge
		 */
		Graph(int N){
			_v = N;
			_e = 0;
			adj = vector<list<int> >(N);
		}
		
		/*	@brief	return an object not reference of v's adjacent list
		 */ 
		const list<int>& adjacent(int v)const{
			assert ( check_vertex(v) );
			return adj[v];
		}
		
		/*	@brief add an edge connect u and v
		 *		not check for duplicate edge
		 *	@param u	vertex u
		 *	@param v	vertex v
		 */
		void addEdge(int u, int v){
			adj[u].push_back(v);
			adj[v].push_back(u);
			++_e;
		}

		/*	@brief return number of vertices
		 */
		int V() const { return _v; }
		/*	@brief return num of edges
		 */
		int E() const { return _e; }
};

/*	@brief Depth First search Tree
 */
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

		/*	@brief depth first search construct a search tree
		 */
		void dfs(const Graph &g, int v);

	public:
		/*	@brief constructor with a graph	and a source
		 */
		DepthFirstPaths(const Graph &g, int s){
			__s = s;
			marked = vector<bool>(g.V(), false);
			edgeTo = vector<int>(g.V(),-1);
			__count = 0;
			dfs(g,s);
		}
	
		/*	@brief bfs path from s to v
		 */
		inline deque<int> pathTo(int v)const;
	
		/*	@brief check v is reachable
		 */
		bool connected(int v)const{
			return marked[v];
		}
		/*	@brief check if there exists a path from s to v
		 */
		bool hasPathTo(int v)const{
			return marked[v];
		}
		/*	@brief how many components 
		 */
		int count()const{
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
		/*	@brief bfs
		 */
		void bfs(const Graph &g, int s);

		/*	@brief breadth first search to construct a search forest
		 */
		void bfs(const Graph &g, const vector<int> &sources);

	public:
		/*	@brief construct with a graph
		 */
		BreadthFirstPaths(const Graph &g, int s){
			marked = vector<bool>(g.V(), false);
			edgeTo = vector<int>(g.V());
			for(int i=0; i<g.V(); ++i){
				edgeTo[i] = i;
			}
			distTo = vector<int>(g.V(), INT_MAX);
			bfs(g,s);
		}

		/*	@brief construct with a graph and a vector of sources
		 *	@param g	graph
		 *	@param sources
		 */
		BreadthFirstPaths(const Graph &g, const vector<int> &sources){
			marked = vector<bool>(g.V(), false);
			edgeTo = vector<int>(g.V());
			for(int i=0; i<g.V(); ++i){
				edgeTo[i] = i;
			}
			distTo = vector<int>(g.V(), INT_MAX);
			bfs(g, sources);	
		}

		//return path fron source to v
		deque<int> pathTo(int v)const;
	
		//return true if there exists a path to v	
		bool hasPathTo(int v)const{
			return marked[v];
		}
		
		//distance from source to v
		int distanceTo(int v)const{
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

		void dfs(const Graph &g, int v);
	public:
		CC(const Graph &g);
		//return id of vertex v
		int id(int v)const {
			return __id[v];
		}

		//return no. of connected components
		int count()const{
			return __count;
		}

		//u and v are connected ?
		bool connected(int u, int v)const{
			return __id[v] == __id[u];
		}
		//size of connected component of contains v
		int size(int v)const{
			return sz[ __id[v] ];
		}
};
#endif 
