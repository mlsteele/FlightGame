#include "Claw.h"

Claw::Claw (V3D _pos, V3D _vel)
	: Pushable(_pos, .02, 0.168389)
	, Dolly(NULL)
	, Frozen(false)
{
	Vel = _vel;
}

void Claw::Update() {
	// Abort
	if (Frozen) {
		return;
	}
	
	// Not attached
	if (Dolly == NULL) {
//		Pushable::Update();
		Pos += Vel;
	}
	
	// Attached
	else {
		Pos = Dolly->Pos;
		// Transfer momentum to Dolly
		Dolly->PushGlobal(Accel*Mass);
		Accel.Zero();
	}
}

void Claw::Render() {
	glPushMatrix();
	glTranslatef(Pos.x, Pos.y, Pos.z);
	
	if (Dolly == NULL) {
		glColor3f(.3, .3, .3);
	} else {
		glColor3f(1, 1, 1);
	}
	
	glutSolidSphere(Rad, 8, 8);
	glPopMatrix();
}

void Claw::AttachmentCheck (vector<Pushable*> objs) {
	// abort if already attached
	if (Dolly != NULL) {return;}
	
	// Iterate through objs
	for (vector<Pushable*>::iterator itA = objs.begin(); itA != objs.end(); ++itA) {
		// If collision then attach
		if (
			(Pos - (**itA).Pos).Length() <= (**itA).Rad
		) {
			Attach(*itA);
			return;
		}
		
	}
}

void Claw::Attach (Pushable* obj) {
	Dolly = obj;
	Vel.Zero();
}
