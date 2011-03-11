#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <map>
#include <istream>
#include <iterator>
#include <vector>

#include "Mol.h"
#include "Point.h"
#include "Noeud.h"
#include "Constantes.cpp"

using namespace std;

Mol::Mol() {

}

Mol::~Mol() {

}

/**
 * Surcharge de l'opérateur [] pour un accés direct aux noeuds d'un objet mol
 * @param i index du noeud dans la molécule
 */
Noeud* Mol::operator[](int i)
{
	return noeuds[i];
}


/**
 * Export du graphe construit à l'aide de l'objet mol courant
 * @return une chaine de caractéres qui liste d'abord l'ensemble des noeuds
 *         qui forme la molécule puis la liste des liens existants entre deux
 *         donnés en indiquant les noeuds concernés et la distance entre eux
 */
string Mol::exporterGraphe() {
	stringstream out_noeuds;
	stringstream out_liens;

	int i = 1;
	for (map<int, Noeud*>::iterator it = noeuds.begin() ; it != noeuds.end(); ++it) {
		Noeud* n = it->second;
		out_noeuds << "N " << n->getIndex() << " " << n->getStringType() << endl;
		if (i <= 3) {
			Point p = n->getCoord();
			out_noeuds << "P " << n->getIndex() << " " << p.getX() << " " << p.getY() << " " << p.getZ() << endl;
		}

		for (map<Noeud*, double>::iterator sub = n->getVoisins().begin() ; sub != n->getVoisins().end(); ++sub) {
			out_liens << "L " << n->getIndex() << " " << sub->second << " " << sub->first->getIndex() << endl;
		}

		i++;
	}

	out_noeuds << out_liens.str();
	return out_noeuds.str();
}

/**
 * Importe un fichier PDB et crée les liens de voisinage entre les noeuds de la molécule
 * @param path fichier .PDB é traiter
 * @return Un objet Mol correspondant au fichier importé
 */
Mol Mol::importerPDB(string path) {
	Mol mol;

	ifstream infile(path.c_str());
	istream_iterator<string> ii(infile);
	istream_iterator<string> eos;
	vector<string> allinstr(ii,eos); //all file is stocked in a vector of string
	vector<string>::const_iterator lec;
	string Atom("ATOM");
	string N("N");
	string C("C");
	string CA("CA");

	int counterm = 0;	//counter to identity the Atom
	double cor1, cor2, cor3;
	bool Bb = false; //Backbone or not
	Point* P;
	Noeud* NN;
	Noeud::Atom AT;
	for(lec=allinstr.begin(); lec!= allinstr.end(); lec++) {
		// On s'arrête à la fin de la première molécule décrite
		if(lec->compare("TER") == 0 || lec->compare("ENDMDL") == 0) {
			break;
		}
		if(lec->compare(Atom)==0) {
			lec++;
			lec++;
			if(lec->compare(N)==0) {
				AT=Noeud::N;
				Bb=true;
			}
			if(lec->compare(C)==0) {
				AT=Noeud::C;
				Bb=true;
			}
			if(lec->compare(CA)==0) {
				AT=Noeud::Ca;
				Bb=true;
			}
			if(Bb) {
				counterm++;
				lec+=4;
				cor1=(double) atof(lec->c_str()); //coord X
				lec++;
				cor2=(double) atof(lec->c_str()); //coord Y
				lec++;
				cor3=(double) atof(lec->c_str()); //coord Z
				P=new Point(cor1,cor2,cor3);
				NN=new Noeud(counterm, AT);
				NN->setCoord(*P);
				mol.insert(NN);
				Bb=false;
			}
		}
	}

	for(int i=1; i <= counterm; i++) {
		for(int j=i; j <= counterm; j++) {
			if(j>i && (mol[j]->getCoord().dist(mol[i]->getCoord()) < Constantes::voisinage)) {
				mol[i]->addVoisin(mol[j]);
			}
		}
	}

	return mol;
}

/**
 * Crée un objet Mol à partir d'un fichier de données
 * @param path adresse d'un fichier de données
 */
Mol Mol::importerGraphe(string path) {
	Mol mol;

	ifstream grapheFile(path.c_str());

	char buf[80] = {0};
	while (!grapheFile.eof()) {
		grapheFile.getline( buf, sizeof( buf ) );
		string buf1(buf);
		istringstream istr(buf1);

		char type = ' ';
		istr.get(type); // On regarde si on charge un noeud ou un lien
		istr.get(); // On consomme l'espace suivant aussi.

		if (type == 'N') {
			int index;
			string atome;

			istr >> index >> atome;

			Noeud::Atom atom;

			if (atome.compare("C")) {
				atom = Noeud::C;
			} else if (atome.compare("Ca")) {
				atom = Noeud::Ca;
			} else if (atome.compare("N")) {
				atom = Noeud::N;
			}

			Noeud* n = new Noeud(index, atom);
			mol.insert(n);
		} else if (type == 'L') {
			int indexA, indexB;
			double dist;

			istr >> indexA >> dist >> indexB;

			mol[indexA]->addVoisin(dist, mol[indexB]);
			mol[indexB]->addVoisin(dist, mol[indexA]);
		} else if (type == 'P') {
			int index;
			double x, y, z;

			istr >> index >> x >> y >> z;

			Point p = Point(x, y, z);
			mol[index]->affecter(p);
		}
	}

	return mol;
}
/**
 * Export du fichier mol sous format .xyz
 * @return une chaine de caractères qui à chaque noeud associe son index et ses coordonnées
 */
string Mol::exporterXYZ() {
	stringstream out;

	int a = noeuds.size();
	out << a << "\n";
	out << "This geometry optimized by G92;  MP2/6-31G* \n";

	for (int i=1;i<=a;i++){
		out << noeuds[i]->getStringType() << " " << noeuds[i]->getCoord().getX() << " "<< noeuds[i]->getCoord().getY() << " "<< noeuds[i]->getCoord().getZ() << "\n" ;
	}

	return out.str();
}

/**
 * Ajoute le noeud n à la molécule courante
 * @param n noeud d'index n
 */
void Mol::insert(Noeud* n) {
	noeuds.insert(pair<int, Noeud*>(n->getIndex(), n));
}

/**
 * @return le nombre de noeuds de la molécule
 */
int Mol::size() {
	return noeuds.size();
}

/**
 *Parcours des noeuds de la molécule, utilisé pour alléger les notations dans les autres fonctions du programme
 *
 */
Noeud* Mol::reset() {
	internalIterator = noeuds.begin();
	return internalIterator->second;
}

/**
 * @return un pointeur vers le noeud suivant le noeud courant
 */
Noeud* Mol::next() {
	if (internalIterator != noeuds.end()) {
		return (internalIterator++)->second;
	}
	return NULL;
}
