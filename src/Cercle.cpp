/*
 * Cercle.cpp
 *
 *  Created on: 15 févr. 2011
 *      Author: samuel
 */

#include "Point.h"
#include "Plan.h"
#include "Cercle.h"

Cercle::Cercle() {
	// TODO Auto-generated constructor stub

}

Cercle::~Cercle() {
	// TODO Auto-generated destructor stub
}

Cercle::Cercle (Point point, double d, Plan h): centre(point), rayon(d), p(h){}
