#include <iostream>
#include <vector>
#include <algorithm>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#include "Pushable.h"

using std::vector;
using std::min;

class Strand {
	private:
		vector<Pushable*> Nodes;
		float Length;
		float TargL;
	
	public:
		int Res;
	
	public:
		Strand(V3D _start, V3D _end, float _targl, int _res);
		
		void Splice(int _index, Pushable&, bool _delete);
		
		void Update();
		
		void Render();
		
		// Extractor Functions
		inline Pushable* GetStart() {return Nodes[ 0 ];};
		inline Pushable* GetEnd  () {return Nodes[Res];};
};
