/*
 * =====================================================================================
 *
 *       Filename:  rbtree.h
 *
 *    Description: a C++ template implementation of red black tree 
 *    which is one-to-one corresponding a left leaning 2-3 tree
 *    implementation based on Algorithm 4th by Sedgewick and Wayne.
 *    the worst case of height is 2log(n).
 *    
 *
 *        Version:  1.0
 *        Created:  08/06/2014 09:08:00 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */

#ifndef RBTREE_H
#define RBTREE_H
#include <stdlib.h>
#include <iostream>
#include <cassert>
#include <queue>
#include <deque>

#define DEBUG_CHECK
#define DEBUG_TEST
#define DEBUG_PRINT
#ifdef DEBUG
using namespace std;
#endif

#define maximum(A,B)  ( (A) > (B) ) ? (A) : (B)

#ifdef DEBUG_TEST
	static unsigned long NUM_OF_LEFT_ROTATION = 0;
	static unsigned long NUM_OF_RIGHT_ROTATION = 0;
	static unsigned long NUM_OF_INSERTION = 0;
	static unsigned long NUM_OF_DELETION = 0;
#endif
const bool RED = true;
const bool BLACK = false;

template <typename K, typename V> class RBTree;

template <typename K, typename V> class RBTNode{

	template <typename U, typename S>
		friend void traverse(std::ostream &os, RBTNode<U,S> *p);

	template <typename T, typename Tp>
		friend std::ostream& operator<<( std::ostream &, const RBTNode<T,Tp>& );

	template <typename T, typename R> friend class RBTree;

	private:
		//key
		K key;
		//value
		V value;
		//color
		bool color;
		//size of subtree
		int sz;
		RBTNode *left;
		RBTNode *right;

	public:
		RBTNode(const K &k, const V &v, bool c, int s):
			key(k), value(v), color(c), sz(s),left(NULL), right(NULL) { }
};

template <typename K, typename V>
class RBTree{
	template <typename TS, typename US>
		friend std::ostream& operator<<( std::ostream &os, RBTree<TS,US> &rbt);

	typedef RBTNode<K,V> Node;

	private:
		Node *root;
		bool isRed(Node *p){
			if ( !p ) return false;
			return p->color == RED;
		}
		int size(Node *p){
			if( !p ) return 0;
			return p->sz;
		}

		//reccursively get key	
		Node * get(Node *p, const K &k){
			if( !p ) return p;
			if( k == p->key ){
				//k == p->key
				return p;
			}else if( k < p->key ){
				//k < p->key
				return get(p->left, k);
			}else{
				//k > p->key
				return get(p->right,k);
			}
		}

		int max(int a, int b)const{
			return a > b ? a : b;
		}

		int height(const Node *p)const{
			if( !p ) return 0;
			return 1 + max( height(p->left), height(p->right) );
		}

		//flip p and its children's color
		void flipColors(Node *p){
			//assert all p && p->left && p->right are non-NULL
			//assert ( p  && p->left && p->right );
			//assert p's color is opposite to its children
			//these two children have same color
			assert ( (!isRed(p) &&  isRed(p->left) &&  isRed(p->right) ) 
				|| (isRed(p)  && !isRed(p->left) && !isRed(p->right)) );
			//flip p's color
			p->color = !p->color;
			//flip p's children's colors
			p->left->color = !p->left->color;
			p->right->color = !p->right->color;
		}

		Node *insert(Node *p, const K &k, const V &v){
			if( !p ){
#ifdef DEBUG_TEST
				//how many times you insert
				++NUM_OF_INSERTION;
#endif
				return new Node(k,v,RED,1);
			}
			if( k == p->key ){
				// k == p->key, change value to v
				p->value = v;
			}else if( k < p->key ){
				// k < p->key
				p->left = insert(p->left, k, v);
			}else{
				// k > p->key
				p->right = insert(p->right, k, v);
			}
			
			//adjust color
			//these if blocks are ordered

			//right is red and left is black
			//rotate left 
			if (isRed(p->right) && !isRed(p->left)){
				p = leftRotate(p);
			}
			//both p->left and p->left->left are red
			//rotate right and then check next case
			if (isRed(p->left)  &&  isRed(p->left->left)){
				p = rightRotate(p);
			}
			//both left and right are red 
			//flip colors
			if (isRed(p->left)  &&  isRed(p->right)) {
				flipColors(p);
			}
			//update sz
			p->sz = 1 + size(p->left) + size(p->right);
			return p;
		}

