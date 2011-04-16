#ifndef _ORB_H_
	#define _ORB_H_

#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#include "Pushable.h"

/// \brief Basic game sphere
class Orb : public Pushable {
	public:
		/// \brief Create with appropriate mass by radius
		Orb (V3D _pos, float _rad);
		
		/// \brief Render with appropriate radius
		void Render();
};

#endif
