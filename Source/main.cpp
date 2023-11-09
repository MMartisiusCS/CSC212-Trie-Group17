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

    //menu - insert, dotfile, search, all of words of length, find largest, auto complete
    std::cout << "Please insert the number that corresponds to the function you wish to invoke:" << std::endl;
    std::cout << "0 - Exit" << std::endl;
    std::cout << "1 - Insert" << std::endl;
    std::cout << "2 - Output to Dotfile" << std::endl;
    std::cout << "3 - Search for a Word" << std::endl;
    std::cout << "4 - Find words of a specified length" << std::endl;
    std::cout << "5 - Find largest word" << std::endl;
    std::cout << "6 - Auto-complete word" << std::endl;
    std::cout << std::endl;

    bool end = false;
    int input;
    std::string input2; // variable used in INSERT case - causes error when initialized in switch statement
    while (!end) {
        std::string pre = "";
        int depth = 0;
        std::cout << "Enter a number 0-6: ";
        std::cin >> input;
        std::cout << std::endl;
        switch(input) {
            case 0:
                end = true;
                break;
            
            case 1: // insert
                std::cout << "0 - Insert through command line" << std::endl;
                std::cout << "1 - Insert using txt file" << std::endl;
                std::cout << std::endl;
                
                bool isValidInput = false;
                int inputValue;

                while (!isValidInput) {
                    std::cout << "Enter 0 or 1: ";
                    std::cin >> input2;
                    std::cout << std::endl;

                    try {
                        inputValue = std::stoi(input2);

                        if (inputValue == 0 || inputValue == 1) {
                            isValidInput = true;
                        } else {
                            std::cout << "Invalid input. Please enter 0 or 1." << std::endl;
                        }
                    } catch (const std::invalid_argument& e) {
                        std::cout << "Invalid input. Please enter a valid integer." << std::endl;
                    }
                }

                if(inputValue == 0) {
                    std::cout << "Please enter a word to be inserted: ";
                    std::cin >> input2;
                    // add expression to check for isEnglishWord
                    tree->insert(input2, 0);
                    std::cout << std::endl;
                } else if (inputValue == 1) {
                    std::cout << "Please enter the name of the file to be inserted: ";
                    std::cin >> input2;
                    fileSetup(input2, tree);
                    std::cout << std::endl;
                }
                break;

            case 2:
                std::cout << "Enter the prefix you would like to start from: ";
                std::cin >> pre;
                std::cout << "Enter the depth you would like to search to(-1 to reach bottom of the tree): ";
                std::cin >> depth;

                tree->outputDOTfile(pre,depth);
                break;

            case 3: // search for word

                break;

            case 4:
                std::cout << "Enter the length of word you would like to search for: ";
                std::cin >> depth;
                tree->findWordOfLength(depth);
                break;

            case 5: // largest word

                break;
            
            case 6: // auto-complete

                break;
            
            default:
                // change number depending on amount of menu options
                std::cout << "Invalid input, Please enter a number 0-6" << std::endl;

        }
    }

    tree->outputDOTfile("ar",4);
}
