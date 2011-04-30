#ifndef _CLAW_H_
	#define _CLAW_H_

#include <vector>
using std::vector;
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#include "Pushable.h"

class Claw : public Pushable {
	public:
		/// \brief Object to which Claw is attached
		Pushable* Dolly;
		/// \brief Whether object is frozen
		bool Frozen;
		
		public:
			Claw(V3D _pos, V3D _vel);
			
			void Update();
			void Render();
			
			void AttachmentCheck(vector<Pushable*> objs);
			void Attach(Pushable* obj);
			
			inline void Freeze() {Frozen = true;};
};

#endif
