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

Sphere::intersectionSphere(Sphere s){
	Point axe = this.getCentre().moins(s.getCentre());
	double X = ( this.getRayon() * this.getCentre().getX() + s.getRayon() * s.getCentre().getX() ) / axe.norme();
	double Y = ( this.getRayon() * this.getCentre().getY() + s.getRayon() * s.getCentre().getY() ) / axe.norme();
	double Z = ( this.getRayon() * this.getCentre().getZ() + s.getRayon() * s.getCentre().getZ() ) / axe.norme();
	Point barycentre = new Point(X,Y,Z);

	Plan p = new Plan(axe, barycentre);

}


Point getCentre(void);
double getRayon(void);

void setCentre(Point centre);
void setRayon(double d);



