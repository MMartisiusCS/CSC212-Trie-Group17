#pragma once
#include <string>
#include <vector>

class TrieNode{
    private:
        std::string nodeString;
        bool isEnglishWord;
        std::vector<TrieNode*> branches;

        friend class TrieTree;
    public:
        TrieNode(std::string nodeString, bool isEnglishWord);
        ~TrieNode();
};

class TrieTree{
    private:
        TrieNode* root;
        //TrieNode* insert(std::string nodeString, bool isEnglishWord);
        //int height(TrieNode* node);
        //void preorder(std::ostream& os, BSTNode* node);
        //void inorder(std::ostream& os, BSTNode* node);
        //void postorder(std::ostream& os, BSTNode* node);
        //void destroy(BSTNode* node);
    public:
        TrieTree();
        ~TrieTree();

        TrieNode* insert(std::string nodeString, bool isEnglishWord);
        //int height();
        //void preorder(std::ostream& os);
        //void inorder(std::ostream& os);
        //void postorder(std::ostream& os);
        //bool search(std::string nodeString);
};