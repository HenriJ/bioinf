#include <iostream>
#include "Noeud.h"


using namespace std;

/*
 * Constructeurs & Destructeur & Affichage
 */

Noeud::Noeud(int index, Atom type): index(index), type(type) {
	placed = false;
	compteur = 0;
}

Noeud::Noeud(int index, Atom type, Point p): index(index), type(type), coord(p) {
	placed = false;
	compteur = 0;
}

string Noeud::toString() {
	stringstream out;
	out << "{index: " << index << ", type: ";

	out << getStringType();

	out << ", place: " << placed << "}";
	return out.str();
}

/*
 * Getters
 */

int Noeud::getIndex() {
	return index;
}

bool Noeud::isPlaced() {
	return placed;
}

int Noeud::getCompteur() {
	return compteur;
}

string Noeud::getStringType() {
	if (type == Ca)
		return "Ca";

	if (type == C)
		return "C";

	if (type == N)
		return "N";

	return "0";
}

map<Noeud*, double> &Noeud::getVoisins() {
	return voisins;
}

string Noeud::getStringVoisins() {
	stringstream out;

	for (map<Noeud*, double>::iterator it = voisins.begin() ; it != voisins.end(); it++ ) {
		out << it->second << ","  << it->first->getIndex() << " ";
	}

	return out.str();
}

Point Noeud::getCoord(void){
	return coord;
}

/*
 * Setters
 */

void Noeud::setCoord(Point& P) {
	coord = P;
}

void Noeud::affecter(Point& P) {
	setCoord(P);
	setPlaced();
}

void Noeud::setPlaced() {
	placed = true;
}

void Noeud::unPlaced(){
	placed=false;
}

void Noeud::addVoisin(double dist, Noeud *n) {
	voisins.insert(pair<Noeud*, double>(n, dist));
}

void Noeud::addVoisin(Noeud *n) {
	addVoisin(coord.dist(n->coord), n);
}

void Noeud::incrCompteur() {
	compteur++;
}

void Noeud::decrCompteur() {
	compteur--;
}

Intersection Noeud::trouverIntersection(void) {

	Sphere s1;
	Sphere s2;
	Sphere s3;
	Sphere s4;
	int i=1;
	for (map<Noeud*, double>::iterator it = voisins.begin() ; it != voisins.end(); it++ ) {
		if ((*it).first->isPlaced()){
			if (i==1){
				s1=Sphere ((*it).first->getCoord(),(*it).second);
				i++;
			}
			else if (i==2){
				s2=Sphere ((*it).first->getCoord(),(*it).second);
				i++;
			}
			else if (i==3){
				s3=Sphere ((*it).first->getCoord(),(*it).second);
				i++;
				cout << getCompteur() << " noeud " << index;int a; cin >> a;
				if(getCompteur()==3){
					return s1.intersectionTroisSpheres (s2, s3);
				}
			}
			else if (i==4){
				cout << getCompteur() << " noeud " << index;int a; cin >> a;
				s4=Sphere ((*it).first->getCoord(),(*it).second);
				break;
			}
		}
	}
	// s4 est vide ?
	return s1.intersectionQuatreSpheres( s2, s3, s4);

}

