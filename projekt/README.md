# Projekt: Maximaler Spannbaum  
## Installation  
Fuer die graphische Darstellung, ist SFML benoetigt. Siehe: https://www.sfml-dev.org/tutorials/2.5/  
Der Code kann jedoch ohne SFML verwendet werden: Dafuer muss in `main.cpp` #define SFML_BIBLIOTHEK_INSTALLIERT false 
gesetzt werden.  

### Kompilierung  
 - Fall 1: Ohne SFML installiert (!Machen Sie sich sicher, dass in 'main.cpp': #define SFML_BIBLIOTHEK_INSTALLIERT false)  
    - Mit g++:  (In dem 'src' Ordner)
         ```bash
              g++ main.cpp graph/grap.h -std=c++11 -o3 -o maxSpannbaum
         ```
    - Mit CMake: (In dem 'projekt' Ordner)
        ```bash
              mkdir build
              cmake . -Bbuild -DCMAKE_BUILD_TYPE=Release -DSFML_INSTALLED=OFF
              make -C build
              ./build/project
        ```
 - Fall 2: Mit SFML installiert  (!!Machen Sie sich sicher, dass in 'main.cpp': #define SFML_BIBLIOTHEK_INSTALLIERT true)
    - Mit g++ (In dem 'src' Ordner)  
        ```bash
              g++ main.cpp graph/grap.h -std=c++11 -o3 -lsfml-graphics -lsfml-window -lsfml-system -o maxSpannbaum 
        ```
    - Mit CMake: (Ind dem 'projekt' Ordner)  
        ```bash
              mkdir build
              cmake . -Bbuild -DCMAKE_BUILD_TYPE=Release -DSFML_INSTALLED=ON
              make -C build
              ./build/project
        ```
## Beispiel
![Original](assets/Screenshot%20from%202019-06-22%2021-50-56.png)  
---------
![Loesung](assets/Screenshot%20from%202019-06-22%2021-50-26.png)