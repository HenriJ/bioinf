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

	enum types {Ca=1, C=2, N=3};

public:
	bool getPlace(void);
	int getCompteur(void);
	void setPlace(boolean b);
	void incrCompteur(void);
	int getIndex(void);

private:
	bool place;	//indique si le noeud est déjà positionné
	int compteur;	//donne le nombre de voisins du noeud déjà placés
	int index;		//identifiant du noeud
	std::map<int,double> voisins;
	int type;		//type de l'atome
	Point coord;	//position de l'atome

};


#endif /* NOEUD_H_ */
