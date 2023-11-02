#include "trie.h"
#include <iostream>
#include <fstream>  

//Set up trie with txt file
void fileSetup(std::string fileName,TrieTree* tree) {
    //Create: Section that creates a file reader, reads each line from the file and loads it into the tree.
    std::ifstream infile;
    std::string line;
    infile.open(fileName);

    if (infile.fail()) {
        std::cerr << "Can't open file\n";
        return;
    }

    while(std::getline(infile,line)) {
        tree->insert(line,true);
    }
}

int main(int argc, char*argv[]){
    //Add: Time measurment of time to create and load tree, and time to output DOT file?
    

    TrieTree* tree = new TrieTree();
    fileSetup("words_alpha.txt",tree);
    tree->outputDOTfile("",-1);
}
