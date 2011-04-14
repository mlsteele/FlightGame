#ifndef _SHIP_H_
	#define _SHIP_H_

#include "Pushable.h"

class Ship : public Pushable {
	public:
		bool IsTractor;
	
	public:
		Ship (V3D _pos, float _mass);
		
		inline void TractorOn () { IsTractor = true; };
		inline void TractorOff () { IsTractor = false; };
//		void Update();		
};

#endif
