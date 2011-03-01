//============================================================================
// Name        : PDB Destructor
// Author      : Introduction au C++
// Version     :
// Copyright   :
// Description : Ce programme prend en entrée un fichier.pdb puis envoie
//				 en sortie une représentation du graphe partiel
//============================================================================

#include <iostream>
#include <string>
#include <sstream>
#include "../Noeud.h"
#include "../Mol.h"
using namespace std;

int main(int argc, char *argv[]) {
	Mol mol;

	/*
	 * TODO: lire le fichier PDB et le convertir en graphe
	 */
	mol = mol.importerPDB("mol.pdb");

	/*
	 * TODO: Construire les liens entres Noeud
	 * étant distants de moins de X
	 */
	mol[1].addVoisin(mol[2]);
	mol[2].addVoisin(mol[1]);

//	for (Noeud* n = graphe.reset(); n = graphe.next();) {
//		cout << n->getIndex() << endl;
//	}

	/*
	 * Exporte le graphe (ie juste les atomes et leurs liaisons)
	 */
	cout << mol.exporterGraphe();

	return 0;
}
