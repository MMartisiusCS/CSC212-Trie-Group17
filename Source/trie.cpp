#include "trie.h"
#include <iostream>
#include <fstream>  
#include <algorithm>

TrieNode::TrieNode(std::string nodeString, bool isEnglishWord){
    this->nodeString = nodeString;
    this->isEnglishWord = isEnglishWord;
    this->branches = {};
}

TrieNode::~TrieNode()
{
}

TrieNode *TrieTree::insertPrivate(TrieNode* node, std::string nodeString, bool isEnglishWord)
{
    //If node == nodeString, return node
    //else, If node->branches contains substring of nodeString(0,node.nodeString.size()+1), call insert at that node, with nodeString and isEnglishWord
            //Else, make a new node in node-branches(nodeString(0,nodeString.size()+1),false), then call inser at that node with nodeString and isEnglishWord
    if(node->nodeString == nodeString){
        node->isEnglishWord = isEnglishWord;
        return node;
    } else {
        for(int i = 0; i < node->branches.size();i++){
            //If node->branches contains substring of nodeString(0,nodeString.size()+1), call insert at that node, with nodeString and isEnglishWord
            if(node->branches[i]->nodeString == nodeString.substr(0,node->nodeString.size()+1)){
                return insertPrivate(node->branches[i],nodeString,isEnglishWord);
            }
        }
        node->branches.push_back(new TrieNode(nodeString.substr(0,node->nodeString.size()+1),false));
        return insertPrivate(node->branches.back(),nodeString,isEnglishWord);
    }
}

TrieNode *TrieTree::search(std::string nodeString, TrieNode *node)
{
    for(int i = 0; i < node->branches.size(); i++){
        if(node->branches[i]->nodeString == nodeString){
            return node->branches[i];
        } else if(node->branches[i]->nodeString == nodeString.substr(0,node->nodeString.size()+1) ){
            return search(nodeString,node->branches[i]);
        }
    }
    return nullptr;
}

std::string TrieTree::outputDOTfile(TrieNode *node, int distance, std::ofstream *outfile)
{
    std::string outputString;
    if(distance != 0){
        //Add current node's branches to output
        *outfile << node->nodeString << "_ [label=" << node->nodeString << "]\n";
        for (int i = 0; i < node->branches.size();i++){
            if (node->nodeString.length() == 0){
                *outfile << "ROOTNODE_ -- " << node->branches[i]->nodeString << "_\n";
            } else {
                *outfile << node->nodeString << "_ -- " << node->branches[i]->nodeString << "_\n";
            }
            if(node->branches[i]->isEnglishWord){
                *outfile << node->branches[i]->nodeString << "_ [style=\"filled,dashed\",shape=box,fontsize=20.0,fillcolor=lightblue];\n";
            }
        }
        // call for each branch
        for (int i = 0; i < node->branches.size();i++){
            *outfile << outputDOTfile(node->branches[i], distance-1,outfile);
        }
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
    insertPrivate(root,nodeString,isEnglishWord);
    return;
}

TrieNode* TrieTree::search(std::string nodeString)
{   
    if(nodeString == ""){
        return root;
    }
    return search(nodeString,root);
}

void TrieTree::outputDOTfile(std::string prefix,int distance)
{
    std::ofstream outfile ("graph_"+ prefix + "_" + std::to_string(distance) + ".gv");
    outfile << "graph TrieTreeGraph {\n";
    if(prefix.size() == 0){
         outfile << "ROOTNODE_ [label=\"\"]\n";
    }
    this->outputDOTfile(search(prefix),distance,&outfile);
    outfile << "}"<<std::endl;
    outfile.close();
}

void TrieTree::findWordOfLength(TrieNode* node, int length){
    if (length!=0){
        for(int i = 0; i < node->branches.size(); i++){
            findWordOfLength(node->branches[i], length-1);
        }
    }
    if (length == 0 && node->isEnglishWord){
        std::cout << node->nodeString << std::endl;
    }
}

void TrieTree::findWordOfLength(int length){
    findWordOfLength(root, length);
}
std::string TrieTree::getStringNode(TrieNode* node) {
    return node->nodeString;
}

void TrieTree::searchForWord(std::string word){
    TrieNode* node = search(word, root);
    if(node == nullptr){
        std::cout << "Word does not exist." << std::endl;
    }
    else{
        std::cout << "Word does exist!" << std::endl;
    }
}
