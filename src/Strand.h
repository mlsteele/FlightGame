#ifndef _STRAND_H_
	#define _STRAND_H_


#include <iostream>
#include <vector>
#include <algorithm>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#include "Pushable.h"

using std::vector;

/// \brief Stretchy tension device
///
/// Strand is a linear string of pushables which cohere.\n
/// Ends are pushables which are interacted with but updated independently
/// \n Constants compiled in: Node Mass, Spring Constant, Viscosity Constant, Density

class Strand {
	public:
		/// \brief Container for in-between nodes
		vector<Pushable*> Nodes;
		/// \brief Pointer to head end
		Pushable* Head;
		/// \brief Pointer to tail end
		Pushable* Tail;
		/// \brief Target length of whole strand
		const float TargL;
	
	public:
		/// \param _head Head end ([0]) of strand
		/// \param _tail Tail end of strand
		/// \param _targl Target length. If negative, represents fraction of auto-distance. Defaults to auto-distance * 1.
		Strand(Pushable* _head, Pushable* _tail, float _targl = -1);
		~Strand();
		
		/// \brief Update hidden members
		///
		/// Does not update ends, those are assumed to be handled elsewhere. 
		/// Does, however, push ends.
		void Update();
		
		/// \brief Visualize
		void Render() const;
		
		// \brief Calculate target length of each partition
		inline float MiniTargL() const {return TargL / Nodes.size();};
	
	private:
		void InfluencePair(Pushable* A, Pushable* B, bool Viscize);
};

#endif
