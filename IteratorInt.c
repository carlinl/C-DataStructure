#include <stdlib.h>

#include <stdio.h>

#include <assert.h>

#include "listIteratorInt.h"

//define a new struct node

typedef struct Node {

    int data;

    struct Node *prev;

       struct Node *next; 


} Node;

//create a new node

static Node *createNew(int v){

    Node *new = malloc(sizeof (struct Node));
 
    new->prev = NULL;

    new->next = NULL;

    new->data = v;
    
    return new;
      
}

//define an  iterator

typedef struct IteratorIntRep {


    Node *current; //the cursor

    Node *head;//point to the first element inthe list

    Node *tail;//point to the last element in the list

    Node *condition; //the cursor's previous position

    int nitems;

} IteratorIntRep;



int flag = 0;


typedef IteratorIntRep *IteratorInt;

IteratorInt IteratorIntNew(){
   
    IteratorInt it;
    
    it = malloc(sizeof (struct IteratorIntRep));
  
    it->head = NULL;
 
    it->tail = NULL;
  
    it->current = NULL;
   
    it->condition = NULL;
  
    it->nitems = 0;
    
    return it;
}


int add(IteratorInt it, int v){

    assert(it != NULL);
    
    Node *new = createNew(v);
    
    assert(new != NULL);
    
    if ( new == NULL){ 

        return 0; 

      }

//add an element to the empty list
    if(it->head == NULL && it->tail == NULL){

              it->head = new;

              it->tail = new; 
   
              new->next = new->prev = NULL; 

              it->current = NULL; 
 

    }
//add to the tail
       else if(it->current == NULL){

              it->tail->next = new;

              new->prev = it->tail;

              it->tail = new;

              new->next = NULL;

    }
//add before the head
       else if(it->current == it->head){

        it->head->prev = new; 

               new->next = it->head;
  
               new->prev = NULL;
 
               it->head = new;

    }
//add before cursor
    else{

              new->next = it->current; 

              new->prev = it->current->prev; 

              new->prev->next = new; 

              new->next->prev = new; 
        

    }

    it->nitems++;

    return 1;

}

int hasPrevious(IteratorInt it){
    
    assert(it != NULL);
 
    flag = 0;
    
    if(it->current != it-> head){

        return 1;

    }

    else{

        return 0;
   
    }
}


int hasNext(IteratorInt it){
   
    assert(it != NULL);
    
    flag = 0;
   
    if(it->current != NULL){
  
        return 1;

    }
 
    else{
      
        return 0;
  
    }
}

int *next(IteratorInt it){
   
    Node *curr = it->current;
 
    assert(it != NULL);
  
    if(hasNext(it) == 1){
//only one node in the list        
        if(it->current == NULL && it-> nitems == 1){
           
           it->current = NULL;
           }
//the cursor point to the tail                          
        else if(it->current == it->tail){
            
            it->current = NULL;
            
        }
        else{
            
            it->current = it->current->next;
            
        }
        
        
        it->condition = curr;
        
        flag = 1;
      
        return &curr->data;
    }
    else{
      
        flag = 0;
      
        return NULL;
    }
}

int *previous(IteratorInt  it){
  
    assert(it != NULL);
    
    Node *curr;
    
    if(hasPrevious(it) == 1){
        
        if(it->current == NULL || it->nitems == 1){
            
            it->current = it->tail;
    
        }
        else{
           
            it->current = it->current->prev;
            
            
        }
        
      curr = it->current;
     
      it->condition = curr;
      
      flag = 1;
      
      return &curr->data;
        
    }
    else{
        
        flag = 0;
       
        return NULL;
        
    }
    
    
}


int *findNext(IteratorInt it, int v){
    
    Node *curr = it->current;
   
    assert(it != NULL);
   
    if(hasNext(it)){
    
        while(it->current != NULL && it->current->data != v){
        
            it->current = it->current->next;
        }
    }
    
    if(hasNext(it)){
       
        curr = it->current;
        
        it->condition = curr;
       
        it->current = it->current->next;
        
        flag = 1;
      
        return &curr->data;
        
    }
    else{
            
        flag = 0;
        
        return NULL;
       
        
    }
    
    
}



int *findPrevious(IteratorInt it, int v){
    
    assert(it != NULL);
    
    Node *curr;
    
    if(hasPrevious(it)){
//move the cursor first        
        if(it->current == NULL){
            
            it->current = it->tail;
            
            curr = it->tail;
                
        }
       
        else{
            
                it->current = it->current->prev;
          
            } 
//search the value            
        while(it->current->prev != NULL && it->current->data != v ){
           
            it->current = it->current->prev;
    
            }
        if(it->current->data == v){ 
        
            flag = 1;
           
            curr = it->current;
              
            it->condition = it->current;
            
            return &curr->data;
                 
        }
        
        else{
            
            flag = 0;
            
            return NULL;
        }
   }
    else{
       
        flag = 0;
        
        return NULL;
    }
    
}

int delete(IteratorInt it){
    
    assert(it != NULL);
    
    Node *temp = it->condition;
    
    
    if(flag == 1){
        
        if(it->nitems == 1){
            
            it->head = NULL;
            
            it->tail = NULL;
            
            it->current = NULL;
            
            it->condition = NULL;
            
            free(temp);
        }
        
        else if(it->condition  == it->tail){
            
            it->current = NULL;
            
            temp->prev->next = NULL;
            
            it->tail = temp->prev;
            
            free(temp);
        
        }
        
        else if(it->condition == it->head){
            
            temp->next->prev = NULL;
            
            it->head = temp->next;
            
            it->current = it->head;
            
            free(temp);
            
        }
    
        else{
            
            temp->next->prev = temp->prev;
            
            temp->prev->next = temp->next;
            
            it->current = temp->next;
            
            free(temp);
            
            
        }
        
        flag = 0;
        
        it->nitems--;
        
        return 1;
        
    }
    else{
        
        return 0;
    
    }
}

int set(IteratorInt it, int v){
    
    assert(it != NULL);
    
    if(flag == 1){
        
        it->condition->data = v;
        
        flag = 0;
        
        return 1;
    }
    
    else{
        
        return 0;
    }
    
    
}

void reset(IteratorInt it){
    
    assert(it != NULL);
    
    it->current = it-> head;
    
}

void freeIt(IteratorInt it){
    
    assert(it != NULL);
    
    Node *curr,*temp;
   
    curr = it->head;
    
    while(curr != NULL){
        
        temp = curr;
        
        curr = curr->next;
        
        free(temp);
        
    }
    free(curr);
    
    free(it);
    
    }


int main(){

    printf("hello cat.\n");
    
    int a[5] = {1,2,3,4,5};
  
    IteratorInt it = IteratorNew();
  
    for(int i=0;i<5;i++){

        add(it,a[i]);
   
        printf("add %d return %d\n",a[i],add(it,a[i]));
 
    }
   
    previous(it);
    
    printf("1 %d\n",*previous(it));
    
    previous(it);
    
    printf("2 %d\n",*previous(it));
    
    next(it);
    
    printf("3 %d\n",*next(it));
    
    findNext(it,5);
    
    printf("4 %d\n",*findNext(it,5));
        
        
    findPrevious(it,5);
    
    printf("5 %d\n",*findPrevious(it,5));
    
    findPrevious(it,1);
    
    printf("6 %d\n",*findPrevious(it,1));
    
    next(it);
    
    printf("7 %d\n",*next(it));
    
    delete(it);
    
    reset(it);
    
    next(it);
    
    printf("8 %d\n",*next(it));
    
    
}
