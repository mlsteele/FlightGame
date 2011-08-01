#ifndef _OCTREE_H_
#define _OCTREE_H_

#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <vector>
using std::vector;

#include "Pushable.h"

template <class T>
class Octree {
	public:
		float CornerMin[3];
		float CornerMax[3];
		float SplitPoint[3];
		
		vector<T> Items;
		Octree<T>* Trees[2][2][2];
	
	public:
		Octree (float cornerMinX, float cornerMinY, float cornerMinZ, float cornerMaxX, float cornerMaxY, float cornerMaxZ);
		~Octree ();
		
		vector<T> getItems ();
		void fillPairs (vector<T> a, vector<T> b);
		
		void Insert (T insertion);
		void Insert (vector<T> insertions);
		
		void Render();
};

#endif
