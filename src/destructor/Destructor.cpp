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
#include <fstream>

#include "../Noeud.h"
#include "../Mol.h"

using namespace std;

int main(int argc, char *argv[]) {
	std::string path = "mol.pdb";

	if (argc > 1) {
		path = argv[1];
	}

	/*
	 * Lis le fichier PDB et le converti en graphe
	 */
	Mol mol = mol.importerPDB(path);

	/*
	 * Exporte le graphe (ie juste les atomes et leurs liaisons)
	 */
	ostream* output = &cout;

	if (argc > 2) {
		ofstream *outfile = new ofstream(argv[2]);
		output = outfile;
	}

	*output << mol.exporterGraphe();

	return 0;
}
