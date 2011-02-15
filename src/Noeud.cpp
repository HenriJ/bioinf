#include "Noeud.h"
#include <string>
#include <sstream>
#include <math.h>

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
void Noeud::setCord(Point& P){
coord=P;

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

map<double, Noeud> Noeud::getVoisins() {
	return voisins;
}

string Noeud::getStringVoisins() {
	stringstream out;

	for (map<double, Noeud>::iterator it = voisins.begin() ; it != voisins.end(); it++ ) {
		out << it->first << ","  << it->second.getIndex() << " ";
	}

	return out.str();
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

map<double, Noeud> Noeud::getVoisins() {
	return voisins;
}

string Noeud::getStringVoisins() {
	stringstream out;

	for (map<double, Noeud>::iterator it = voisins.begin() ; it != voisins.end(); it++ ) {
		out << it->first << ","  << it->second.getIndex() << " ";
	}

	return out.str();
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
