#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List* lista = (List*) malloc(sizeof(List));
  lista->head = NULL;
  lista->tail = NULL;
  lista->current = NULL;

  return lista;
}

void * firstList(List * list) {
  if (list->current == NULL && list->head == NULL) return NULL;
  list->current = list->head;

  return(list->current->data);
}

void * nextList(List * list) {
  if (list->current == NULL || list->current->next == NULL) return NULL;

  list->current = list->current->next;

  return(list->current->data);
}

void * lastList(List * list) {
  if (list->tail == NULL && list->current == NULL) return NULL;
  list->current = list->tail;

  return(list->current->data);
}

void * prevList(List * list) {
  if (list->current == NULL || list->current->prev == NULL) return NULL;

  list->current = list->current->prev;

  return(list->current->data);
}

void pushFront(List * list, void * data) {
  Node* nuevo = createNode(data);
  
  list->head = list->current;

  if(list->tail==NULL){
    list->tail = nuevo;
    
  } else list->current->next = nuevo;

  list->head = nuevo; 
  nuevo->next = list->current;

}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  Node* nodoN = createNode(data);

  if(list->current->next==NULL){
    list->current->next = nodoN;
    nodoN->prev = list->current;
    list->tail = nodoN;
  } else{
    list->current->next->prev = nodoN;
    list->current->next = nodoN;
    nodoN->next = list->current->next;
    nodoN->prev = list->current;
  }

}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if(list->current == NULL){
      return NULL;
    } else if(list->current->prev == NULL){
      list->head = list->current->next;
      list->head->prev = NULL;
      return (list->current->data);
    } else if(list->current->next == NULL){
      list->tail = list->current->prev;
      return (list->current->data);
    } else{
      list->current->next->prev = list->current->prev;
      list->current->prev->next = list->current->next;
      return(list->current->data);
    }

}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}