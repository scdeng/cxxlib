/*
 * =====================================================================================
 *
 *       Filename:  mst.cpp
 *
 *    Description:  minimum spanning tree implementation
 *    		1. lazy Prim's algorithm
 *    		2. instant Prim's algorithm
 *    		3. Kruskal's algorithm
 *
 *        Version:  1.0
 *        Created:  08/10/2014 10:00:51 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */

#include "mst.h"

/*	@brief add v into mst and add it's adjacent edges
 *		whose other vertices are not marked
 */
void LazyPrim::traverse(const EdgeWeightGraph &G, int v){
	marked[v] = true;
	list<Edge>::const_iterator it;
	for( it = G.adj(v).begin(); it != G.adj(v).end(); ++it){
		int w = it->other(v);
		if( !marked[w] ){
			pq.insert(*it);
		}
	}
}


/*	@brief	default constructor 
*/
LazyPrim::LazyPrim(const EdgeWeightGraph &G){
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

/*	@brief visit vertex v(add v to MST)
 *		update adjacent vertices weight to MST
 */
void PrimMST::traverse(const EdgeWeightGraph &G, int v){
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

/*	@brief constructor
 *
 */
PrimMST::PrimMST(const EdgeWeightGraph &G):
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

/*	@brief construct a KruskalMST object
 *	@param G	edge weighted graph
 */
KruskalMST::KruskalMST(const EdgeWeightGraph &G):
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

