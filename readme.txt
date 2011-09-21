################################################################################
#                                                                              #
#  Tomas Hurban                                                                #
#  Diploma project                                                             #
#                                                                              #
#  Hair simulation and visualization using GPU                                 #
#  2011, June                                                                  #
#                                                                              #
#  Slovak University of Technology Bratislava                                  #
#  FACULTY OF INFORMATICS AND INFORMATION TECHNOLOGIES                         #
#                                                                              #
################################################################################

Index:
1. Vytvorene subory
2. Vytvorenie projektu
3. Moznosti aplikacie
4. Ovladanie aplikacie
5. Bugs

################################################################################
# 1. Do Visualisation Library boli vlozene subory
################################################################################

- v "src/src/CMakeList.txt" pridane riadky (bez uvodzoviek):
  
  "add_subdirectory("hairs")"
  "add_subdirectory("bullet")"

+ zmeny:

  - QT4 (ON)
  - Win32 (OFF)

- pridane adresare:

  "src/src/hairs" (hlavny projekt)
  "src/src/bullet" (rozbalene subory Bullet physics library)


################################################################################
# 2. Vytvorenie projektu
################################################################################

1. Stiahnut (pre Windows nainstalovat) Boost C++ library

2. V CMake pri vytvarani projektu treba oznacit: USE_MSVC_RUNTIME_LIBRARY_DLL - ON

3. Vo vytvorenom projekte treba nastavit projekt Hairs ako "startup projekt"

(dalsie len vo Visual Studiu)

4. Nastavit v projekte Hairs - Project Dependencies (BulletCollision, BulletDynamics, BulletSoftBody, LinearMath, OpenGLSupport)

5. Nastavit vo vlastnostiach projektu: C/C++->General: Additional Include Directories - pridat cestu ku knizniciam Bullet 

( $Project$/src/bullet/src/ )

6. Pridat kniznice Bullet Physics library do projektu (ako bod 4) NA KONIEC ZOZNAMU(!): C/C++->General: Additional Include Directories 

( $Project$/src/bullet/Demos/OpenGL/ )
( $Project$/src/bullet/Glut/ )

7. V nastaveniach projektu Hairs treba nastavit: Linker->General: Link Library Dependencies - Yes

8. Pridat kniznice Bullet Physics library do projektu: Linker->General: Additional Library Directories 

( $Project$/src/bullet/Glut/ )

9. Nastavit vo vlastnostiach projektu: C/C++->General: Additional Include Directories - pridat cestu ku knizniciam Boost library

10. Pridat kniznice Boost library do projektu: Linker->General: Additional Library Directories 


################################################################################
# 3. Moznosti aplikacie
################################################################################

- Geometry Antialiasing (multisampling) - vyhladzovanie hran - ak sa nastavi vyssi nez je podporovany, je automaticky znizeny na najvyssi mozny


################################################################################
# 4. Ovladanie aplikacie
################################################################################

- lave tlacidlo mysi: rotacia objektu / rotacia kamery
- prave tlacidlo mysi: zoom
- stlacene koliesko mysi: pohyb objektu / pohyb v priestore
- F: aktivovanie WSAD pohybu v priestore
- T: ukoncenie pohybu pomocou WSAD
- C: zastavenie / spustenie animacie
- M: zobrazenie Menu dialogu
- H: zobrazenie / skrytie okna simulacie
- Space: spustenie / zastavenie simulacie
- F1: fulscreen on/off
- F5: ulozi screenshot OpenGL okna
- ESC: ukoncenie programu


################################################################################
# 5. Bugs
################################################################################

- v okne simulacie vlasy nie su vizualne spojene s kontrolnymi bodmi
- runtime error pri stlaceni klavesy Space v okne simulacie

 