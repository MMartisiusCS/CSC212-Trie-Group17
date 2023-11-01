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

std::string TrieTree::outputDOTfile(TrieNode *node,int depth,std::ofstream *outfile)
{
    std::string outputString;
    //Add current node's branches to output
    for (int i = 0; i < node->branches.size();i++){
        if (node->nodeString.length() == 0){
            *outfile << "ROOTNODE_ -- " << node->branches[i]->nodeString << "_\n";
        } else {
            *outfile << node->nodeString << "_ -- " << node->branches[i]->nodeString << "_\n";
        }
        if(node->branches[i]->isEnglishWord){
            *outfile << node->branches[i]->nodeString << "_ [style=\"filled,dashed\"\nshape=box\nfontsize=20.0\nfillcolor=lightblue];\n";
        }
    }
    // call for each branch
    for (int i = 0; i < node->branches.size();i++){
        *outfile << outputDOTfile(node->branches[i], depth,outfile);
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
    /*
    if(nodeString.size() > 1){
        for(int i = 1; i < nodeString.size();i++){
            std::string strToInsert = nodeString.substr (0,i);
            insertPrivate(root,strToInsert,false);
        }
    }
    insertPrivate(root,nodeString,isEnglishWord);
    */
    insertPrivate(root,nodeString,isEnglishWord);
    return;
}

TrieNode* TrieTree::search(std::string nodeString)
{
    return nullptr;
}

void TrieTree::outputDOTfile(std::string prefix,int depth)
{
    std::ofstream outfile ("graphs/graph_"+prefix+".cv");
    outfile << "graph TrieTreeGraph {\n";
    if(prefix.size() == 0){
         outfile << "ROOTNODE_ [label=\"\"]\n";
    }
    this->outputDOTfile(search(prefix),depth,&outfile);
    outfile << "}"<<std::endl;
    outfile.close();
}
