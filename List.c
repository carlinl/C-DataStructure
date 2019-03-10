//
//  List.c
//  Assignment2
//
//  Created by JIHUI LIANG on 21/1/19.
//  Copyright © 2019 JIHUI LIANG. All rights reserved.
//

#include "List.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node *Node;

typedef struct node{
    
    int data;          //to store the int type url
    int index;         //the index of the url
    int outdegree;     //the outdegree of an url
    Node next;         //the next node
    
}node;
//create a new node
Node newNode(int url){
    //init a node
    Node newnode = malloc(sizeof(struct node));
    assert(newnode != NULL);
    newnode->data = url;
    newnode->index = 0;
    newnode->outdegree = 0;
    newnode->next = NULL;
    
    return newnode;
}
//List info
typedef struct ListRep{
    
    int count;  //the number of the url in list
    Node head;  //the first in list
    Node tail;  //the last in list
    
}ListRep;

typedef struct ListRep *List;
//init a list
List newList(){

    List L = malloc(sizeof(struct ListRep));
    assert(L != NULL);
    L->count = 0;
    L->head = NULL;
    L->tail = NULL;
    
    return L;
}
//insert node into the list
void insert(List L, int url){
    
    Node new = newNode(url);
    if(!L->head){
        new->index = L->count;
        L->head = L->tail = new;
        L->tail->next = NULL;
    }
    else{
        new->index = L->count;
        L->tail->next = new;
        L->tail = new;
    }
    L->count++;
}
//get the index of node
int getIndex(List L, int url){
    Node cur = L->head;
    while(cur){
        if (cur->data == url){
            return cur->index;
        }
        cur = cur->next;
    }
    return 0;
}
//print list
void printList(List L){
    
    assert(L != NULL);
    Node cur = L->head;
    while(cur){
        printf("%d  ",cur->data);
        cur = cur->next;
    }
    printf("\n");
}
//free the list and the node
void freeList(List L){
    
    assert(L != NULL);
    Node cur, pre;
    cur = L->head;
    while(cur != NULL){
        pre = cur;
        cur = cur->next;
        free(pre);
    }
    free(L);
}

//order the list by descending order
List orderList(List urls,double pr[]){
    List orderlist=newList();
    int i;
    for (i = 0; i <urls->count ; ++i) {
        int maxid = maxID(urls, pr);
        //        printf("%d\n",maxid);
        Node tempnode = head(urls);
        for (; tempnode && id(tempnode) != maxid; tempnode = next(tempnode)) {
        }
        insert(orderlist, data(tempnode));
        Node tempnode1 = head(orderlist);
        for (; tempnode1 && data(tempnode1) != data(tempnode); tempnode1 = next(tempnode1)) {
        }
        tempnode1->outdegree = tempnode->outdegree;
        tempnode1->index=tempnode->index;
    }
    return orderlist;
}

//because of descending order, find the max ID every time
//set the previous max ID=0 in order to find 2th max ID until last one
int maxID(List urls,double pr[]){
    int N=urls->count;
    int ID=0;
    double max=pr[0];
    int i;
    for (i = 1; i <N ; ++i) {
        if (pr[i]>max){
            max=pr[i];
            ID=i;
        }
    }
    pr[ID]=0;
    return ID;
}


//some operation  to find the info of nodes and list
int nElement(List L){
    return L->count;
}
int out(Node n){
    return n->outdegree;
}
int  id(Node n){
    return n->index;
}
int data(Node n){
    return n->data;
}
void setoutd(Node n, int degree){
    n->outdegree = degree;
}
Node head(List L){
    return L->head;
}
Node tail(List L){
    return L->tail;
}
Node next(Node n){
    return n->next;
}

/**
int main(){
    
    int a[] = {1,2,3,4,5};
    List L = newList();
    int i;
    for(i = 0; i < 5; i++){
        insert(L, a[4]);
    }
    printList(L);
    printf("%d",nElement(L));
    return  0;
}
**/
