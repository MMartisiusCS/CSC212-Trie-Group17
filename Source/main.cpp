#include "trie.h"
void outputDOTfile();
int main(int argc, char*argv[]){
    TrieTree tree;
    tree.insert("a",false);
    tree.insert("b",false);
    tree.insert("c",false);
    tree.insert("aa",false);
    tree.insert("ab",false);
    tree.insert("ac",false);
    tree.insert("ba",false);
    tree.insert("dddd",false);
    tree.insert("testword",true);
    int test = 0;
    tree.outputDOTfile();
}
