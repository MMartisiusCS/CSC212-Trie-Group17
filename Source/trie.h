#pragma once
#include <string>
#include <vector>

class TrieNode{
    private:
        char nodeChar;
        bool isEnglishWord;
        TrieNode *branches [26] = {};
        int repeats = 0;
        int depth;

        friend class TrieTree;
    public:
        TrieNode(char nodeChar, bool isEnglishWord, int depth);
        TrieNode(bool isEnglishWord, int depth);
        ~TrieNode();
};

class TrieTree{
    private:
        int nodes;
        int words;
        TrieNode* root;
        TrieNode* insertPrivate(TrieNode* node,std::string nodeString, bool isEnglishWord);
        TrieNode* search(std::string nodeString,TrieNode* node);
        void outputDOTfile(TrieNode* node,int distance,std::ofstream* outfile,std::string prefixFromLastNode);
        void findWordOfLength(TrieNode* node, int length, std::string str);
        std::string findLargestWord(TrieNode* node);
        void autocompleteHelper(TrieNode* node, int length, std::string currentWord);
    public:
        TrieTree();
        ~TrieTree();

        void findWordOfLength(int length);
        void insert(std::string nodeString, bool isEnglishWord);
        TrieNode* search(std::string nodeString);
        void outputDOTfile(std::string prefix,int distance);
        std::string getStringNode(TrieNode* nodeString);
        void searchForWord(std::string word);
        std::string findLargest();
        void autocomplete(std::string suffix, int length);
};
