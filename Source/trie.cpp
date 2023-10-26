#include "trie.h"

TrieNode::TrieNode(std::string nodeString, bool isEnglishWord){
    this->nodeString = nodeString;
    this->isEnglishWord = isEnglishWord;
    this->branches = {};
}

TrieNode::~TrieNode()
{
}

bool TrieNode::stringMatch(std::string a, std::string b)
{
    return false;
}

TrieNode *TrieTree::insert(std::string nodeString, bool isEnglishWord)
{

    return nullptr;
}

TrieTree::TrieTree()
{
    this->root = new TrieNode("",false);
}

TrieTree::~TrieTree()
{
}

void *TrieTree::insert(std::string nodeString, bool isEnglishWord)
{
    for(int i = 1; i < nodeString.size();i++){
        std::string strToInsert = nodeString.substr (0,i);
    }
    return nullptr;
}
bool TrieTree::search(int nodeString) {
    return false;
}
