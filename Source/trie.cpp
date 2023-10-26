#include "trie.h"

TrieNode::TrieNode(std::string nodeString, bool isEnglishWord){
    this->nodeString = nodeString;
    this->isEnglishWord = isEnglishWord;
    this->branches = {};
}

TrieNode::~TrieNode()
{
}

TrieTree::TrieTree()
{
    this->root = new TrieNode("",false);
}

TrieTree::~TrieTree()
{
}

TrieNode *TrieTree::insert(std::string nodeString, bool isEnglishWord)
{
    return nullptr;
}
bool TrieTree::search(int nodeString) {
    return false;
}
