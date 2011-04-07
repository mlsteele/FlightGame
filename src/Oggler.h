#ifndef _CAPP_H_
	#define _CAPP_H_

#include <OpenGL/gl.h>
#include "v3d.h"

// Oggler OpenGL Camera
// Rotation is represented by a [pitch, yaw, roll] vector
class Oggler {
	private:
		V3D Center;
		V3D Rotation;
	
	public:
		Oggler();
		
		// State Manipulation
		void TranslateGlobal(float, float, float);
		void RotateGlobal(float, float, float);
		void TranslateLocal(float, float, float);
		void Zero();
		
		// OpenGL Action
		void View();
};

#endif
