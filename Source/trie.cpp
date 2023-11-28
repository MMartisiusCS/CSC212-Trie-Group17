#include "trie.h"
#include <iostream>
#include <fstream>  
#include <algorithm>

// Michael M
// Constructor for creating a node, which stores a char, if the node is a word from rootnode, and the depth/length of the node
TrieNode::TrieNode(char nodeChar, bool isEnglishWord, int depth){
    this->nodeChar = nodeChar;
    this->isEnglishWord = isEnglishWord;
    this->depth = depth;
}


TrieNode::~TrieNode()
{
    for(TrieNode* branchNode : this->branches){
        if(branchNode){
            branchNode->~TrieNode();
        }
    }
    delete this;
}

// Michael M
// Recursive function to insert node in tree
// At the give node "node", the function will check if char to be inserted already exists as a branch.
// If it does, it will recurse to that node, otherwise it will make a new node with the char to insert, and then recurse to it
// Once we reach the node that is the depth of the length of nodeString (depth = length of string), we mark it with the given isEnglishWord flag, and return out of recursion
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

// Michael M
// Function that will search for a given string in the tree, checking at the current node
// If the given node has a depth equal to the length of the given string, we have reached the node to search for, return the node
// Else, if the next char exists as a child of the current node, search at that node
// Otherwise, the string does not exist in the tree, return a nullptr
TrieNode *TrieTree::search(std::string nodeString, TrieNode* node)
{
    // if the current node is the length of the string, we have found our string, return the node to mark it found
    // else, if the current char of the string we are searching for exist as a branch from the current node, search from that node
    if(node->depth == nodeString.size()){
        return node;
    } else if (node->branches[nodeString[node->depth]-97] != nullptr){
        return search(nodeString,node->branches[nodeString[node->depth]-97]);
    }
    // If node is not the length of the string we are searching for, and if the next char does not exist as a child of this node, the string will not exist in the tree, return a nullptr marking that it does not exist
    return nullptr;
}

// Michael M
// Recursive Function to write to a given dot file
// The given outfile should already contain header information for the dot file
// This function will recurse though each node of the graph, starting at the first node passed into as node, and limited to a depth of distance
// For each node that exists from and including the given node, and each node that exist within the distance limit, it will be added to the graph file
// The variable name in the file will be the string name plus an underscore to prevent the strings being processed as commands in the dot file
// If the current node is a word, we add formating to signify it in the graph visulization.
// We also check if the length of the node is 0, signifying that this is the rootnode, so we instead use a variable name of ROOTNODE_
void TrieTree::outputDOTfile(TrieNode *node, int distance, std::ofstream *outfile, std::string prefixFromLastNode)
{
    // If we are on the rootnode, use ROOTNODE_ as a variable name, otherwise use the current node's string from the rootnode as the variable name
    // Include the amount of times the current node is used as a prefix for other words
    if(node->depth == 0){
        *outfile << "ROOTNODE_ [label=\"" << "\0" << "," << node->repeats <<"\"]\n";
    } else {
        *outfile << prefixFromLastNode + node->nodeChar << "_ [label=\"" << prefixFromLastNode + node->nodeChar << "," << node->repeats <<"\"]\n";
    }

    // If the current node is an english word, add formating to make it stand out in the graph
    if(node->isEnglishWord){
        *outfile << prefixFromLastNode + node->nodeChar << "_ [style=\"filled,dashed\",shape=box,fontsize=20.0,fillcolor=lightblue];\n";
    }

    // If we have not reached out distance limit, add each branch from this node as a connection in the graph
    if(distance != 0){
        //Add current node's branches to output
        for (TrieNode *branchNode : node->branches) {
            if(branchNode != nullptr){
                // Check if we are on rootnode
                if (node->depth == 0){
                    *outfile << "ROOTNODE_ -- " << prefixFromLastNode + branchNode->nodeChar << "_\n";
                } else {
                    *outfile << prefixFromLastNode + node->nodeChar << "_ -- " << prefixFromLastNode + node->nodeChar + branchNode->nodeChar << "_\n";
                }
            }
        }
        // Call recursive function on each branch of the current node, bringing the distance limit down by one, and adding the current char to the prefix string IF it is not the rootnode
        for (TrieNode *branchNode : node->branches) {
            if(branchNode != nullptr){
                if(node->depth == 0){
                    outputDOTfile(branchNode, distance-1,outfile,prefixFromLastNode);
                } else {
                    outputDOTfile(branchNode, distance-1,outfile,prefixFromLastNode + node->nodeChar);
                }
            }
        }
    }
}

