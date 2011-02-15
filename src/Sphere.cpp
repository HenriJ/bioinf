/*
 * Sphere.cpp
 *
 *  Created on: 15 févr. 2011
 *      Author: samuel
 */

#include "Sphere.h"

Sphere::Sphere() {
	// TODO Auto-generated constructor stub

}

Sphere::Sphere(Point centre, double rayon){
	this.centre = centre;
	this.rayon = rayon;
}

Sphere::~Sphere() {
	// TODO Auto-generated destructor stub
}

/**
 * Calcule l'intersection de deux sphères. Si elle n'existe pas, rend un cercle de rayon -1
 */
Sphere::intersectionSphere(Sphere s){
	Point axe = this.getCentre().moins(s.getCentre());
	double X = ( this.getRayon() * this.getCentre().getX() + s.getRayon() * s.getCentre().getX() ) / axe.norme();
	double Y = ( this.getRayon() * this.getCentre().getY() + s.getRayon() * s.getCentre().getY() ) / axe.norme();
	double Z = ( this.getRayon() * this.getCentre().getZ() + s.getRayon() * s.getCentre().getZ() ) / axe.norme();
	Point barycentre = new Point(X,Y,Z);

	Plan p = new Plan(axe, barycentre);

	double d = pow(this.getRayon(), 2) - pow( (barycentre.moins(this.getCentre()) ).norme() , 2) ;
	if(d>=0){
		double rayonCercle = sqrt(d);
		return new Cercle(baryCentre, rayonCercle, p);
	} else {
		return new Cercle (new Point(), -1, new Plan());
	}
}

Sphere::intersectionCercle(Cercle c){

}


Point getCentre(void);
double getRayon(void);

void setCentre(Point centre);
void setRayon(double d);



