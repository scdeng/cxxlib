/*
 * =====================================================================================
 *
 *       Filename:  mst.h
 *
 *    Description:  minimum spaning tree
 *
 *        Version:  1.0
 *        Created:  08/08/2014 08:59:52 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */

#ifndef MST_H
#define MST_H
#include "graph.h"
#include "priority_queue.h"
#include "union_find.h"
#include <deque>

/*	@brief prim's minimum spanning tres algorithm lazy implementation
 *
 */
class LazyPrim{
	private:
		typedef WeightEdge Edge;
		//marked[v] is true if and only if v is on mst
		vector<bool> marked;
		//edges on mst
		std::deque<Edge> mst;
		//possible edges mst
		//cross edges(maybe ineligible)
		//cross edges mean that one vertex is on mst and another is not
		//ineligit means that both vertices are on mst
		MinPQ<Edge> pq;
		//minimum weight
		double minWt;

		/*	@brief add v into mst and add it's adjacent edges
		 *		whose other vertices are not marked
		 */
		void traverse(const EdgeWeightGraph &G, int v);

	public:

		/*	@brief 
		 */
		LazyPrim(const EdgeWeightGraph &G);
		
		/*	@brief return minimum weight of spanning tree
		 */
		double weight() const {
			return minWt;
		}
		
		/*	@brief return const reference of edges of Minimum spanning tree
		 */
		const std::deque<Edge> & MST() const {
			return mst;
		}
};

/*
 */
class PrimMST{

	private:
		typedef WeightEdge Edge;
		//if visited
		std::vector<bool> marked;
		//distTo == edgeTo.weight()
		std::vector<double> distTo;
		//....mst
		std::vector<Edge> edgeTo;
		//....
		IndexMinPQ<double> pq;
		
		//minimum weight
		double minWT;

		/*	@brief visit vertex v(add v to MST)
		 *		update adjacent vertices weight to MST
		 */
		void traverse(const EdgeWeightGraph &G, int v);

	public:
		
		/*	@brief constructor
		 *
		 */
		PrimMST(const EdgeWeightGraph &G);

		/*	@brief return minimum weight
		 */
		double weight() const{
			return minWT;
		}
		
		/*	@brief return 
		 */
		std::vector<Edge> MST() const {
			//edgeTo is the edges of mst
			std::vector<Edge>::const_iterator it = edgeTo.begin();
			++it;
			std::vector<Edge> mst( it, edgeTo.end() );
			return mst;
		}
};

/*	@brief implementation of Kruskal minimum spanning tree
 *		
 *		implementation based on 
 *		min priority queue and fast union find algorithm
 */
class KruskalMST{

	private:

		typedef WeightEdge Edge;

		//edges of minimum spanning tree
		vector<Edge> mst;
		//weight of MST
		double minWT;

	public:

		/*	@brief construct a KruskalMST object
		 *	@param G	edge weighted graph
		 */
		KruskalMST(const EdgeWeightGraph &G);
	
		/*	@brief return minimum weight of MST
		 */
		double weight() const {
			return minWT;
		}
	
		/*	@brief return a vector of MST edges
		 */
		const vector<Edge>& MST() const {
			return mst;
		}

};

#endif
