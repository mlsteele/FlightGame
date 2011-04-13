/// \brief Object in space with orientation.
/// 
/// \n Holds position (vector), and orientation (3 vectors).
/// \n Orientation is represented by right, up, and forward directions.
/// \n Default orientation uses a negative z axis as forward for OpenGL compliance.

#ifndef _ORIENTABLE_H_
	#define _ORIENTABLE_H_

#include "V3D.h"

class Orientable {
	public:
		/// Position Vector
		V3D Pos;
		/// Rotation right component
		V3D Rt;
		/// Rotation up component
		V3D Up;
		/// Rotation forward component
		V3D Fd;
	
	public:
		Orientable();
		
		// Position Manipulation
		void TranslateGlobal(float, float, float);
		void TranslateLocal(float, float, float);
		
		// Rotation
		
		/// \brief Rotate around right
		void Pitch(float);
		/// \brief Rotate around up
		void Yaw(float);
		/// \brief Rotate around forward
		void Roll(float);
		
		// Special
		void Zero();
		
		/// \brief Unitize directions if they have decayed
		void Calibrate();
};

#endif
