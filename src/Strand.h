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
/// Strand is a linear string of pushables which cohere.

class Strand {
	private:
		/// \brief Container for nodes along strand
		vector<Pushable*> Nodes;
		/// \brief Target length of whole strand
		float TargL;
	
	public:
		/// \brief Resolution of strand (number of nodes)
		int Res;
	
	public:
		Strand(const V3D _start, const V3D _end, float _targl, int _res);
		
		/// \brief Place object into string
		void Splice(int _index, Pushable&, bool _delete);
		
		/// \brief Update members of Nodes
		void Update();
		
		/// \brief Visualize
		void Render() const;
		
		// Extractor Functions
		/// \brief Pointer to first element in string [NOT TESTED]
		inline Pushable* GetStart() const { return Nodes[ 0 ]; };
		/// \brief Pointer to last element in string [NOT TESTED]
		inline Pushable* GetEnd  () const { return Nodes[Res]; };
		/// \brief Pointer to any element in string [NOT TESTED]
		Pushable* GetIndex (int _index) const;
};

#endif
