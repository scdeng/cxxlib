/*
 * =====================================================================================
 *
 *       Filename:  sp.h
 *
 *    Description:  shortest path algorithm
 *    		1. bellman-Ford algorithm
 *    		2. Dijkstra's algorithm
 *
 *        Version:  1.0
 *        Created:  08/11/2014 01:20:52 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */

#ifndef SHORTEST_PATH_H
#define SHORTEST_PATH_H

#include "digraph.h"
#include "priority_queue.h"
using namespace std;

class DijkstraSP{
	
	private:
		typedef DirectedWeightedEdge Edge;
		typedef EdgeWeightedDigraph EWD;
		//edge to vertex
		vector<Edge> edgeTo;
		//distTo[v] is distance to vertex v
		vector<double> distTo;
		//index priority queue of shortest path
		IndexMinPQ<double> pq;
		int _s;

		/*	@brief relax all edges from v
		 *		if path from v to w(v's adjacent vertex)
		 *		is shorter than previous path relax it
		 */
		void relax(const EWD &G, int v);

		/*	@brief check if v is a valid vertex
		 *		if v is not a valid vertex return false;
		 */
		bool check_vertex(int v);
	
	public:
		/*	@brief construct DSP with an EWD
		 */
		DijkstraSP(const EWD &G, int s);
	
		/*	@brief weight of path to v
		 */
		double weightTo(int v){
			if( !check_vertex(v) ){
				return DBL_MAX;
			}
			return distTo[v];
		}
		
		/*	@brief return a deque of edges which form the shortest path to vertex v
		 */
		deque<Edge> pathTo(int v) const{
			deque<Edge> path;
			while( edgeTo[v].from() != _s ){
				path.push_front(edgeTo[v]);
			}
			return path;
		}
};

class NaiveBellmanFordSP{
	private:
		typedef DirectedWeightedEdge Edge;
		typedef EdgeWeightedDigraph EWD;
		vector<Edge> edgeTo;
	    vector<double> distTo;
		int _s;
	
		/*	@brief relax an edge
		 *		edge = u->v
		 *		if path from s to u to v is shorter than current path
		 *		then update path from s to v to from s to u to v
		 *		...change   s->...->v  to s->...->u->v
		 */
		void relax(const Edge &e);
		
		/*	@brief check if a vertex is valid
		 */
		bool check_vertex(int v)const{
			int _V = distTo.size();
			if( v < _V && v >= 0 ){
				return true;
			}else{
				return false;
			}
		}

	public:
		
		/*	@brief construct with a EWD and a source vertex
		 *		compute shortest path from s
		 *		based on Bellman-Ford algorithm
		 */
		NaiveBellmanFordSP(const EWD &G, int s);
	
		/*	@brief return weight to vertex v
		 *		if v is not a valid vertex return DBL_MAX
		 */
		double weightTo(int v) const {
			if( !check_vertex(v) ){
				std::cerr<<"invalid vertex index..."<<std::endl;
				std::cerr<<"please check your vertex index..."<<std::endl;
				return DBL_MAX;
			}
			return distTo[v];
		}

		/*	@brief return a deque of edges 
		 *		which are path from s to v
		 */
		deque<Edge> pathTo(int v) const;
			
};

/*	@brief Bellman-Ford shortest path based on queue
 *		typical case it is efficient
 *
 */
class BellmanFordSP{
	
	private:
		typedef DirectedWeightedEdge Edge;
		typedef EdgeWeightedDigraph EWD;
		typedef EdgeWeightedDirectedCycle EWDC;
		//prescdence of vertices
		vector<Edge> edgeTo;
		//distance to 
	    vector<double> distTo;
		//if v is on queue
		vector<bool> onQ;
		//next relaxion vertex
		queue<int> Q;
		//if there exists a negative cycle
		deque<Edge> __negativeCycle;
		//how many relaxion
		int count;
		int _s;

		/*	@brief this is a stub function
		 *		implement later
		 */
		void findNegativeCycle() ;
		
		/*	@brief relax v's adjacent edges
		 *		push vertex which is not on queue to queue 
		 *		check negative cycle every G.V() relaxion
		 */
		void relax(const EWD &G, int v);
		
		/*	@brief check if a vertex is valid
		 */
		bool check_vertex(int v)const{
			int _V = distTo.size();
			if( v < _V && v >= 0 ){
				return true;
			}else{
				return false;
			}
		}


	public:

		/*	@brief construct with an EWD and a source s
		 */
		BellmanFordSP(const EWD &G, int s);
		
		/*	@brief return weight from s to v
		 *		if v is not a valid vertex return DBL_MAX
		 */
		double weightTo(int v) const {
			if( !check_vertex(v) ){
				std::cerr<<"invalid vertex index..."<<std::endl;
				std::cerr<<"please check your vertex index..."<<std::endl;
				return DBL_MAX;
			}
			return distTo[v];	
		}

		/*	@brief return a deque of path from s to v
		 */
		deque<Edge> pathTo(int v) const ;
		
		/*	@brief this is a stub function
		 */
		bool hasNegativeCycle() const{
			return __negativeCycle.size() != 0;
		}

		const deque<Edge>& negativeCycle() const {
			return __negativeCycle;
		}
};


#endif
