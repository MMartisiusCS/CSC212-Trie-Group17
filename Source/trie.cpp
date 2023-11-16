#include "trie.h"
#include <iostream>
#include <fstream>  
#include <algorithm>

TrieNode::TrieNode(char nodeChar, bool isEnglishWord, int depth){
    this->nodeChar = nodeChar;
    this->isEnglishWord = isEnglishWord;
    this->depth = depth;
}

TrieNode::~TrieNode()
{
}

TrieNode *TrieTree::insertPrivate(TrieNode* node, std::string nodeString, bool isEnglishWord)
{
    //If nodeChar == nodeString[node->depth], return node
    //else, If node->branches contains substring of nodeString(0,node.nodeString.size()+1), call insert at that node, with nodeString and isEnglishWord
            //Else, make a new node in node-branches(nodeString(0,nodeString.size()+1),false), then call inser at that node with nodeString and isEnglishWord
    if(node->depth == nodeString.size()){
        node->isEnglishWord = isEnglishWord;
        if(isEnglishWord){
            this->words++;
        }
        return node;
    } else if(node->branches[nodeString[node->depth]-97] != nullptr) {
        if(node->branches[nodeString[node->depth]-97]->isEnglishWord && isEnglishWord){
            node->branches[nodeString[node->depth]-97]->repeats++;
        }
        return insertPrivate(node->branches[nodeString[node->depth]-97],nodeString,isEnglishWord);
    } else {
        node->branches[nodeString[node->depth]-97] = new TrieNode(nodeString[node->depth],false,node->depth+1);
        this->nodes++;
        return insertPrivate(node->branches[nodeString[node->depth]-97],nodeString,isEnglishWord);
    }
}

TrieNode *TrieTree::search(std::string nodeString, TrieNode* node)
{
   //if node branch array contains the current char
        //If node depth == nodeString.size, node is found and exists, return it and print count
        //else, search at the node for nodeString
    if(node->depth == nodeString.size()){
        //std::cout << "Count found at node \"" << nodeString << "\" is " << node->branches[nodeString[node->depth]-97]->repeats << std::endl;
        return node;
    } else if (node->branches[nodeString[node->depth]-97] != nullptr){
        return search(nodeString,node->branches[nodeString[node->depth]-97]);
    }
    return nullptr;
}

std::string TrieTree::outputDOTfile(TrieNode *node, int distance, std::ofstream *outfile, std::string prefixFromLastNode)
{
    std::string outputString;
    if(node->depth == 0){
        *outfile << "ROOTNODE_ [label=\"" << "\0" << "," << node->repeats <<"\"]\n";
    } else {
        *outfile << prefixFromLastNode + node->nodeChar << "_ [label=\"" << prefixFromLastNode + node->nodeChar << "," << node->repeats <<"\"]\n";
    }
    if(node->isEnglishWord){
        *outfile << prefixFromLastNode + node->nodeChar << "_ [style=\"filled,dashed\",shape=box,fontsize=20.0,fillcolor=lightblue];\n";
    }
    if(distance != 0){
        //Add current node's branches to output
        for (TrieNode *branchNode : node->branches) {
            if(branchNode != nullptr){
                if (node->depth == 0){
                    *outfile << "ROOTNODE_ -- " << prefixFromLastNode + branchNode->nodeChar << "_\n";
                } else {
                    *outfile << prefixFromLastNode + node->nodeChar << "_ -- " << prefixFromLastNode + node->nodeChar + branchNode->nodeChar << "_\n";
                }
            }
        }
        // call for each branch
        for (TrieNode *branchNode : node->branches) {
            if(branchNode != nullptr){
                if(node->depth == 0){
                    *outfile << outputDOTfile(branchNode, distance-1,outfile,prefixFromLastNode);
                } else {
                    *outfile << outputDOTfile(branchNode, distance-1,outfile,prefixFromLastNode + node->nodeChar);
                }
            }
        }
    }
    return outputString;
}

TrieTree::TrieTree()
{
    this->root = new TrieNode('\0',false,0);
}

TrieTree::~TrieTree()
{
}

void TrieTree::insert(std::string nodeString, bool isEnglishWord)
{
    if(!search(nodeString)){
        insertPrivate(root,nodeString,isEnglishWord);
    }
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
    TrieNode *searchResult = search(prefix);
    std::string prefixFromLastNode = prefix; 
    if(prefix.length() != 0){
        prefixFromLastNode.pop_back();
    }
    this->outputDOTfile(searchResult,distance,&outfile,prefixFromLastNode);
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
void TrieTree::findLargest(std::string node){
    findLargestWord(node);
}

void TrieTree::findLargestWord(std::string nodeString){
    TrieNode* node = search(nodeString);

    if (node == nullptr) {
        return;
    }
    while (!node->branches.empty()) {
        //Set largest branch to first
        TrieNode* maxBranch = node->branches[0];
        //Iterates through each branch in the tree and compares each branch to the next
        for (TrieNode* branch : node->branches) {
            if(branch->nodeString.size() > maxBranch->nodeString.size()) {
                maxBranch = branch;
            }
        }
        //Set node to the largest branch
        node = maxBranch;
    }

    std::cout << node->nodeString << std::endl;
}