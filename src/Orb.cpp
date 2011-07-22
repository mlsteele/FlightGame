#include "Orb.h"
#define _USE_MATH_DEFINES

Orb::Orb (V3D _pos, float _rad)
	: Pushable(
		  _pos
		, (1 /*Density*/ ) * (4.f/3.f) * M_PI * pow(_rad, 3) // Orb density compiled in
		, _rad
	)
	, Color( 0.525, 0.525, 0.525 )
{
//	float SurfaceArea = 4*M_PI*pow(_rad,2);
	int res = 2;
	if (_rad <= 3.) {
		res = 16;
	} else if (_rad <= 20.) {
		res = 20;
	} else {
		std::cerr << "ERROR: Sphere bigger than I know how to draw!\n\t" << __FILE__ << ": " << __LINE__ << "\n";
	}
	
	// Setup Rendering Display List
	DL = glGenLists(1);
	
	glNewList(DL, GL_COMPILE);
	glutSolidSphere(Rad, res, res);
	glEndList();
}

void Orb::Render() const {
	// Draw a sphere!
	glPushMatrix();
	glTranslatef(Pos.x, Pos.y, Pos.z);
	Color.Apply();
	glCallList(DL);
	glPopMatrix();
}

void Orb::SetColor(float r, float g, float b) {
	Color = glColor(r, g, b);
}

void Orb::ColorDefault() {
	Color = glColor(0.525, 0.525, 0.525);
}
