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

/**
 * Constructeur vide
 */
Intersection::Intersection() {}

Intersection::~Intersection() {}

/**
 * Constructeur à partir des éléments
 * @param n nombre de points dans l'intersection
 * @param points liste des spoints de l'intersection
 */
Intersection::Intersection(int n, std::list<Point> points){
	this->nombre = n;
	this->points = points;
}
/**
 * Rend le nombre de points dans l'intersection
 */

int Intersection::getNombre(void){
	return this->nombre;
}

/**
 * Rend la liste des points dans l'intersection
 */
std::list<Point> &Intersection::getPoints(void){
	return this->points;
}


