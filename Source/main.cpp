#include "trie.h"

//Set up trie with txt file
Trietree fileSetup(std::string fileName) {
    //Create: Section that creates a file reader, reads each line from the file and loads it into the tree.
    std::ifstream infile;
    std::string line;
    infile.open(fileName);

    Trietree tree;

    if (infile.fail()) {
        std::cerr << "Can't open file\n";
        return 1;
    }

    while(std::getline(infile,line)) {
        tree.insert(line, true);
    }
}

int main(int argc, char*argv[]){
    //Add: Time measurment of time to create and load tree, and time to output DOT file?
    

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
    tree.outputDOTfile("",-1);
}
