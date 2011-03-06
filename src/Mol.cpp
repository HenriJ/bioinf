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

Noeud& Mol::operator[](int i)
{
	return noeuds[i];
}

string Mol::exporterGraphe() {
	stringstream out_noeuds;
	stringstream out_liens;

	for (map<int, Noeud>::iterator it = noeuds.begin() ; it != noeuds.end(); ++it) {
		Noeud& n(it->second);
		out_noeuds << "N " << n.getIndex() << " " << n.getStringType() << endl;

		for (map<double, Noeud>::iterator sub = n.getVoisins().begin() ; sub != n.getVoisins().end(); ++sub) {
			out_liens << "L " << n.getIndex() << " " << sub->first << " " << sub->second.getIndex() << endl;
		}
	}

	out_noeuds << out_liens.str();
	return out_noeuds.str();
}

/*
 * Importe un fichier PDB et créé les liens entre les Noeuds
 */
Mol Mol::importerPDB(std::string path) {
	Mol mol;

	ifstream infile;
	infile.open(path.c_str());
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
				mol.insert(*NN);
				Bb=false;
			}
		}
	}

	for(int i=1; i <= counterm; i++) {
		for(int j=i; j <= counterm; j++) {
			if(j>i && (mol[j].getCoord().dist(mol[i].getCoord()) < Constantes::voisinage)) {
				mol[i].addVoisin(mol[j]);
			}
		}
	}

	return mol;
}

string Mol::exporterXYZ() {
	ofstream myFile;

	myFile.open("example.xyz");
	int a=noeuds.size();
	myFile << a << "\n";
	myFile << "This geometry optimized by G92;  MP2/6-31G* \n";

	for (int i=1;i<=a;i++){
		myFile << noeuds[i].getStringType() << " " << noeuds[i].getCoord().getX() << " "<< noeuds[i].getCoord().getY() << " "<< noeuds[i].getCoord().getZ() << "\n" ;
	}

	myFile.close();
	return "";
}

void Mol::insert(Noeud& n) {
	noeuds.insert(pair<int, Noeud>(n.getIndex(), n));
}

Noeud* Mol::reset() {
	internalIterator = noeuds.begin();
	return &((internalIterator)->second);
}

Noeud* Mol::next() {
	if (internalIterator != noeuds.end()) {
		return &((internalIterator++)->second);
	}
	return NULL;
}
