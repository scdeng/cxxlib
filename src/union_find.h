/*
 * =====================================================================================
 *
 *       Filename:  union_find.h
 *
 *    Description:  union find implementation
 *
 *        Version:  1.0
 *        Created:  08/04/2014 04:23:47 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */

#ifndef UNION_FIND_H
#define UNION_FIND_H

class UF{

	private:
		//parent[i] is parent of i
		Array<int> parent;
		//sz[i] is number of subtree rooted at i
		Arran<int> sz;
		//no. of componets
		int count;

		//find root of u
		int find(int u){
			while( u != parent[u]){
				u = parent[u];
			}
			return u;
		}

	public:
		UF(int N){
			count = N;
			parent = Array<int>(N,0);
			sz = Array<int>(N,1);
			for(int i=0; i<N; ++i){
				parent[i] = i;
			}
		}

		bool isConnected(int u, int v){
			return find(u) == find(v);
		}
		void connect(int u, int v){
			//find root of u
			int rootU = find(u);
			//find root of v
			int rootV = find(v);
			
			//connect smaller one to bigger one
			if (sz[rootU] > sz[rootV]){
				parent[rootV] = rootU;
				//update sz
				sz[rootU] += sz[rootV];
			}else{
				parent[rootU] = rootV;
				sz[rootV] += sz[rootU];
			}
			//decrease components
			--count;
		}
		size_t size();

};

#endif
