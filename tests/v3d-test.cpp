#include <iostream>
#include "../src/V3D.h"

void PrintVector(const V3D& v, const int line) {
	std::cout << v.x << ", ";
	std::cout << v.y << ", ";
	std::cout << v.z << "\t\t";
	std::cout << "(" << line << ")" << "\n";
}

int main() {
	V3D a(0, 0, 0);
	V3D b(.2, 1, .4);
	V3D c(4, 0, .25);
	V3D r(0, 0, 1);
	V3D s(0, 1, 0);
	
	PrintVector(a, __LINE__);
	a += b;
	PrintVector(a, __LINE__);
	a += c * 4;
	PrintVector(a, __LINE__);
	a.SpinAxis(90*0.017453292519943, r);
	PrintVector(a, __LINE__);
	a.SpinAxis(90*0.017453292519943, s);
	PrintVector(a, __LINE__);
	
	std::cout << "\n\n";
	
	V3D u(1, 2, 3);
	V3D o(0, 0, 1);
	V3D p(0, 1, 0);
	V3D i(1, 0, 0);
	
	PrintVector(u, __LINE__);
	u.SpinAxis(90*0.017453292519943, o);
	PrintVector(u, __LINE__);
	u.SpinAxis(90*0.017453292519943, p);
	PrintVector(u, __LINE__);
	u.SpinAxis(90*0.017453292519943, i);
	PrintVector(u, __LINE__);
}
