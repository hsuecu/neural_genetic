#!/bin/sh

g++ -O2 -m64  main.cpp Node.cpp Connections.cpp Model.cpp Genetic.cpp -lm -o main
strip main

