/*
 * =====================================================================================
 *
 *       Filename:  shortest_path.cpp
 *
 *    Description:  shortest path implementation
 *    		1. Bellman Ford Algorithm
 *    		2. Dijkstra Algorithm
 *
 *        Version:  1.0
 *        Created:  08/11/2014 02:30:30 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */
#include "shortest_path.h"


/*	@brief relax all edges from v
 *		if path from v to w(v's adjacent vertex)
 *		is shorter than previous path relax it
 */
void DijkstraSP::relax(const EWD &G, int v){
	//for all edges from v
	list<Edge>::const_iterator it;
	for(it = G.adj(v).begin(); it != G.adj(v).end(); ++it){
		int w = it->to();
		//from s to w has a shorter path
		//which is from s to v to w
		double wght = distTo[v] + it->weight();
		if( wght < distTo[w] ){
			//update path to w
			distTo[w] = wght;
			edgeTo[w] = *it;
			//update mim queue
			pq.insert(w, wght);
		}
	}
}

/*	@brief check if v is a valid vertex
 *		if v is not a valid vertex return false;
 */
bool DijkstraSP::check_vertex(int v){
	int V = distTo.size();
	if( v < V && v >= 0 ){
		return true;
	}else{
		return false;
	}
}


/*	@brief construct DSP with an EWD
*/
DijkstraSP::DijkstraSP(const EWD &G, int s){
	//initialize members
	edgeTo = vector<Edge>(G.V());
	distTo = vector<double>(G.V(), DBL_MAX);
	pq = IndexMinPQ<double>(G.V());
	_s = s;
	distTo[s] = .0;
	pq.insert(s,.0);

	while( !pq.empty() ){
		int v = pq.removeMin();
		relax(G, v);
	}
}


//===============================naive Bellman Ford====================//

/*	@brief relax an edge
 *		edge = u->v
 *		if path from s to u to v is shorter than current path
 *		then update path from s to v to from s to u to v
 *		...change   s->...->v  to s->...->u->v
 */
void NaiveBellmanFordSP::relax(const DirectedWeightedEdge &e){
	int u = e.from();
	int v = e.to();
	double wt = e.weight();
	//it's a shorter path 
	//update it
	if( distTo[u] + wt < distTo[v] ){
		distTo[v] = distTo[u] + wt;
		edgeTo[v] = e;
	}
}


/*	@brief construct with a EWD and a source vertex
 *		compute shortest path from s
 *		based on Bellman-Ford algorithm
 */
NaiveBellmanFordSP::NaiveBellmanFordSP(const EWD &G, int s):
	edgeTo(vector<DirectedWeightedEdge>(G.V())), 
	distTo(vector<double>(G.V(),DBL_MAX)),
	_s(s) { 

	distTo[s] = .0;
	for( int pass=0; pass<G.V(); ++pass){
		for(int v=0; v<G.V(); ++v){
			list<Edge>::const_iterator it;
			for(it = G.adj(v).begin(); it != G.adj(v).end(); ++it){
				relax(*it);
			}
		}
	}
}

/*	@brief return a deque of edges 
 *		which are path from s to v
 */
deque<DirectedWeightedEdge> NaiveBellmanFordSP::pathTo(int v) const{
	deque<Edge> path;
	//check vertex
	if( !check_vertex(v) ){
		std::cerr<<"invalid vertex index..."<<std::endl;
		std::cerr<<"please check your vertex index..."<<std::endl;
		return path;
	}
	//push all edges in reverse order
	while( edgeTo[v].from() != _s ){
		path.push_front(edgeTo[v]);
		v = edgeTo[v].from();
	}
	return path;
}


//======================Bellman Ford===================//

/*	@brief this is a stub function
 *		implement later
 */
void BellmanFordSP::findNegativeCycle() {
	int V = distTo.size();
	EWD spt(V);
	//add every edgeTo edge to spt
	//
	for( int v=0; v<V; ++v){
		//but default constructed edge could not be added
		if( edgeTo[v].from() != -1 && edgeTo[v].to() != -1 ){
			spt.addEdge(edgeTo[v]);
		}
	}
	//check if spt has cycle
	EWDC cf(spt);
	__negativeCycle = cf.cycle();
}

/*	@brief relax v's adjacent edges
 *		push vertex which is not on queue to queue 
 *		check negative cycle every G.V() relaxion
 */
void BellmanFordSP::relax(const EWD &G, int v){
	//for every adjacent edges
	//relax and enqueue w if necessary
	list<Edge>::const_iterator it;
	for(it=G.adj(v).begin(); it != G.adj(v).end(); ++it){
		int w = it->to();
		double wt = it->weight();
		//distance v to w is shorter than previous one
		if( distTo[v] + wt < distTo[w] ){
			distTo[w] = distTo[v] + wt;
			edgeTo[w] = *it;
			if( !onQ[w] ){
				//only vertex which is not on queue 
				//shoud be push on queue
				Q.push(w);
				onQ[w] = true;
			}
		}

		//pioredically check if there exists a negative path
		if( count++ % G.V() == 0 ){
			findNegativeCycle();
		}
	}
}


/*	@brief construct with an EWD and a source s
*/
BellmanFordSP::BellmanFordSP(const EWD &G, int s){
	//initialize data
	edgeTo = vector<Edge>(G.V());
	distTo = vector<double>(G.V(), DBL_MAX);
	onQ = vector<bool>(G.V(), false);
	__negativeCycle = deque<Edge>();
	count = 0; 
	_s = s;

	//source vertex distance is 0
	distTo[s] = 0.0;
	//enqueue s
	Q.push(s);	
	onQ[s] = true;

	//no vertex to be relax or there exists a negative cycle
	while( !Q.empty() && !hasNegativeCycle() ){
		int v = Q.front();
		Q.pop();
		onQ[v] = false;
		relax(G, v);
	}
}

/*	@brief return a deque of path from s to v
*/
deque<DirectedWeightedEdge> BellmanFordSP::pathTo(int v) const {
	deque<DirectedWeightedEdge> path;
	//check vertex
	//if vertex is not valid
	//return a empty deque
	if( !check_vertex(v) ){
		std::cerr<<"invalid vertex index..."<<std::endl;
		std::cerr<<"please check your vertex index..."<<std::endl;
		return path;
	}
	while( edgeTo[v].from() != _s ){
		//put edges in reverse order
		path.push_front(edgeTo[v]);
		v = edgeTo[v].from();
	}
	return path;
}


