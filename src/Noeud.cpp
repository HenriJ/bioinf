#include "Noeud.h"


using namespace std;

Noeud::Noeud(int index, Atom type): index(index), type(type) {
	placed = false;
	compteur = 0;
}

Noeud::Noeud(int index, Atom type, Point p): index(index), type(type), coord(p) {
	placed = false;
	compteur = 0;
}

int Noeud::getIndex() {
	return index;
}

bool Noeud::isPlaced() {
	return placed;
}

int Noeud::getCompteur() {
	return compteur;
}

Point Noeud::getCoord() {
	return coord;
}


void Noeud::setCoord(Point& P){
	coord = P;
}

void Noeud::affecter(Point& P){
	setCoord(P);
	setPlaced();
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

map<double, Noeud> &Noeud::getVoisins() {
	return voisins;
}

string Noeud::getStringVoisins() {
	stringstream out;

	for (map<double, Noeud>::iterator it = voisins.begin() ; it != voisins.end(); it++ ) {
		out << it->first << ","  << it->second.getIndex() << " ";
	}

	return out.str();
}

Point Noeud::getCord(void){
	return coord;
}

void Noeud::setPlaced() {
	placed = true;
}

void Noeud::unPlaced(){
	placed=false;
}

void Noeud::addVoisin(double dist, Noeud &n) {
	voisins.insert(pair<double, Noeud>(dist, n));
}

void Noeud::addVoisin(Noeud &n) {
	addVoisin(coord.dist(n.coord), n);
}

void Noeud::incrCompteur() {
	compteur++;
}

void Noeud::decrCompteur() {
	compteur--;
}


string Noeud::toString() {
	stringstream out;
	out << "{index: " << index << ", type: ";

	out << getStringType();

	out << ", place: " << placed << "}";
	return out.str();
}

Intersection Noeud::trouverIntersection(void){

		Sphere s1;
		Sphere s2;
		Sphere s3;
		Sphere s4;
		int i=1;
		for (map<double, Noeud>::iterator it = voisins.begin() ; it != voisins.end(); it++ ) {
			if ((*it).second.isPlaced()){
				if (i==1){
					s1=Sphere ((*it).second.getCord(),(*it).first);
					i++;
				}
				if (i==2){
					s2=Sphere ((*it).second.getCord(),(*it).first);
					i++;
				}
				if (i==3){
					s3=Sphere ((*it).second.getCord(),(*it).first);
					i++;
					if(getCompteur()==3){
						return Intersection(s1, s2, s3);
					}
				}
				if (i==4){
					s4=Sphere ((*it).second.getCord(),(*it).first);
					break;
				}
			}
		}

		return Intersection(s1, s2, s3, s4);

}
