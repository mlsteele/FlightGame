// 3 Dimension Vector
// Comprised of floats

#ifndef _V3D_H_
	#define _V3D_H_

#include <cmath>

class V3D {
	
	// Base floats
	public:
		float x;
		float y;
		float z;
	
	
	// Public Operations
	public:
	
		// Constructor zeroes vector
		inline V3D() {
			x = 0;
			y = 0;
			z = 0;
		};
		
		// Constructor sets vector
		inline V3D(float _x, float _y, float _z) {
			x = _x;
			y = _y;
			z = _z;
		};
		
		// Zeroes out floats
		inline void Zero() {
			x = 0;
			y = 0;
			z = 0;
		}
		
		// Set vector value
		inline void Set(float _x, float _y, float _z) {
			x = _x;
			y = _y;
			z = _z;
		}
		
		// Vector addition (set)
		inline V3D& operator+= (const V3D& _vec) {
			x += _vec.x;
			y += _vec.y;
			z += _vec.z;
		}
		
		// Vector subtraction (set)
		inline V3D& operator-= (const V3D& _vec) {
			x -= _vec.x;
			y -= _vec.y;
			z -= _vec.z;
		}
		
		// Scalar multiplication (set)
		inline V3D& operator*= (const float &s) {
			x *= s;
			y *= s;
			z *= s;
		}
		
		// Scalar division (set)
		inline V3D& operator/= (const float &s) {
			x /= s;
			y /= s;
			z /= s;
		}
		
		// Scalar multiplication (no set)
		inline const V3D operator* (const float &s) {
			return V3D(x*s, y*s, z*s);
		}
		
		// SpinAxis
		// Spins around the given vector
		inline void SpinAxis(float _theta, V3D _axis) {
			float u = _axis.x;
			float v = _axis.y;
			float w = _axis.z;
			
			// http://inside.mines.edu/~gmurray/ArbitraryAxisRotation/ArbitraryAxisRotation.html
			float nx = u*(u*x + v*y + w*z)*(1 - cos(_theta)) + x*cos(_theta) + (- w*y + v*z)*sin(_theta);
			float ny = v*(u*x + v*y + w*z)*(1 - cos(_theta)) + y*cos(_theta) + (w*x - u*z)*sin(_theta);
			float nz = w*(u*x + v*y + w*z)*(1 - cos(_theta)) + z*cos(_theta) + (- v*x + u*y)*sin(_theta);
			
			Set(nx, ny, nz);
		}
		
		// Length
		// Computer the length of a vector
		inline float Length() {
			return sqrt( pow(x,2) + pow(y,2) + pow(z,2) );
		}
		
		// Normalize
		// Unitize vector
		inline void Normalize() {
			float len = Length();
			x /= len;
			y /= len;
			z /= len;
		}

};

#endif