// Michael M
// Simple constructor that creates a tree with the root node being a blank node that is not a word.
TrieTree::TrieTree()
{
    this->root = new TrieNode('\0',false,0);
}

TrieTree::~TrieTree()
{
    root->~TrieNode();
    delete this;
}

// Michael M
// Public non-recursive helper insert function to insert string into the tree
// If the given string does not exist in the tree, we pass it into the recursive insert function to push it into the tree
void TrieTree::insert(std::string nodeString, bool isEnglishWord)
{
    if(!search(nodeString)){
        insertPrivate(root,nodeString,isEnglishWord);
    }
}

// Michael M
// Public non-recursive helper search function to start the search for a given string.
// if the given string is blank, we know it is the rootnode, we we just return the root node
// otherwise, we return the result from the recursive search function
TrieNode* TrieTree::search(std::string nodeString)
{   
    if(nodeString == ""){
        return root;
    }
    return search(nodeString,root);
}

// Michael M
// Public non-recursive helper function to start and finish the dot file
// This will create a new file called after the prefix and distance given and add some header information
// It will then utilize the recursive function to fill in the data for the graph
// Finally, it will cap off the file and close the outfile
void TrieTree::outputDOTfile(std::string prefix,int distance)
{
    // Start of dot file
    std::ofstream outfile ("graph_"+ prefix + "_" + std::to_string(distance) + ".gv");
    outfile << "graph TrieTreeGraph {\n";

    // Store data about given prefix to find node to start at and it's prefix
    TrieNode *searchResult = search(prefix);
    std::string prefixFromLastNode = prefix; 

    // If the node is not the rootnode, remove the last char from the prefix to allow correct printing in the recursive function
    if(prefix.length() != 0){
        prefixFromLastNode.pop_back();
    }

    // Add data to file using recursive function
    this->outputDOTfile(searchResult,distance,&outfile,prefixFromLastNode);

    // End file and close it
    outfile << "}"<<std::endl;
    outfile.close();
}

void TrieTree::autocompleteHelper(TrieNode* node, int length, std::string currentWord) {
    // If the length of word has been reached, print the current word
    if (length == 0) {
        std::cout << currentWord << std::endl;
        return;
    }

    // Traverse all branches of the current node
    for (int i = 0; i < 26; ++i) {
        if (node->branches[i] != nullptr) {
            char nextChar = 'a' + i;
            autocompleteHelper(node->branches[i], length - 1, currentWord + nextChar);
        }
    }
}

void TrieTree::autocomplete(std::string suffix, int length) {
    // Search for suffix in the tree, starting at the end node of the suffix path
    TrieNode* startNode = search(suffix, root);

    // If the suffix is not found, or the length is invalid, return
    if (startNode == nullptr || length < suffix.length()) {
        std::cout << "No words found." << std::endl;
        return;
    }

    // Call the recursive helper function to find words of the specified length
    autocompleteHelper(startNode, length - suffix.length(), suffix);
}

void TrieTree::findWordOfLength(TrieNode* node, int length, std::string str){
    if(node->nodeChar != '\0'){
        str += node->nodeChar;
    }
    if (length == 0 && node->isEnglishWord){
            std::cout << str << std::endl;
        }
    if (length!=0){
        for(int i = 0; i < 26; i++){
            if(node->branches[i] != nullptr){
                findWordOfLength(node->branches[i], length-1, str);
            }
        }
    }
}

void TrieTree::findWordOfLength(int length){
    std::string str = "";
    findWordOfLength(root, length, str);
}

std::string TrieTree::getStringNode(TrieNode* node) {
    //return node->nodeString;
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
std::string TrieTree::findLargest(){
    return findLargestWord(root);
}
//Nathan R
//private method to check every branch in the trie to find the largest formed word
//in each branch and then compare it to every other branch to find the biggest one
std::string TrieTree::findLargestWord(TrieNode* node){
    if (node == nullptr) {
        return "";
    }
    std::string nodeSuffix = "";
    bool hasChildren = false;
    for (TrieNode *branchNode : node->branches) {
        if(branchNode){
            hasChildren = true;
            std::string tmp = findLargestWord(branchNode);
            if (tmp.size() > nodeSuffix.size()){
                nodeSuffix = tmp;
            }
        }
    }
    if(!hasChildren){
        return std::string {node->nodeChar};
    } else {
        return std::string {node->nodeChar} + nodeSuffix;
    }
}
