# CYKalgorithm
//Developed by Javier Rodríguez 
               Christian Solis
               Juan Carlos Estevez
               
CYK algorithm implementation in C++ for a second partial project of Computational Math.

To run input the following commands in a unix console:

g++ CYK.cpp 
./a.out < test.in

On the test.in the gramatic should be in this format
ID Prod Prod
S AB BC
A BA a
B CC b
C AB a
//a space is used to finish the gramatic 
//the word should be writen after 
ababa


We are using maps to be able to process the grammar
the matrix is arranged in a diagonal in the top part of the table.
It starts at [0],[0]
and goes down until [n][m]

beeing the top right corner the last state, which should always be S
