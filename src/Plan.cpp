/*
 * Plan.cpp
 *
 *  Created on: 15 févr. 2011
 *      Author: samuel
 */
#include "Point.h"
#include "Plan.h"
/**
 * Méthode constructeur générale
 **/
Plan::Plan() {
	// TODO Auto-generated constructor stub
}
/**
 *Méthode destructeur générale
 **/
Plan::~Plan() {
	// TODO Auto-generated destructor stub
}
/**
 * Méthode constructeur définissant un Plan
 * par sa normale et un point lui appartenant
 **/
Plan::Plan(Point n, Point p): normale(n),point(p) {
}

/**
 * Renvoie le Point appartenant au Plan
 * qui a été utilisé lors de la construction
 * du Plan
 **/
Point Plan::getPoint(void){
	return point;
}

/**
 * Renvoie la normale du Plan qui a
 * été utilisée lors de la construction
 * du Plan
 **/
Point Plan::getNormale(void){
	return normale;
}
