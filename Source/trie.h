#pragma once
#include <string>
#include <vector>

class TrieNode{
    private:
        char nodeChar; // Character to store at node
        bool isEnglishWord; // If this node is a english word, starting from root node
        TrieNode *branches [26] = {}; // Storage of children/branches
        int repeats = 0; // How many times is this used in other words.
        int depth; // Depth of node in tree (also represents length of string starting from rootnode)

        friend class TrieTree;
    public:
        TrieNode(char nodeChar, bool isEnglishWord, int depth);
        TrieNode(bool isEnglishWord, int depth);
        ~TrieNode();
};

class TrieTree{
    private:
        int nodes = 0; // How many nodes are in the tree
        int words = 0; // Hoe many words are in the tree
        TrieNode* root; // Starting node, char is empty char
        TrieNode* insertPrivate(TrieNode* node,std::string nodeString, bool isEnglishWord);
        TrieNode* search(std::string nodeString,TrieNode* node);
        void outputDOTfile(TrieNode* node,int distance,std::ofstream* outfile,std::string prefixFromLastNode);
        void findWordOfLength(TrieNode* node, int length, std::string str);
        std::string findLargestWord(TrieNode* node);
        bool deletePrivate(TrieNode*& node, const std::string &word, int depth);
        void autocompleteHelper(TrieNode *node, int length, std::string currentWord);

    public:
        TrieTree();
        ~TrieTree();

        int getWords();
        int getNodes();
        void findWordOfLength(int length);
        void insert(std::string nodeString, bool isEnglishWord);
        TrieNode* search(std::string nodeString);
        void outputDOTfile(std::string prefix,int distance);
        std::string getStringNode(TrieNode* nodeString);
        void searchForWord(std::string word);
        std::string findLargest();
        void autocomplete(std::string prefix, int length);
        bool deleteWord(const std::string &word);
};
