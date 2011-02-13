#include "Noeud.h"
#include <string>
#include <sstream>
#include <math.h>

using namespace std;

Noeud::Noeud(int index, Atom type): index(index), type(type) {
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

void Noeud::setPlaced() {
	placed = true;
}

void Noeud::incrCompteur() {
	compteur++;
}

string Noeud::toString() {
	stringstream out;
	out << "{index: " << index << ", type: ";

	switch (type) {
		case Ca:
			out << "Ca";
			break;

		case C:
			out << "C";
			break;

		case N:
			out << "N";
			break;
	}

	out << ", place: " << placed << "}";
	return out.str();
}
