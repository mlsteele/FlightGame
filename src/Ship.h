#ifndef _SHIP_H_
	#define _SHIP_H_

#include "Pushable.h"

class Ship : public Pushable {
	public:
		/// \brief Thrust represented as a local vector
		V3D Thrust;
		/// \brief Rotation [Pitch, yaw, roll] vector representing rate
		V3D Rot;
		bool IsTractor;
	
	public:
		Ship (V3D _pos, float _mass);
		
		inline void AddThrust(float _x, float _y, float _z) {AddThrust(V3D(_x,_y,_z));};
		inline void AddThrust(V3D _jerk) { Thrust += _jerk; };
		inline void KillThrust() { Thrust.Zero(); };
		
		inline void AddRot(float _pitch, float _yaw, float _roll) {AddRot(V3D(_pitch,_yaw,_roll));};
		inline void AddRot(V3D _rot) { Rot += _rot; };
		inline void AddPitch(float _pitch) { Rot.x += _pitch; };
		inline void AddYaw(float _yaw) { Rot.y += _yaw; };
		inline void AddRoll(float _roll) { Rot.z += _roll; };
		inline void KillRot() { Rot.Zero(); };
		
		void Update();
		
		inline void TractorOn () { IsTractor = true; };
		inline void TractorOff () { IsTractor = false; };
};

#endif
