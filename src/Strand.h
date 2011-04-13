#ifndef _STRAND_H_
	#define _STRAND_H_


#include <iostream>
#include <vector>
#include <algorithm>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#include "Pushable.h"

using std::vector;
using std::min;

/// \brief Stretchy tension device
///
/// Strand is a linear string of pushables which cohere.\n
/// Ends are pushables which are interacted with but updated independently
/// \n Constants compiled in: Node Mass, Spring Constant, Viscosity Constant, Density

class Strand {
	private:
		/// \brief Container for nodes and ends along strand
		vector<Pushable*> Nodes;
		/// \brief Target length of whole strand
		float TargL;
	
	public:
		/// \param _head Head end ([0]) of strand
		/// \param _tail Tail end of strand
		/// \param _targl Target length
		Strand(Pushable* _head, Pushable* _tail, float _targl);
		
		/// \brief Update hidden members
		///
		/// Does not update ends, those are assumed to be handled elsewhere. 
		/// Does, however, push ends.
		void Update();
		
		/// \brief Visualize
		void Render() const;
};

#endif
