#include <iostream>
#include <vector>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#include "Pushable.h"

using std::vector;

class Strand {
	private:
		vector<Pushable> Nodes;
		float Length;
		float TargL;
	
	public:
		int Res;
	
	public:
		inline Strand() {};
		Strand(V3D _start, V3D _end, float _targl, int _res);
		
		void SetStart(Pushable&);
		
		void Update();
		
		void Render();
		
		// Extractor Functions
		inline Pushable GetStart() {return Nodes[ 0 ];};
		inline Pushable GetEnd  () {return Nodes[Res];};
};
