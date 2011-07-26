#ifndef _PUSHABLE_H_
	#define _PUSHABLE_H_

#include "Orientable.h"
#include "V3D.h"

/// \brief Object in physical space
/// 
/// Physical object with mass and motion

class Pushable : public Orientable {
	public:
		float Mass;
		/// \brief Radius
		float Rad;
		V3D<float> Vel;
		V3D<float> Accel;
		
	public:
		Pushable (V3D<float> _pos, float _mass, float _rad);
		
		/// \brief Push along global space
		void PushGlobal(V3D<float> _force);
		inline void PushGlobal(float _x, float _y, float _z) {PushGlobal(V3D<float>(_x, _y, _z));};
		
		/// \brief Push along local space
		void PushLocal(V3D<float> _force);
		inline void PushLocal (float _x, float _y, float _z) {PushLocal(V3D<float>(_x, _y, _z));};
		
		/// \brief Physics integration method
		virtual void Update ();
		
		// Extractor functions
		/// \brief Returns magnitude of velocity
		inline float Speed() const { return sqrt(pow(Vel.x, 2) + pow(Vel.y, 2) +	pow(Vel.z, 2));	};
};

#endif
