#pragma once

//defining a double linked list node.
typedef struct node
{
	int data;
	node* next;
	node* prev;
	node(int);
};

 //To initialize the structure with a single digit 
node::node(int val)
{
	data = val;
	next = NULL;
	prev = NULL;
}

void print(node* result);

int countthenumberofnodes(node* input);

void insertatrear(int data, node* db);

void insertatrear(int data, node* db);

void insertatfront(int data, node* db);

void insertatfrontwithhead(int data, node* additive, node* head);

void deleteatrear(node* db);

void deleteatfront(node* db);

node*  addsinglezeroatfront(node* db);

node* copy(node* first);

int numberofnodeswithoutfrontzeroes(node* input);

int compare(node* first, node* second);

node* makesmallernumber(node* first, int digitsindividend);

node* addition(node* first, node* second);

node* subtract(node* first, node* second);

node* mul(node* first, node* second);

node* division(node* first, node* second);

node* modulo(node* first, node* second);

node* gcd(node* first, node* second);

node* findinverese(node* inversetobefound, node* modn);

node* moduloinverse(node* modn, node* inversetobefound);

int trial();


