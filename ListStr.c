//
//  ListStr.c
//  Assignment2
//
//  Created by JIHUI LIANG on 31/1/19.
//  Copyright © 2019 JIHUI LIANG. All rights reserved.
//

#include "ListStr.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

typedef struct ListNode {
    char   value[100];  // value of this list item (string)
    LNode next;
    // pointer to next node in list
}ListNode;

typedef struct ListRep {
    int  nitems;// count of items in list
    LNode first;
    LNode last;
} ListRep;

// create a new DLListNode (private function)
LNode newLNode(char *val)
{
    LNode new= malloc(sizeof(struct ListNode));
    assert(new != NULL);
    strcpy(new->value, val);  // for int, new->value = it;
    new->next = NULL;
    return new;
}

// create a new empty DLListStr
List new2List()
{
    List L = malloc(sizeof (struct ListRep));
    assert (L != NULL);
    L->nitems = 0;
    L->first = NULL;
    L->last = NULL;
    return L;
}


/*
 pre-reqisite: L is ordered (increasing) with no duplicates
 post-condition: val is inserted in L, L is ordered (increasing) with no duplicates
 */
void insertSetOrd(List L, char *val){
    char g[100];
    strcpy(g,val);
    assert(L!=NULL);
    LNode new=newLNode(val);
    assert(new!=NULL);
    if (L->first==NULL){
        L->first=L->last=new;
    }
    else {
        LNode tempnode=L->first;
        for (; tempnode; tempnode=tempnode->next) {
            if (strcmp(tempnode->value,g)==0)
                return;
        }
        L->last->next=new;
        L->last=new;
    }
    L->nitems++;
    
    /*
     implement this function to
     insert val in L  (in order), no duplicates (set)
     
     */
    if (L->nitems>=2) {
        //qsortList(L->first, L->last);
        bubblesort(L->first);
    }
}
void bubblesort(struct ListNode *start){
    int swapped;
    struct ListNode *ptr1 = start;
    struct ListNode *lptr = NULL;
    
    /* Checking for empty list */
    if (ptr1 == NULL)
        return;
    do
    {
        swapped = 0;
        ptr1 = start;
        
        while (ptr1->next != lptr)
        {
            //            if (ptr1->data > ptr1->next->data)
            if (strcmp(ptr1->value,ptr1->next->value)>0)
            {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}
void swap(struct ListNode *a, struct ListNode *b)
{
    char temp[100];
    strcpy(temp,a->value);
    //    int temp = a->data;
    strcpy(a->value,b->value);
    //    a->data = b->data;
    strcpy(b->value,temp);
    //    b->data = temp;
}


void showLL(List L){
    LNode tempnode=L->first;
    while(tempnode){
        printf("%s ",tempnode->value);
        tempnode=tempnode->next;
    }
    printf("\n");
}



// display items from a DLListStr, comma separated
void free2LL(List L) {
    assert(L!=NULL);
    LNode cur,pre;
    cur=L->first;
    if (cur != NULL) {
        pre=cur;
        cur=cur->next;
        free(pre);
    }
    free(L);
}

LNode first_node(List L){
    return L->first;
}
LNode next_node(LNode N){
    return N->next;
}
char *url2(LNode N){
    return N->value;
}

int L_elements(List L){
    return L->nitems;
}
