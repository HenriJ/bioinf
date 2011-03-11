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

/**
 * Constructeur vide
 */
Sphere::Sphere() {}

/**
 * Constructeur à partir d'un point et d'un rayon
 * @param centre: centre de la sphère
 * @param rayon: rayon de la sphère
 */
Sphere::Sphere(Point centre, double rayon){
	this->centre = centre;
	this->rayon = rayon;
}

Sphere::~Sphere() {}

/**
 *retourne le rayon de la sphère courante
 */
Point Sphere::getCentre(void){
	return centre;
}

/**
 *retourne le rayon de la sphère courante
 */
double Sphere::getRayon(void){
	return rayon;
}

/**
 * Calcule l'intersection de deux sphères
 * @param s sphere dont on veut calculer l'intersection avec la sphere courante
 * @return le cercle intersection s'il existe, un cercle de rayon -1 sinon
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

Intersection Sphere::intersectionTroisSpheresArrondi(Sphere t, Sphere u){
	Intersection E = intersectionTroisSpheres(t,u);
	Sphere v;
	return choisir(t, u, v, E, 3);
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
			//cout << "Point : " << (*it).toString() << endl;
			if (this->appartient(*it)){
				s.push_front(*it);
				k++;
			}
		}
		return choisir( t, u, v, Intersection(k,s), 4);
	}
}

bool Sphere::appartient(Point p){
	double diff = p.moins(this->getCentre()).norme() - this->getRayon();
	if ( diff < Constantes::EPSILON_APPARTIENT && diff > - Constantes::EPSILON_APPARTIENT){
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

Intersection Sphere::choisir(Sphere t, Sphere u, Sphere v, Intersection E, int k){
	if (E.getNombre() == 0){
		return E;
	}
	list<Point> ok;
	int compt = 0;
	Point meilleur = Point (0,3,6);
	Point meilleur1= Point (1,4,7);
	for (list<Point>::iterator it = E.getPoints().begin() ; it != E.getPoints().end() ; it++){
		list<Point> possibles = (*it).arrondi();
		double a = 9999.0;
		for (list<Point>::iterator it2 = possibles.begin() ; it2 != possibles.end() ; it2++){
			Point p = (*it2);
			double somme = max (p.moins(centre).norme() - rayon, rayon - p.moins(centre).norme());
			somme += max (p.moins(t.centre).norme() - t.rayon, t.rayon - p.moins(t.centre).norme());
			somme += max (p.moins(u.centre).norme() - u.rayon, u.rayon - p.moins(u.centre).norme());
			if (k==4){
				somme += max (p.moins(v.centre).norme() - v.rayon, v.rayon - p.moins(v.centre).norme());
			}
			if (somme < a){
				if (compt == 0){
					meilleur = p;
				} else {
					meilleur1 = p;
				}
				a = somme;
			}
		}
		compt++;
	}
	ok.push_front(meilleur);
	if (compt>1 && !(meilleur.equals(meilleur1))){
		ok.push_front(meilleur1);
	}
	Intersection rep =  Intersection(ok.size(), ok);
	return rep;
}



