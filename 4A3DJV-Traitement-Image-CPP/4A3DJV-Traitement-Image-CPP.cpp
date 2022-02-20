// 4A3DJV-Traitement-Image-CPP.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <jpeglib.h>
#include <filesystem> // C++17 standard header file name
#include <filesystem> // Header file for pre-standard implementation

namespace fs = std::filesystem;


int main(int argc, char* argv[])
{
    std::string path = "";

    if (argv[1]!=NULL) {
        std::string path = argv[1];
        std::cout << "There is a path: "<<path<<"\n";
    }
    else {
        //std::cout << "There is no path !";
        //return 0;
    }

    if (argc > 1 && argv[2] != NULL) {
        std::string option = argv[2];
        std::cout << "There is an option: " << option << "\n";
    }
    else {
        //std::cout << "There is no option !";
    }

    path = "./picture";
    for (const auto& entry : fs::directory_iterator(path)) {
        std::cout << entry.path() << std::endl;
    }

    return 0;
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
