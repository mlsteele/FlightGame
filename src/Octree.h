#ifndef _OCTREE_H_
#define _OCTREE_H_

#include <GL/gl.h>
#include <GL/glut.h>
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
		vector<T> SubItems;
		Octree<T>* Trees[2][2][2];
		Octree<T>* Parent;

		bool PruneMe;
	public:
		Octree (float cornerMinX, float cornerMinY, float cornerMinZ, float cornerMaxX, float cornerMaxY, float cornerMaxZ);
		~Octree ();

		void getItems (vector<T>* items);
		void fillPairs (vector<T>* a, vector<T>* b);

		void Insert (T insertion);
		void Insert (vector<T>* insertions);

		void Update ();
		void Prune ();

		void Render();
};

#endif
