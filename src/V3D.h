// 3 Dimension Vector
// Comprised of floats

#ifndef _V3D_H_
	#define _V3D_H_

class V3D {

// Base floats
public:
float x;
float y;
float z;


// Public Operations
public:

// Constructor zeros vector
inline V3D() {
	x = 0;
	y = 0;
	z = 0;
};

// Zeroes out floats
inline void Zero() {
	x = 0;
	y = 0;
	z = 0;
}

// End of Class
};

#endif