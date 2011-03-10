/*
 * Cercle.cpp
 *
 *  Created on: 15 févr. 2011
 *      Author: samuel
 */

#include "Constantes.cpp"
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
	// axe this - c
	Point axe = c.getCentre().moins(centre);
	// Distance algébrique de s2.centre au barycentre
	double BG = ( pow(rayon, 2) - pow(c.getRayon(), 2) - pow( axe.norme() , 2) ) / (2 * pow( axe.norme(), 2)) ;
	// Barycentre des centres des sphères
	Point barycentre = c.getCentre().plus(axe.foisScalaire(BG));
	// Rayon du cercle intersection
	double distanceCarree = pow(rayon, 2) - pow( (barycentre.moins(centre)).norme() , 2) ;


	Point direction = axe.vectoriel(c.getPlan().getNormale());

	std::list<Point> ens = std::list<Point>();

	// Deux points distincts
	if (distanceCarree > 0 + pow (Constantes::EPSILON_CERCLES, 2) ){
		double distance = sqrt(distanceCarree);
		Point p1 = barycentre.plus(direction.foisScalaire(distance/direction.norme()));
		Point p2 = barycentre.moins(direction.foisScalaire(distance/direction.norme()));
		ens.push_front(p1);
		ens.push_front(p2);
		return Intersection(2,ens);
	}
	// Un seul point
	else if (distanceCarree > - pow (Constantes::EPSILON_CERCLES, 2)){
		ens.push_front(barycentre);
		return Intersection(1,ens);
	}
	// Pas de point
	else {
		return Intersection(0,ens);
	}
}



