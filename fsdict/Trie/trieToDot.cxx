#include "Trie.h"
#include<iostream>

using namespace fsdict;
int main(int argc, char** argv) {
    Alphabet alph(argv[1]);
    Trie t(alph, argv[2]);

    t.toDot();


}
