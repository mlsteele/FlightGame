#include "Strand.h"

Strand::Strand(Pushable* _head, Pushable* _tail, float _targl) 
	: Head(_head)
	, Tail(_tail)
	// If negative, represents fraction of auto-distance
	, TargL(_targl >= 0 ? _targl : (_tail->Pos - _head->Pos).Length() * -_targl)
{
	// nNodes is the number of nodes in between the two ends
	unsigned int nNodes = ceil(TargL* 2 ); // Density of nodes
	V3D<float> shift = _tail->Pos - _head->Pos;
	shift /= nNodes+1;
	
	// Create nodes along string
	for (unsigned int n = 1; n < nNodes+1; ++n) {
		Nodes.push_back( new Pushable( _head->Pos + shift*n
			, .05 // Mass of string nodes
			, .22853907486704164 // Radius of string nodes
		) );
	}
}

Strand::~Strand() {
	for(std::vector<Pushable*>::iterator it = Nodes.begin(); it != Nodes.end(); ++it) {
		delete *it;
	}
}

// Private helper function
void Strand::InfluencePair(Pushable* A, Pushable* B, bool viscize) {
	float k;
	V3D<float> diffp = B->Pos - A->Pos;
	V3D<float> force;
	
	// F [varies with] k*x
	k = .012; // Spring Constant
	float x = diffp.Length() - MiniTargL();
	force = diffp.Normalized()*x*k;
	A->PushGlobal(force);
	B->PushGlobal(-force);
	
	// Viscosity
	if (viscize) {
		k = .015; // Viscosity Constant
		V3D<float> diffvel = B->Vel - A->Vel;
		force = diffvel*k;
		A->PushGlobal(force);
		B->PushGlobal(-force);
	}
}

void Strand::Update() { for (int c = 0; c < 5; ++c) {
	// Influence all by pairs
	for (unsigned int n = 1; n < Nodes.size(); ++n) {
		InfluencePair( Nodes[n], Nodes[n-1], true );
	}
	
	// Influence end pairs
	InfluencePair( Nodes[0], Head, false );
	InfluencePair( *Nodes.rbegin(), Tail, false );
	
	
	// Update all internal nodes (not ends)
	for (vector<Pushable*>::iterator itA = Nodes.begin(); itA != Nodes.end(); ++itA) {
		(**itA).Update();
	}
}}

void Strand::Render() const {
	glDisable(GL_LIGHTING);
	
	// Reusables
	V3D<float> diffv;
	float x;
	
	// Draw and influence pairs
	for (unsigned int n = 1; n < Nodes.size(); ++n) {
		diffv = Nodes[n-1]->Pos - Nodes[n]->Pos;
		x = diffv.Length() - MiniTargL();
		x = fmin(abs(x)/3.f, 1.f);
		glColor3f(0.867, 0.867, 0.867);
		glBegin(GL_LINES);
			glVertex3f(Nodes[n]->Pos.x, Nodes[n]->Pos.y, Nodes[n]->Pos.z);
			glVertex3f(Nodes[n-1]->Pos.x, Nodes[n-1]->Pos.y, Nodes[n-1]->Pos.z);
		glEnd();
	}
	
	glBegin(GL_LINES);
		diffv = Nodes[0]->Pos - Head->Pos;
		x = diffv.Length() - MiniTargL();
		x = fmin(fabs(x)/3.f, 1.f);
		glColor3f(0.867, 0.867, 0.867);
		glVertex3f(Nodes[0]->Pos.x, Nodes[0]->Pos.y, Nodes[0]->Pos.z);
		glVertex3f(Head->Pos.x, Head->Pos.y, Head->Pos.z);
	glEnd();
	
	glBegin(GL_LINES);
		diffv = (*Nodes.rbegin())->Pos - Head->Pos;
		x = diffv.Length() - MiniTargL();
		x = fmin(fabs(x)/3.f, 1.f);
		glColor3f(0.867, 0.867, 0.867);
		glVertex3f((*Nodes.rbegin())->Pos.x, (*Nodes.rbegin())->Pos.y, (*Nodes.rbegin())->Pos.z);
		glVertex3f(Tail->Pos.x, Tail->Pos.y, Tail->Pos.z);
	glEnd();
	
	glEnable(GL_LIGHTING);
}
