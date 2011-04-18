#ifndef _ARENA_H_
	#define _ARENA_H_

#include <vector>
using std::vector;
#include <fstream>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

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
		
		/// \brief Graphis have been setup
		bool BB_COMPILED;
		/// \brief Bounding Box List ID
		GLuint BB_DL;
	
	public:
		/// \brief Constructor loads bounding model
		Arena();
		/// \brief Compile display list (call after lighting!)
		void GraphicsSetup();
		
		/// \brief Run physics updates on all objects in arena
		void Update();
		/// \brief Render physical objects
		void Render();
		
		/// \brief Register Orb into arena
		inline Orb* 	Register(Orb* _op)		{ Orbs.push_back(_op); return _op; };
		/// \brief Register Ship into arena
		inline Ship* 	Register(Ship* _op)		{ Ships.push_back(_op); return _op; };
//		inline Claw* 	Register(Ship* _op)		{ Claws.push_back(_op); return _op; };
		/// \brief Register Strand into arena
		inline Strand* 	Register(Strand* _op)	{ Strands.push_back(_op); return _op; };
		
		/// \brief Enact a soft elastic collision on two pushables
		/// \return Whether collision occured
		bool FluffyCollideSpheres (Pushable* sphereA, Pushable* sphereB);
		/// \brief Collide with arena walls
		/// \return Whether collision occured
		bool CollideBounds (Pushable* obj);
};

#endif
