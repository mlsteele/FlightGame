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
		
		/// \brief Convert from local to global space
		inline V3D LTG(V3D L) const {
			V3D G = (Rt * L.x) + (Up * L.y) + (Fd * L.z);
			G += Pos;
			return G;
		}
		/// \brief Convert from global to local space
		inline V3D GTL(V3D G) const {
			V3D L(G);
			L -= Pos;
			L = V3D(Rt.Dot(L), Up.Dot(L), Fd.Dot(L));
			return L;
		}
		
		/// \brief Convert from local orientation to global orientation
		inline V3D OLTG(V3D L) const {
			V3D G = (Rt * L.x) + (Up * L.y) + (Fd * L.z);
			return G;
		}
		/// \brief Convert from global orientation to local orientation
		inline V3D OGTL(V3D G) const {
			V3D L(G);
			L = V3D(Rt.Dot(L), Up.Dot(L), Fd.Dot(L));
			return L;
		}
};

#endif
