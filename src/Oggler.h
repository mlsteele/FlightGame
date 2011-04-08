#ifndef _OGGLER_H_
	#define _OGGLER_H_

#include <iostream>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include "Orientable.h"

// Oggler OpenGL Camera
// Attached to an Orientable, attempts to emulate interface
class Oggler {
	public:
		// Orientable to which the camera is attached
		Orientable* Dolly;
		bool OwnDolly;
	
	public:
		Oggler();
		Oggler(Orientable*);
		
		// OpenGL Action
		void View();		
};

#endif