		//left rotation
		Node* leftRotate(Node *p){
			//assert p is not NULL and p's right's color is red
			assert ( (p) && isRed(p->right) );
			//x point to p->right
			Node *x = p->right;	
			//p point to x->left
			//link x's left subtree to p's right
			p->right = x->left;
			//x->left point to p
			//link p to x's left
			x->left = p;
			//x's color's previous p's color
			x->color = x->left->color;
			//p's color becomes red
			x->left->color = RED;
			//x's size is p's(previous) size
			x->sz = p->sz;
			//update p's size
			p->sz = size(p->left) + size(p->right) + 1;
#ifdef DEBUG_TEST
			++NUM_OF_LEFT_ROTATION;
#endif
			return x;
		}

		//right rotation
		Node* rightRotate(Node *p){
			//assert p is not NULL
			//p's left is red
			assert ( p && isRed(p->left) );
			//x point to p's left
			Node *x = p->left;
			p->left = x->right;
			x->right = p;
			x->color = p->color;
			p->color = RED;
			x->sz = p->sz;
			p->sz = 1 + size(p->left) + size(p->right);
#ifdef DEBUG_TEST
			++NUM_OF_RIGHT_ROTATION;
#endif
			return x;
		}
		
		//return maximum node of subtree rooted at p
		Node* max(Node *p){
			if( !p ) return p;
			while( p->right ){
				p = p->right;
			}
			return p;
		}
		
		//return minimum node of subtree rooted at p
		Node* min(Node *p){
			if( !p ) return p;
			while( p->left ){
				p = p->left;
			}
			return p;
		}

