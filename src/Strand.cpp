#include "Strand.h"

Strand::Strand(Pushable* _head, Pushable* _tail, float _targl)
	: TargL(_targl)
{
	// nNodes is the number of nodes in between the two ends
	unsigned int nNodes = ceil(TargL* 1 ); // Density of nodes (compiled in)
	V3D shift = _tail->Pos - _head->Pos;
	shift /= nNodes+1;
	
	// Create nodes along string
	Nodes.push_back(_head);
	for (unsigned int n = 1; n < nNodes+1; ++n) {
		Nodes.push_back( new Pushable( _head->Pos + shift*n,
			.05 // Mass of string nodes (compiled in)
		) );
	}
	Nodes.push_back(_tail);
}

void Strand::Update() {
	// Length of each segment
	float MiniTargL = TargL / Nodes.size();
	
	// Influence all by pairs
	for (unsigned int n = 1; n < Nodes.size(); ++n) {
		float k;
		V3D diffp = Nodes[n-1]->Pos - Nodes[n]->Pos;
		V3D force;
		
		// F [varies with] k*x
		k = .005; // Spring Constant (compiled in)
		float x = diffp.Length() - MiniTargL;
		force = diffp.Normalized()*x*k;
		Nodes[n]->PushGlobal(force);
		Nodes[n-1]->PushGlobal(-force);
		
		// Viscosity
		k = .01; // Viscosity Constant (compiled in)
		V3D diffvel = Nodes[n-1]->Vel - Nodes[n]->Vel;
		force = diffvel*k;
		Nodes[n]->PushGlobal(force);
		Nodes[n-1]->PushGlobal(-force);
	}
	
	// Update all internal (not ends)
	for (unsigned int n = 1; n < Nodes.size()-1; ++n) {
		Nodes[n]->Update();
	}
}

void Strand::Render() const {
	float MiniTargL = TargL / Nodes.size();
	
	// Draw and influence pairs
	for (unsigned int n = 1; n < Nodes.size(); ++n) {
		glPushMatrix();
		V3D diffv = Nodes[n-1]->Pos - Nodes[n]->Pos;
		float x = diffv.Length() - MiniTargL;
		x = min(abs(x)/3.f, 1.f);
		glColor3f(x, 1-x, 0);
		glBegin(GL_LINES);
			glVertex3f(Nodes[n]->Pos.x, Nodes[n]->Pos.y, Nodes[n]->Pos.z);
			glVertex3f(Nodes[n-1]->Pos.x, Nodes[n-1]->Pos.y, Nodes[n-1]->Pos.z);
		glEnd();
		glPopMatrix();
	}
	
	// Draw all nodes (including ends)
	for (unsigned int n = 0; n < Nodes.size(); ++n) {
		glColor3f(.5, .5, .9);
		glPushMatrix();
		glTranslatef(Nodes[n]->Pos.x, Nodes[n]->Pos.y, Nodes[n]->Pos.z);
		glutSolidSphere(.05, 4, 4);
		glPopMatrix();
	}
}
