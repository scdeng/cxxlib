/*
 * =====================================================================================
 *
 *       Filename:  tree.h
 *
 *    Description:  binary tree data structure
 *
 *        Version:  1.0
 *        Created:  08/05/2014 06:55:38 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */

#ifndef TREE_H
#define TREE_H
#include <stdlib.h>
#include <cassert>
#include "queue.h"
#include <iostream>
//#define DEBUG_PRINT
//#define DEBUG_CHECK
//#define DEBUG_CHECK_PRINT

template <typename T> 
T maximum(const T &one, const T &another){
	return  (one > another ? one : another);
}


template <typename KEY, typename VALUE> struct TreeNode;
#ifdef DEBUG_PRINT
template <typename K,typename V> void traverse(TreeNode<K,V> *);
#endif
/*
 *	template binary tree node struct
 *	TreeNode has left & right child
 *
 */
template <typename KEY, typename VALUE> struct TreeNode{
#ifdef DEBUG_PRINT
	template <typename K, typename V>
	friend void traverse(TreeNode<K,V> *);
#endif
	template <typename K, typename V> friend class BSTree;
	private:
		//key
		KEY key;
		//value
		VALUE value;
		//no. of nodes rooted in this node
		size_t sz;
		//left right child
		TreeNode *left;
		TreeNode *right;
	public:

		//default constructor
		TreeNode(): key(KEY()), value(VALUE()), sz(1), left(NULL), right(NULL) {}
		//construct with key, value pair
		TreeNode(const KEY &k, const VALUE &v ): 
				key(k), value(v), sz(1), left(NULL), right(NULL) {}

};



/*
 *	binary search tree class
 */
