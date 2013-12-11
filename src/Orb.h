#ifndef _ORB_H_
	#define _ORB_H_

#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>

#include "Pushable.h"
#include "glColor.h"

/// \brief Basic game sphere
class Orb : public Pushable {
	private:
		glColor Color;
		GLuint DL;

	public:
		/// \brief Create with appropriate mass by radius
		Orb (V3D<float> _pos, float _rad);

		/// \brief Render with appropriate radius
		void Render() const;

		/// \brief Set rendering color
		void SetColor(float r, float g, float b);
		/// \brief Return rendering color to default
		void ColorDefault();
};

#endif
