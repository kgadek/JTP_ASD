#include <vector>
#include "polygon.h"

Polygon::Polygon() {
	it = p.begin();
}

Polygon::Polygon(const Polygon &x) {
	p = x.p;
	w = x.w;
	it = p.begin();
}

void Polygon::add(Punkt x) {
	p.push_back(x);
}

void Polygon::move(const Wektor &x) {
	w+=x;
}

void Polygon::show_reset() {
	it = p.begin();
}

Punkt Polygon::show_next() {
	return *it + w;
}

bool Polygon::show_end() const {
	return it == p.end();
}

