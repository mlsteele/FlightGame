#ifndef _DUMBSHIP_H_
	#define _DUMBSHIP_H_

#include "Orientable.h"
#include "V3D.h"

// Dumb Testing Ship
// Inherits from Orientable, some basics physics
class DumbShip : public Orientable {
	public:
		V3D Accel;
		V3D Vel;
	
	public:
		
		inline void Zero() {
			Accel.Zero();
			Vel.Zero();
			((Orientable*)this)->Zero();
		};
		
		inline void PushGlobal(V3D& _pushv) {
			Accel += _pushv;
		};
		
		inline void PushGlobal(float _x, float _y, float _z) {
			Accel += V3D(_x, _y, _z);
		};
		
		inline void PushLocal(V3D& _pushv) {
			Accel += Rt * _pushv.x;
			Accel += Up * _pushv.y;
			Accel += Fd * _pushv.z;
		};
		
		inline void PushLocal(float _x, float _y, float _z) {
			Accel += Rt * _x;
			Accel += Up * _y;
			Accel += Fd * _z;
		};
		
		inline void AirBrake(float factor) {
			Vel *= factor;
		};
		
		void Update() {
			Vel += Accel;
			Pos += Vel;
			Accel.Zero();
		};
};

#endif
