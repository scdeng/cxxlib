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
		void traverse(const EdgeWeightGraph &G, int v){
			marked[v] = true;
			list<Edge>::const_iterator it;
			for( it = G.adj(v).begin(); it != G.adj(v).end(); ++it){
				int w = it->other(v);
				if( !marked[w] ){
					pq.insert(*it);
				}
			}
		}

	public:

		/*	@brief 
		 */
		LazyPrim(const EdgeWeightGraph &G){
			marked = vector<bool>(G.V(), false);
			mst = deque<Edge>();
			pq = MinPQ<Edge>();
			minWt = 0.0;
			//assume that G is connected
			traverse(G, 0);
			while( !pq.empty() ){
				//get minimum weight edge
				Edge e = pq.removeMin();
				//get edge's vertices
				int v = e.either();
				int w = e.other(v);
				//if both vertices are on mst
				//edge is ineligible
				//ignore it 
				if( marked[v] && marked[w] ){
					continue;
				}
				//add edge to mst
				mst.push_back(e);
				//add to minWt;
				minWt += e.weight();

				//add either edge to mst
				if( !marked[v] ){
					traverse(G,v);
				}
				if( !marked[w] ){
					traverse(G,w);
				}
			}
		}
		
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
		void traverse(const EdgeWeightGraph &G, int v){
			marked[v] = true;
			list<Edge>::const_iterator it;
			for( it = G.adj(v).begin(); it != G.adj(v).end(); ++it){
				int w = it->other(v);
				if( !marked[w] ){
					double wt = it->weight();
					if( wt < distTo[w] ){
						//update it's weight to MST
						distTo[w] = wt;
						pq.insert(w, wt);
						edgeTo[w] = *it;
					}
				}
			}
		}

	public:
		
		/*	@brief constructor
		 *
		 */
		PrimMST(const EdgeWeightGraph &G):
			marked(vector<bool>(G.V(),false) ),
			distTo(vector<double>(G.V(), DBL_MAX) ),
			edgeTo(vector<Edge>(G.V())),
			pq(IndexMinPQ<double>(G.V())),
			minWT(.0){

			//assume vertices are connected
			//add vertex 0 to MST
			distTo[0] = .0;
			//edgeTo[0] = 0;
			pq.insert(0, 0.0);

			while( !pq.empty() ){
				//get next vertex which should be on mst
				minWT += pq.min();
				int v = pq.removeMin();			
				//traverse v
				traverse(G,v);
			}
		}

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
		KruskalMST(const EdgeWeightGraph &G):
			mst( vector<Edge>() ), minWT(0.0)
		{
			//sort edges by weight	
			MinPQ<Edge> pq;
			//add all edges into priority queue
			vector<Edge> edges = G.allEdges();		
			for(vector<Edge>::iterator it = edges.begin();
						it != edges.end(); ++it){
				pq.insert(*it);
			}		
			//union find to detect two vertices are connected
			UF uf(G.V());
			while( !pq.empty() ){
				//get minimum weight edge 
				Edge e = pq.removeMin();
				int u = e.either();
				int v = e.other(u);
				if( uf.isConnected(u,v) ){
					continue;
				}else{
					//u and v are not connected
					//then e is a MST edge
					mst.push_back(e);
					minWT += e.weight();
					//connect u and v
					uf.connect(u, v);
				}
			}
		}
	
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
