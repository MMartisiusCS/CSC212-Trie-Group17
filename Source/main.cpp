#include "trie.h"
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include <chrono>

//Set up trie with txt file
void fileSetup(std::string fileName,TrieTree* tree) {
    // Nathan L
    // Trie setup with file loading
    auto start = std::chrono::high_resolution_clock::now();
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
    // Michael M
    // Added some simple timing information
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = (std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count()/1000.0);
    std::cout << "Time to load file into tree: " << duration << "s" << std::endl;
    std::cout << "Total nodes in tree: " << tree->getNodes() << std::endl;
    std::cout << "Total words in tree: " << tree->getWords() << std::endl;
}

int main(int argc, char*argv[]){
    
    // Michael M
    // Starting code for tree initialization
    TrieTree* tree = new TrieTree();
    std::cout << "Compiling trie..." << std::endl;
    fileSetup("words_alpha.txt",tree);
    std::cout << "Trie load complete!" << std::endl;

    bool end = false;
    bool isValidInput; // ERROR/EXCEPTION CHECKING BOOL
    std::string inputText;
    std::string input2; // variable used in INSERT case - causes error when initialized in switch statement
    std::string pre = ""; // variable for taking prefix in case 2 for dot file and searching for word in case 3
    
    // Nathan L
    // Established menu setup, error/exception checking, switch statement
    while (!end) {
        //menu - insert, dotfile, search, all of words of length, find largest, auto complete
        std::cout << "Please insert the number that corresponds to the function you wish to invoke:" << std::endl;
        std::cout << "0 - Exit" << std::endl;
        std::cout << "1 - Insert" << std::endl;
        std::cout << "2 - Output to Dotfile" << std::endl;
        std::cout << "3 - Search for a Word in Trie" << std::endl;
        std::cout << "4 - Find words of a specified length" << std::endl;
        std::cout << "5 - Find largest word" << std::endl;
        std::cout << "6 - Auto-complete word" << std::endl;
        std::cout << std::endl;

        int depth = 0;
        std::cout << "Enter a number 0-6: ";
        std::cin >> inputText;
        std::cout << std::endl;
        try {
            int input = stoi(inputText);
        switch(input) {
            case 0:
            {
                end = true;
                break;
            }
            case 1: // insert
            {
                std::cout << "0 - Insert through command line" << std::endl;
                std::cout << "1 - Insert using txt file" << std::endl;
                std::cout << std::endl;
                
                isValidInput = false;
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
                    std::cout << "Please enter a word to be inserted (Valid chars are a-z ONLY): ";
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
            }
            case 2: // output to dot-file
            {
                std::cout << "Enter the prefix you would like to search for (Enter 'ROOTNODE' to start from root): ";
                std::cin >> pre;
                std::cout << std::endl;

                isValidInput = false;

                while (!isValidInput) {
                    std::cout << "Enter the depth you would like to search to(-1 to reach bottom of the tree): ";
                    std::cin >> input2;
                    std::cout << std::endl;

                    try {
                        depth = std::stoi(input2);
                        isValidInput = true;

                    } catch (const std::invalid_argument& e) {
                        std::cout << "Invalid input. Please enter a valid integer." << std::endl;
                    }
                }

                if(pre == "ROOTNODE"){
                    tree->outputDOTfile("",depth);
                }
                else{
                    tree->outputDOTfile(pre,depth);
                }
                break;
            }
            case 3: // search for word
            {
                std::cout << "Enter a word to search for: ";
                std::cin >> pre;
                tree->searchForWord(pre);
                sleep(1);
                break;
            }
            case 4: // find words of specified length 
            {
                isValidInput = false;

                while (!isValidInput) {
                    std::cout << "Enter the length of word you would like to search for: ";
                    std::cin >> input2;
                    std::cout << std::endl;

                    try {
                        depth = std::stoi(input2);
                        isValidInput = true;

                    } catch (const std::invalid_argument& e) {
                        std::cout << "Invalid input. Please enter a valid integer." << std::endl;
                    }
                }
            
                tree->findWordOfLength(depth);
                break;
            }
            case 5: // largest word
            {
                std::string longestWord = tree->findLargest();
                std::cout << "Largest word: " << longestWord << "\n";
                std::cout << "Length: " << longestWord.size() << "\n";
                sleep(1);
                break;
            }
            case 6: // auto-complete
            {
                std::cout << "Please Enter a suffix to complete: ";
                    std::cin >> inputText;
                    std::cout << std::endl;

                    isValidInput = false;

                    while (!isValidInput) {
                        std::cout << "Enter the length of word to complete the suffix too: ";
                        std::cin >> input2;
                        std::cout << std::endl;

                        try {
                            depth = std::stoi(input2);
                            isValidInput = true;

                        } catch (const std::invalid_argument& e) {
                            std::cout << "Invalid input. Please enter a valid integer." << std::endl;
                        }
                    }
                    
                tree->autocomplete(inputText, depth);
                break;
            }
            default:
            {
                // change number depending on amount of menu options
                std::cout << "Invalid input, Please enter a number 0-6" << std::endl;
            }
        }
        } catch (const std::invalid_argument& e) {
            std::cout << "Invalid input. Please enter a valid integer." << std::endl;
        }
    }
}
