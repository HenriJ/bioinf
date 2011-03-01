/*
 * Sphere.cpp
 *
 *  Created on: 15 févr. 2011
 */

#include "Plan.h"
#include "Sphere.h"
#include <math.h>

Sphere::Sphere() {}

Sphere::Sphere(Point centre, double rayon){
	this->centre = centre;
	this->rayon = rayon;
}

Sphere::~Sphere() {}

Point Sphere::getCentre(void){
	return centre;
}
double Sphere::getRayon(void){
	return rayon;
}

/**
 * Calcule l'intersection de deux sphères. Si elle n'existe pas, rend un cercle de rayon -1
 */
Cercle Sphere::intersectionSphere(Sphere s){
	Point axe = centre.moins(s.getCentre());
	double X = ( this->getRayon() * this->getCentre().getX() + s.getRayon() * s.getCentre().getX() ) / axe.norme();
	double Y = ( this->getRayon() * this->getCentre().getY() + s.getRayon() * s.getCentre().getY() ) / axe.norme();
	double Z = ( this->getRayon() * this->getCentre().getZ() + s.getRayon() * s.getCentre().getZ() ) / axe.norme();
	Point baryCentre = Point(X,Y,Z);

	Plan p = Plan(axe, baryCentre);

	double d = pow(this->getRayon(), 2) - pow( (baryCentre.moins(this->getCentre()) ).norme() , 2) ;
	if(d>=0){
		double rayonCercle = sqrt(d);
		return Cercle(baryCentre, rayonCercle, p);
	} else {
		return Cercle ( Point(), -1, Plan());
	}
}

Intersection Sphere::intersectionCercle(Cercle c){
	Point POmega = this->getCentre().moins(c.getPlan().getPoint());

	return Intersection();
}




void Sphere::setCentre(Point centre){
	this->centre = centre;
}
void Sphere::setRayon(double d){
	this->rayon = d;
}



