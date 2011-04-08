#ifndef _CAPP_H_
	#define _CAPP_H_

#include <iostream>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include "V3D.h"

// Oggler OpenGL Camera
// Rotation is represented by a [pitch, yaw, roll] vector
class Oggler {
	public:
		V3D Center;
		V3D Rt;
		V3D Up;
		V3D Fd;
	
	public:
		Oggler();
		
		// Position Manipulation
		void TranslateGlobal(float, float, float);
		void TranslateLocal(float, float, float);
		
		// Rotation
		void Pitch(float);
		void Yaw(float);
		void Roll(float);
		
		// Special
		void Zero();
		void Calibrate();
		
		// OpenGL Action
		void View();
};

#endif
