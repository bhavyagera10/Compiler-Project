#include "hash.h"

int hashcode(char* string){
	int hash = 3;
	for(int i = 0; i < strlen(string); i++){
		hash = (hash*29 + string[i])%500;
	}
	return hash;
}

hashtable* createHashTable(){
	hashtable* ht = (hashtable*)malloc(sizeof(hashtable)*501);
	//printf("Here6");
	int i;
	for(i = 0; i < 501; i++){
		ht[i]=(hashtable)malloc(sizeof(struct listForHash));
		ht[i]->head=NULL;
	}
	if(ht==NULL) printf("LOL Sahil!!");
	//	printf("Here5");
	return ht;
}

element createElement(char*string){
	element e = (element)malloc(sizeof(struct elementOfHash));
	e->grammar = createListofList();
	e->first = createLinkedList();
	e->follow = createLinkedList();
	char* str = (char*) malloc(sizeof(char)*20);
	strcpy(str,string);
	e->value = str;
	if(strcmp("eps", string)==0){
		e->flag = 0;
	}else{
		e->flag = 1;   //-1 : Non Terminal, 0: eps, 1: Terminal
	}
	return e;
}

hashtable* insertToHash(element e,hashtable* ht){
	int hash = hashcode(e->value);
	element temp = ht[hash]->head;
	ht[hash]->head = e;
	e->next = temp;
	return ht;
}

element searchInTable(hashtable* ht,char* string){
	int hash = hashcode(string);
	element temp = createElement("");
	temp = ht[hash]->head;
	while(temp!=NULL){
		if(strcmp(temp->value, string)==0)
			return temp;
		temp = temp->next;
	}
	printf("element not found, inserting... %s\n", string);
	return NULL;
}

dl createListofList(){
	dl list = (dl)malloc(sizeof(struct listOfList));
	list->head = NULL;
	return list;
}

ll createLinkedList(){
	ll ls = (ll)malloc(sizeof(struct LinkedList));
	ls->head = NULL;
	return ls;
}

node createNode(element e){
	node n = (node)malloc(sizeof(struct Node));
	//char* str = (char*) malloc(sizeof(char)*20);
	//strcpy(str,a);
	n->ele = e;
	//printf("%s\n",n->data);
	return n;
}
ll insertInOrder(ll ls ,node n){
	node temp = ls->head;
	if(temp==NULL){
		ls->head = n;
		return ls;
	}
	while(temp->next!=NULL)
		temp = temp->next;
	temp->next = n;
	return ls;
}
ll insertInList(ll ls,node n){
	node temp = ls->head;
	ls->head = n;
	n->next = temp;
	return ls; 
}
void print2(dl d){
	ll temp = createLinkedList();
	temp = d->head;
	while(temp!=NULL){
		print(temp);
		temp = temp->next1;
		printf("\n");
	}
}
dl insertInOrderList(dl d,ll ls){
	ll temp = d->head;
	if(temp==NULL){
		d->head = ls;
		return d;
	}
	while(temp->next1!=NULL)
		temp = temp->next1;
	temp->next1 = ls;
	return d;
}
dl insertInListOfList(dl d,ll ls){
	ll temp = createLinkedList();
	temp = d->head;
	d->head = ls;
	ls->next1 = temp;
	//print2(d);
	return d;
}

void print(ll ls){
	node temp = ls->head;
	while(temp!=NULL){
		printf("%s(%d)\t",temp->ele->value, temp->ele->flag);
		temp = temp->next;
	}
}

/*void print2(dl d){
	ll temp = d->head;
	while(temp!=NULL){
		print(temp);
		printf("\n");
		temp = temp->next1;
	}
}
*/


void printNtList(ll ls){
	node temp = ls->head;
	while(temp!=NULL){
		//if(temp->flag == -1) printf("%s\n",temp->data);
		//temp = temp->next;
	}
}

void printTList(ll ls){
	node temp = ls->head;
	while(temp!=NULL){
		//if(temp->flag == 1) printf("%s\n",temp->data);
		//temp = temp->next;
	}
}


void printFollowSet(dl d){
	ll temp = createLinkedList();
	temp = d->head;
	while(temp!=NULL){
		printf("Follow [ %s ] = ",temp->head->ele->value);
		print(temp->head->ele->first);
		printf("\n");
		temp = temp->next1;
	}
}

void printT(dl d){
	ll temp = createLinkedList();
	temp = d->head;
	while(temp!=NULL){
		printTList(temp);
		temp = temp->next1;
	}
}

ll copyList(node n){
	ll l = createLinkedList();
	while(n!=NULL){
		node t = createNode(n->ele);
		l = insertInOrder(l, t);
		n = n->next;
	}
	return l;
}

int find(node n, ll l){
	node temp = l->head;
	while(temp!=NULL){
		if(strcmp(temp->ele->value, n->ele->value)==0) return 1;
		temp = temp->next;
	}
	return 0;
} 

ll concatList(ll l1, ll l2){
	node templ1 = l1->head;
	node templ2 = l2->head;
	if(templ1==NULL) return l2;
	if(templ2 == NULL) return l1;

	while(templ2!=NULL){
		if(find(templ2, l1)==0){
			l1 = insertInList(l1, createNode(templ2->ele));
		}
		templ2 = templ2->next;
	}	
	return l1;
}