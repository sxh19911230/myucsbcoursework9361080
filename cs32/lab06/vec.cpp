// vec.cpp - implements Vec3 functions
// Xianghong Sun

#include <iostream>
#include "vec.h"
using namespace std;

// constructors done
Vec3::Vec3() : x(0), y(0), z(0) { }
Vec3::Vec3(double x, double y, double z) : x(x), y(y), z(z) { }
/* Do not modify the following line. If you see the message "Pass by value
   fail." in your output, it means you aren't using a reference somewhere
   that you should be. */
Vec3::Vec3(const Vec3 &other) { cout << "Pass by value fail."; }

// getters and setters done
double Vec3::get_x() const { return x; }
double Vec3::get_y() const { return y; }
double Vec3::get_z() const { return z; }
void Vec3::set_x(double value) { x = value; }
void Vec3::set_y(double value) { y = value; }
void Vec3::set_z(double value) { z = value; }

// YOUR WORK GOES HERE
ostream& operator << (ostream& out, const Vec3& tmp) {
	out << "(" << tmp.get_x() << ", " << tmp.get_y() << ", " << tmp.get_z() << ")";
	return out;
}

istream& operator>> (istream& in, Vec3& tmp) {
	in >> tmp.x  >> tmp.y >>  tmp.z ;
	return in;
}

Vec3 Vec3::operator+ (const Vec3& other) const {
	Vec3 tmp;
	tmp.x = get_x() + other.get_x();
	tmp.y = get_y() + other.get_y();
	tmp.z = get_z() + other.get_z();
	return tmp;
}

Vec3& Vec3::operator+= (const Vec3& other) {
	x += other.get_x();
	y += other.get_y();
	z += other.get_z();
	return *this;
}

Vec3& Vec3::operator++ () {
	x += 1;
	y += 1;
	z += 1;
	return *this;
}

Vec3 Vec3::operator++ (int) {
	Vec3 other;
	other.x = x;
	other.y = y;
	other.z = z;
	x += 1;
	y += 1;
	z += 1;
	return other;
}


Vec3 Vec3::operator- (const Vec3& other) const {
	Vec3 tmp;
	tmp.x = get_x() - other.get_x();
	tmp.y = get_y() - other.get_y();
	tmp.z = get_z() - other.get_z();
	return tmp;
}

Vec3& Vec3::operator-= (const Vec3& other) {
	x -= other.get_x();
	y -= other.get_y();
	z -= other.get_z();
	return *this;
}

Vec3 Vec3::operator* (const double n) const {
	Vec3 tmp;
	tmp.x = get_x() * n;
	tmp.y = get_y() * n;
	tmp.z = get_z() * n;
	return tmp;
}

Vec3 operator* (const double n, const Vec3& other) {
	Vec3 tmp;
	tmp.x = other.get_x() * n;
	tmp.y = other.get_y() * n;
	tmp.z = other.get_z() * n;
	return tmp;
}

Vec3& Vec3::operator*= (const double n) {
	x *= n;
	y *= n;
	z *= n;
	return *this;
}

double& Vec3::operator[](int index){

	if (index == 0)
		return x;
	if (index == 1)
		return y;
	
	return z;
}

const double Vec3::operator[](int index) const {
	
	if (index == 0)
		return x;
	if (index == 1)
		return y;

	return z;
}
