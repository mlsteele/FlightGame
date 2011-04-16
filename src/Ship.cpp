#include "Ship.h"

Ship::Ship (V3D _pos)
	: Pushable(_pos, 5, 2) // Ship mass and radius compiled in
	, Thrust(V3D(0, 0, 0))
	, ThrustFactor(.006)
	, Rot(V3D(0, 0, 0))
	, TractorDir(0)
	, TractorPower(.004) // Tractor beam power compiled in
{
	
}

void Ship::Update() {
	PushLocal(Thrust * ThrustFactor);
	Pitch(Rot.x);
	Yaw(Rot.y);
	Roll(Rot.z);
	Pushable::Update();
}

void Ship::TractorEffect (vector<Pushable*> objs) {
	// Power switch
	if (TractorDir == 0) {return;}
	
	// Effect
	for (vector<Pushable*>::iterator itA = objs.begin(); itA != objs.end(); ++itA) {
		// Local position of target object
		V3D LP = GTL((**itA).Pos);
		
		// Abort if out of region
		float r = sqrt( (LP.x)*(LP.x) + (LP.y)*(LP.y) ); // pythagorean theorem
		float rmax = r + (**itA).Rad;
		float rmin = r - (**itA).Rad;
		if (not(
			// TODO: Define smarter cone
			0 < rmax/LP.z && rmin/LP.z < .1 // Define region
		)) {
			continue;
		}
		
		// Local Force
		V3D LF(0, 0, TractorDir * TractorPower);
		
		// Apply
		(**itA).Vel += (OLTG(LF));
	}
}

// Should sync with TractorEffect();
void Ship::PaintTargets (vector<Orb*> objs) {
	// Effect
	for (vector<Orb*>::iterator itA = objs.begin(); itA != objs.end(); ++itA) {
		// Local position of target object
		V3D LP = GTL((**itA).Pos);
		
		// Abort if out of region
		float r = sqrt( (LP.x)*(LP.x) + (LP.y)*(LP.y) ); // pythagorean theorem
		float rmax = r + (**itA).Rad;
		float rmin = r - (**itA).Rad;
		if (not(
			0 < rmax/LP.z && rmin/LP.z < .1 // Define region
		)) {
			(**itA).ColorDefault();
			continue;
		}
		
		// Paint
		(**itA).SetColor(.5, 1, .5);
	}
}
