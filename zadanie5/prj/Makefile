TASKNO=5
APP=sterowanie-dronem
TASKDIR=${HOME}/edu/po/zad/z${TASKNO}

__start__: obj dat ./${APP}
	rm -f core.* core; ./${APP}

# Tworzy katalog "obj" gdy go nie ma
# 
obj:
	mkdir obj

dat:
	mkdir dat


./${APP}: obj/main.o obj/lacze_do_gnuplota.o
	g++ -o ./${APP} obj/main.o obj/lacze_do_gnuplota.o


ext: ./${APP}_rozszerzony
	rm -f core.* core; echo "2i 1+3.1i 2 ? / + ?" | ./${APP}_rozszerzony


obj/main.o: src/main.cpp inc/lacze_do_gnuplota.hh inc/Dron.hh inc/BrylaGeometryczna.hh\
			inc/Graniastoslup6.hh inc/Prostopadloscian.hh inc/Scena.hh inc/Macierz3x3.hh\
			inc/Wektor3D.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/main.o src/main.cpp

obj/lacze_do_gnuplota.o: src/lacze_do_gnuplota.cpp inc/lacze_do_gnuplota.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/lacze_do_gnuplota.o src/lacze_do_gnuplota.cpp

obj/Dron.o: src/Dron.cpp inc/Dron.hh inc/lacze_do_gnuplota.hh inc/Prostopadloscian.hh inc/Graniastoslup6.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/Dron.o src/Dron.cpp

obj/BrylaGeometryczna.o: src/BrylaGeometryczna.cpp inc/BrylaGeometryczna.hh inc/wektor3D.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/BrylaGeometryczna.o src/BrylaGeometryczna.cpp

obj/Graniastoslup6.o: src/Graniastoslup6.cpp inc/Graniastoslup6.hh inc/BrylaGeometryczna.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/Graniastoslup6.o src/Graniastoslup6.cpp

obj/Prostopadloscian.o: src/Prostopadloscian.cpp inc/Prostopadloscian.hh inc/BrylaGeometryczna.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/Prostopadloscian.hh src/Prostopadloscian.cpp

obj/Scena.o: src/Scena.cpp inc/Scena.hh inc/BrylaGeometryczna.hh inc/Dron.hh inc/lacze_do_gnuplota.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/Scena.o src/Scena.cpp

obj/Macierz3x3.o: inc/Macierz3x3.hh inc/Macierz.hh inc/Wektor3D.hh inc/Wektor.hh
	g++ -Iinc -W -Wall -pedantic -c -o obj/Macierz3x3.o 

obj/Wektor3D.o: inc/Wektor3D.hh inc/Wektor.hh
	g++ -Iinc -W -Wall -pedantic -c -o obj/Wektor3D.o 

clean:
	rm -f obj/* ./${APP} core.* core

${TASKDIR}:
	mkdir -p ${TASKDIR}/bin.diablo ${TASKDIR}/bin.panamint

__TARGET__:
	if [ ! "${HOST}" = "diablo" ] && [ ! "${HOST}" = "panamint" ]; then exit 1; fi

export: __TARGET__ ./${APP}  ./${APP}_rozszerzony ${TASKDIR}
	mv ${APP} ${APP}_rozszerzony ${HOME}/edu/po/zad/z${TASKNO}/bin.${HOST}/

help:
	@echo
	@echo " make        - tworzenie i uruchomienie aplikacji"
	@echo " make ext    - tworzenie i uruchomienie aplikacji w wersji rozszerzonej"
	@echo " make clean  - usuniecie produktow kompilacji i konsolidacji"
	@echo " make help   - wyswietla niniejsza informacje"
	@echo
