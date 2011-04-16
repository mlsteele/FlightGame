#ifndef _OGGLER_H_
	#define _OGGLER_H_

#include <iostream>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#include "Orientable.h"

/// \brief OpenGL Camera
/// 
/// A camera class which can modify OpenGL stack to mimic camera movement.
/// \n Attaches to an Orientable

// Oggler OpenGL Camera
// Attached to an Orientable, attempts to emulate interface
class Oggler {
	public:
		/// \brief Orientable to which the camera is attached
		Orientable* Dolly;
		/// \brief Whether the current dolly is one used for the sole purpose of carrying the camera
		bool OwnDolly;
		
		/// \brief Field of view
		float Fov;
		/// \brief Aspect ratio to display to
		float Aspect;
		/// \brief Near clipping plane
		float Near;
		/// \brief Far clipping plane
		float Far;
	
	public:
		Oggler();
		Oggler(Orientable*);
		
		/// \brief Attach camera to orientable
		void Attach(Orientable*);
		
		/// \brief Assign sight parameters
		void Settings(float _fov, float _aspect, float _near, float _far);
		
		/// \brief Applies MODELVIEW transformation
		void ViewModel();
		/// \brief Applies PERSPECTIVE transformation
		void ViewPerspective();
};

#endif
