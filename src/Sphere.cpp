/*
 * Sphere.cpp
 *
 *  Created on: 15 févr. 2011
 */
#include "Constantes.h"
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
	if (c.getRayon() < 0){
		return Intersection (0, std::list<Point>());
	}
	Point normale = c.getPlan().getNormale();
	Point POmega = this->getCentre().moins(c.getPlan().getPoint());
	Point H = this->getCentre().moins( normale.foisScalaire( POmega.scalaire(normale) / pow(normale.norme(),2) ) );

	double rayonCarre = pow( this->getRayon(), 2) - pow( H.moins(this->getCentre()).norme() ,2 );

	// Si l'intersection de la sphère et du plan est non vide
	if (rayonCarre >= 0 ){
		double R = sqrt(rayonCarre);
		Cercle c2 = Cercle(H, R, c.getPlan());
		return c.intersectionCercle(c2);
	}
	// Si la sphère ne touche pas le plan, pas de point d'intersection possible
	else {
		std::list<Point> s = std::list<Point>();
		return Intersection(0, s);
	}
}

Intersection Sphere::intersectionTroisSpheres(Sphere t, Sphere u){
	return ( this->intersectionCercle(t.intersectionSphere(u)));
}

Intersection Sphere::intersectionQuatreSpheres(Sphere t, Sphere u, Sphere v){
	std::list<Point> s = std::list<Point>();
	int k = 0;
	Intersection E = t.intersectionTroisSpheres(u,v);
	int Card = E.getNombre();
	if (Card==0){
		return E;
	}
	else{
		for (list<Point>::iterator it = E.getPoints().begin() ; it != E.getPoints().end() ; it++){
			if (this->appartient(*it)){
				s.pushFront(*it);
				k++;
			}
		}
		return Intersection(k,s);
	}
}

bool Sphere::appartient(Point p){
	double diff = p.moins(this->getCentre()).norme() - this->getRayon();
	if ( diff < Constantes::EPSILON && diff > - Constantes::EPSILON){
		return true;
	}
	return false;
}




void Sphere::setCentre(Point centre){
	this->centre = centre;
}
void Sphere::setRayon(double d){
	this->rayon = d;
}



