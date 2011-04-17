#include "Arena.h"

void Arena::Update () {	
	vector<Pushable*> sphericals;
	sphericals.insert( sphericals.end(), Orbs.begin(), Orbs.end() );
	sphericals.insert( sphericals.end(), Ships.begin(), Ships.end() );
	
	vector<Pushable*> tractorables;
	tractorables.insert( tractorables.end(), Orbs.begin(), Orbs.end() );
	tractorables.insert( tractorables.end(), Ships.begin(), Ships.end() );
	
	vector<Pushable*> boundables;
	boundables.insert( boundables.end(), Orbs.begin(), Orbs.end() );
	boundables.insert( boundables.end(), Ships.begin(), Ships.end() );
	
	// Collision section
	// Collide sphericals
	for (vector<Pushable*>::iterator itA = sphericals.begin(); itA != sphericals.end(); ++itA) {
		for(vector<Pushable*>::iterator itB = itA; ++itB != sphericals.end();) {
			FluffyCollideSpheres( *itA, *itB );
		}
	}
	
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
		(**it).PaintTargets(Orbs);
		(**it).TractorEffect(tractorables);
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
	
	// Render Bounds
	glColor3f(.6, .6, .6);
	glutSolidCube(200);
}


/// Uses fluffy collision.\n
/// If objects are intersecting, use a spring from the farthest intersecting surface.
bool Arena::FluffyCollideSpheres (Pushable* A, Pushable* B) {
	// Information
	float distance = (A->Pos - B->Pos).Length();
	float mindist = (A->Rad + B->Rad);
	
	// Do nothing if there is no collision
	if ( distance > mindist ) {
		return false;
	}
	
	V3D ColAxis = (A->Pos - B->Pos).Normalized();
	
	// Fluffy collision
	float k = 6.1; // Fluffiness constant
	A->PushGlobal( ColAxis * (distance-mindist) * -k );
	B->PushGlobal( ColAxis * (distance-mindist) * k );
	return true;
}

/* DEPRECATED physically accurate collision
	
	// One Dimensional Collision
	// http://en.wikipedia.org/wiki/Elastic_collision#One-dimensional_Newtonian
	float mA = A->Mass;
	float mB = B->Mass;
	float uA = A->Vel.Dot(ColAxis); // Starting velocity of A
	float uB = B->Vel.Dot(ColAxis); // Starting velocity of B
	
	// Calculate new velocities
	float vA = ( (uA*(mA-mB)) + (2*mB*uB) ) / (mA + mB); // Final 1d velocity of A
	float vB = ( (uB*(mB-mA)) + (2*mA*uA) ) / (mA + mB); // Final 1d velocity of B
	
	// Zero velocity in collision axis
	A->Vel -= ColAxis * uA;
	B->Vel -= ColAxis * uB;
	
	// Apply calculated velocities
	A->Vel += ColAxis * vA;
	B->Vel += ColAxis * vB;
*/

bool Arena::CollideBounds (Pushable* obj) {
	bool hit = false;
	float rad = (*obj).Rad;
	
	// X
	if ( (*obj).Pos.x - rad < -100 ) {
		(*obj).Vel.x = fabs((*obj).Vel.x);
		(*obj).Pos.x = -100 + rad;
		hit = true;
	} else
	if ( (*obj).Pos.x + rad > 100 ) {
		(*obj).Vel.x = -fabs((*obj).Vel.x);
		(*obj).Pos.x = 100 - rad;
		hit = true;
	}
	
	// Y
	if ( (*obj).Pos.y - rad < -100 ) {
		(*obj).Vel.y = fabs((*obj).Vel.y);
		(*obj).Pos.y = -100 + rad;
		hit = true;
	} else
	if ( (*obj).Pos.y + rad > 100 ) {
		(*obj).Vel.y = -fabs((*obj).Vel.y);
		(*obj).Pos.y = 100 - rad;
		hit = true;
	}
	
	// Z
	if ( (*obj).Pos.z - rad < -100 ) {
		(*obj).Vel.z = fabs((*obj).Vel.z);
		(*obj).Pos.z = -100 + rad;
		hit = true;
	} else
	if ( (*obj).Pos.z + rad > 100 ) {
		(*obj).Vel.z = -fabs((*obj).Vel.z);
		(*obj).Pos.z = 100 - rad;
		hit = true;
	}
	
	// Wall Friction (..., yeah, that)
	if (hit) {
		(*obj).Vel *= .9;
	}
	
	return hit;
}
