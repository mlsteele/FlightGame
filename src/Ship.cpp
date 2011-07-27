#include "Ship.h"

#include "Arena.h"

Ship::Ship (V3D<float> _pos, Arena* _arena)
	: Pushable(_pos, 5, 2) // Ship mass and radius
	, Thrust(V3D<float>(0, 0, 0))
	, ThrustFactor(.009)
	, RotCmd(V3D<float>(0, 0, 0))
	, RollStore(0)
	, BrakeVal(false)
	, TractorDir(0)
	, TractorPower(.04) // Tractor beam power
	, ActiveBall(NULL)
	, GrappleStrand(NULL)
{
	SArena = _arena;
}

void Ship::Update() {
	// Translation
	PushLocal(Thrust * ThrustFactor);
	
	RollStore *= .99;
	RollStore += RotCmd.z * .04;
	
	// Rotation
	Pitch(RotCmd.x);
	Yaw(RotCmd.y);
	Roll(RollStore);
	
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
	V3D<float> LF(0, 0, TractorDir * TractorPower);
	V3D<float> GF(OLTG(LF));
	
	// Apply Force
	TractorBall->PushGlobal(GF);
}

void Ship::Shoot() {
	Orb* a = SArena->Register( new Orb(Pos + Rt*3 - Up*3, .5) );
	Orb* b = SArena->Register( new Orb(Pos + Rt*3 + Up*3, .5) );
	a->Vel = Vel + Fd + Rt * (rand()/static_cast<float>(RAND_MAX)*.3 -0.15);
	b->Vel = Vel + Fd + Rt * (rand()/static_cast<float>(RAND_MAX)*.3 -0.15);
	SArena->Register(new Strand(a, b, 6));
}

// Should sync with TractorEffect();
void Ship::PaintTargets() {
	
	// Default Colors
	for (list<Orb*>::iterator itA = SArena->Orbs.begin(); itA != SArena->Orbs.end(); ++itA) {
		(**itA).ColorDefault();
	}
	
	// Color Scoped
	Orb* ToPaint = FirstInScope();
	float bt = .1;
	if (ToPaint != NULL) { ToPaint->SetColor(0.525+bt, 0.525+bt, 0.525+bt); }
	
	// Color Active
	if (ActiveBall != NULL) { ActiveBall->SetColor(.33, .33, .33); }
	
	// Color Grappled
	if (GrappleStrand) {
		static_cast<Orb*>(GrappleStrand->Head)->SetColor(.33, .33, .33);
	}
}

void Ship::ConnectOn() {
	ActiveBall = FirstInScope();
}

void Ship::ConnectOff() {
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

void Ship::GrappleOn() {
	Orb* GrappleBall = FirstInScope();
	
	// Safety
	if (GrappleBall == NULL) {return;}
	
	GrappleStrand = SArena->Register( new Strand(GrappleBall, this, (GrappleBall->Pos - Pos).Length() ) );
//	GrappleStrand = SArena->Register( new Strand(GrappleBall, this, 4 ) );
}

void Ship::GrappleOff() {
	// Safety
	if (GrappleStrand == NULL) {return;}
	
	SArena->Unregister(GrappleStrand);
	
	delete GrappleStrand;
	GrappleStrand = NULL;
}


Orb* Ship::FirstInScope() {
	Orb* theOne = NULL;
	float theZ = 1e40;
	
	for (list<Orb*>::iterator itA = SArena->Orbs.begin(); itA != SArena->Orbs.end(); ++itA) {
		V3D<float> LP = GTL((**itA).Pos); // Local position of target object
		float r = sqrt( (LP.x)*(LP.x) + (LP.y)*(LP.y) ); // Cylindrical coordinate. Cylinder long axis from eyes to back of head.
		float rmax = r + (**itA).Rad;
		float rmin = r - (**itA).Rad;
		
		// Select if in region & closer than candidate
		if (0 < rmax/LP.z && rmin/LP.z < .05 && LP.z < theZ) {
			theOne = (*itA);
			theZ = LP.z;
		}
	}
	
	return theOne;
}
