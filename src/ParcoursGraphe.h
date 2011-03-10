/*
 * ParcoursGraphe.h
 *
 *  Created on: 15 févr. 2011
 *      Author: Marie
 */



#ifndef PARCOURSGRAPHE_H_
#define PARCOURSGRAPHE_H_

#include <map>
#include <string>
#include <iostream>
#include"Noeud.h"
#include <set>
#include "Mol.h"
using namespace std;

class ParcoursGraphe{


public:
	ParcoursGraphe(Mol noeuds);
	void placer (int i);
	bool anticiper (int i, int k);
	void desanticiper(int i);
	void stocker();
	int NombreSolutions;

private:
	Mol noeuds;
	map<int, set<int> > anticipation;
};



#endif /* PARCOURSGRAPHE_H_ */
