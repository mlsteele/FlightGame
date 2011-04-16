#ifndef _ARENA_H_
	#define _ARENA_H_

#include <vector>
using std::vector;

#include "Pushable.h"
#include "Ship.h"
#include "Orb.h"
#include "Strand.h"

/// \brief Physical object container
class Arena {
	public:
		vector<Orb*>		Orbs;
		vector<Ship*>		Ships;
//		vector<Claw*>		Claws;
		vector<Strand*> 	Strands;
	
	public:
		/// \brief Register Orb into arena
		inline Orb* 	Register(Orb* _op)		{ Orbs.push_back(_op); return _op; };
		/// \brief Register Ship into arena
		inline Ship* 	Register(Ship* _op)		{ Ships.push_back(_op); return _op; };
//		inline Claw* 	Register(Ship* _op)		{ Claws.push_back(_op); return _op; };
		/// \brief Register Strand into arena
		inline Strand* 	Register(Strand* _op)	{ Strands.push_back(_op); return _op; };
		
		/// \brief Run physics updates on all objects in arena
		void Update();
		/// \brief Render autonomous physical objects
		void Render();
		
		/// \brief Enact a soft elastic collision on two pushables
		void FluffyCollideSpheres (Pushable* sphereA, Pushable* sphereB);
};

#endif
