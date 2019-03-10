//
//  pagerank.c
//  Assignment2
//
//  Created by JIHUI LIANG on 29/1/19.
//  Copyright © 2019 JIHUI LIANG. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "readData.h"

int main(int argc, char *argv[]){
    double d, diffR;
    int maxIteration;
 
    if (argc != 4){
        printf("Wrong Input.");
        exit(1);
    }
    
    d = atof(argv[1]);  //convert string to float
    diffR = atof(argv[2]);
    maxIteration = atoi(argv[3]);

    List urls = getCollection();
    //printList(urls);
    Graph urlG = getGraph(urls);
    int N = nElement(urls);
    //find the node outdegree
    Node init_outdegree;
    for(init_outdegree = head(urls); init_outdegree; init_outdegree = next(init_outdegree)){
        if(out(init_outdegree) == 0){
            for(int i = 0; i < N; ++i){
                if( i != id(init_outdegree)){
                    Edge e;
                    e.v = id(init_outdegree);
                    e.w = i;
                    insertEdge(urlG, e);
                }
            }
            
        }
    }
    
    double pr[N];
    double pv[N];
    double dN = (double)N;
    for(int i = 0; i < N; ++i){
        pr[i] = pv[i] = 1.0/dN;
    }
    int iteration = 0;
    double diff = diffR;
    double dam = (1.0 - d)/dN;
    while(iteration < maxIteration && diff >= diffR){
        iteration++;
        diff = 0.0;
        Node cur;
        for(cur = head(urls); cur; cur = next(cur)){
            double rank = 0.0;
            for(int i = 0; i < N; i++){
                if(adjacent(urlG, i, id(cur))){
                    Node temp;
                    for(temp = head(urls); temp;temp = next(temp)){
                        if(id(temp)==i){
                            double outlength;
                            if(out(temp) != 0){
                                outlength = out(temp);
                            }
                            else{
                                outlength = N-1;
                            }
                            rank += d*pr[i]/outlength;
                        }
                    }
                }
            }
            rank += dam;
            diff += fabs(rank - pr[id(cur)]);
            pv[id(cur)] = rank;
        }
        for(int j = 0; j < N; ++j){
            pr[j] = pv[j];
        }
    }
    double newpr[N];
    for (int i = 0; i < N; ++i) { //copy the whole pagerank value for every url to new array.
        newpr[i]=pr[i];
    }
    List order_list = orderList(urls,pr);
    FILE *outfile = fopen("pagerankList.txt","w");
    for(Node outnode = head(order_list);outnode;outnode = next(outnode)){
        fprintf(outfile, "url%d, %d, %0.7f\n", data(outnode),out(outnode),newpr[id(outnode)]);
    }
    fclose(outfile);
    free(urls);
    freeGraph(urlG);
    return 0;
}


