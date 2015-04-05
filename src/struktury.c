/*
 * struktury.c
 *	@brief Plik zawierający implementacje funkcji operujących na strukturach.
 *  Created on: 04-04-2015
 *      Author: zakp2
 */


#include "struktury.h"

key_vector *new_key_vector(){
	key_vector *new;
	new=(key_vector*)malloc(sizeof(key_vector));
	new->cap=2;
	new->oc=0;
	new->var=(int*)malloc(new->cap*sizeof(int));
	return new;
}

void del_key_vector(key_vector*key_p){
	free(key_p->var);
	free(key_p);
}

void add_to_key_vector(key_vector*key_p,int key){
	if(key_p->cap==key_p->oc){
		key_p->var=(int*)realloc(key_p->var,2*key_p->cap*sizeof(int));
		key_p->cap*=2;
	}
	key_p->var[++key_p->oc]=key;
}

in_vector *new_in_vector(){
	in_vector *new;
	new=(in_vector*)malloc(sizeof(in_vector));
	new->cap=2;
	new->oc=0;
	new->var=(char**)malloc(new->cap*sizeof(char*));
	return new;
}

/**
 * @brief Funkcja usuwająca @ref in_vector .
 * @param *in_p Wskaźnik na wektor do usunięcia.
 */
void del_in_vector(in_vector*in_p){
	int i;
	for(i=0;i<in_p->oc;i++){
		free(in_p->var[i]);
	}
	free(in_p->var);
	free(in_p);
}

/**
 * @brief Funkcja dodająca wystąpienie do @ref in_vector .
 * @param *in_p Wskaźnik na wektor do którego ma być dodana wartość.
 * @param dn (destination) Wystąpienie.
 */
void add_to_in_vector(in_vector*in_p,char *dn){
	if(in_p->cap==in_p->oc){
		in_p->var=(char**)realloc(in_p->var,2*in_p->cap*sizeof(char*));
		in_p->cap*=2;
	}

	in_p->var[++in_p->oc]=(char*)malloc(sizeof(int[MAX_DN]));
	strcpy(in_p->var[in_p->oc],dn);
}



node* new_node(int key,char var[MAX_WRD]){
	node*tmp;
	tmp=(node*)malloc(sizeof(node));
	tmp->bf=0;
	tmp->left=(node*)NULL;
	tmp->right=(node*)NULL;
	tmp->parent=(node*)NULL;
	strcpy(tmp->var,var);
	tmp->keys=new_key_vector();
	add_to_key_vector(tmp->keys,key);
	return tmp;
}

void del_node(node*no_p){
	del_key_vector(no_p->keys);
	free(no_p);
}

node * AVLrotationRR(node * root, node * A)
{
  node * B = A->right, * parent = A->parent;

  A->right = B->left;
  if(A->right) A->right->parent = A;
  B->left = A;
  B->parent = parent;
  A->parent = B;
  if(parent)
  {
    if(parent->left == A) parent->left = B; else parent->right = B;
  }
  else root = B;

  if(B->bf == -1)
  {
    A->bf = B->bf = 0;
  }
  else
  {
    A->bf = -1; B->bf = 1;
  }
  return B;
}

node * AVLrotationLL(node * root, node * A)
{
  node * B = A->left, * parent = A->parent;

  A->left = B->right;
  if(A->left) A->left->parent = A;
  B->right = A;
  B->parent = parent;
  A->parent = B;
  if(parent)
  {
    if(parent->left == A) parent->left = B; else parent->right = B;
  }
  else root = B;

  if(B->bf == 1)
  {
    A->bf = B->bf = 0;
  }
  else
  {
    A->bf = 1; B->bf = -1;
  }

  return B;
}

node * AVLrotationRL(node * root, node * A)
{
  node * B = A->right, * C = B->left, * parent = A->parent;

  B->left = C->right;
  if(B->left) B->left->parent = B;
  A->right = C->left;
  if(A->right) A->right->parent = A;
  C->left = A;
  C->right = B;
  A->parent = B->parent = C;
  C->parent = parent;
  if(parent)
  {
    if(parent->left == A) parent->left = C; else parent->right = C;
  }
  else root = C;

  A->bf = (C->bf == -1) ?  1 : 0;
  B->bf = (C->bf ==  1) ? -1 : 0;
  C->bf = 0;

  return C;
}


node * AVLrotationLR(node * root, node * A)
{
  node * B = A->left, * C = B->right, * parent = A->parent;

  B->right = C->left;
  if(B->right) B->right->parent = B;
  A->left = C->right;
  if(A->left) A->left->parent = A;
  C->right = A;
  C->left = B;
  A->parent = B->parent = C;
  C->parent = parent;
  if(parent)
  {
    if(parent->left == A) parent->left = C; else parent->right = C;
  }
  else root = C;

  A->bf = (C->bf ==  1) ? -1 : 0;
  B->bf = (C->bf == -1) ?  1 : 0;
  C->bf = 0;

  return C;
}

void AVLinsert(node * root, int key,char var[MAX_WRD])
{
	{
	  node * x = root, * y, * z;
	  node*n;
	  n=new_node(key,var);

	  y = n->left = n->right = (node*)NULL;
	  n->bf = 0;

	  while(x!=(node*)NULL)
	  {
	    if(strcmp(x->var,n->var)==0)
	    {
	      del_node(n);
	      add_to_key_vector(x->keys,key);
	      return ;
	    }
	    y = x;
	    x = strcmp(x->var,n->var) ? x->left : x->right;
	  }

	  if(!(n->parent = y))
	  {
	    root = n;
	    return ;
	  }

	  if(strcmp(y->var,n->var)) y->left = n; else y->right = n;
	  if(y->bf)
	  {
	    y->bf = 0;
	    return ;
	  }
	  y->bf = (y->left == n) ? 1 : -1;
	  z = y->parent;
	  while(z)
	  {
	    if(z->bf) break;
	    z->bf = (z->left == y) ? 1 : -1;
	    y = z; z = z->parent;
	  }

	  if(!z) return ;

	  if(z->bf == 1)
	  {
	    if(z->right == y)
	    {
	      z->bf = 0;
	      return ;
	    }
	    if(y->bf == -1) AVLrotationLR(root,z); else AVLrotationLL(root,z);
	    return ;
	  }
	  else
	  {
	    if(z->left == y)
	    {
	      z->bf = 0;
	      return ;
	    }
	    if(y->bf == 1) AVLrotationRL(root,z); else AVLrotationRR(root,z);
	    return ;
	  }
	}
}
