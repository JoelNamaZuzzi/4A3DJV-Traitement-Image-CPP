#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <jpeglib.h>
#include <algorithm>
#include <filesystem>
#include "Image.h"
#include<string>

namespace fs = std::filesystem;


int main(int argc, char* argv[])
{
    std::string path = "";
    std::string finalName = "";
    bool isDir = FALSE;
    int img_nb=0;
    int i = 0;
    std::string properpath;

    //On regarde si il y a un chemin d'acces qui est renseigne
    if (argv[1]!=NULL) {
        std::string path = argv[1];
        std::replace(path.begin(),path.end(), '\\', '/');
        std::cout << "There is a path: "<<path<<"\n";
    }
    else {
        std::cout << "There is no path !";
        return 0;
    }

    //On regarde si le fichier final a un nom
    if (argc > 1 && argv[2] != NULL) {
        std::string finalName = argv[2];
        std::cout << "The new file name will be: " << finalName << "\n";
    }
    else {
        std::cout << "There is no new file name !" << "\n";
        return 0;
    }

    //On regarde si il y a une option
    if (argc > 2 && argv[3] != NULL) {
        std::string option = argv[3];
        std::cout << "There is an option: " << option << "\n";
    }
    else {
        std::cout << "There is no option !";
    }

    //pathsrcc = "C:/Users/Nama/Pictures/CPP/wallpaper sonic.jpeg";
    //pathdstc = "C:/Users/Nama/Pictures/CPP/wallpaper sonic_modif.jpeg";
    //path = "C:/Users/Nama/Pictures/CPP";

    //On regarde si le chemin renseigner est un dossier, si oui on récupère uniquement les jpeg et les jpg, et on ajoute tout à un compteur pour faire un tableau
    if (fs::is_directory(fs::status(path))) {
        isDir = TRUE;
        for (const auto& entry : fs::directory_iterator(path)) {
            if (entry.path().extension() == ".jpeg" || entry.path().extension() == ".jpg") {
                img_nb += 1;
                std::cout << entry.path() << std::endl;
            }
        }
    }
    //sinon on regarde si le chmin mêne à un fichier image ou video (mpeg)
    else {
        if (fs::path(path).extension() == ".jpeg" || fs::path(path).extension() == ".jpg") {
            std::cout << "This file is a jpeg/jpg, I can't do something with it alone";
            return 0;
        }
        else if (fs::path(path).extension() == ".mpeg") { 
            std::cout << "This file is a mpeg, I can't do something with it";
            return 0;
        }

    }

    //Si on a bien le lien vers un dossier, on créée un tableau correspondant au nombre jpg/jpeg
    //puis on crée des objets Image en envoyant le chemin d'accès
    if (isDir) {
        Image* imgs = new Image[img_nb];
        for (const auto& entry : fs::directory_iterator(path)) {
            if (entry.path().extension() == ".jpeg" || entry.path().extension() == ".jpg") {
                imgs[i] = Image(entry.path());
                i += 1;
            }
        }
        i = 0;
        //On parcours le tableau pour charger les Images
        for (i = 0; i < img_nb; i++) {
            imgs[i].readImg();
        }
    }
    
    return 0;
}
