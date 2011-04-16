#include "Orb.h"
#define _USE_MATH_DEFINES

Orb::Orb (V3D _pos, float _rad)
	: Pushable(
		  _pos
		, (1 /*Density*/ ) * (4.f/3.f) * M_PI * pow(_rad, 3) // Orb density compiled in
		, _rad
	)
{
	
}

void Orb::Render() {
	// Draw a sphere!
	glPushMatrix();
	glTranslatef(Pos.x, Pos.y, Pos.z);
	glColor3f(1, .5, .5);
	glutSolidSphere(Rad, 32, 32);
	glPopMatrix();
}
