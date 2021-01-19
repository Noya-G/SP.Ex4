#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "frequency.h"

///////////////////////////////////////////////////////////////////
///////////////////////////Create Trie/////////////////////////////
///////////////////////////////////////////////////////////////////

trie* newTrie(){
    trie* tree;
    tree = (trie*)malloc(sizeof(trie));
    if(tree == NULL){
        printf("[-] memory allocation error!\n");
        exit(1);
    }
    node* root;
    root = (node*)malloc(sizeof(node));
    if(root == NULL){
        printf("[-] memory allocation error!\n");
        exit(1);
    }
    tree->num_world=0;
    tree->depth=0;
    tree->size=0;
    tree->longest_word=0;
    return tree;
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////Read Input//////////////////////////////
/////////////////////////////////////////////////////////////////////

trie* readInput(){
   char c;
   int len;
   trie* root;
   root = newTrie();
   while((c=getchar()) != EOF)
   {
       c = tolower(c);
       len = readChar(root,c,c-'a',0);
   }
    root->word=newWord(1+sizeof(char)*(root->longest_word));
   return root;
}


char* newWord(int size){
    char* word;
    word = (char*)malloc(size);
    if(word == NULL)
      {
          printf("[-] memory allocation error!\n");
          exit(1);
      }
    return word;
}


int readChar(trie* root, char c,int i,int len){
   int biggestWord = root->longest_word;
   if(!(isalpha(c))){
       if(root->node_pointer == NULL)
       {
           return len;
       }
       root->node_pointer->is_end_of_world = 1;
       root->node_pointer->counter++;
       root->node_pointer = NULL;
       return len;
   }
   if(root->node_pointer != NULL)
   {
       len++;
        if(len > biggestWord)
        {
            root->longest_word = len;
        }
       root->node_pointer->leaf = 1;
         if(root->node_pointer->children[i] == NULL)
         {
             root->node_pointer->children[i] = newNode(c);
         }
       root->node_pointer = root->node_pointer->children[i];
   }
   else
   {
       len++;
       if(len > biggestWord)
       {
           root->longest_word = len;
       }
       if(root->children[i] == NULL)
        {
            root->children[i] = newNode(c);
        }
        root->node_pointer = root->children[i];
        root->size = 0;
   }
   return len;
}




///////////////////////////////////////////////////////////////////
///////////////////////////create node/////////////////////////////
///////////////////////////////////////////////////////////////////

node* newNode(char ch){
    node* n;
    n=(node*)malloc(sizeof(node));
    if (n == NULL) {
        printf("[-] memory allocation error!\n");
        exit(1);
    }
    n->letter = ch;
    n->counter = 0;
    n->leaf = 0;
    n->is_end_of_world = 0;

    for(int i=0 ; i<NUM_LETTERS ; i++){
       (n->children)[i] = NULL;
   }
   return  n;
}

///////////////////////////////////////////////////////////////////
///////////////////////////print tree//////////////////////////////
///////////////////////////////////////////////////////////////////

void printTree(trie *root, int flag){
    if (root == NULL)//if the tree is nor exist.
    {
        return;
    }
    int isEmpty=0;
    for (int i = 0; i < 26; i++)
    {
        if(root->children[i] != NULL){
            isEmpty++;
        }
    }
    
    if(isEmpty == 0){//if the tree is empty.
        return;
    }
    if(flag == 0){
        
        for(int i=0 ; i<26 ; i++){
           if(root->children[i] != NULL)
           {
               root->node_pointer = root->children[i];
               printTree_Aid(root);
           }
        }
    }
    else{
        for(int i=25 ; i>=0 ; i--){
           if(root->children[i] != NULL)
           {
            root->node_pointer = root->children[i];
             printTree_R_Aid(root);
           }
        }
    }
    freeAllocatedMemmory(root);
}

void printTree_R_Aid(trie* root){
    
    static int index = 0;
    node* pointer;
    root->word[index++] = root->node_pointer->letter;
    if (root->node_pointer->leaf != 1)
    {
        if(root->node_pointer->is_end_of_world)
        {
                print(root->word, root->node_pointer->counter,index);
            }
        index--;
        return;
    }

    for(int i=25 ; i>=0 ; i--){
        pointer = root->node_pointer;
        if(pointer->children[i] != NULL)
        {
            root->node_pointer = pointer->children[i];
            printTree_R_Aid(root);
        }
        root->node_pointer = pointer;
    }
    if(root->node_pointer->is_end_of_world)
    {
        print(root->word, root->node_pointer->counter,index);
    }
    index--;
}

void printTree_Aid(trie* root){
    static int index = 0;
    root->word[index++] = root->node_pointer->letter;
    node* pointer;
       if(root->node_pointer->is_end_of_world){
         root->word[index] = '\0';
         print(root->word, root->node_pointer->counter,index);
       }
       if(root->node_pointer->leaf){
         for(int i=0 ; i<NUM_LETTERS ; i++){
            pointer = root->node_pointer;
            if(pointer->children[i] != NULL)
            {
                root->node_pointer = root->node_pointer->children[i];
                printTree_Aid(root);
            }
             root->node_pointer = pointer;
         }
       }
       else{
           index--;
            return;
       }
    
       index--;
}




void printWord(trie* root){
    static int index = 0;
    node* pointer;
    root->word[index++] = root->node_pointer->letter;
    if(root->node_pointer->is_end_of_world)
    {
        print(root->word, root->node_pointer->counter,index);
       }
    if(root->node_pointer->leaf){
        for(int i=0 ; i<NUM_LETTERS ; i++){
            if(root->node_pointer->children[i] != NULL)
            {
                pointer = root->node_pointer;
                root->node_pointer = root->node_pointer->children[i];
                printWord(root);
            }
            root->node_pointer = pointer;
         }
       }
    else{
        index--;
        return;
       }
    index--;
}

void print(char* word,int appearance,int index){
    word[index] = '\0';
    printf("%s %d\n", word, appearance);
}

///////////////////////////////////////////////////////////////////
///////////////////////////free alloccated ma//////////////////////
///////////////////////////////////////////////////////////////////

void freeAllocatedMemmory(trie* root){
    for (int i=0; i<NUM_LETTERS; i++) {
        if (root->children[i] != NULL) {
            freeAllocatedMemmory_Aid(root->children[i]);
        }
    }
    free(root->word);
    free(root);
}

void freeAllocatedMemmory_Aid(node* n){
    if(n!=NULL)
    {
        for(int i=0 ; i<NUM_LETTERS ; i++)
        {
            freeAllocatedMemmory_Aid((n->children)[i]);
        }
        free(n);
        return;
    }
    return;
}
