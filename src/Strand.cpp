#include "Strand.h"

Strand::Strand(Pushable* _head, Pushable* _tail, float _targl) 
	: Head(_head)
	, Tail(_tail)
	, TargL(_targl)
{
	// nNodes is the number of nodes in between the two ends
	unsigned int nNodes = ceil(TargL* 2 ); // Density of nodes (compiled in)
	V3D shift = _tail->Pos - _head->Pos;
	shift /= nNodes+1;
	
	// Create nodes along string
	for (unsigned int n = 1; n < nNodes+1; ++n) {
		Nodes.push_back( new Pushable( _head->Pos + shift*n
			, .05 // Mass of string nodes (compiled in)
			, .22853907486704164 // Radius of string nodes (compiled in)
		) );
	}
}

// Private helper function
void Strand::InfluencePair(Pushable* A, Pushable* B) {
	float k;
	V3D diffp = B->Pos - A->Pos;
	V3D force;
	
	// F [varies with] k*x
	k = .007; // Spring Constant (compiled in)
	float x = diffp.Length() - MiniTargL();
	force = diffp.Normalized()*x*k;
	A->PushGlobal(force);
	B->PushGlobal(-force);
	
	// Viscosity
	k = .02; // Viscosity Constant (compiled in)
	V3D diffvel = B->Vel - A->Vel;
	force = diffvel*k;
	A->PushGlobal(force);
	B->PushGlobal(-force);
}

void Strand::Update() {
	// Influence all by pairs
	for (unsigned int n = 1; n < Nodes.size(); ++n) {
		InfluencePair( Nodes[n], Nodes[n-1] );
	}
	
	// Influence end pairs
	InfluencePair( Nodes[0], Head );
	InfluencePair( Nodes[Nodes.size()-1], Tail );
	
	// Update all internal (not ends)
	for (vector<Pushable*>::iterator itA = Nodes.begin(); itA != Nodes.end(); ++itA) {
		(**itA).Update();
	}
}

void Strand::Render() const {
	glDisable(GL_LIGHTING);
	
	// Draw and influence pairs
	for (unsigned int n = 1; n < Nodes.size(); ++n) {
		glPushMatrix();
		V3D diffv = Nodes[n-1]->Pos - Nodes[n]->Pos;
		float x = diffv.Length() - MiniTargL();
		x = min(abs(x)/3.f, 1.f);
		glColor3f(x, 1-x, 0);
		glBegin(GL_LINES);
			glVertex3f(Nodes[n]->Pos.x, Nodes[n]->Pos.y, Nodes[n]->Pos.z);
			glVertex3f(Nodes[n-1]->Pos.x, Nodes[n-1]->Pos.y, Nodes[n-1]->Pos.z);
		glEnd();
		glPopMatrix();
	}
	
/*
	// Draw all nodes (including ends)
	for (unsigned int n = 0; n < Nodes.size(); ++n) {
		glColor3f(.5, .5, .9);
		glPushMatrix();
		glTranslatef(Nodes[n]->Pos.x, Nodes[n]->Pos.y, Nodes[n]->Pos.z);
		glutSolidSphere(.05, 4, 4);
		glPopMatrix();
	}
*/
	
	glEnable(GL_LIGHTING);
}
