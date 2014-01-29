#include "../Alphabet/Alphabet.cxx"
#include "../TransTable/TransTable.cxx"
#include "Trie.cxx"
#include<iostream>

using namespace fsdict;

int main(int argc, char** argv) {
    Alphabet alph(argv[1]);
    Trie t(alph);
    t.compileDic(argv[2],argv[3]);
    t.printDic(0);
}
