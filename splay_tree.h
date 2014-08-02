/*
 * =====================================================================================
 *
 *       Filename:  splay_tree.h
 *
 *    Description:  definition of splay tree
 *
 *        Version:  1.0
 *        Created:  07/31/2014 06:13:54 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */

#include <functional>

#ifndef SPLAY_TREE
#define SPLAY_TREE



/*
 *	splay tree node template class
 *	template type T must be overload copy constructor
 *	and comparable
 */
template <typename T> struct node {
	node<T> *left, *right;
	node<T> *parent;
	T key;
	node( const T& init = T( ) ) : left( 0 ), right( 0 ), parent( 0 ), key( init ) { }
};




template< typename T, typename Comp = std::less< T > >
class splay_tree {
	private:
		//compare function
		Comp comp;
		//no. of node
		unsigned long p_size;
		//root node of splay tree
		//a node is root when its parent is null
		node<T> *root;

		//rotate left
		// 1. y replaces x and becomes x's parent
		// 2. x becomes y's left child
		// 3. y's left child becomes x's right child
		void left_rotate( node<T> *x ) {
			node<T> *y = x->right;
			x->right = y->left;
			if( y->left ) 
			  	y->left->parent = x;
			
			y->parent = x->parent;

			//x is root
			if( !x->parent ){
			  	root = y;
			}else if( x == x->parent->left ){ //x is its parent's left child 
			  	x->parent->left = y;
			}else{	// x is its parent's right child 
			  	x->parent->right = y;
			}
			y->left = x;
			x->parent = y;
		}

		//right rotate
		//	1. y replaces x and becomes x's parent
		//  2. x becomes y's right child
		//  3. y's right child becomes x's left child
		void right_rotate( node<T> *x ) {
			node<T> *y = x->left;
			x->left = y->right;

			//y has right child
			if( y->right ){ 
			  	y->right->parent = x;
			}
			
			y->parent = x->parent;
			//x is root then y becomes root after rotation
			if( !x->parent ){ 
			  	root = y;
			}else if( x == x->parent->left ) {	//x is its parent's left child before rotation
			  	x->parent->left = y;
			}else {		//x is its parent's right child before rotation
			  	x->parent->right = y;
			}
			y->right = x;
			x->parent = y;
		}

		void splay( node<T> *x ) {
			//splay until x's parent is root
			while( x->parent ) {
				//x's grandparent is root
				if( !x->parent->parent ) {
					//x is a left child
					if( x->parent->left == x ){ 
					  	right_rotate( x->parent );
					}else{	//x is a right child
					  left_rotate( x->parent );
					}
				//x is a left child and so is its parent 
				} else if( x->parent->left == x && x->parent->parent->left == x->parent ) {
					right_rotate( x->parent->parent );
					right_rotate( x->parent );
				//x is a right child and so is its parent
				} else if( x->parent->right == x && x->parent->parent->right == x->parent ) {
					left_rotate( x->parent->parent );
					left_rotate( x->parent );
				//x is a left child and its parent is a right child
				} else if( x->parent->left == x && x->parent->parent->right == x->parent ) {
					right_rotate( x->parent );
					left_rotate( x->parent );
				//x is a right child and its parent is a left child
				} else {
					left_rotate( x->parent );
					right_rotate( x->parent );
				}
			}
		}
	
		//replace tree rooted in u by tree rooted in v
		//v can be null which means delete u
		void replace( node<T> *u, node<T> *v ) {
			//u is root then set v to be root
			if( !u->parent ) {
			  	root = v;
			}else if( u == u->parent->left ) {
			  	u->parent->left = v;
			}else{ 
			  	u->parent->right = v;
			}

			if( v ) {
			  	v->parent = u->parent;
			}
		}

		//find the minimun of a tree rooted in u
		node<T> * subtree_minimum( node<T> *u ) {
			while( u->left ) 
			  	u = u->left;
			return u;
		}

		//find the maximum of a tree rooted in u
		node<T> * subtree_maximum( node<T> *u ) {
			while( u->right ) 
			  	u = u->right;
			return u;
		}
	public:
		//default constructor
		splay_tree() :  p_size( 0 ),  root( 0 ) { }

		void insert( const T &key ) {
			
			node<T> *z = root;
			// p is the parent of new node
			node<T> *p = 0;

			while( z ) {
				p = z;
				if( comp( z->key, key ) ) {
					z = z->right;
				}else{
					z = z->left;
				}
			}

			z = new node<T>( key );
			z->parent = p;
			//p is null means that the tree is empty
			if( !p ) {
				root = z;
			}else if( comp( p->key, z->key ) ) {
				p->right = z;
			}else {
				p->left = z;
			}
			
			//splay z to the root
			splay( z );
			//increase size of node 
			p_size++;
		}
		
		//return the node pointer with key equals key
		node<T>* find( const T &key ) {
			node<T> *z = root;
			while( z ) {
				if( comp( z->key, key ) ) {
					z = z->right;
				}else if( comp( key, z->key ) ){
					z = z->left;
				}else {
					return z;
				}
			}
			return 0;
		}
		
		//delete node with key equals key
		void erase( const T &key ) {
			node<T> *z = find( key );
			//not contain	
			if( !z ) return;
			//splay to root
			splay( z );
			
			//left is null
			if( !z->left ) {
				replace( z, z->right );
			//right is null
			}else if( !z->right ) {
				replace( z, z->left );
			//both left and right are not null
			//using the right child's maximun as the root
			}else {
				node<T> *y = subtree_minimum( z->right );
				if( y->parent != z ) {
					replace( y, y->right );
					y->right = z->right;
					y->right->parent = y;
				}
				//set y as root
				replace( z, y );

				//link z's left child to y's left child
				y->left = z->left;
				y->left->parent = y;
			}

			delete z;
			p_size--;
		}
		
		//returning the minimun key
		const T& minimum( ) { 
			return subtree_minimum( root )->key; 
		}
		//returning the maximun key
		const T& maximum( ) { 
			return subtree_maximum( root )->key; 
		}

		bool empty( ) const { 
			return root == 0; 
		}
		unsigned long size( ) const { 
			return p_size; 
		}
};

#endif // SPLAY_TREE
