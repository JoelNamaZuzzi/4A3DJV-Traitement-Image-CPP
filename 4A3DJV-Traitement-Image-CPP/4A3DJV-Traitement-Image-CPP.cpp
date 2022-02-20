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

#include "Image.h"
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

    Image newImage = Image(180, 500);

    Image imageload = Image("./picture/test.jpg");

    newImage.save("./picture/newImage.jpg");
    imageload.save("./picture/testCopy.jpg");

    return 0;
}