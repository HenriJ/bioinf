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

/**
 * Constructeur par copie d'un objet de type mol
 * @param noeuds Objet copié pour créer le ParcoursGraphe
 */
ParcoursGraphe::ParcoursGraphe(Mol noeuds): noeuds(noeuds) {
	NombreSolutions = 0;

}

/**
 * Efface toute trace d'une éventuelle anticipation sur le noeud i, c'est à dire met à faux la
 * variable placed de tous les noeuds concernés et décrémente les compteurs correspondants
 * @param i index du noeud sur lequel on veut désanticiper
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
 *  essaye d'anticiper sur les voisins du noeud i, c'est à dire les place avant leur tour
 *  s'ils n'ont plus qu'une seule possibilité et stocke cette anticipation comme venant du noeud k
 *
 *  @param i index du noeud sur lequel on veut anticiper
 *  @param k index du noeud courant dans le parcours du graphe
 *  @return faux si on trouve une incohérence, vrai sinon
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
			if (n->getCompteur()==4 && res){

				Intersection inter=n->trouverIntersection();
				if (inter.getNombre()==1 ){

					Point p=*(inter.getPoints().begin());
					if (n->affecter(p)){
						anticipation[k].insert(n->getIndex());
						if (!anticiper(n->getIndex(),k)){
							res= false;
						}
					}
					else{
						res=false;
					}
				}
				else if (inter.getNombre() ==0 ){
					res= false;
				}
			}
		}
	}
	return res;
}


/**
 * parcourt l'arbre des choix de façon récursive en profondeur. La fonction place le noeud i,
 * s'appelle elle meme sur le noeud i+1, et revient au point de départ pour essayer une éventuelle
 * deuxième possibilité
 * @param i noeuds courant dans le parcours du graphe
 */
void  ParcoursGraphe::placer (int i){
	//cout << "debut";
	if(i==1){
		// Point p=Point(0,0,0);
		Point p = Point (-18.709, -35.5, -0.007);
		noeuds[i]->affecter(p);
		anticiper(i,i);
		placer(i+1);
	}
	else if (i==2){
		map<Noeud*, double> voisins=noeuds[1]->getVoisins();
		for (map<Noeud*, double>::iterator it = voisins.begin() ; it != voisins.end(); it++ ) {
			if ((*it).first->getIndex()==2){
				// Point p=Point(0,0,(*it).second);
				Point p = Point(-19.164, -35.301, 1.410);
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

		// axe s1 - s2
		Point axe = s2.getCentre().moins(s1.getCentre());
		// Distance algébrique de s2.centre au barycentre
		double BG = ( pow(s1.getRayon(), 2) - pow(s2.getRayon(), 2) - pow( axe.norme() , 2) ) / (2 * pow( axe.norme(), 2)) ;
		// Barycentre des centres des sphères
		Point baryCentre = s2.getCentre().plus(axe.foisScalaire(BG));

		// Rayon du cercle intersection
		double d = pow(s1.getRayon(), 2) - pow( (baryCentre.moins(s1.getCentre())).norme() , 2) ;


		// CONSIDERER LE CAS OU LE BARYCENTRE N'EST PAS DANS LE SEGMENT...


		if(d>=0){
			// double rayonCercle = sqrt(d);
			// Point p=Point(0,rayonCercle,baryCentre.getZ());
			Point p = Point(-18.27, -36.021, 2.403);
			noeuds[3]->affecter(p);
			anticiper(i,i);
			placer(i+1);
		} else {
			cout << "erreur : les trois premiers points ne sont pas reliés";
		}


	}
	else if (i==(int)(1+noeuds.size())){
		cout << noeuds.exporterXYZ();
		NombreSolutions ++;
		cout << NombreSolutions << " solutions trouvées" << endl;
		//int jj; cin>>jj;
	}
	else{
		if (!(noeuds[i]->isPlaced())){
			Intersection inter=noeuds[i]->trouverIntersection();
			int m=inter.getNombre(); //normalement, m=1 ou m=2
			std::list<Point>::iterator it=inter.getPoints().begin();
			for( int k=0; k<m;k++){
				cout << " Noeud " << i << "  --  essai " << k << endl;
				Point p=*it;
				if(noeuds[i]->affecter(p)){
					if (anticiper(i,i)){
						placer(i+1);
					}
					//cout << "FIN ANTICIPATION " << i << endl;
					desanticiper(i);
				}

				//cout << "FIN DESANTICIPATION " << i << endl;
				it++;
			}
		}
		else{
			placer(i+1);
		}
	}

}
