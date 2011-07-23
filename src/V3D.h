// 3 dimensional vector
// Comprised of floats
/// \brief 3 Dimensional Vector
/// 
/// Holder for 3 floats as well as common vector operations

#ifndef _V3D_H_
	#define _V3D_H_

#include <iostream>
#include <cmath>

class V3D {
	
	// Base floats
	public:
		/// \brief x-axis component
		float x;
		/// \brief y-axis component
		float y;
		/// \brief z-axis component
		float z;
	
	
	// Public Operations
	public:
	
		/// \brief Constructs a default zero vector
		inline V3D() {
			x = 0;
			y = 0;
			z = 0;
		};
		
		/// \brief Constructor sets vector to floats
		inline V3D(float _x, float _y, float _z) {
			x = _x;
			y = _y;
			z = _z;
		};
		
		/// \brief Zeroes out components
		inline void Zero() {
			x = 0;
			y = 0;
			z = 0;
		};
		
		/// \brief Set vector value
		inline void Set(float _x, float _y, float _z) {Set(V3D(_x, _y, _z));};
		/// \brief Set vector value
		inline void Set(V3D _in) {
			x = _in.x;
			y = _in.y;
			z = _in.z;
		};
		
		/// \brief Vector addition (set)
		inline V3D& operator+= (const V3D& _vec) {
			x += _vec.x;
			y += _vec.y;
			z += _vec.z;
			return *this;
		};
		
		/// \brief Vector subtraction (set)
		inline V3D& operator-= (const V3D& _vec) {
			x -= _vec.x;
			y -= _vec.y;
			z -= _vec.z;
			return *this;
		};
		
		/// \brief Scalar multiplication (set)
		inline V3D& operator*= (const float &s) {
			x *= s;
			y *= s;
			z *= s;
			return *this;
		};
		
		/// \brief Scalar division (set)
		inline V3D& operator/= (const float &s) {
			x /= s;
			y /= s;
			z /= s;
			return *this;
		};
		
		/// \brief Negation
		inline const V3D operator- () const {
			return V3D(-x, -y, -z);
		};
		
		/// \brief Vector Addition (no set)
		inline const V3D operator+ (const V3D& _v) const {
			return V3D(*this) += _v;
		};
		
		/// \brief Vector Subtraction (no set)
		inline const V3D operator- (const V3D& _v) const {
			return V3D(*this) -= _v;
		};
		
		/// \brief Scalar Multiplication (no set)
		inline const V3D operator* (const float &s) const {
			return V3D(*this) *= s;
		};
		
		/// \brief Scalar Divison (no set)
		inline const V3D operator/ (const float &s) const {
			return V3D(x/s, y/s, z/s);
		};
		
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
		};
		
		/// \brief Compute the length of a vector
		inline float Length() const {
			return sqrt( x*x + y*y + z*z );
		};
		
		/// \brief Compute the length squared of a vector
		inline float LengthSq() const {
			return x*x + y*y + z*z;
		};
		
		/// \brief Normalize vector into unit (set)
		inline void Normalize() {
			float len = Length();
			x /= len;
			y /= len;
			z /= len;
		};
		
		/// \brief Return normalized vector
		inline const V3D Normalized() const {
			V3D result = V3D(x, y, z);
			result.Normalize();
			return result;
		};
		
		/// \brief Dot product of two vectors
		inline float Dot(const V3D& _v) const {
			return (x*_v.x + y*_v.y + z*_v.z);
		};
		
		inline void Print(std::string ID) const {
			std::cout << ID << " -> V3D( " << x << ", " << y << ", " << z << " )\n";
		}
		
		inline void Print() const {
			std::cout << "V3D( " << x << ", " << y << ", " << z << " )\n";
		}
};

#endif