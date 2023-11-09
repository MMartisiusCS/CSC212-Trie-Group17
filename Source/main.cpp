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
    
    TrieTree* tree = new TrieTree();
    fileSetup("words_alpha.txt",tree);

    //menu - insert, dotfile, search, all of words of length, find largest
    std::cout << "Please insert the number that corresponds to the function you wish to invoke:" << std::endl;
    std::cout << "0 - Exit" << std::endl;
    std::cout << "1 - Insert" << std::endl;
    std::cout << "2 - Output to Dotfile" << std::endl;
    std::cout << "3 - Search for a Word" << std::endl;
    std::cout << "4 - Find words of a specified length" << std::endl;
    std::cout << "5 - Find largest word" << std::endl;
    
    bool end = false;
    int input;
    while (!end) {
        std::string pre = "";
        int depth = 0;
        std::cout << "Enter a number 0-5: ";
        std::cin >> input;
        std::cout << std::endl;
        switch(input) {
            case 0:
                end = true;
                break;
            
            case 1:

                break;

            case 2:
                std::cout << "Enter the prefix you would like to search for: ";
                std::cin >> pre;
                std::cout << "Enter the depth you would like to search (-1 to reach bottom of the tree): ";
                std::cin >> depth;

                tree->outputDOTfile(pre,depth);
                break;

            case 3:

                break;

            case 4:
                std::cout << "Enter the length of word you would like to search for: ";
                std::cin >> depth;
                tree->findWordOfLength(depth);
                break;

            case 5:

                break;

            default:
                // change number depending on amount of menu options
                std::cout << "Invalid input, Please enter a number 0-5" << std::endl;

        }
    }

    tree->outputDOTfile("ar",4);
}
