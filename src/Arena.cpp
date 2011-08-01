#include "Arena.h"

#include "Ship.h"

Arena::Arena()
: asize(100)
, FrameTree(NULL)
{}

void Arena::Update () {	
	vector<Pushable*> tractorables;
	tractorables.insert( tractorables.end(), Orbs.begin(), Orbs.end() );
	tractorables.insert( tractorables.end(), Ships.begin(), Ships.end() );
	
	vector<Pushable*> boundables;
	boundables.insert( boundables.end(), Orbs.begin(), Orbs.end() );
	boundables.insert( boundables.end(), Ships.begin(), Ships.end() );
	
	// Collisions
	vector<Pushable*> colloids;
	colloids.insert( colloids.end(), Orbs.begin(), Orbs.end() );
	colloids.insert( colloids.end(), Ships.begin(), Ships.end() );
	float octMax = asize + 40;
	float octMin = -asize - 40;
	delete FrameTree;
	FrameTree = new Octree<Pushable*>(octMin, octMin, octMin, octMax, octMax, octMax);
  FrameTree->Insert(colloids);
	FrameTree->Render();
//	vector<Pushable*> colloidsA;
//	vector<Pushable*> colloidsB;
//	frameTree.fillPairs(colloidsA, colloidsB);
//	vector<Pushable*>::iterator itA = colloidsA.begin();
//	vector<Pushable*>::iterator itB = colloidsB.begin();
//	while ( itA != colloidsA.end() && itB != colloidsB.end() ) {
//		FluffyCollideSpheres( *itA, *itB );
//		++itA;
//		++itB;
//	}
		
	// Bounding Box
	for(std::vector<Pushable*>::iterator it = boundables.begin(); it != boundables.end(); ++it) {
		CollideBounds(*it);
	}
		
	// Update Strands
	for(std::vector<Strand*>::iterator it = Strands.begin(); it != Strands.end(); ++it) {
		(**it).Update();
	}
	
	// Update Orbs
	for(std::vector<Orb*>::iterator it = Orbs.begin(); it != Orbs.end(); ++it) {
		(**it).Update();
	}

	// Update Ships
	for(std::vector<Ship*>::iterator it = Ships.begin(); it != Ships.end(); ++it) {
		(**it).Update();
		(**it).TractorEffect();
	}
}

void Arena::Render() {
	// Strands
	for(std::vector<Strand*>::iterator it = Strands.begin(); it != Strands.end(); ++it) {
		(**it).Render();
	}
	
	// Orbs
	for(std::vector<Orb*>::iterator it = Orbs.begin(); it != Orbs.end(); ++it) {	
		(**it).Render();
	}
	
	// Render Octree
	FrameTree->Render();
	
	// Render Bounds
//	glColor3f(.6, .6, .6);
//	glutSolidCube(asize*2);
}

/// Uses fluffy collision.\n
/// If objects are intersecting, use a spring from the farthest intersecting surface.
bool Arena::FluffyCollideSpheres (Pushable* A, Pushable* B) {
	// Information
	float distanceSq = (A->Pos - B->Pos).LengthSq();
	float mindistSq = (A->Rad + B->Rad) * (A->Rad + B->Rad);
	
	// Do nothing if there is no collision
	if ( distanceSq > mindistSq ) {
		return false;
	}
	
	V3D<float> ColAxis = (A->Pos - B->Pos).Normalized();
	
//	// Operate directly on position to eliminate overlap
//	float offBy = sqrt(mindistSq) - sqrt(distanceSq);
//	A->Pos += ColAxis * offBy;
//	B->Pos -= ColAxis * offBy;
	
	// Fluffy collision
//	float k = 6.1; // Fluffiness constant
//	A->PushGlobal( ColAxis * (distance-mindist) * -k );
//	B->PushGlobal( ColAxis * (distance-mindist) * k );
	
//	// Weird collision
//	A->Pos += ColAxis * ( A->Mass / (A->Mass + B->Mass) ) * (mindist - distance);
//	B->Pos -= ColAxis * ( B->Mass / (A->Mass + B->Mass) ) * (mindist - distance);
	
	// Abort if going in the right direction (kiss efficiency goodbye!)
	if ( B->Vel.Dot(ColAxis) < A->Vel.Dot(ColAxis) ) {
		// Report a hit(, a very palpable hit), but carry on.
		return true;
	}
	
	float mA = A->Mass;
	float mB = B->Mass;
	float uA = A->Vel.Dot(ColAxis); // Starting velocity of A
	float uB = B->Vel.Dot(ColAxis); // Starting velocity of B
	
//	// Physically Accurate Elastic (1D) Collision
//	// http://en.wikipedia.org/wiki/Elastic_collision#One-dimensional_Newtonian
//	float vA = ( (uA*(mA-mB)) + (2*mB*uB) ) / (mA + mB); // Final 1d velocity of A
//	float vB = ( (uB*(mB-mA)) + (2*mA*uA) ) / (mA + mB); // Final 1d velocity of B
	
	// Physically Inelastic Elastic (1D) Collision
	// http://en.wikipedia.org/wiki/Inelastic_collision
	float Cr = .5; // Coefficient of elasticity
	float vA = ( Cr*mB*(uB-uA) + (mA*uA) +(mB*uB) ) / (mA + mB); // Final 1d velocity of A
	float vB = ( Cr*mA*(uA-uB) + (mA*uA) +(mB*uB) ) / (mA + mB); // Final 1d velocity of B
	
	// Zero velocity in collision axis
	A->Vel -= ColAxis * uA;
	B->Vel -= ColAxis * uB;
	
	// Apply calculated velocities
	A->Vel += ColAxis * vA;
	B->Vel += ColAxis * vB;

	return true;
}

bool Arena::CollideBounds (Pushable* obj) {
	bool hit = false;
	float rad = (*obj).Rad;
	
	// X
	if ( (*obj).Pos.x - rad < -asize ) {
		(*obj).Vel.x = fabs((*obj).Vel.x);
		(*obj).Pos.x = -asize + rad;
		hit = true;
	} else
	if ( (*obj).Pos.x + rad > asize ) {
		(*obj).Vel.x = -fabs((*obj).Vel.x);
		(*obj).Pos.x = asize - rad;
		hit = true;
	}
	
	// Y
	if ( (*obj).Pos.y - rad < -asize ) {
		(*obj).Vel.y = fabs((*obj).Vel.y);
		(*obj).Pos.y = -asize + rad;
		hit = true;
	} else
	if ( (*obj).Pos.y + rad > asize ) {
		(*obj).Vel.y = -fabs((*obj).Vel.y);
		(*obj).Pos.y = asize - rad;
		hit = true;
	}
	
	// Z
	if ( (*obj).Pos.z - rad < -asize ) {
		(*obj).Vel.z = fabs((*obj).Vel.z);
		(*obj).Pos.z = -asize + rad;
		hit = true;
	} else
	if ( (*obj).Pos.z + rad > asize ) {
		(*obj).Vel.z = -fabs((*obj).Vel.z);
		(*obj).Pos.z = asize - rad;
		hit = true;
	}
	
	// Wall Friction (..., yeah, that)
	if (hit) {
		(*obj).Vel *= .9;
	}
	
	return hit;
}
