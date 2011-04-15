#ifndef _ARENA_H_
	#define _ARENA_H_

#include <vector>
using std::vector;

#include "Pushable.h"
#include "Ship.h"
//#include "Orb.h"
#include "Strand.h"

class Arena {
	public:
//		vector<Orb*>		Orbs;
		vector<Ship*>		Ships;
//		vector<Claw*>		Claws;
		vector<Strand*> 	Strands;
	
	public:
//		inline void Register(Orb* _op)		{ Orbs.push_back(_op); };
		inline void Register(Ship* _op)		{ Ships.push_back(_op); };
		inline void Register(Strand* _op)	{ Strands.push_back(_op); };
		
		void Update();
		void Render();
		
		void CollideSpheres (Pushable* sphereA, Pushable* sphereB);
};

#endif
