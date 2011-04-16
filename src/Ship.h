#ifndef _SHIP_H_
	#define _SHIP_H_

#include <iostream>
#include <vector>
using std::vector;

#include "Pushable.h"
#include "Orb.h"

/// \brief Player avatar
///
/// Knows about thrust and and handles its own
class Ship : public Pushable {
	public:
		/// \brief Thrust rate represented as a local vector
		V3D Thrust;
		/// \brief Thrust factor of ship
		float ThrustFactor;
		/// \brief Rotation [Pitch, yaw, roll] vector representing rate
		V3D Rot;
		/// \brief Direction of tractor beam (positive is forward)
		int TractorDir;
		/// \brief Power factor for tractor beam
		float TractorPower;
	
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
		
		/// \brief Paint targeted orbs
		void PaintTargets (vector<Orb*> objs);
		/// \brief Effect objects in list with tractor beam
		void TractorEffect (vector<Pushable*> objs);
		/// \brief Tell tractor to pull towards ship
		inline void TractorIn () { TractorDir = -1; };
		/// \brief Tell tractor to push from ship
		inline void TractorOut () { TractorDir = 1; };
		/// \brief Turn tractor beam off
		inline void TractorOff () { TractorDir = 0; };
};

#endif
