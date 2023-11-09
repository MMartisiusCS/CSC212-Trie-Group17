#pragma once
#include <string>
#include <vector>

class TrieNode{
    private:
        std::string nodeString;
        bool isEnglishWord;
        std::vector<TrieNode*> branches;
        int repeats = 0;

        friend class TrieTree;
    public:
        TrieNode(std::string nodeString, bool isEnglishWord);
        ~TrieNode();
};

class TrieTree{
    private:
        TrieNode* root;
        TrieNode* insertPrivate(TrieNode* node,std::string nodeString, bool isEnglishWord);
        TrieNode* search(std::string nodeString,TrieNode* node);
        std::string outputDOTfile(TrieNode* node,int distance,std::ofstream* outfile);
        void findWordOfLength(TrieNode* node, int length);
    public:
        TrieTree();
        ~TrieTree();

        void findWordOfLength(int length);
        void insert(std::string nodeString, bool isEnglishWord);
        TrieNode* search(std::string nodeString);
        void outputDOTfile(std::string prefix,int distance);
        std::string getStringNode(TrieNode* nodeString);
};
