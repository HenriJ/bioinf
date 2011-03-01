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
using namespace std;

class ParcoursGraphe{


public:
	ParcoursGraphe(){}
	ParcoursGraphe(std::string s);
	void placer (int i);
	bool anticiper (int i, int k);
	void desanticiper(int i);
	void stocker();


private:
	map<int, Noeud> noeuds;
	map<int, set<int> > anticipation;
};



#endif /* PARCOURSGRAPHE_H_ */
