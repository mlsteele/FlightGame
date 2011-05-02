#include "Ship.h"

#include "Arena.h"

Ship::Ship (V3D _pos, Arena* _arena)
	: Pushable(_pos, 5, 2) // Ship mass and radius compiled in
	, Thrust(V3D(0, 0, 0))
	, ThrustFactor(.009)
	, Rot(V3D(0, 0, 0))
	, BrakeVal(false)
	, TractorDir(0)
	, TractorPower(.04) // Tractor beam power compiled in
	, ActiveBall(NULL)
{
	SArena = _arena;
}

void Ship::Update() {
	// Translation
	PushLocal(Thrust * ThrustFactor);
	
	// Rotation
	Pitch(Rot.x);
	Yaw(Rot.y);
	Roll(Rot.z);
	
	// AirBrake
	if (BrakeVal){
		if (Vel.Length() > 0) {
			Vel += -Vel.Normalized()*.002;
		}
	}
	
	// Update Physics
	Pushable::Update();
}

void Ship::TractorEffect() {
	// Power switch
	if (TractorDir == 0) {return;}
	
	// Ball Safety
	Orb* TractorBall = FirstInScope();
	if (TractorBall == NULL) {return;}
	
	// Local Force
	V3D LF(0, 0, TractorDir * TractorPower);
	V3D GF(OLTG(LF));
	
	// Apply Force
	TractorBall->PushGlobal(GF);
}

// Should sync with TractorEffect();
void Ship::PaintTargets() {
	
	// Default Colors
	for (vector<Orb*>::iterator itA = SArena->Orbs.begin(); itA != SArena->Orbs.end(); ++itA) {
		(**itA).ColorDefault();
	}
	
	// Color Scoped
	Orb* ToPaint = FirstInScope();
	if (ToPaint != NULL) { ToPaint->SetColor(0.263, 0.525, 0.745); }
	
	// Color Active
	if (ActiveBall != NULL) { ActiveBall->SetColor(.5, 1, .5); }
}

void Ship::FireOn() {
	ActiveBall = FirstInScope();
}

void Ship::FireOff() {
	Orb* SecondBall = FirstInScope();
	
	// Safeties
	if (ActiveBall == NULL)       {ActiveBall = NULL; return;}
	if (SecondBall == NULL)       {ActiveBall = NULL; return;}
	if (ActiveBall == SecondBall) {ActiveBall = NULL; return;}
	
	// Creation of Strand
	SArena->Register( new Strand (
			  ActiveBall
			, SecondBall
			, 4
	));
	
	ActiveBall = NULL;
}

Orb* Ship::FirstInScope() {
	Orb* theOne = NULL;
	float theZ = 1e40;
	
	for (vector<Orb*>::iterator itA = SArena->Orbs.begin(); itA != SArena->Orbs.end(); ++itA) {
		// Local position of target object
		V3D LP = GTL((**itA).Pos);
		
		// Abort if out of region
		float r = sqrt( (LP.x)*(LP.x) + (LP.y)*(LP.y) ); // pythagorean theorem
		float rmax = r + (**itA).Rad;
		float rmin = r - (**itA).Rad;
		if (not(
			0 < rmax/LP.z && rmin/LP.z < .05 // Define region
		)) {
			continue;
		}
		
		// Pick the closest
		if (LP.z < theZ) {
			theOne = (*itA);
			theZ = LP.z;
		}
	}
	
	return theOne;
}
