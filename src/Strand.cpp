#include "Strand.h"

Strand::Strand(const V3D _start, const V3D _end, float _targl, int _res) {
	Res = _res;
	TargL = _targl;
	
	V3D shift = _end - _start;
	shift /= Res;
	
	for (int n = 0; n < Res; ++n) {
		Nodes.push_back( new Pushable( _start + shift*n, .01 ) );
	}
}

/// Replace the pushable at [_index] with the input
/// Index 0 is string beginning, index -1 is string end
void Strand::Splice(int _index, Pushable& _p, bool _delete) {
	if (_delete)
		{ delete Nodes[_index]; }
	
	if (_index < 0) {
		_index = Nodes.size() + _index;
	}
	
	// Safety check
	if ( _index >= (int) Nodes.size() ) {
		std::cerr << "ERROR: Strand splice out of bounds\n\tFile: " << __FILE__ << "\n\tLine: " << __LINE__ << "\n";
		return;
	}
	
	Nodes[_index] = &_p;
}

void Strand::Update() {
	float MiniTargL = TargL / Nodes.size();
	
	// Influence
	for (unsigned int n = 1; n < Nodes.size(); ++n) {
		float k;
		V3D diffp = Nodes[n-1]->Pos - Nodes[n]->Pos;
		V3D force;
		
		// F [varies with] k*x
		k = .001;
		float x = diffp.Length() - MiniTargL;
		force = diffp.Normalized()*x*k;
		Nodes[n]->PushGlobal(force);
		Nodes[n-1]->PushGlobal(-force);
		
		// Viscosity
		k = .001;
		V3D diffvel = Nodes[n-1]->Vel - Nodes[n]->Vel;
		force = diffvel*k;
		Nodes[n]->PushGlobal(force);
		Nodes[n-1]->PushGlobal(-force);
	}
	
	// Updates
	for (unsigned int n = 0; n < Nodes.size(); ++n) {
		Nodes[n]->Update();
	}
}

void Strand::Render() const {
	float MiniTargL = TargL / Nodes.size();
	
	for (unsigned int n = 1; n < Nodes.size(); ++n) {
		glPushMatrix();
		V3D diffv = Nodes[n-1]->Pos - Nodes[n]->Pos;
		float x = diffv.Length() - MiniTargL;
		x = min(abs(x)/MiniTargL, 1.f);
		glColor3f(x, 1-x, 0);
		glBegin(GL_LINES);
			glVertex3f(Nodes[n]->Pos.x, Nodes[n]->Pos.y, Nodes[n]->Pos.z);
			glVertex3f(Nodes[n-1]->Pos.x, Nodes[n-1]->Pos.y, Nodes[n-1]->Pos.z);
		glEnd();
		glPopMatrix();
	}
}

Pushable* Strand::GetIndex (int _index) const {
	if (_index < 0) {
		_index = Nodes.size() + _index;
	}
	
	// Safety check
	if ( _index >= (int) Nodes.size() ) {
		std::cerr << "ERROR: Strand retrieve out of bounds\n\tFile: " << __FILE__ << "\n\tLine: " << __LINE__ << "\n";
	}
	
	return Nodes[_index];
}
