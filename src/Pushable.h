#ifndef _PUSHABLE_H_
	#define _PUSHABLE_H_

#include <iostream>
#include "V3D.h"

// Orientable
// An object space which exists in global space
// Rotation is represented by a [pitch, yaw, roll] vectors
class Pushable {
	public:
		V3D Pos;
		V3D Vel;
		V3D Accel;
	
	public:
		// Initialize zeroed
		Pushable();
		// Initialize with given position and zero velocity
		Pushable(float, float, float);
		Pushable(V3D&);
		// Initialize with given position and velocity
		Pushable(float, float, float, float, float, float);
		Pushable(V3D&, V3D&);
		
		// Zero Position and Velocity
		void Zero();
		// Direct Position Manipulation
		void SetPos(float, float, float);
		void SetPos(V3D);
		
		// Physics
		void PushGlobal(V3D);
		void PushGlobal(float, float, float);
		void PushLocal(V3D); // Only valid for Pushable & Orientable!
		void PushLocal(float, float, float); // Only valid for Pushable & Orientable!
		void Update();
};

#endif
