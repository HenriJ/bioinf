/*
 * Cercle.cpp
 *
 *  Created on: 15 févr. 2011
 *      Author: samuel
 */

#include "Constantes.h"
#include "Point.h"
#include "Plan.h"
#include "Cercle.h"
#include "math.h"

Cercle::Cercle() {
	// TODO Auto-generated constructor stub

}

Cercle::~Cercle() {
	// TODO Auto-generated destructor stub
}

Cercle::Cercle (Point point, double d, Plan h): centre(point), rayon(d), p(h){}

Point Cercle::getCentre(void){
	return centre;
}
double Cercle::getRayon(void){
	return rayon;
}
Plan Cercle::getPlan(void){
	return p;
}

// Les deux cercles sont coplanaires (assuré par le reste du programme)
Intersection Cercle::intersectionCercle(Cercle c){
	Point axe = c.getCentre().moins(this->getCentre());
	Point barycentre = c.getCentre().moins( axe.foisScalaire( c.getRayon() / (c.getRayon() + this->getRayon()) ) );
	Point direction = axe.vectoriel(c.getPlan().getNormale());

	double distanceCarree = pow( this->getRayon() , 2 ) - pow( barycentre.moins(this->getCentre()).norme() , 2 );
	std::list<Point> ens = std::list<Point>();

	// Deux points distincts
	if (distanceCarree > 0 + Constantes::EPSILON ){
		double distance = sqrt(distanceCarree);
		Point p1 = barycentre.plus(direction.foisScalaire(distance/direction.norme()));
		Point p2 = barycentre.moins(direction.foisScalaire(distance/direction.norme()));
		ens.pushFront(p1);
		ens.pushFront(p2);
		return Intersection(2,ens);
	}
	// Un seul point
	else if (distanceCarree > - Constantes::EPSILON){
		ens.pushFront(barycentre);
		return Intersection(1,ens);
	}
	// Pas de point
	else {
		return Intersection(0,ens);
	}
}



