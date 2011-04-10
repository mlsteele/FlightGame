#ifndef _PUSHABLE_H_
	#define _PUSHABLE_H_

#include "Orientable.h"
#include "V3D.h"

// Pushable
// An Orientable that can be pushed
class Pushable : public Orientable {
	public:
		V3D Vel;
		V3D Accel;
		
	public:
		Pushable (V3D);
		Pushable ();
		
		inline void PushLocal (float _x, float _y, float _z) {PushLocal(V3D(_x, _y, _z));};
		void PushLocal (V3D);
		
		inline void PushGlobal (float _x, float _y, float _z) {PushGlobal(V3D(_x, _y, _z));};
		void PushGlobal (V3D);
		
		void Update ();
};

#endif
