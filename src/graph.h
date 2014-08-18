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
#include <float.h>
#include <list>
using namespace std;
#define DEBUG_PRINT

class Graph;
class DepthFirstPaths;
class BreadthFirstPaths;
class WeightEdge;
class EdgeWeightGraph;
ostream& operator<<(ostream &os, const Graph &g);
ostream& operator<<( ostream &os, const DepthFirstPaths &dfs);
ostream& operator<<(ostream &, const BreadthFirstPaths &);
std::ostream& operator<<(std::ostream &os, const WeightEdge &e);
std::ostream& operator<<(std::ostream &os, const EdgeWeightGraph &g);

class Graph{
	
	friend ostream& operator<<(ostream &os, const Graph &g);

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
	friend ostream& operator<<(ostream&, const DepthFirstPaths &);
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
	friend ostream& operator<<(ostream&, const BreadthFirstPaths &);
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

class WeightEdge{
	private:
		//one vertex
		int u;
		//another vertex
		int v;
		//weight
		double wt;
	public:
	
		/*	@brief default constructor
		 */
		WeightEdge():u(-1),v(-1),wt(DBL_MAX){}
	
		/*	@brief copy constructor
		 */
		WeightEdge(const WeightEdge &that):
			u(that.u), v(that.v), wt(that.wt){}

		/*	@brief assignment operator
		 */
		WeightEdge& operator=(const WeightEdge &that){
			u = that.u;
			v = that.v;
			wt = that.wt;
			return *this;
		}
		/*	@brief construct with tree parameters
		 */
		WeightEdge(int _u, int _v, double _w):
			u(_u), v(_v), wt(_w) { }
		
		/*	@brief return weight of this edge
		 */
		double weight() const {
			return wt;
		}

		/*	@brief return either vertex of Edge
		 */
		int either()const{
			return u;
		}
		/*	@brief return another vertex of edge
		 */
		int other(int _v) const{
			if( _v == u ){
				return v;
			}else if( _v == v){
				return u;
			}else{
				std::cerr<<"in consistent"<<std::endl;
				return -1;
			}
		}

		/*	@brief one vertex
		 */
		int oneVertex()const{
			return u;
		}
		/*	@brief another vertex
		 */
		int anotherVertex() const{
			return v;
		}

		/*	@brief six comparative operators overload
		 */
		bool operator==(const WeightEdge &that) const {
			return wt == that.wt;
		}
		bool operator<(const WeightEdge &that) const {
			return wt < that.wt;
		}
		bool operator>(const WeightEdge	&that) const {
			return wt > that.wt;
		}
		bool operator<=(const WeightEdge &that) const {
			return wt <= that.wt;
		}
		bool operator>=(const WeightEdge &that) const {
			return wt >= that.wt;
		}
		bool operator!=(const WeightEdge &that) const {
			return wt != that.wt;
		}

};

/*	@brief edge weighted graph
 *	
 */
class EdgeWeightGraph{
	
	friend std::ostream& operator<<(std::ostream &os, const EdgeWeightGraph &g);

	private:
		typedef WeightEdge Edge;
		//no. of vertices
		int _V;
		//no. of edges
		int _E;
		//adjacent list
		vector<list<Edge> > _adj;

	public:

		/*	@brief construct with V vertices and no edges
		 */
		EdgeWeightGraph(int V){
			_V = V;
			_E = 0;
			_adj = vector<list<Edge> >(V);
		}
	

		/*	@brief get all edges
		 *		return a vector of all edges
		 */
		vector<Edge> allEdges()const{
			vector<Edge> edges;
			//for all vertex
			for(int v=0; v<_V; ++v){
				//for all adjacent vertices add it's corresponding edge
				//but only add a time
				list<Edge>::const_iterator it;
				for(it = _adj[v].begin(); it != _adj[v].end(); ++it){
					int w = it->other(v);
					//only add a time
					if( v > w ){
						edges.push_back(*it);	
					}
				}
			}
			return edges;
		}

		/*	@brief return const reference of vertex v's adjacent list
		 */
		const list<Edge>& adj(int v)const{
			return _adj[v];
		}

		/*	@brief construct with input stream
		 */
		EdgeWeightGraph(istream &is);

		/*	@brief add a weight edge
		 */
		void addEdge(Edge e);
		
		/*	@brief return no. of vertices
		 */
		int V()const{ return _V; }

		/*	@brief return no. of edges
		 */
		int E()const{ return _E; }
};

/*	@brief articulate point(vertex)
 *		processing Graph
 */
class ArticPoint{
	
	private:
		//is visited
		vector<bool> marked;
		//parent of this vertex
		vector<int> parent;
		//is articulation point
		vector<bool> isAP;
		//lowest node of dfs subtree rooted at this node
		vector<int> low;
		//dfs discovery time
		vector<int> disc;
	
		/*	@brief utility function
		 *		return minimum int of two integers
		 */
		int min(int a, int b){
			return (a < b) ? a : b;
		}
	
		/*	@brief dfs utility function
		 */
		void articUtil(const Graph &G, int v, int &count);

	public:
		/*	@brief constructor with a graph
		 */
		ArticPoint(const Graph &G);
		
		/*	@brief check if vertex v is articulation point
		 */
		bool isArticulationPoint(int v) const {
			return isAP[v];
		}

};



#endif 
