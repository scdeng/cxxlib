/*
 * =====================================================================================
 *
 *       Filename:  queue.h
 *
 *    Description:  FIFO queue data structure
 *
 *        Version:  1.0
 *        Created:  08/04/2014 10:04:43 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */

#include "list.h"

/*
 *	FIFO queue data structure
 *	adapter
 *	using list as data structure
 *
 */
template <typename T> class Queue{
private:
	List<T> data;
	size_t sz;

};
