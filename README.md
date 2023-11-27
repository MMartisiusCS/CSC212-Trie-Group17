# CSC212-Trie-Group17

Group 17 Trie Project for URI-CSC212-0001

Google Doc: https://docs.google.com/document/d/1aIXSi-ceuWrmeGQbZBFSY8oBCYyYb8HH1WF6GVgXjlg/edit?usp=sharing

Michael Martisius, Joseph May, Nathan Roy, Nathan Lichtenfels

Generating image file from .gv: To process the .gv file into an image file, run "dot -Tsvg graph_[suffix]\_[distance].gv -o graph_[suffix]_[distance].svg" in the source folder, editing the [suffix] and [distance] blocks with the used suffix and distance. graphviz must be installed and on the windows PATH. SVG files can be opened with chrome or any other web browsing software. Graphs with too many nodes will not process with dot, so only create dot files that have no more than ~250-500 nodes (very rough estimate, experiment with what works on your machine)

To compile, simply run "g++ -g -std=c++11 main.cpp trie.cpp -o prog && ./prog" in the source folder. Make sure that words_alpha.txt is included, as well as any text files you would like to load into the tree after words_alpha is loaded.

VoxedVEVO: Michael M

nroy0703: Nathan R

nlichtenfels: Nathan L

mayjg26: Joesph M
