#ifndef _SHIP_H_
	#define _SHIP_H_

#include <iostream>
#include <vector>
using std::vector;

#include "Pushable.h"
#include "Orb.h"
#include "Strand.h"

class Arena;

/// \brief Player avatar
///
/// Knows about thrust and and handles its own
class Ship : public Pushable {
	public:
		/// \brief World it's in
		Arena* SArena;
		
		/// \brief Thrust rate represented as a local vector
		V3D<float> Thrust;
		/// \brief Thrust factor of ship
		float ThrustFactor;
		/// \brief Rotation [Pitch, yaw, roll] vector representing command rate
		V3D<float> RotCmd;
		/// \brief Rotational roll velocity store
		float RollStore;
		/// \brief Whether or not the brake is on
		bool BrakeVal;
		
		/// \brief Direction of tractor beam (positive is forward)
		int TractorDir;
		/// \brief Power factor for tractor beam
		float TractorPower;
		
		Orb* ActiveBall;
		Strand* GrappleStrand;
	
	public:
		Ship (V3D<float> _pos, Arena* _arena);
		
		/// \brief Add to thrust
		inline void AddThrust(V3D<float> _jerk) { Thrust += _jerk; }
		inline void AddThrust(float _x, float _y, float _z) {AddThrust(V3D<float>(_x,_y,_z));};
		/// \brief Zero out thrust
		inline void KillThrust() { Thrust.Zero(); };
		
		/// \brief Add to rotation [pitch, yaw, roll]
		inline void AddRot(V3D<float> _rot) { RotCmd += _rot;};
		inline void AddRot(float _pitch, float _yaw, float _roll) {AddRot(V3D<float>(_pitch,_yaw,_roll));};
		/// \brief Add to pitch
		inline void AddPitch(float _pitch) { RotCmd.x += _pitch; };
		/// \brief Add to yaw
		inline void AddYaw(float _yaw) { RotCmd.y += _yaw; };
		/// \brief Add to roll
		inline void AddRoll(float _roll) { RotCmd.z += _roll; };
		/// \brief Zero out rotation
		inline void KillRot() { RotCmd.Zero(); };
		
		// AirBrake
		/// \brief Turn on the air brake
		inline void BrakeOn()  {BrakeVal = true;};
		/// \brief Turn off the air brake
		inline void BrakeOff() {BrakeVal = false;};
		
		/// \brief Physics Update
		void Update();
		
		/// \brief Shoot!
		void Shoot();
		/// \brief Paint targeted orbs
		void PaintTargets();
		/// \brief Effect objects in list with tractor beam
		void TractorEffect();
		/// \brief Tell tractor to pull towards ship
		inline void TractorIn () { TractorDir = -1; };
		/// \brief Tell tractor to push from ship
		inline void TractorOut () { TractorDir = 1; };
		/// \brief Turn tractor beam off
		inline void TractorOff () { TractorDir = 0; };
		
		void ConnectOn();
		void ConnectOff();
		
		void GrappleOn();
		void GrappleOff();
		
		private:
			Orb* FirstInScope();
};

#endif
