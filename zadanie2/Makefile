TRGDIR=.
OBJ=./obj
SRC=./src
INC=./inc
TESTS=./tests
TBIN=./tests/bin
FLAGS= -Wall -pedantic -std=c++14 -iquote inc

${TRGDIR}/test_arytm_zesp: ${OBJ} ${OBJ}/main.o ${OBJ}/LZespolona.o\
                     ${OBJ}/WyrazenieZesp.o ${OBJ}/BazaTestu.o ${OBJ}/BazaTestu.o ${OBJ}/Statystyka.o
	g++ -o ${TRGDIR}/test_arytm_zesp ${OBJ}/main.o ${OBJ}/LZespolona.o\
                     ${OBJ}/WyrazenieZesp.o ${OBJ}/BazaTestu.o ${OBJ}/Statystyka.o

${OBJ}:
	mkdir ${OBJ}

${OBJ}/main.o: ${SRC}/main.cpp inc/LZespolona.hh inc/BazaTestu.hh 
	g++ -c ${FLAGS} -o ${OBJ}/main.o ${SRC}/main.cpp

${OBJ}/LZespolona.o: ${SRC}/LZespolona.cpp inc/LZespolona.hh
	g++ -c ${FLAGS} -o ${OBJ}/LZespolona.o ${SRC}/LZespolona.cpp

${OBJ}/BazaTestu.o: ${SRC}/BazaTestu.cpp inc/BazaTestu.hh inc/WyrazenieZesp.hh\
                       inc/LZespolona.hh
	g++ -c ${FLAGS} -o ${OBJ}/BazaTestu.o ${SRC}/BazaTestu.cpp

${OBJ}/WyrazenieZesp.o: ${SRC}/WyrazenieZesp.cpp inc/WyrazenieZesp.hh\
                       inc/LZespolona.hh
	g++ -c ${FLAGS} -o ${OBJ}/WyrazenieZesp.o ${SRC}/WyrazenieZesp.cpp

${OBJ}/Statystyka.o: ${SRC}/Statystyka.cpp inc/Statystyka.hh
	g++ -c ${FLAGS} -o ${OBJ}/Statystyka.o ${SRC}/Statystyka.cpp

${TBIN}/test_1: ${TBIN} ${OBJ}/LZespolona.o 
	g++ -o ${TESTS}/bin/test_1 ${FLAGS} -I${TESTS}/doctest ${TESTS}/test1.cpp ${OBJ}/LZespolona.o

${TBIN}/test_2: ${TBIN} ${OBJ}/LZespolona.o 
	g++ -o ${TESTS}/bin/test_2 ${FLAGS} -I${TESTS}/doctest ${TESTS}/test2.cpp ${OBJ}/LZespolona.o

${TBIN}/test_3: ${TBIN} ${OBJ}/LZespolona.o 
	g++ -o ${TESTS}/bin/test_3 ${FLAGS} -I${TESTS}/doctest ${TESTS}/test3.cpp ${OBJ}/LZespolona.o

${TBIN}/test_4: ${TBIN} ${OBJ}/LZespolona.o 
	g++ -o ${TESTS}/bin/test_4 ${FLAGS} -I${TESTS}/doctest ${TESTS}/test4.cpp ${OBJ}/LZespolona.o

${TBIN}/test_5: ${TBIN} ${OBJ}/LZespolona.o 
	g++ -o ${TESTS}/bin/test_5 ${FLAGS} -I${TESTS}/doctest ${TESTS}/test5.cpp ${OBJ}/LZespolona.o

${TBIN}/test_6: ${TBIN} ${OBJ}/LZespolona.o 
	g++ -o ${TESTS}/bin/test_6 ${FLAGS} -I${TESTS}/doctest ${TESTS}/test6.cpp ${OBJ}/LZespolona.o

${TBIN}:
	mkdir ${TBIN}

test: ${TBIN}/test_1 ${TBIN}/test_2 ${TBIN}/test_3 ${TBIN}/test_4 ${TBIN}/test_5 ${TBIN}/test_6

run:
	${TRGDIR}/test_arytm_zesp latwy

clean:
	rm -f ${TRGDIR}/test_arytm_zesp ${OBJ}/* ${TBIN}/*
