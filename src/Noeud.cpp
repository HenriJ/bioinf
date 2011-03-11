#include <iostream>
#include "Noeud.h"


using namespace std;

/*
 * Constructeurs & Destructeur & Affichage
 */

/**
 * Constructeur pour la molécule sans position absolue
 * @param index Index numérique (position)  identifiant l'atome
 * @param type Type de l'atome (C, Ca ou N)
 */
Noeud::Noeud(int index, Atom type): index(index), type(type) {
	placed = false;
	compteur = 0;
}

/**
 * Constructeur pour la mocule avec position absolue
 * @param index Index numérique (position)  identifiant l'atome
 * @param type Type de l'atome (C, Ca ou N)
 * @param p Coordonnées de l'atome dans l'espace
 */
Noeud::Noeud(int index, Atom type, Point p): index(index), type(type), coord(p) {
	placed = false;
	compteur = 0;
}

/**
 * Affichage de l'index, du type et de l'état placé ou non
 * utilisé pour débugger le programme
 */
string Noeud::toString() {
	stringstream out;
	out << "{index: " << index << ", type: ";

	out << getStringType();

	out << ", place: " << placed << "}";
	return out.str();
}

/*
 * Getters
 */

/**
 * Retourne l'index identifiant l'atome
 */
int Noeud::getIndex() {
	return index;
}

/**
 * Retourne l'état, placé ou non, de l'atome
 */
bool Noeud::isPlaced() {
	return placed;
}

/**
 * Retourne le nombre de voisins placés
 */
int Noeud::getCompteur() {
	return compteur;
}

/**
 * Retourne le type de l'atome (C, Ca ou N)
 */
string Noeud::getStringType() {
	if (type == Ca)
		return "Ca";

	if (type == C)
		return "C";

	if (type == N)
		return "N";

	return "0";
}

/**
 * Retourne une référence de la map associant à un voisin sa distance
 */
map<Noeud*, double> &Noeud::getVoisins() {
	return voisins;
}

/**
 * Retourne une représentation en chaine de caractères des voisins.
 * Utilisé pour débugger le programme
 */
string Noeud::getStringVoisins() {
	stringstream out;

	for (map<Noeud*, double>::iterator it = voisins.begin() ; it != voisins.end(); it++ ) {
		out << it->second << ","  << it->first->getIndex() << " ";
	}

	return out.str();
}

/**
 * Retourne les coordonnées de l'atome
 */
Point Noeud::getCoord(void){
	return coord;
}

/*
 * Setters
 */

/**
 * Affecte des coordonnées au noeud
 * @param p Coordonnées
 */
void Noeud::setCoord(Point& p) {
	coord = p;
}

/**
 * Affecte des coordonnées au noeud et le considère comme placé
 * @param p Coordonnées
 * @return faux s'il y a ue incohérence avec les voisins déjà placés, vrai sinon
 */
bool Noeud::affecter(Point& P) {
	bool res=true;
	map<Noeud*, double> voisins=getVoisins();
	for (map<Noeud*, double>::iterator it=voisins.begin(); it!=voisins.end(); it++){
		if ((*it).first->isPlaced()){
			if (!Sphere ((*it).first->getCoord(), (*it).second).appartient(P)){
				res=false;
				break;
			}
		}
	}
	if (res){
		setCoord(P);
		setPlaced();
	}

	cout << " Noeud n°" << index << " <- " << P.toString() << endl;
	return res;
}

/**
 * Considère l'atome comme placé
 */
void Noeud::setPlaced() {
	placed = true;
}

/**
 * Considère l'atome comme non-placé
 */
void Noeud::unPlaced(){
	placed=false;
}

/**
 * Ajoute un voisin avec sa distance à l'atome
 * @param dist La distance entre les deux atomes
 * @param n Pointeur vers le noeud voisin
 */
void Noeud::addVoisin(double dist, Noeud *n) {
	voisins.insert(pair<Noeud*, double>(n, dist));
}

/**
 * Ajoute un voisin, la distance est calculée
 * à partir des coordonnée des deux atomes
 * @param n Pointeur vers le noeud voisin
 */
void Noeud::addVoisin(Noeud *n) {
	addVoisin(coord.dist(n->coord), n);
}

/**
 * Incrémente le compteur du nombre de voisins placés
 */
void Noeud::incrCompteur() {
	compteur++;
}

/**
 * Décrément le compteur du nombre de voisins placés
 */
void Noeud::decrCompteur() {
	compteur--;
}


Intersection Noeud::trouverIntersection(void) {

	int v1, v2, v3, v4;
	Sphere s1;
	Sphere s2;
	Sphere s3;
	Sphere s4;
	int i=1;
	for (map<Noeud*, double>::iterator it = voisins.begin() ; it != voisins.end(); it++ ) {
		if ((*it).first->isPlaced()){
			if (i==1){
				s1=Sphere ((*it).first->getCoord(),(*it).second);
				v1 = (*it).first->getIndex();
				i++;
			}
			else if (i==2){
				s2=Sphere ((*it).first->getCoord(),(*it).second);
				v2 = (*it).first->getIndex();
				i++;
			}
			else if (i==3){
				s3=Sphere ((*it).first->getCoord(),(*it).second);
				v3 = (*it).first->getIndex();
				i++;
				if(getCompteur()==3){
					return s1.intersectionTroisSpheresArrondi (s2, s3);
				}
			}
			else if (i==4){
				s4=Sphere ((*it).first->getCoord(),(*it).second);
				v4 = (*it).first->getIndex();
				break;
			}
		}
	}
	// s4 est vide ?

	Intersection inter = s1.intersectionQuatreSpheres( s2, s3, s4);
	if( inter.getNombre() == 0){
		cout << endl << " INTERSECTION VIDE : " << endl;
		cout << endl;
		cout<< "Noeud n°" << v1 << " : [ " << s1.getCentre().toString() << " ; " << s1.getRayon() <<" ]  _  " <<endl;
		cout<< "Noeud n°" << v2 << " : [ " << s2.getCentre().toString() << " ; " << s2.getRayon() <<" ]  _  " <<endl;
		cout<< "Noeud n°" << v3 << " : [ " << s3.getCentre().toString() << " ; " << s3.getRayon() <<" ]  _  " <<endl;
		cout<< "Noeud n°" << v4 << " : [ " << s4.getCentre().toString() << " ; " << s4.getRayon() <<" ]  _  " <<endl;
		cout << "Sur le noeud : " << index << endl;
	}

	if( inter.getNombre() > 1){
		cout << endl << " INTERSECTIONS TROP NOMBREUSES : ( " << inter.getNombre() << " )" << endl;
		cout << endl;
		cout<< "Noeud n°" << v1 << " : [ " << s1.getCentre().toString() << " ; " << s1.getRayon() <<" ]  _  " <<endl;
		cout<< "Noeud n°" << v2 << " : [ " << s2.getCentre().toString() << " ; " << s2.getRayon() <<" ]  _  " <<endl;
		cout<< "Noeud n°" << v3 << " : [ " << s3.getCentre().toString() << " ; " << s3.getRayon() <<" ]  _  " <<endl;
		cout<< "Noeud n°" << v4 << " : [ " << s4.getCentre().toString() << " ; " << s4.getRayon() <<" ]  _  " <<endl;
		cout << "Sur le noeud : " << index << endl;
		for (list<Point>::iterator it = inter.getPoints().begin() ; it != inter.getPoints().end() ; it++){
			cout << "Point : " << (*it).toString() <<endl;
		}
	}
	return inter;

}

