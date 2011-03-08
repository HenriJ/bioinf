/*
 * ParcoursGraphe.cpp
 *
 *  Created on: 15 févr. 2011
 *      Author: Marie
 */

#include "ParcoursGraphe.h"
#include "Noeud.h"
#include "Point.h"
#include <math.h>
#include <map>
#include <set>

ParcoursGraphe::ParcoursGraphe(Mol noeuds): noeuds(noeuds) {

}

/**
 * cette fonction efface toute trace d'une éventuelle anticipation sur le noeud i
 */
void ParcoursGraphe::desanticiper(int i){
	set<int> settmp=anticipation[i];
	for (set<int>::iterator it=settmp.begin(); it != settmp.end(); it++) {
		noeuds[*it]->unPlaced();
		map<Noeud*, double> m=noeuds[*it]->getVoisins();
		for (map<Noeud*, double>::iterator it1 =m.begin(); it1!=m.end(); it1++){
			it1->first->decrCompteur();
		}
	}
}

/**
 *  Cette fonction essaye d'anticiper sur les voisins du noeud i, sachant que
 *  le noeud courant est le noeud k
 */
bool ParcoursGraphe::anticiper (int i, int k){

	bool res=true;
	anticipation.insert(make_pair (i, set<int>()));

	anticipation[k].insert(i);
	map<Noeud*, double> m=noeuds[i]->getVoisins();
	for (map<Noeud*, double>::iterator it1 =m.begin(); it1!=m.end(); it1++){
		Noeud* n = it1->first;
		n->incrCompteur();
		if (!(n->isPlaced())){
			cout <<  " bo ";
			if (n->getCompteur()==4&& res){

				Intersection inter=n->trouverIntersection();
				cout <<  " boup " <<inter.getNombre(); cin >> a;
				if (inter.getNombre()==1 ){

					Point p=*(inter.getPoints().begin());
					n->affecter(p);
					anticipation[k].insert(n->getIndex());
					if (!anticiper(n->getIndex(),k)){
						res= false;
					}
				}
				else{
					res= false;
				}
			}
		}
	}
	return res;
}


/**
 * cette fonction parcourt l'arbre des choix de façon récursive en profondeur. Elle place le noeud i,
 * s'appelle elle meme sur le noeud i+1, et revient au point de départ
 */
void  ParcoursGraphe::placer (int i){
	if(i==1){
		Point p=Point(0,0,0);
		noeuds[i]->affecter(p);
		anticiper(i,i);
		placer(i+1);
	}
	else if (i==2){
		map<Noeud*, double> voisins=noeuds[1]->getVoisins();
		for (map<Noeud*, double>::iterator it = voisins.begin() ; it != voisins.end(); it++ ) {
			if ((*it).first->getIndex()==2){
				Point p=Point(0,0,(*it).second);
				noeuds[i]->affecter(p);
				break;
			}
		}
		anticiper(i,i);
		placer(i+1);

	}
	else if (i==3){
		Sphere s1;
		Sphere s2;
		int j=0;
		map<Noeud*, double> voisins=noeuds[3]->getVoisins();
		for (map<Noeud*, double>::iterator it = voisins.begin() ; it != voisins.end(); it++ ) {
			if ((*it).first->isPlaced()){
				if (j==0){
					s1=Sphere ((*it).first->getCoord(),(*it).second);
					j++;
				}
				else if (j==1){
					s2=Sphere ((*it).first->getCoord(),(*it).second);
					break;
				}
			}
		}

		// Barycentre des centres des sphères
		Point axe = s1.getCentre().moins(s2.getCentre());
		double X = ( s1.getRayon() * s1.getCentre().getX() + s2.getRayon() * s2.getCentre().getX() ) / axe.norme();
		double Y = ( s1.getRayon() * s1.getCentre().getY() + s2.getRayon() * s2.getCentre().getY() ) / axe.norme();
		double Z = ( s1.getRayon() * s1.getCentre().getZ() + s2.getRayon() * s2.getCentre().getZ() ) / axe.norme();
		Point baryCentre = Point(X,Y,Z);

		// Rayon du cercle intersection
		double d = pow(s1.getRayon(), 2) - pow( (baryCentre.moins(s1.getCentre())).norme() , 2) ;

		if(d>=0){
			double rayonCercle = sqrt(d);
			Point p=Point(0,rayonCercle,baryCentre.getZ());
			noeuds[3]->affecter(p);
			anticiper(i,i);
			placer(i+1);
		} else {
			cout << "erreur : les trois premiers points ne sont pas reliés";
		}


	}
	else if (i==(int)(1+noeuds.size())){
		cout << noeuds.exporterXYZ();
	}
	else{
		if (!(noeuds[i]->isPlaced())){
			Intersection inter=noeuds[i]->trouverIntersection();
			int m=inter.getNombre(); //normalement, m=1 ou m=2
			std::list<Point>::iterator it=inter.getPoints().begin();
			for( int k=0; k<m;k++){
				cout << " Noeud " << i << "essai" << k;int a; cin >> a;
				Point p=*it;
				noeuds[i]->affecter(p);
				if (anticiper(i,i)){
					cout <<  " anticiper " ; cin >> a;
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
