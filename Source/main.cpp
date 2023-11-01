#include "trie.h"
void outputDOTfile();
int main(int argc, char*argv[]){
    //Add: Time measurment of time to create and load tree, and time to output DOT file?
    //Create: Section that creates a file reader, reads each line from the file and loads it into the tree.
    TrieTree tree;
    //Remove: These test inserts
    tree.insert("a",false);
    tree.insert("b",false);
    tree.insert("c",false);
    tree.insert("aa",false);
    tree.insert("ab",false);
    tree.insert("ac",false);
    tree.insert("ba",false);
    tree.insert("dddd",false);
    tree.insert("testword",true);
    tree.outputDOTfile();
}
