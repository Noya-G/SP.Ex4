#include <string.h>

#ifndef ASSIGNMENT

#define NUM_LETTERS ((int)26)
#define END_OF_STRING '\0'

typedef struct node {
    char letter;
    struct node* children[NUM_LETTERS];
    struct node* parent;
    int counter;
    int is_end_of_world;
    int leaf;
} node;

typedef struct Trie{
    node* node_pointer;
    int num_world;
    int depth;
    node* children[NUM_LETTERS];
    int size;
    int longest_word;
    char* word;
    
    
} trie;

#endif

trie* newTrie();
trie* readInput();
int readChar(trie* root, char c,int index,int wordLen);
node* newNode(char ch);
void printTree(trie *root, int flag);
void printTree_R_Aid(trie* root);
void printTree_Aid(trie* root);
void printWord(trie* root);
void freeAllocatedMemmory(trie* root);
void freeAllocatedMemmory_Aid(node* node_pointer);
char* newWord(int size);
void print(char* word,int appearance, int index);
