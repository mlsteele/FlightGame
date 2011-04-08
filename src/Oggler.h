#ifndef _OGGLER_H_
	#define _OGGLER_H_

#include <iostream>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include "Orientable.h"

// Oggler OpenGL Camera
// Rotation is represented by a [pitch, yaw, roll] vector
class Oggler : public Orientable {
	public:
		Oggler();
		
		// OpenGL Action
		void View();
};

#endif
