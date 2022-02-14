# 4A3DJV-Traitement-Image-CPP
Pour install des librairies CPP sous VS
1. Installer vcpkg à la racine via le command prompt
tuto:
https://github.com/microsoft/vcpkg/blob/master/README_fr.md

2. Dans le command prompt taper .\vcpkg\vcpkg install libjpeg-turbo
Cela télécharger et installera la lib libjpeg

3. taper: .\vcpkg\vcpkg\integrate install
Cela permetra à VS de faire les includes sans se casser la tête avec du linkage à la con

4. Sous VS dans Propriétés du projet-> C/C++ -> Général -> Autre répertoires Include ajouter:
.\vcpkg\vcpkg\installed\x64-windows\include
