/// \brief Object in physical space
/// 
/// Physical object with mass and motion

#ifndef _PUSHABLE_H_
	#define _PUSHABLE_H_

#include "Orientable.h"
#include "V3D.h"

// Pushable
// An Orientable that can be pushed
class Pushable : public Orientable {
	public:
		float Mass;
		V3D Vel;
		V3D Accel;
		
	public:
		Pushable (V3D _pos, float _mass);
		
		inline void PushLocal (float _x, float _y, float _z) {PushLocal(V3D(_x, _y, _z));};
		void PushLocal(V3D _force);
		
		inline void PushGlobal(float _x, float _y, float _z) {PushGlobal(V3D(_x, _y, _z));};
		void PushGlobal(V3D _force);
		
		/// \brief Physics integration method
		void Update ();
		
		// Extractor functions
		/// \brief Returns magnitude of velocity
		inline float Speed() const { return sqrt(pow(Vel.x, 2) + pow(Vel.y, 2) +	pow(Vel.z, 2));	};
};

#endif
