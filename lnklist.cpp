#include <iostream>
using namespace std;
struct node{
  int data;
  struct node* next;
};
struct head{
  struct node* head;
};
using node = struct node;
using head = struct head;
void traversal(head *h){
  node* i = h->head;
  while(i->next != NULL){
    cout << i->data << " -> ";
    i = i->next;
  }
  cout << i->data << endl;
  node* j = h->head;
  while(j->next != NULL){
    cout << j << " -> ";
    j = j->next;
  }
  cout << j << endl;
}
void garbage(head *h){
  while(h->head != NULL){
    node *tmp = h->head;
    h->head = tmp->next;
    delete tmp;
  }
}
void rm_lnk_list(head *h, node *entry){
  node** i = &h->head;
  //cout << h << " " << &h << " " << &h->head << endl;
  while((*i) != entry){ 
    //cout << (*i) << " " << i << endl;
    i = &(*i)->next;
  }
  *i = entry->next;
  delete entry;
  traversal(h);
}
void mk_lnk_list(head *h, int data){
  node *n = new node;
  n->data = data;
  n->next = NULL;
  node **i = &h->head;
  while(*i != NULL) i = &(*i)->next;
  *i = n;
}
void mk_lnk_list(head *h, int data, int pos){
  node *n = new node;
  n->data = data;
  n->next = NULL;
  node **i = &h->head;
  while(pos-- && *i != NULL) i = &(*i)->next;
  n->next = (*i)->next;
  (*i)->next = n;
}
node* ret_entry(head *h, int pos){
  node **i = &h->head;
  while(pos-- && *i != NULL) i = &(*i)->next;
  return (*i);
}
void push_front(head *h, int data){
  node *n = new node;
  n->data = data;
  n->next =  h->head;
  h->head = n;
}
void rev_list(head *h){
  node *prev = NULL, *next = NULL;
  node *curr = h->head;
  while(curr != NULL){
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }
  h->head = prev;
  delete next;
  delete curr;
}

int main(){
  head h;
  h.head = NULL;
  for(int i=0; i<10; i++)
    mk_lnk_list(&h, i);
  traversal(&h); 
  mk_lnk_list(&h, 10, 3);
  traversal(&h);
  rm_lnk_list(&h, ret_entry(&h,1));
  push_front(&h, -1);
  traversal(&h);
  cout<< "Warning!!: Reversing the list" << endl;
  rev_list(&h);
  traversal(&h);
  garbage(&h);
  return 0;
}
