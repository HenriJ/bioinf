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

bool ParcoursGraphe::anticiper (int i){
	anticipation[i].insert(i);
	map<double, Noeud> m=noeuds[i].getVoisins();
	for (map<double, Noeud>::iterator it1 =m.begin(); it1!=m.end(); it1++){
		Noeud n=(*it1).second;
		n.incrCompteur();
		if (!(n.isPlaced())){
			if (n.getCompteur()==4){
				Intersection inter=n.trouverIntersection();
				if (inter.getNombre()==1){
					Point p=*(inter.getPoints().begin());
					n.affecter(p);
					anticipation[i].insert(n.getIndex());
					if (!anticiper(n.getIndex())){
						return false;
					}
				}
				else{
					return false;
				}
			}
		}
	}
	return true;

}
