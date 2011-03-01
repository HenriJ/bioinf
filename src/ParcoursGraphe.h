/*
 * ParcoursGraphe.h
 *
 *  Created on: 15 févr. 2011
 *      Author: Marie
 */

#include <map>
#include <string>
#include <iostream>
#include"Noeud.h"
#include <set>
using namespace std;

#ifndef PARCOURSGRAPHE_H_
#define PARCOURSGRAPHE_H_

class ParcoursGraphe{


public:
	ParcoursGraphe(){}
	ParcoursGraphe(std::string s);
	void placer (int i);
	bool anticiper (int i);
	void desanticiper(int i);


private:
	map<int, Noeud> noeuds;
	map<int, set<int> > anticipation;
};



#endif /* PARCOURSGRAPHE_H_ */
