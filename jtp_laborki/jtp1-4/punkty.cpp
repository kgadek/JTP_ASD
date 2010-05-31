#include <cmath>
#include <iostream>
#include "punkty.h"

/* ====================[ Wektor ]==================== */
Wektor::Wektor() : x(0.0), y(0.0), z(0.0) { }

Wektor::Wektor(const double a,const double b,const double c) : x(a), y(b), z(c) { }

double Wektor::len() const {
	return sqrt(x*x+y*y+z*z);
}

Wektor Wektor::operator+(const Wektor &w) const {
	return Wektor(x+w.x, y+w.y, z+w.z);
}

Wektor& Wektor::operator+=(const Wektor &w) {
	x += w.x; y += w.y; z += w.z;
	return *this;
}

Wektor Wektor::operator-() const {
	return Wektor(-x, -y, -z);
}

std::ostream& operator<<(std::ostream &out, const Wektor &w) {
	out << "(" << w.x << "," << w.y << "," << w.z << ")";
	return out;
}

/* ====================[ Punkt ]===================== */
Punkt::Punkt() : x(0.0), y(0.0), z(0.0) { }

Punkt::Punkt(const double a,const double b,const double c) : x(a), y(b), z(c) { }

double odl(const Punkt &a, const Punkt &b) {
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z));
}

Punkt operator+(const Punkt &p, const Wektor &w) {
	return Punkt(p.x+w.x, p.y+w.y, p.z+w.z);
}

Punkt& operator+=(Punkt &p, const Wektor &w) {
	p.x += w.x; p.y += w.y; p.z += w.z;
	return p;
}

Punkt Punkt::operator-() const {
	return Punkt(-x,-y,-z);
}

Punkt Punkt::operator-(const Punkt &p) const {
	return Punkt(x-p.x, y-p.y, z-p.z);
}

std::ostream& operator<<(std::ostream &out, const Punkt &w) {
	out << "[" << w.x << "," << w.y << "," << w.z << "]";
	return out;
}

/* ====================[  Main  ]==================== */
int main() {
	std::ios_base::sync_with_stdio(0);
	return 0;
}