template <typename K, typename V> class BSTree{
	private:
		//root node
		TreeNode<K,V> *root;
		
		size_t size(TreeNode<K,V> *p){
			if ( !p ) return 0;
			return p->sz;
		}
		
		//check binary search tree
		bool checkBST(TreeNode<K,V> *p){
			if ( !p ) return true;

			if (p->sz != 1 + size(p->left) + size(p->right) ){
#ifdef DEBUG_CHECK_PRINT
				std::cout << "check failed" << std::endl;
				traverse(p);
				std::cout << "size is: " <<  p->sz << std::endl;
				std::cout << "left size is: " << size(p->left) <<std::endl;
				std::cout << "rifht size is: " << size(p->right) << std::endl;
#endif
				return false;
			}

			if ( p->left ){
				if ( ! (p->left->key < p->key) ){
#ifdef DEBUG_CHECK_PRINT
					std::cout << "check failed" << std::endl;
					traverse(p);
					std::cout << "size is: " <<  p->sz << std::endl;
					std::cout << "left size is: " << size(p->left) <<std::endl;
					std::cout << "rifht size is: " << size(p->right) << std::endl;
#endif
					return false;
				}
			}
			if ( p->right ){
				if ( ! ( p->key < p->right->key) ){
					
#ifdef DEBUG_CHECK_PRINT
					std::cout << "check failed" << std::endl;
					traverse(p);
					std::cout << "size is: " <<  p->sz << std::endl;
					std::cout << "left size is: " << size(p->left) <<std::endl;
					std::cout << "rifht size is: " << size(p->right) << std::endl;
#endif
					return false;
				}
			}
			return checkBST(p->left) && checkBST(p->right);

		}
		//insert k,v pair
		TreeNode<K,V> *insert(TreeNode<K,V> *p, const K &k, const V &v){
			//p is null
			//create a new node and return
			if(p == NULL){
				return new TreeNode<K,V>(k,v);
			}
			//contains k
			//change value
			if( p->key == k ){
				p->value = v;
			}else if( k < p->key ){
				//insert to p's left child
				p->left = insert(p->left, k, v);
			}else{
				p->right = insert(p->right, k, v);
			}
			//update sz of tree rooted in p 
			p->sz = 1 + size(p->left) + size(p->right);

			return p;
		}


		TreeNode<K,V> * find_node(TreeNode<K,V> *p, const K &k){
			//p is null
			if(p == NULL){
				return NULL;
			}
			//k equals to p's key
			if( p->key == k ){
				return p;
			}else if( k < p->key ){
			//k goes to p's left
				return find_node(p->left, k);
			}else {
			//k goes to p's right
				return find_node(p->right, k);
			}
		}
		
		//return the max node of tree rooted in p	
		TreeNode<K,V> * max(TreeNode<K,V> *p){
			if(p == NULL){
				return p;
			}
			while(p->right){
				p = p->right;
			}
			return p;
		}
		
		//return the min node of tree rooted in p	
		TreeNode<K,V> * min(TreeNode<K,V> *p){
			if ( !p ){
				return NULL;
			}
			while(p->left){
				p = p->left;
			}
			return p;
		}
		//remove node with key equals to k	
		TreeNode<K,V> * remove(TreeNode<K,V> *p, const K &k){
			//NULL pointer
			if (p == NULL){
				return NULL;
			}
			//k < p->key
			if( k < p->key ){
				p->left = remove(p->left, k);
			}else if (k > p->key){
			//k > p->key
				p->right = remove(p->right, k);
			}else{
			//k == p->key
				//left is null
				//return right
				if( !(p->left) ) {
					TreeNode<K,V> *t = p->right;
					//delete node p
					delete p;
					//return p's right
					return t;
				}
				//right is null
				//return left
				if( !(p->right) ) {
					TreeNode<K,V> *t = p->left;
					//delete p
					delete p;
					//fucking coding
					//return p's left
					return t;
				}
				//find p's right subtree's minimum
				TreeNode<K,V> *t = min(p->right);
				p->key = t->key;
				p->value = t->value;
				p->right = removeMin(p->right);

			}
			p->sz = 1 + size(p->left) + size(p->right);
			return p;
		}
		
		//remove min key of tree rooted in p
		TreeNode<K,V> * removeMin(TreeNode<K,V> *p){
			if( !p ) return NULL;
			//p is minimum
			if ( p->left == NULL ){
				TreeNode<K,V> *t = p->right;
				delete p;
				return t;
			}
			p->left = removeMin(p->left);
			//update size
			p->sz = 1 + size(p->left) + size(p->right);
			return p;
		}

		//remove max key of tree rooted in p
		TreeNode<K,V> * removeMax(TreeNode<K,V> *p){
			if ( !p ) return NULL;
			//p is maximum
			if ( p->right == NULL ){
				TreeNode<K,V> *t = p->left;
				delete p;
				return t;
			}
			//reccursively delete min
			p->right = removeMax(p->right);
			//update size
			p->sz = 1 + size(p->left) + size(p->right);
			return p;
		}
#ifdef DEBUG_PRINT	
		//inorder traverse tree rooted at p
		void inorder(TreeNode<K,V> *p){
			if( !p ) return ;
			inorder(p->left);
			traverse(p);
			inorder(p->right);
		}
#endif

		//return height of tree rooted p
		int height(TreeNode<K,V> *p){
			if ( !p ) return 0;
			return 1 + maximum( height(p->left),  height(p->right) );
		}

		//collect all keys in increasing order
		void keys(Queue<K> &q, TreeNode<K,V> *p){
			if( !p ) return;
			//collect left subtree
			keys(q,p->left);
			//enque p's key
			q.enqueue(p->key);
			//collect right subtree
			keys(q,p->right);
		}
		//return no. of keys in subtree rooted at p less than k
		unsigned rank(TreeNode<K,V> *p, const K &k){
			// p is null return 0
			if( !p ) return 0;
			//p->key == k
			//return p->left's sz if p->left is not null
			//return 0 otherwise
			if ( p->key == k ){
				return size(p->left);
			}else if ( p->key < k ){
				//p->key < k
				//all keys in p's left subtree are less than k
				//p's k is less than k
				//plus right subtree's key
				return 1 + size(p->left) + rank(p->right, k);
			}else{
				//all keys that less than k
				//are in the left subtree of p
				return rank(p->left, k);
			}
		}
		//select k th key in subtree of p
		TreeNode<K,V> * select(TreeNode<K,V> *p, unsigned k){
			if ( !p ) return NULL;

			unsigned t = size(p->left);
			if ( t > k ){
				return select( p->left, k);
			}else if ( t < k ){
				return select( p->right, k-t-1);
			}else{
				return p;
			}
		}

	public:
		BSTree():root(NULL){}
		~BSTree(){
			while( !empty()){
				removeMax();
			}
		}
		
		//select k th Key in increasing order
		K select(unsigned k){
			if (k < 0 || k > size(root) ){
				return K();
			}
			return select(root,k)->key;
		}
		
		//no. of keys less than k
		int rank(const K &k){
			return rank(root, k);
		}
		//return a queue contains all keys in increasing order
		Queue<K> keys(){
			Queue<K> q;
			keys(q, root);
			return q;
		}

		//return height of tree
		int height(){
			return height(root);
		}

		//remove maximum key
		void removeMax(){
			root = removeMax(root);
#ifdef DEBUG_CHECK
			bool yes = checkBST(root);
#endif
#ifdef DEBUG_CHECK
			std::cout << (yes? "check passed" : "check failed") << std::endl;
#endif
		}
		//remove minimum key
		void removeMin(){
			root = removeMin(root);
#ifdef DEBUG_CHECK
			bool yes = checkBST(root);
#endif
#ifdef DEBUG_CHECK
			std::cout << (yes? "check passed" : "check failed") << std::endl;
#endif
		}

#ifdef DEBUG_PRINT
		//print inorder of tree
		//it should be sorted output
		void inorder(){
			inorder(root);
		}
#endif
		//return true if contains
		//else return false
		bool contain(const K &k){
			return find_node(root,k) != NULL;
		}
		
		//find k
		//return K's value
		V find(const K &k){
			TreeNode<K,V> *p = find_node(root, k);
			if(p){
				return p->value;
			}else{
				//undefined if k is not containing is tree
				std::cerr << "return value is not defined "
					<<  "\n find a key is not contained" << std::endl;
				return V();
			}
		}

		//return max key
		K max(){
			TreeNode<K,V> *p = max(root);
			assert (p);
			if(p == NULL){
				std::cerr<< " access empty BST " <<std::endl;
				std::cerr<< " returning Key is undefined... " << std::endl;
			}
			return p->key;
		}
		//return min node
//		TreeNode<K,V> * min(){
//			return min(root);
//		}
		//return min key
		K min(){
			TreeNode<K,V> *p = min(root);
			if(p == NULL){
				std::cerr<< " access empty BST " <<std::endl;
				std::cerr<< " returning Key is undefined... " << std::endl;
			}
			return p->key;
		}

		//insert k,v pair 
		void insert(const K &k, const V &v){
			root = insert(root, k, v);

#ifdef DEBUG_CHECK
			bool yes = checkBST(root);
#endif
#ifdef DEBUG_CHECK
			std::cout << (yes? "check passed" : "check failed") << std::endl;
#endif

		}

		//remove node with key equals to t
		void remove(const K &k){
			root = remove(root, k);
#ifdef DEBUG_CHECK
			bool yes = checkBST(root);
#endif
#ifdef DEBUG_CHECK
			std::cout << (yes? "check passed" : "check failed") << std::endl;
#endif
		}

		bool empty()const {
			return root == NULL;
		}

		size_t size() const {
			return size(root);
		}
};
#ifdef DEBUG_PRINT
template <typename K, typename V>
void traverse(TreeNode<K,V> *p){
	std::cout << "<" << p->key << ", " << p->value << ">\t" << p->sz;
	std::cout << "\t";
	if( p->left){
		std::cout << "left is: " << "<" << p->left->key
			<< ", " << p->left->value << ">\t" << p->left->sz;
	}else{
		std::cout << "left is NULL";
	}
	std::cout << "\t" ;
	if (p->right){
		std::cout << "right is: " << "<" << p->right->key
			<< ", " << p->right->value << ">\t" << p->right->sz;
	}else{
		std::cout << "right is NULL";
	}
	std::cout << std::endl;
}
#endif
#endif
