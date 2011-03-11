//============================================================================
// Name        : PDB Destructor
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

namespace Constantes
{
	double voisinage = 6;
	double EPSILON_APPARTIENT = 0.02;
	double EPSILON_CERCLES = 0.0005;
}

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
	output->flush();

	/*
	 * Exporte le XYZ de la première molécule trouvée dans le pdb
	 */
	std::string xyz = "mol.xyz";

	if (argc > 3) {
		xyz = argv[3];
	}

	mol.exporterXYZ(xyz);

	return 0;
}
