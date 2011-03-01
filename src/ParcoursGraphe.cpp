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

bool ParcoursGraphe::anticiper (int i, int k){

	anticipation.insert(make_pair (i, set<int>()));

	anticipation[k].insert(i);
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
					anticipation[k].insert(n.getIndex());
					if (!anticiper(n.getIndex(),k)){
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

void  ParcoursGraphe::placer (int i){
	if (i==(int)(1+noeuds.size())){
		stocker();
	}
	else{
		if (!(noeuds[i].isPlaced())){
			Intersection inter=noeuds[i].trouverIntersection();
			int m=inter.getNombre(); //normalement, m=1 ou m=2
			set<Point>::iterator it=inter.getPoints().begin();
			for( int k=0; k<m;k++){
				Point p=*it;
				noeuds[i].affecter(p);
				if (anticiper(i,i)){
					placer(i+1);
				}
				desanticiper(i);
				it++;
			}
		}
		else{
			placer(i+1);
		}
	}

}
