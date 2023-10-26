#include "trie.h"

TrieNode::TrieNode(std::string nodeString, bool isEnglishWord){
    this->nodeString = nodeString;
    this->isEnglishWord = isEnglishWord;
    this->branches = {};
    this->height = 0;
}

TrieNode::~TrieNode()
{
}

bool TrieNode::stringMatch(std::string a, std::string b)
{

}

TrieNode *TrieTree::insertPrivate(std::string nodeString, bool isEnglishWord)
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

void TrieTree::insert(std::string nodeString, bool isEnglishWord)
{
    for(int i = 1; i < nodeString.size();i++){
        std::string strToInsert = nodeString.substr (0,i);
    }
    return;
}

bool TrieTree::search(std::string nodeString)
{
    return false;
}
