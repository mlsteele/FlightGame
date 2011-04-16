#ifndef _SHIP_H_
	#define _SHIP_H_

#include "Pushable.h"

/// \brief Player avatar
///
/// Knows about thrust and and handles its own
class Ship : public Pushable {
	public:
		/// \brief Thrust rate represented as a local vector
		V3D Thrust;
		/// \brief Rotation [Pitch, yaw, roll] vector representing rate
		V3D Rot;
		/// \brief [NOT READY]
		bool IsTractor;
	
	public:
		Ship (V3D _pos);
		
		/// \brief Add to thrust
		inline void AddThrust(V3D _jerk) { Thrust += _jerk; }
		inline void AddThrust(float _x, float _y, float _z) {AddThrust(V3D(_x,_y,_z));};
		/// \brief Zero out thrust
		inline void KillThrust() { Thrust.Zero(); };
		
		/// \brief Add to rotation [pitch, yaw, roll]
		inline void AddRot(V3D _rot) { Rot += _rot;};
		inline void AddRot(float _pitch, float _yaw, float _roll) {AddRot(V3D(_pitch,_yaw,_roll));};
		/// \brief Add to pitch
		inline void AddPitch(float _pitch) { Rot.x += _pitch; };
		/// \brief Add to yaw
		inline void AddYaw(float _yaw) { Rot.y += _yaw; };
		/// \brief Add to roll
		inline void AddRoll(float _roll) { Rot.z += _roll; };
		/// \brief Zero out rotation
		inline void KillRot() { Rot.Zero(); };
		
		/// \brief Use thrust and rotation and call pushable update
		void Update();
		
		/// \brief [NOT READY]
		inline void TractorOn () { IsTractor = true; };
		/// \brief [NOT READY]
		inline void TractorOff () { IsTractor = false; };
};

#endif
