#include "Strand.h"

Strand::Strand(V3D _start, V3D _end, float _targl, int _res) {
	Res= _res;
	TargL = _targl;
	
	V3D shift = _end - _start;
	Length = shift.Length();
	shift /= Res;
	
	for (int n = 0; n < Res; ++n) {
		Nodes.push_back( new Pushable(_start + shift*n) );
	}
}

void Strand::Splice(int _index, Pushable& _p, bool _delete) {
	if (_delete)
		{ delete Nodes[_index]; }
	
	Nodes[_index] = &_p;
}

void Strand::Update() {
	float MiniTargL = TargL / Res;
	float k = .01;
	
	// Influence
	for (int n = 1; n < Res; ++n) {
		V3D diffv = Nodes[n-1]->Pos - Nodes[n]->Pos;
		float x = diffv.Length() - MiniTargL;
		// F [varies with] k*x
		diffv = diffv.Normalized()*x*k;
		Nodes[n]->PushGlobal(diffv);
		Nodes[n-1]->PushGlobal(-diffv);
	}
	
	// Updates
	for (int n = 0; n < Res; ++n) {
		Nodes[n]->Update();
	}
}

void Strand::Render() {
	for (int n = 1; n < Res; ++n) {
		glPushMatrix();
		glColor3f(.8, .8, .4);
		glBegin(GL_LINES);
			glVertex3f(Nodes[n]->Pos.x, Nodes[n]->Pos.y, Nodes[n]->Pos.z);
			glVertex3f(Nodes[n-1]->Pos.x, Nodes[n-1]->Pos.y, Nodes[n-1]->Pos.z);
		glEnd();
		glPopMatrix();
	}
}
