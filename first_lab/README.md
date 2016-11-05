# LAB_ANRO

Uruchamianie programu:
W wierszu poleceń systemu Linux:
1) wejść do workspace'a catkin.
2) zasourcować odpowiednią wersję ROSa
3) zasourcować plik devel/setup.bash
4) skompilować projekt przy użyciu polecenia 'catkin_make'
5) w oddzielnym oknie uruchamić server ROS poleceniem 'roscore'
6) wejść do katalogu pakiet first_lab poleceniem 'roscd first_lab'
7) uruchomić Node'a z żółwiem używająć polecenia 'roslaunch launch/turtle.launch' 
8) uruchomić skrypt do sterowania polecenie 'rosrun first_lab sterowanie.py'


Objaśnienia dotyczące poszczególnych plików
-----------
***launch/turtle.lounch***
Plik służący do uruchamiania Noda z żółwiem

-----------
***package.xml***
Plik zawiera informacje o pakiecie. Znajdują się w nim nazwa, dane autora,
licencje oraz zależonści (dependecje) z innymi pakietami.

----------
***CMakeFile.txt***
Makefile pakietu. Zawiera wszystkie niezbędne informacje do skompilowania pakietu
takie jak zależności czy załączaone pakiety.

---------
***scripts/sterowanie.py***
Skrypt służący do sterowania żółwiem z pakietu turtlesim poporzez topic
cmd_vel. Umożliwia on poruszanie żółwiem za pomocą klawiszy 'wasd'.

