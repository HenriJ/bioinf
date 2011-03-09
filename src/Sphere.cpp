/*
 * Sphere.cpp
 *
 *  Created on: 15 févr. 2011
 */

#include "Constantes.cpp"
#include <sstream>
#include "Plan.h"
#include "Sphere.h"
#include <math.h>
#include <iostream>

using namespace std;

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
	// axe this - s
	Point axe = s.getCentre().moins(centre);
	// Distance algébrique de s2.centre au barycentre
	double BG = ( pow(rayon, 2) - pow(s.getRayon(), 2) - pow( axe.norme() , 2) ) / (2 * pow( axe.norme(), 2)) ;
	// Barycentre des centres des sphères
	Point baryCentre = s.getCentre().plus(axe.foisScalaire(BG));
	// Rayon du cercle intersection
	double d = pow(rayon, 2) - pow( (baryCentre.moins(centre)).norme() , 2) ;

	Plan p = Plan(axe, baryCentre);

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
	/*
	for (list<Point>::iterator it = E.getPoints().begin() ; it != E.getPoints().end() ; it++){
		cout <<(*it).toString();
	}
	*/
	int Card = E.getNombre();
	if (Card==0){
		return E;
	}
	else{
		for (list<Point>::iterator it = E.getPoints().begin() ; it != E.getPoints().end() ; it++){
			if (this->appartient(*it)){
				s.push_front(*it);
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

string Sphere::toString(void){
	stringstream out;
	out << "[ " << centre.toString() << " ; " << rayon << " ]";
	return out.str();
}



