/*
 * Noeud.h
 *
 *  Created on: 1 févr. 2011
 *      Author: Marie
 */

#include "Point.h"
#include <map>
#include <string>
#include <sstream>
#include <math.h>
#include "Intersection.h"
#include "Sphere.h"


#ifndef NOEUD_H_
#define NOEUD_H_

class Noeud{
	public:

	enum Atom {Ca, C, N};

	Noeud(){}
	Noeud(int index, Atom type);
	Noeud(int index, Atom type, Point p);

	int   getIndex(void);
	bool  isPlaced(void);
	Point getCoord(void);
	int   getCompteur(void);
	std::string getStringType();

	std::map<Noeud*, double> &getVoisins();
	Noeud* next();
	std::string getStringVoisins();


	void setPlaced();

	void unPlaced();

	void addVoisin(double dist, Noeud *n);
	void addVoisin(Noeud *n);

	void incrCompteur(void);
	void decrCompteur(void);

	std::string toString();
	void setCoord(Point& P);
	bool affecter(Point& P);

	Intersection trouverIntersection(void);


	private:

	// Identifiant du noeud
	int index;
	// Type de l'atome
	Atom type;
	// Indique si le noeud est déjà positionné
	bool placed;
	// Donne le nombre de voisins du noeud déjà placés
	int compteur;
	// Voisins du noeud
	std::map<Noeud*, double> voisins;
	// Position de l'atome
	Point coord;

};


#endif /* NOEUD_H_ */
