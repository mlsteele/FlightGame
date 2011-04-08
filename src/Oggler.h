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
	
	public:
		Oggler();
		Oggler(Orientable _dolly);
		
		// OpenGL Action
		void View();
		
		
		//// Transformations forward to orientable
		
		// Position Manipulation
		inline void TranslateGlobal(float _x, float _y, float _z)
			{Dolly->TranslateGlobal(_x, _y, _z);};
		inline void TranslateLocal(float _x, float _y, float _z)
			{Dolly->TranslateLocal(_x, _y, _z);};
		
		// Rotation
		inline void Pitch(float f)
			{Dolly->Pitch(f);};
		inline void Yaw(float f)
			{Dolly->Yaw(f);};
		inline void Roll(float f)
			{Dolly->Roll(f);};
		
		// Special
		inline void Zero()
			{Dolly->Zero();};
		inline void Calibrate()
			{Dolly->Calibrate();};

};

#endif
