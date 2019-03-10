//
//  ListStr.h
//  Assignment2
//
//  Created by JIHUI LIANG on 31/1/19.
//  Copyright © 2019 JIHUI LIANG. All rights reserved.
//

#ifndef ListStr_h
#define ListStr_h

#include <stdio.h>

typedef struct ListRep *List;
typedef struct ListNode *LNode;

List new2List(void);
LNode newLNode(char *val);
void insertSetOrd(List L, char *val);

void bubblesort(struct ListNode *start);
/* Function to swap data of two nodes a and b*/
void swap(struct ListNode *a, struct ListNode *b);

void showLL(List L);
void free2LL(List L);

LNode first_node(List);
LNode next_node(LNode);
LNode pre_node(LNode);
char *url2(LNode);
int L_elements(List);


#endif /* ListStr_h */
