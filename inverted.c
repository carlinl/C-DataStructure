#include <stdio.h>
#include <string.h>
#include "InvertedIdx.h"
#include "readData.h"

Tree wordfillTree(Tree tree, List urls);

int main(){
    List urls=get2Collection();
    Tree tree=newTree();
    tree=wordfillTree(tree,urls);   //read word from section-2
    //printInorder(tree);
    FILE *out=fopen("invertedIndex.txt","w");
    Treetofile(tree,out);   //print the contents of tree to .txt file
    fclose(out);
   // showTree(tree);
    free2LL(urls);  //free the memory associated with List urls
    freeTree(tree); //deallocates the memory associated with Tree tree

    return 0;
}

//read word from section-2 and fill these words to a new tree
//strcmp() compare two strings lexicographically
Tree wordfillTree(Tree tree, List urls){
    LNode tempnode;
    for (tempnode=first_node(urls);tempnode;tempnode=next_node(tempnode)) {
        char filename[100];
        sprintf(filename,"%s.txt",url2(tempnode));
        FILE *web=fopen(filename,"r");
        int reading_flag=0;
        char word[100];
        while (fscanf(web,"%s",word)==1){
            if(strcmp(word,"Section-2")==0 && !reading_flag){   //if word == "Section-2"
                reading_flag=1; //setting reading_flag equals 1
                continue;
            }
            else if (strcmp(word,"Section-2")==0 && reading_flag){  //if word == "Section-2" flag false
                break;
            }
            if (reading_flag && strcmp(word,"#end")!=0){
                adjust(word);   //normalise words
                if (strlen(word)<1)
                    continue;
                tree=TreeInsert(tree,word,url2(tempnode));  //insert word and its url to tree
            }

        }
        fclose(web);
    }
    return tree;
}

