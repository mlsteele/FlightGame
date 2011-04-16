#include "Orb.h"
#define _USE_MATH_DEFINES

Orb::Orb (V3D _pos, float _rad)
	: Pushable(
		  _pos
		, (1 /*Density*/ ) * (4.f/3.f) * M_PI * pow(_rad, 3) // Orb density compiled in
		, _rad
	)
	, Color(1, .5, .5)
{
	
}

void Orb::Render() const {
	// Draw a sphere!
	glPushMatrix();
	glTranslatef(Pos.x, Pos.y, Pos.z);
	Color.Apply();
	glutSolidSphere(Rad, 32, 32);
	glPopMatrix();
}

void Orb::SetColor(float r, float g, float b) {
	Color = glColor(r, g, b);
}

void Orb::ColorDefault() {
	Color = glColor(1, .5, .5);
}
