/*
 * Noeud.h
 *
 *  Created on: 1 févr. 2011
 *      Author: Marie
 */

#include "Point.h"
#include <map>


#ifndef NOEUD_H_
#define NOEUD_H_

class Noeud{
	public:

	enum Atom {Ca, C, N};

	Noeud(int index, Atom type);

	int  getIndex(void);
	bool isPlaced(void);
	int  getCompteur(void);

	void setPlaced();

	void incrCompteur(void);

	std::string toString();


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
	std::map<int, double> voisins;
	// Position de l'atome
	Point coord;

};


#endif /* NOEUD_H_ */
