#ifndef _ORIENTABLE_H_
	#define _ORIENTABLE_H_

#include <iostream>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include "V3D.h"

// Orientable
// An object space which exists in global space
// Rotation is represented by a [pitch, yaw, roll] vectors
class Orientable {
	public:
		V3D Pos;
		V3D Rt;
		V3D Up;
		V3D Fd;
	
	public:
		Orientable();
		
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
