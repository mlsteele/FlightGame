#ifndef _ORIENTABLE_H_
	#define _ORIENTABLE_H_

#include "V3D.h"

/// \brief Object in space with orientation.
/// 
/// \n Holds position (vector), and orientation (3 vectors).
/// \n Orientation is represented by right, up, and forward directions.
/// \n Default orientation uses a negative z axis as forward for OpenGL compliance.

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
		
		// Translation
		
		/// \brief Translates along global space
		void TranslateGlobal(V3D _offset);
		inline void TranslateGlobal (float _x, float _y, float _z) {TranslateGlobal(V3D(_x, _y, _z));};
		
		/// \brief Translates along local space
		void TranslateLocal(V3D _offset);
		inline void TranslateLocal (float _x, float _y, float _z) {TranslateLocal(V3D(_x, _y, _z));};
		
		// Rotation
		
		/// \brief Rotate around right
		void Pitch(float);
		/// \brief Rotate around up
		void Yaw(float);
		/// \brief Rotate around forward
		void Roll(float);
		
		/// \brief Return to default orientation and position
		void Zero();
		
		/// \brief Unitize directions if they have decayed
		void Calibrate();
};

#endif
