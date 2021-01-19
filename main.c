#include <stdio.h>
#include "frequency.h"

int main(int argc, char* argv[]){
    trie* root;
    root=readInput();

    if(argc > 1 && *(argv[1])=='r')
    {
        printTree(root,1);
        return(0);
    }
    else if(argc == 1)
    {
        printTree(root,0);
        return(0);
    }
    printf("[-] invalid input\n");
    return(0);
}
