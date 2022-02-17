// 4A3DJV-Traitement-Image-CPP.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <jpeglib.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavdevice/avdevice.h>
#include <libswscale/swscale.h>
#include <libavfilter/avfilter.h>
#include <libswresample/swresample.h>
#include <libavutil/avutil.h>
#include <libavutil/imgutils.h> 
#include <libavutil/timestamp.h>
#include <algorithm>
#include <filesystem> // C++17 standard header file name
#include <filesystem> // Header file for pre-standard implementation

namespace fs = std::filesystem;


int main(int argc, char* argv[])
{
    std::string path = "";
    std::string finalName = "";

    if (argv[1]!=NULL) {
        std::string path = argv[1];
        std::replace(path.begin(),path.end(), '\\', '/');
        std::cout << "There is a path: "<<path<<"\n";
    }
    else {
        //std::cout << "There is no path !";
        //return 0;
    }

    if (argc > 1 && argv[2] != NULL) {
        std::string finalName = argv[2];
        std::cout << "The new file name will be: " << finalName << "\n";
    }
    else {
        std::cout << "There is no new file name !" << "\n";
        //return 0;
    }

    if (argc > 2 && argv[3] != NULL) {
        std::string option = argv[3];
        std::cout << "There is an option: " << option << "\n";
    }
    else {
        //std::cout << "There is no option !";
    }


    path = "C:/Users/Nama/Pictures/CPP/wallpaper sonic.jpg";
    if (fs::is_directory(fs::status(path))) {
        //std::cout << "Test"<<"\n";
        for (const auto& entry : fs::directory_iterator(path)) {
            if (entry.path().extension() == ".jpeg" || entry.path().extension() == ".jpg") {
                std::cout << entry.path() << std::endl;
            }
        }
    }
    else {
        if (fs::path(path).extension() == ".jpeg" || fs::path(path).extension() == ".jpg") {
            std::cout << "This file is a jpeg/jpg";
        }
        else if (fs::path(path).extension() == ".mpeg") {
            std::cout << "This file is a mpeg";
        }

    }
    /*
    path = "C:/Users/Nama/Pictures/CPP";
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.path().extension() == ".jpg" || entry.path().extension() == ".jpeg") {
            std::cout << entry.path() << std::endl;
        }
    }
    */

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
