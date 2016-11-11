// ===============================================
// @file   text_Pool.cpp
// @author kmurphy
// @brief  Test driver for class Pool
// ===============================================

#include <iostream>
#include "Pool.h"
#include "Vector2f.h"

using namespace std;

int main () {
	cout <<"Testing class Pool ... \n";
	
	Pool<Vector2f> pool(5);
	
	cout <<"Empty pool ... \n";
	cout <<pool <<endl;
	
	cout <<"Allocate a all elements ... \n";
	for (int k=0; k<pool.capacity(); ++k) {
		Vector2f & a = pool.allocate();
		a.x = k;
		cout <<&a <<" " <<&(pool[k]) <<"\t " <<pool.size() <<endl;
	}
	cout <<pool <<endl;
	
	cout <<"Deleting element 2 ... \n";
	pool.free(2);
	for (int k=0; k<pool.size(); ++k) {
		cout <<&(pool[k]) <<endl;
	}
	cout <<pool <<endl;

	cout <<"Deleting all elements (individually) ... \n";
	while (!pool.isEmpty()) {
		pool.free(0);
		cout <<pool <<endl;
	}
	
	cout <<"Fill pool and loop over elements while some elements are being deleted ... \n";
	while (!pool.isFull()) {
		Vector2f & a = pool.allocate();
		a.x = pool.size();
	}
	cout <<pool <<endl;

	int k = 0;
	while (k<pool.size()) {
		Vector2f & a = pool[k];
		a.y = 1;				// set y coodinate to ensure all elements are visited
		if (randomBool()) {
			pool.free(k);		// free random element (simulate bullet disappearing)
		} else {
			k++;				// process next bullet 
		}
	}
	cout <<pool <<endl;
}



