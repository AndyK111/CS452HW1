#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "deq.h"
#include "error.h"

// indices and size of array of node pointers
typedef enum {Head,Tail,Ends} End;

typedef struct Node {
  struct Node *np[Ends];        // next/prev neighbors
  Data data;
} *Node;

typedef struct {
  Node ht[Ends];                // head/tail nodes
  int len;
} *Rep;

static Rep rep(Deq q) {
  if (!q) ERROR("zero pointer");
  return (Rep)q;
}

static void put(Rep r, End e, Data d) 
{
  //Extraction & allocate nodes
  Node n_old = r->ht[e]; //Grab old node
  Node n_new = calloc(1, sizeof(*n_new)); //Allocate new node & populate fields with 0's
  if (!n_new) ERROR("calloc failure while allocating new node in put()!"); //calloc NULL check

  //Populate new node
  n_new->data = d; //Attach new data to new node
  n_new->np[1-e] = n_old; //new node tail/head -> old node

  //First insertion check
  if (!n_old) r->ht[1-e] = n_new; //Deque tail/head -> new node (on empty deque)
  else n_old->np[e] = n_new; //old node head/tail -> new node

  //Update deque struct
  r->ht[e] = n_new; //Deque head/tail -> new node
  r->len++; //Increment length
}

static Data ith(Rep r, End e, int i)  
{
  if (i < 0 || i >= r->len) ERROR("Index out of bounds!"); //Throw on empty deque, negative index, and index out of bounds

  Node curr_node = r->ht[e]; //Grab starting node (head/tail)

  for (; i>0; i--) //Decrement towards tail/head by decrementing i as a counter
  {
    curr_node = curr_node->np[1-e]; //Swap curr node with tail/head
  }

  return curr_node->data;
}

static Data get(Rep r, End e)
{
  Node gotten = r->ht[e]; //The head/tail of the deque, we got it

  if (!gotten) ERROR("Cannot get from empty deque!"); //Error on empty deque

  Node new_ht = gotten->np[1-e]; //The new head/tail of the deque, it is the tail/head of the gotten node
  if (r->ht[1-e] == gotten) r->ht[e] = r->ht[1-e] = new_ht; //If gotten from 1 element deque, set both head & tail to null
  else 
  {
    r->ht[e] = new_ht; //Set the head/tail of deque to the tail/head of the gotten node
    new_ht->np[e] = NULL; //Set the head/tail of the gotten node to NULL
  }
  Data to_return = gotten->data; //Extract data from the gotten node

  free(gotten);

  r->len--;
  return to_return;
}

static Data rem(Rep r, End e, Data d) 
{
  Node curr_node = r->ht[e]; //head/tail node to which we start searching from

  while (curr_node && curr_node->data != d) //Loop until a matching data pointer is found or all nodes are exhausted
  {
    curr_node = curr_node->np[1-e]; //Set curr node to the tail/head of itself (walk backwards)
  }

  if (curr_node) //If node with matching data exists
  {
    Node curr_node_e = curr_node->np[e]; //Extract node head/tail
    Node curr_node_ne = curr_node->np[1-e]; //Extract node tail/head

    if (curr_node_e) curr_node_e->np[1-e] = curr_node_ne; //If the head/tail exists, stitch the tail/head across the curr node
    else r->ht[e] = curr_node_ne; //If the curr node has no head/tail, it is the head/tail, thus stitch across the deque head/tail

    //Same as above, but for the tail/head
    if (curr_node_ne) curr_node_ne->np[e] = curr_node_e; 
    else r->ht[1-e] = curr_node_e;

    free(curr_node);
    r->len--;
    return d;
  }

  return curr_node; //Type mismatch but curr_node pointer is null under the same conditions we return null.
}

extern Deq deq_new() {
  Rep r=(Rep)malloc(sizeof(*r));
  if (!r) ERROR("malloc() failed");
  r->ht[Head]=0;
  r->ht[Tail]=0;
  r->len=0;
  return r;
}

extern int deq_len(Deq q) { return rep(q)->len; }

extern void deq_head_put(Deq q, Data d) {        put(rep(q),Head,d); }
extern Data deq_head_get(Deq q)         { return get(rep(q),Head);   }
extern Data deq_head_ith(Deq q, int i)  { return ith(rep(q),Head,i); }
extern Data deq_head_rem(Deq q, Data d) { return rem(rep(q),Head,d); }

extern void deq_tail_put(Deq q, Data d) {        put(rep(q),Tail,d); }
extern Data deq_tail_get(Deq q)         { return get(rep(q),Tail);   }
extern Data deq_tail_ith(Deq q, int i)  { return ith(rep(q),Tail,i); }
extern Data deq_tail_rem(Deq q, Data d) { return rem(rep(q),Tail,d); }

extern void deq_map(Deq q, DeqMapF f) {
  for (Node n=rep(q)->ht[Head]; n; n=n->np[Tail])
    f(n->data);
}

extern void deq_del(Deq q, DeqMapF f) {
  if (f) deq_map(q,f);
  Node curr=rep(q)->ht[Head];
  while (curr) {
    Node next=curr->np[Tail];
    free(curr);
    curr=next;
  }
  free(q);
}

extern Str deq_str(Deq q, DeqStrF f) {
  char *s=strdup("");
  for (Node n=rep(q)->ht[Head]; n; n=n->np[Tail]) {
    char *d=f ? f(n->data) : n->data;
    char *t; asprintf(&t,"%s%s%s",s,(*s ? " " : ""),d);
    free(s); s=t;
    if (f) free(d);
  }
  return s;
}
