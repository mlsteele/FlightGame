#include "Octree.h"

template <class T>
Octree<T>::Octree (float cornerMinX, float cornerMinY, float cornerMinZ, float cornerMaxX, float cornerMaxY, float cornerMaxZ)
{
	// There has GOT to be a better way to do this!
	for (int tx = 0; tx < 2; tx++)
		for (int ty = 0; ty < 2; ty++)
			for (int tz = 0; tz < 2; tz++)
				Trees[tx][ty][tz] = NULL;
	
	CornerMin[0] = cornerMinX;
	CornerMin[1] = cornerMinY;
	CornerMin[2] = cornerMinZ;
	
	CornerMax[0] = cornerMaxX;
	CornerMax[1] = cornerMaxY;
	CornerMax[2] = cornerMaxZ;
	
	SplitPoint[0] = (CornerMin[0] + CornerMax[0]) / 2;
	SplitPoint[1] = (CornerMin[1] + CornerMax[1]) / 2;
	SplitPoint[2] = (CornerMin[2] + CornerMax[2]) / 2;
	printf("");
}

template <class T>
Octree<T>::~Octree ()
{
	for (int tx = 0; tx < 2; tx++)
		for (int ty = 0; ty < 2; ty++)
			for (int tz = 0; tz < 2; tz++)
				if (Trees[tx][ty][tz] != NULL)
					delete Trees[tx][ty][tz];
}

template <class T>
void Octree<T>::getItems (vector<T> items)
{
	// allItems extend Items
	items.insert(items.end(), Items.begin(), Items.end());
	
	for (int tx = 0; tx < 2; tx++)
		for (int ty = 0; ty < 2; ty++)
			for (int tz = 0; tz < 2; tz++)
				if (Trees[tx][ty][tz] != NULL) {
					// subItems extend Trees[tx][ty][tz]->getItems();
					Trees[tx][ty][tz]->getItems(items);
	}
}

template <class T>
void Octree<T>::fillPairs (vector<T> a, vector<T> b)
{
  for (vector<Pushable*>::iterator itA = Items.begin(); itA != Items.end(); ++itA) {
		// Pairs from below
		for (int tx = 0; tx < 2; tx++)
			for (int ty = 0; ty < 2; ty++)
				for (int tz = 0; tz < 2; tz++)
					if (Trees[tx][ty][tz] != NULL) {
						vector<T> subItems;
						Trees[tx][ty][tz]->getItems(subItems);
						for (vector<Pushable*>::iterator itB = subItems.begin(); itB != subItems.end(); ++itB) {
							a.push_back(*itA);
							b.push_back(*itB);
						}
		}
		
		// Pairs from this level
		for(vector<Pushable*>::iterator itB = itA; ++itB != Items.end();) {
			a.push_back(*itA);
			b.push_back(*itB);
		}
	}
	
	// Recurse
	for (int tx = 0; tx < 2; tx++)
		for (int ty = 0; ty < 2; ty++)
			for (int tz = 0; tz < 2; tz++)
				if (Trees[tx][ty][tz] != NULL)
					Trees[tx][ty][tz]->fillPairs(a, b);
}

template <class T>
void Octree<T>::Insert (T insertion)
{
	// Abort if too big for this cell
	if ( !(
		insertion->Pos.x - insertion->Rad > CornerMin[0] &&
		insertion->Pos.y - insertion->Rad > CornerMin[1] &&
		insertion->Pos.z - insertion->Rad > CornerMin[2] &&
		insertion->Pos.x + insertion->Rad < CornerMax[0] &&
		insertion->Pos.y + insertion->Rad < CornerMax[1] &&
		insertion->Pos.z + insertion->Rad < CornerMax[2]
	)) {
		std::cerr << "ERROR: Object too big for Octree cell.\n\t" << __FILE__ << ": " << __LINE__ << "\n";
		exit(EXIT_FAILURE);
		return;
	}
	
	// If it fits in a subcell
	for (int tx = 0; tx < 2; tx++)
		for (int ty = 0; ty < 2; ty++)
			for (int tz = 0; tz < 2; tz++) {
				
				float potentialMin[3] = {
					(tx == 0) ? CornerMin[0] : SplitPoint[0],
					(ty == 0) ? CornerMin[1] : SplitPoint[1],
					(tz == 0) ? CornerMin[2] : SplitPoint[2]
				};
				
				float potentialMax[3] = {
					(tx == 0) ? SplitPoint[0] : CornerMax[0],
					(ty == 0) ? SplitPoint[1] : CornerMax[1],
					(tz == 0) ? SplitPoint[2] : CornerMax[2]
				};
				
				if (
					insertion->Pos.x - insertion->Rad > potentialMin[0] &&
					insertion->Pos.y - insertion->Rad > potentialMin[1] &&
					insertion->Pos.z - insertion->Rad > potentialMin[2] &&
					insertion->Pos.x + insertion->Rad < potentialMax[0] &&
					insertion->Pos.y + insertion->Rad < potentialMax[1] &&
					insertion->Pos.z + insertion->Rad < potentialMax[2]
				) {
					// Insert into subcell (create subcell if not existant)
					if (Trees[tx][ty][tz] != NULL) {
						Trees[tx][ty][tz]->Insert(insertion);
					} else {
						Trees[tx][ty][tz] = new Octree(potentialMin[0], potentialMin[1], potentialMin[2], potentialMax[0], potentialMax[1], potentialMax[2]);
						Trees[tx][ty][tz]->Insert(insertion);
					}
					
					return;
				}
	}
	
	// Fits only into this cell
	Items.push_back(insertion);
}

template <class T>
void Octree<T>::Insert (vector<T> insertions)
{
	for (class std::vector<T>::iterator iInsertions = insertions.begin(); iInsertions != insertions.end(); ++iInsertions) {
		Insert(*iInsertions);
	}
}

template <class T>
void Octree<T>::Render ()
{
	glDisable(GL_LIGHTING);
	glColor3f(1, 0, 0);
	glPushMatrix();
	float oscale = CornerMax[0] - CornerMin[0];
	glTranslatef(CornerMax[0] - oscale/2, CornerMax[1] - oscale/2, CornerMax[2] - oscale/2);
	glutWireCube(oscale);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	
	for (int tx = 0; tx < 2; tx++)
		for (int ty = 0; ty < 2; ty++)
			for (int tz = 0; tz < 2; tz++)
				if (Trees[tx][ty][tz] != NULL)
					Trees[tx][ty][tz]->Render();
}

template class Octree<Pushable*>;
