g++ tuto.cpp -I/usr/include/irrlicht/ -lIrrlicht -lGL -LGLU


Installer cmake.msi sur leur site et enable pour qu'il soit executable en ligne de commande (1 case a cocher)
Avoir un FindIrrlicht.cmake dans "Program Files/CMake/share/cmake-3.11/Modules"
Aller sur powershell dans le repo Bomberman
Effacer tous les elements non necessaires
Clean le dossier build
Aller dans le dossier build
1) cmake -G "VIsual Studio 15 2017 Win64" ..
2) cmake --build . --config Release
L'executable a été crée dans le dossier release
