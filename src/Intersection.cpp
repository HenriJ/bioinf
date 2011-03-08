/*
 * Intersection.cpp
 *
 *  Created on: 15 févr. 2011
 *      Author: samuel
 */
#include "Sphere.h"
#include "Point.h"
#include <list>
#include "Intersection.h"

Intersection::Intersection() {}

Intersection::~Intersection() {}

Intersection::Intersection(int n, std::list<Point> points){
	this->nombre = n;
	this->points = points;
}

int Intersection::getNombre(void){
	return this->nombre;
}
std::list<Point> Intersection::getPoints(void){
	return this->points;
}