		//return no. of keys in subtree rooted at p less than k
		unsigned rank(Node *p, const K &k){
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
		Node * select(Node *p, unsigned k){
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
		
		//collect all keys in increasing order
		void keys(std::deque<K> &q, Node *p){
			if( !p ) return;
			//collect left subtree
			keys(q,p->left);
			//enque p's key
			q.push_back(p->key);
			//collect right subtree
			keys(q,p->right);
		}
		
		

		Node* balance(Node *p){
			assert (p);
			
			//right is red ratate left
			if( isRed(p->right) ){
				p = leftRotate(p);
			}
			//p->left and p->left->left are red
			//rotate right
			if( isRed(p->left) && isRed(p->left->left) ){
				p = rightRotate(p);
			}
			//only two children are red
			//flip color
			if( isRed(p->left) && isRed(p->right) ){
				flipColors(p);
			}
			p->sz = 1 + size(p->left) + size(p->right);
			return p;
		}		
		Node * removeMin(Node *p){
			if( !p->left ) {
				//delete node

#ifdef DEBUG_TEST
			++NUM_OF_DELETION;
#endif
				delete p;
				return NULL;

			}
			//indicate that p->left is a 2-node
			//so...create a tmp 3-node or 4-node
			if( !isRed(p->left) && !isRed(p->left->left) ){
				p = moveRedLeft(p);
			}

			p->left = removeMin(p->left);
			return balance(p);	
		}
	
		// Assuming that p is red and both p->left and p->left->left
		// are black, make p->left or one of its children red.
		//
		// p's left is a 2-node
		// you shoud make it as a tmp 3-node, 4-node or 5-node
		// by calling this function
		// maitaining an invariant that next remove node is not a 2-node
		Node* moveRedLeft(Node *p) {
			assert (p != NULL);
			assert (isRed(p) && !isRed(p->left) && !isRed(p->left->left) );
			flipColors(p);
			//mean that p->left's right brother is a 3-node
			//and borrow one by rotation
			if (isRed(p->right->left)) { 
				//you will get a 5-node
				//but don't worry you will flip it back
				p->right = rightRotate(p->right);
				p = leftRotate(p);
			}
			//else brother is a 2-node too...
			//oh. you hurt me...
			return p;
		}


		//when p's right child is a two node
		//you should make p's right a tmp 3-node, 4-node or may 5-node
		//by calling this move red function
		//maitaining an invariant that next remove node is not a 2-node
		Node* moveRedRight(Node *p){
			//flip color and borrow
			assert (p);
			assert ( isRed(p) && !isRed(p->right) && !isRed(p->right->left) );
			flipColors(p);
			//p->right's left brother is a 3-node
			//yes borrow one by rotation
			if ( isRed(p->left->left) ){
				p = rightRotate(p);
			}
			//else 
			//I can borrow a node 
			//feeling frustrating
			return p;
		}

		Node * removeMax(Node *p){
			
			//make it a right leaning tmp 3-node 
			if( isRed(p->left) ){
				p = rightRotate(p);
			}
			//
			if( p->right == NULL ){
				//delete
#ifdef DEBUG_TEST
				++NUM_OF_DELETION;
#endif
				delete p;
				return NULL;
			}
			//p->right is a 2-node
			if( !isRed(p->right) && !isRed(p->right->left) ){
				p = moveRedRight(p);
			}
			//recursively remove max of right subtree
			p->right = removeMax(p->right);
			return balance(p);
		}

		Node* remove(Node *p, const K &k){
			//goes left
			if ( k < p->key )  {
				//p is a 2-node
				//make it a tmp 4-node,maybe 5-node
				//
				if (!isRed(p->left) && !isRed(p->left->left)){
					p = moveRedLeft(p);
				}
				//recursively remove k in subtree rooted at p->left
				p->left = remove(p->left, k);

			} else {
				//goes right or delete p
				
				//if p is a 3-node which means color of p->left is red
				//then rotate right 
				if (isRed(p->left)){
					p = rightRotate(p);
				}
				//this is the end 
				if ( k == p->key && (p->right == NULL)){
					//delete node
#ifdef DEBUG_TEST
					++NUM_OF_DELETION;
#endif
					delete p;
					return NULL;
				}

				//p's right and p's right's left are black and
				//may rotate p->left as p and then go left
				if (!isRed(p->right) && !isRed(p->right->left)){
				  	p = moveRedRight(p);
				}
				
				//k == p->key
				//swap min(p->right) and p
				//remove min of p->right
				if (k == p->key) {
					Node *x = min(p->right);
					//swap p and min(p->right) 
					p->key = x->key;
					p->value = x->value;
					//delete p->right min
					p->right = removeMin(p->right);
				}else {
					//k > p->key
					//recursively delete k subtree rooted at p->right
					p->right = remove(p->right, k);
				}
			}
			return balance(p);	
		}

		Node * floor(Node *p, const K &k){
			if( !p ) {
				return NULL;
			}
			if( k < p->key ){
				//all right subtree of p are greater than k
				return floor(p->left, k);
			}else if ( k > p->key ){
				Node *x = floor(p->right, k);
				//if there exists a node x of p->right subtree
				//that less than k, because x is greater than p
				//return x
				if( x ){
					return x;
				}else{
					//no such node x whose key is less than or equal to k
					//in subtree of p->right
					return p;
				}
			}else{
				return p;
			}
		}

		Node * ceiling(Node *p, const K &k){
			if( !p ) {
				return NULL;
			}
			if( k < p->key ){
			//k < p->key
			//left subtree may exist a smallest one than p or may not
				Node *x = ceiling(p->left, k);
				if( x ){
					//existance
					return x;
				}else{
					//not 
					return p;
				}
			}else if( k > p->key ){
			//k > p->key
				return ceiling(p->right, k);	
			}else{
			//k == p->key
				return p;
			}
		}

#ifdef DEBUG_CHECK
		bool isLeftLeaning23tree(Node *p){
			//NULL is a 2-3 tree
			if( !p ) {
				return true;
			}
			//right leaning
			if( isRed(p->right) ){
				return false;
			}
			if( p != root && isRed(p) && isRed(p->left) ){
				return false;
			}
			return isLeftLeaning23tree(p->left) 
				&& isLeftLeaning23tree(p->right);
		}
		bool isSizeConsistent(Node *p) {
			if( !p ){
				return true;
			}
			if( p->sz != 1 + size(p->left) + size(p->right) ){
				return false;
			}

			return isSizeConsistent(p->left)
				&& isSizeConsistent(p->right);
		}
		bool isBST(Node *p){
			if( !p ) {
				return true;
			}
			if( p->left ){
				Node *max_p = max(p->left);
				if( max_p && !( max_p->key < p->key ) ){
					return false;
				}
			}

			if( p->right ){
				Node *min_p = min(p->right);
				if( min_p && !(min_p->key > p->key) ){
					return false;
				}
			}	
			return isBST(p->left) && isBST(p->right);
		}
#endif
	public:
		
#ifdef DEBUG_CHECK
		bool isRankConsistent(){
			for(unsigned i=0; i<size(); ++i){
				if(i != rank( select(i) ) ){
					return false;
				}
			}
			return true;
		}
		bool isBalancedSearchTree(){
			return isBST(root);
		}
		bool isSizeConsistent()	{
			return isSizeConsistent(root);
		}
		bool isLeftLeaning23tree(){
			return isLeftLeaning23tree(root);
		}
#endif
		
		
		/*	@brief smallest key greater than or equal to k
		 *	@param k 	key
		 */
		K ceiling(const K &k){
			Node *p = ceiling(root, k);
			if( !p ){
				std::cerr << "no such key" << std::endl;
				std::cerr << "key returned is not undefined" << std::endl;
				return K();
			}
			return p->key;
		}


		/*	@brief largest key less than and equal to k
		 *	@param k	key
		 */
		K floor(const K &k){
			Node * p = floor(root, k);
			if( !p ){
				std::cerr << "no such key" << std::endl;
				std::cerr << "key returned is not undefined" << std::endl;
				return K();
			}
			return p->key;
		}

		/*	@brief 	remove a node with key equals to k
		 *			if k is not contained output an error message
		 *			
		 *	@param k key to be remove
		 */
		void remove(const K &k){
			if( !contain(k) ){
				std::cerr << "BST not contains keys " << k << std::endl;
				return ;
			}
			//if both children of root are black, set root to red	
			if( !isRed(root->left) && !isRed(root->right) ){
				root->color = RED;
			}
			root = remove(root, k);
			if( !empty() ){
				root->color = BLACK;
			}
		}
		
		/*	@brief 	remove maximum key of BST
		 *			if BST is empty, output an error message
		 */
		void removeMax(){
			if( empty() ){
				std::cerr<<"remove empty BST error..."<<std::endl;
				return ;
			}
			//if both children of root are black, set root to red
			//root is a 2-node
			//make it a tmp 3-node or 4-node by rotation
			if( !isRed(root->left) && !isRed(root->right) ){
				root->color = RED;
			}
			root = removeMax(root);
			if( !empty() ){
				root->color = BLACK;
			}

		}
		

		/*	@brief 	remove minimum key of BST
		 *			if BST is empty, output an error message
		 */
		void removeMin(){
			if( empty() ){
				std::cerr<<"remove empty BST error..."<<std::endl;
				return ;
			}
			//if both children of root are black, set root to red
			//root is a 2-node
			//make it a tmp 3-node or 4-node by rotation
			if( !isRed(root->left) && !isRed(root->right) ){
				root->color = RED;
			}
			root = removeMin(root);
			if( !empty() ){
				root->color = BLACK;
			}
		}

		/* 	@brief	return ordered keys in a queue
		 */
		std::deque<K> keys(){
			std::deque<K> q;
			keys(q, root);
			return q;
		}
		
		/*	@brief return number of BST
		 */
		unsigned size(){
			return size(root);
		}

		/*	@brief return k th key zero started
		 */
		K select(unsigned k){
			Node *p = select(root, k);
			assert(p);
			return p->key;
		}

		/*	@brief 	return number of keys less than k
		 *	@param k, K type
		 */
		unsigned rank(const K &k) {
			return rank(root, k);
		}

		/*	@brief 	return minimum key of BST
		 *			if BST is empty, output an error message
		 */
		K min (){
			Node *p = min(root);
			if( p == NULL ){
				std::cerr<<"access empty BST error..."<<std::endl;
				std::cerr<<"key returned is not defined" << std::endl;
				return K();
			}
			return p->key;
		}

		/*	@brief 	return maximum key of BST
		 *			if BST is empty, output an error message
		 */
		K max() {
			Node *p = max(root);
			if( p == NULL ){
				std::cerr<<"access empty BST error..."<<std::endl;
				std::cerr<<"key returned is not defined" << std::endl;
				return K();
			}
			return p->key;
		}

		//insert k,v pair
		/*	@brief	insert a k,v pair into BST
		 *	@param k 	key
		 *	@param v	value
		 */
		void insert( const K &k, const V &v){
			root = insert(root, k, v);	
			root->color = BLACK;
		}

		/*	@brief	return height of BST
		 *
		 */
		int height() const {
			return height(root);
		}

		/*	@brief 	return true BST is empty
		 *			else return false
		 */
		bool empty()const {
			return root == NULL;
		}
		
		/*	@brief 	return value associated with key
		 *			if k is not contained
		 *				output an error message
		 */
		V get(const K &k){
			Node *p = get(root,k);
			//assert( p );
			if( !p ){
				std::cerr<<"key is not contained..." << std::endl;
				std::cerr<<"value returned is not defined..." << std::endl;
				return V();
			}
			return p->value;
		}

		/*	@brief check if k is contained
		 *
		 */
		bool contain(const K &k){
			return ( get(root,k) != NULL );
		}
		
		/*	@brief 	default constructor
		 *			construct an empty BST
		 */
		RBTree(): root(NULL) { }
		/*	@brief 	destructor
		 *			delete all nodes
		 */
		~RBTree(){
			while( root ){
				removeMin();
			}
		}
};


#ifdef DEBUG_PRINT
template <typename Tp1, typename Tp2>
std::ostream& operator<<( std::ostream &os, const RBTNode<Tp1,Tp2> &node ){
	//current node
	os << "Key=" << node.key << " ";
	os << "Value=" << node.value << " ";
	os << "Size=" << node.sz << " ";
	os << "color=" << ( node.color? "RED" : "BLACK"  ) << std::endl;
	//left child	
	os << "left is:\t";
	if (node.left){
		os << "Key=" << node.left->key << " ";
		os << "Value=" << node.left->value << " ";
		os << "Size=" << node.left->sz << " ";
		os << "color=" << ( node.left->color? "RED" : "BLACK"  ) << std::endl;
	}else{
		os<<"NULL"<<std::endl;
	}
	//right child
	os << "right is: \t";
	if(node.right){
		os << "Key=" << node.right->key << " ";
		os << "Value=" << node.right->value << " ";
		os << "Size=" << node.right->sz << " ";
		os << "color=" << ( node.right->color? "RED" : "BLACK"  ) << std::endl;
	}else{
		os << "NULL" << std::endl;
	}
	return os;
}
//inorder print nodes
//four lines per node whose children are included
template <typename K, typename V>
std::ostream& operator<<( std::ostream &os, RBTree<K,V> &rbt){
	os << "=========red black tree structure==============="<<std::endl;
	RBTNode<K,V> *p = rbt.root;
	if( !p ) {
		os << "Empty red black tree" << std::endl;
		return os;
	}
	traverse(os, p);
	os << "=========red black tree structure the end========"<<std::endl;
	return os;
}

template <typename U, typename S>
void traverse(std::ostream &os, RBTNode<U,S> *p){
	if( !p ){
		return ;
	}
	traverse(os, p->left);
	os << *p;
	traverse(os, p->right);
}
#endif

#endif
