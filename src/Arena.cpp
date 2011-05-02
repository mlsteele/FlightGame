#include "Arena.h"

#include "Ship.h"

Arena::Arena()
{
}

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
		
	// Render Bounds
	glColor3f(0.176, 0.094, 0.035);
	glutSolidCube(100);
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

bool Arena::CollideBounds (Pushable* obj) {
	bool hit = false;
	float rad = (*obj).Rad;
	
	// X
	if ( (*obj).Pos.x - rad < -50 ) {
		(*obj).Vel.x = fabs((*obj).Vel.x);
		(*obj).Pos.x = -50 + rad;
		hit = true;
	} else
	if ( (*obj).Pos.x + rad > 50 ) {
		(*obj).Vel.x = -fabs((*obj).Vel.x);
		(*obj).Pos.x = 50 - rad;
		hit = true;
	}
	
	// Y
	if ( (*obj).Pos.y - rad < -50 ) {
		(*obj).Vel.y = fabs((*obj).Vel.y);
		(*obj).Pos.y = -50 + rad;
		hit = true;
	} else
	if ( (*obj).Pos.y + rad > 50 ) {
		(*obj).Vel.y = -fabs((*obj).Vel.y);
		(*obj).Pos.y = 50 - rad;
		hit = true;
	}
	
	// Z
	if ( (*obj).Pos.z - rad < -50 ) {
		(*obj).Vel.z = fabs((*obj).Vel.z);
		(*obj).Pos.z = -50 + rad;
		hit = true;
	} else
	if ( (*obj).Pos.z + rad > 50 ) {
		(*obj).Vel.z = -fabs((*obj).Vel.z);
		(*obj).Pos.z = 50 - rad;
		hit = true;
	}
	
	// Wall Friction (..., yeah, that)
	if (hit) {
		(*obj).Vel *= .9;
	}
	
	return hit;
}
