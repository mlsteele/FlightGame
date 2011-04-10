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
		
		float Fov;
		float Aspect;
		float Near;
		float Far;
	
	public:
		Oggler();
		Oggler(Orientable*);
		
		// Attach camera to orientable
		void Attach(Orientable*);
		
		void Settings(float _fov, float _aspect, float _near, float _far);
		
		// OpenGL Action
		void View();		
};

#endif
