#include<iostream>
#include "TransTable.cxx"
#include "../Alphabet/Alphabet.cxx"

int main(int argc, char** argv) {
    fsdict::Alphabet alph(argv[1]);
    fsdict::TransTable t(alph.size(), argv[2]);

    t.printCells();
}
