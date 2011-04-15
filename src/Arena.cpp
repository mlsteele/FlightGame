#include "Arena.h"

void Arena::Update () {
	
	// Collision section
//	Collide spheres (claws, orbs, ships)
	
	
	// Updates
	// Strands
	for(std::vector<Strand*>::iterator it = Strands.begin(); it != Strands.end(); ++it) {
		(**it).Update();
	}
	
//	Update Sphericals

//	Update Ships
	for(std::vector<Ship*>::iterator it = Ships.begin(); it != Ships.end(); ++it) {
		(**it).Update();
	}
}

void Arena::Render() {
	// Strands
	for(std::vector<Strand*>::iterator st = Strands.begin(); st != Strands.end(); ++st) {
		(**st).Render();
	}
}

/*
void Arena::CollideSpheres (Pushable* A, Pushable* B) {
	if ( (A.Pos - B.Pos).Length() > (A.Rad + B.Rad) ) {
		return;
	}
	
	// One Dimensional Collision
	// http://en.wikipedia.org/wiki/Elastic_collision#One-dimensional_Newtonian
	float mA = A.Mass;
	float mB = B.Mass;
	float uA = A.Vel.Dot(ColAxis); // Starting velocity of A
	float uB = B.Vel.Dot(ColAxis); // Starting velocity of B
	float vB = ( (uA(mA-mB)) + (2*mB*uB) ) / (mA + mB); // Final 1d velocity of A
	float vB = ( (uB(mB-mA)) + (2*mB*uB) ) / (mA + mB); // Final 1d velocity of B
}
*/


/*
BLOCKING: One Dimensional Collision
pA = PushableA
pB = PushableB
mA = Mass A
mB = Mass B
uA = Starting velocity of A
uB = Starting velocity of B
vA = Result velocity of A
vB = Result velocity of B


vA = ( (uA(mA-mB)) + (2*mB*uB) ) / (mA + mB)
vB = ( (uB(mB-mA)) + (2*mB*uB) ) / (mA + mB)
*/
