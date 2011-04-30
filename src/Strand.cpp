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
void Strand::InfluencePair(Pushable* A, Pushable* B, bool viscize) {
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
	if (viscize) {
		k = .02; // Viscosity Constant (compiled in)
		V3D diffvel = B->Vel - A->Vel;
		force = diffvel*k;
		A->PushGlobal(force);
		B->PushGlobal(-force);
	}
}

void Strand::Update() {
	// Influence all by pairs
	for (unsigned int n = 1; n < Nodes.size(); ++n) {
		InfluencePair( Nodes[n], Nodes[n-1], true );
	}
	
	// Influence end pairs
	InfluencePair( Nodes[0], Head, false );
	InfluencePair( Nodes[Nodes.size()-1], Tail, false );
	
	// Update all internal (not ends)
	for (vector<Pushable*>::iterator itA = Nodes.begin(); itA != Nodes.end(); ++itA) {
		(**itA).Update();
	}
}

void Strand::Render() const {
	glDisable(GL_LIGHTING);
	
	// Reusable Container
	V3D diffv;
	
	// Draw and influence pairs
	for (unsigned int n = 1; n < Nodes.size(); ++n) {
		diffv = Nodes[n-1]->Pos - Nodes[n]->Pos;
		float x = diffv.Length() - MiniTargL();
		x = min(abs(x)/3.f, 1.f);
		glColor3f(x, 1-x, 0);
		glBegin(GL_LINES);
			glVertex3f(Nodes[n]->Pos.x, Nodes[n]->Pos.y, Nodes[n]->Pos.z);
			glVertex3f(Nodes[n-1]->Pos.x, Nodes[n-1]->Pos.y, Nodes[n-1]->Pos.z);
		glEnd();
	}
	
	glBegin(GL_LINES);
		diffv = Nodes[0]->Pos - Head->Pos;
		float x = diffv.Length() - MiniTargL();
		x = min(abs(x)/3.f, 1.f);
		glColor3f(x, 1-x, 0);
		glVertex3f(Nodes[0]->Pos.x, Nodes[0]->Pos.y, Nodes[0]->Pos.z);
		glVertex3f(Head->Pos.x, Head->Pos.y, Head->Pos.z);
	glEnd();
	
	glBegin(GL_LINES);
		diffv = Nodes[0]->Pos - Tail->Pos;
		x = diffv.Length() - MiniTargL();
		x = min(abs(x)/3.f, 1.f);
		glColor3f(x, 1-x, 0);
		glVertex3f(Nodes[Nodes.size()-1]->Pos.x, Nodes[Nodes.size()-1]->Pos.y, Nodes[Nodes.size()-1]->Pos.z);
		glVertex3f(Tail->Pos.x, Tail->Pos.y, Tail->Pos.z);
	glEnd();
	
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
