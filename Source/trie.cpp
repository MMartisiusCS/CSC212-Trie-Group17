#include "trie.h"
#include <iostream>
#include <fstream>  

TrieNode::TrieNode(std::string nodeString, bool isEnglishWord){
    this->nodeString = nodeString;
    this->isEnglishWord = isEnglishWord;
    this->branches = {};
    this->height = 0;
}

TrieNode::~TrieNode()
{
}

bool TrieNode::stringMatch(std::string b)
{
    int length;
    if (this->nodeString.size() >= b.size()){
        length = this->nodeString.size();
    } else {
        length = b.size();
    }
    for (int i = 0; i < length;i++){
        if(this->nodeString[i] != b[i]){
            return false;
        }
    }
    return true;
}

TrieNode *TrieTree::insertPrivate(TrieNode* node, std::string nodeString, bool isEnglishWord)
{
    //if node is nullptr, make node with nodeString, return new node
    if(node == nullptr){
        node = new TrieNode(nodeString,isEnglishWord);
        return node;
    }
    // if node.size()+1 == nodeString.size, we are going to be inserting a new node
    if (node->nodeString.size()+1 == nodeString.size()){
        // We must check if nodeString exist as any of the branches
        // If it does, we do not insert, and return the pointer that points to nodeString in the tree
        for(int i = 0; i < node->branches.size();i++){
            if(node->branches[i]->stringMatch(nodeString)){
                return node->branches[i];
            }
        }
        // If it does not, we must create it
        node->branches.push_back(new TrieNode (nodeString,isEnglishWord));
        return node->branches[node->branches.size()-1];
    // if node.size()+1 != nodeString.size, we are going to be going deeper into the tree
    } else {
        //We must check if the substring of length node.size()+1 of nodeString is found as a existing branch of node.
        // If it does exist, we must follow that branch down
        // If it does not, we must create the new branch and follow it.
        int index = -1;
        for(int i = 0; i < node->branches.size();i++){
            if(node->branches[i]->stringMatch(nodeString.substr(0,node->nodeString.size()+1))){
                index = i;
                break;
            }
        }
        if(index != -1){
            return insertPrivate(node->branches[index],nodeString,isEnglishWord);
        } else {
            node->branches.push_back(new TrieNode (nodeString.substr(0,node->nodeString.size()+1),false));
            return insertPrivate(node->branches[node->branches.size()-1],nodeString,isEnglishWord);
        }
    }
    return nullptr;
}

std::string TrieTree::outputDOTfileRecursive(TrieNode *node)
{
    std::string outputString;
    //Add current node's branches to output
    for (int i = 0; i < node->branches.size();i++){
        if (node->nodeString.length() == 0){
            outputString = outputString + "ROOTNODE" + " -- " + node->branches[i]->nodeString + "\n";
        } else {
            outputString = outputString + node->nodeString + " -- " + node->branches[i]->nodeString + "\n";
        }
    }
    // call for each branch
    for (int i = 0; i < node->branches.size();i++){
        outputString = outputString + outputDOTfileRecursive(node->branches[i]);
    }
    return outputString;
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
    if(nodeString.size() > 1){
        for(int i = 1; i < nodeString.size();i++){
            std::string strToInsert = nodeString.substr (0,i);
            if (i+1 == nodeString.size()){
                insertPrivate(root,strToInsert,true);
            } else {
                insertPrivate(root,strToInsert,false);
            }
        }
    }
    insertPrivate(root,nodeString,isEnglishWord);
    return;
}

bool TrieTree::search(std::string nodeString)
{
    return false;
}

void TrieTree::outputDOTfile()
{
    std::string outputString;
    std::ofstream outfile ("graph.gv");
    outputString = this->outputDOTfileRecursive(root);
    outfile << "graph TrieTreeGraph {\n" << outputString << "}"<<std::endl;
    outfile.close();
}
