//
//  List.h
//  Assignment2
//
//  Created by JIHUI LIANG on 21/1/19.
//  Copyright © 2019 JIHUI LIANG. All rights reserved.
//

#ifndef List_h
#define List_h
#include <stdbool.h>

typedef struct node *Node;
typedef struct ListRep *List;

List newList(void);
void insert(List L, int url);
void printList(List L);
void freeList(List L);
void setoutd(Node n, int degree);

int getIndex(List L, int url);
int nElement(List L);
int out(Node n);
int  id(Node n);
int data(Node n);

int maxID(List urls,double pr[]);
List orderList(List urls,double pr[]);

Node head(List L);
Node next(Node n);
Node tail(List L);



#endif /* List_h */
