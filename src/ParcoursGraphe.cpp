/*
 * ParcoursGraphe.cpp
 *
 *  Created on: 15 févr. 2011
 *      Author: Marie
 */

#include "ParcoursGraphe.h"
#include "Noeud.h"
#include "Point.h"
#include <map>
#include <set>

ParcoursGraphe::ParcoursGraphe(string s){

}

void ParcoursGraphe::desanticiper(int i){
	set<int> settmp=anticipation[i];
	for (set<int>::iterator it=settmp.begin(); it != settmp.end(); it++) {
		noeuds[*it].unPlaced();
		map<double, Noeud> m=noeuds[*it].getVoisins();
		for (map<double, Noeud>::iterator it1 =m.begin(); it1!=m.end(); it1++){
			it1->second.decrCompteur();
		}
	}
}
