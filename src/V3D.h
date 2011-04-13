// 3 dimensional vector
// Comprised of floats
/// \brief 3 Dimensional Vector
/// 
/// Holder for floats as well as common vector operations

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
		inline void Set(float _x, float _y, float _z) {Set(V3D(_x, _y, _z));};
		inline void Set(V3D _in) {
			x = _in.x;
			y = _in.y;
			z = _in.z;
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
		
		// Negation
		inline const V3D operator- () const {
			return V3D(-x, -y, -z);
		}
		
		// Vector Addition (no set)
		inline const V3D operator+ (const V3D& _v) const {
			return V3D(*this) += _v;
		}
		
		// Vector Subtraction (no set)
		inline const V3D operator- (const V3D& _v) const {
			return V3D(*this) -= _v;
		}
		
		// Scalar Multiplication (no set)
		inline const V3D operator* (const float &s) const {
			return V3D(x*s, y*s, z*s);
		}
		
		// Scalar Divison (no set)
		inline const V3D operator/ (const float &s) const {
			return V3D(x/s, y/s, z/s);
		}
		
		/// \brief Spins around the given UNIT vector
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
		inline float Length() const {
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
		
		// Normalized
		// Unitize vector and return
		inline const V3D Normalized() const {
			V3D result = V3D(x, y, z);
			result.Normalize();
			return result;
		}

};

#endif