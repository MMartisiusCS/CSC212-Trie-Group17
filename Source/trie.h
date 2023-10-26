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
        bool stringMatch(std::string a, std::string b);
};

class TrieTree{
    private:
        TrieNode* root;
        TrieNode* insertPrivate(std::string nodeString, bool isEnglishWord);
        //int height(TrieNode* node);
        //void preorder(std::ostream& os, BSTNode* node);
        //void inorder(std::ostream& os, BSTNode* node);
        //void postorder(std::ostream& os, BSTNode* node);
        //void destroy(BSTNode* node);
    public:
        TrieTree();
        ~TrieTree();

        void insert(std::string nodeString, bool isEnglishWord);
        //int height();
        //void preorder(std::ostream& os);
        //void inorder(std::ostream& os);
        //void postorder(std::ostream& os);
        bool search(std::string nodeString);
};
