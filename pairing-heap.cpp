#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
ifstream fin("mergeheap.in");
ofstream fout("mergeheap.out");

class Node {
public:
	int value;
	Node* leftmost_child;
	Node* next_sibling;

	Node();
	Node(int, Node*, Node*);
};

Node::Node() { this->leftmost_child = NULL; this->next_sibling = NULL; this->value = 0; }
Node::Node(int v, Node* l, Node* n)
{
	this->value = v;
	this->leftmost_child = l;
	this->next_sibling = n;
}

class Pairing_Heap {
	Node* root;
public:
	Pairing_Heap();
	Pairing_Heap(int);
	int get_max();
	bool is_Empty();
	Node* merge(Node*, Node*);
	void merge(Pairing_Heap&);
	void insert(int);
	void del();
	Node* merge_del(Node*);
	void increase_key(Node*&, int);
};


int Pairing_Heap::get_max()
{
	return root->value;
}

Pairing_Heap::Pairing_Heap()
{
	this->root = NULL;
}

Pairing_Heap::Pairing_Heap(int v)
{
	this->root = new Node(v, NULL, NULL);
}


bool Pairing_Heap::is_Empty()
{
	return this->root == NULL;
}

void Pairing_Heap::merge(Pairing_Heap &Heap)
{
	this->root = this->merge(this->root, Heap.root);
	Heap.root = NULL;
}

Node* Pairing_Heap::merge(Node* first_node, Node* second_node)
{
	if (first_node == NULL) return second_node;
	else if (second_node == NULL) return first_node;
	else if (first_node->value > second_node->value)
	{
		if (first_node->leftmost_child == NULL)
			first_node->leftmost_child = second_node;
		else
		{
			second_node->next_sibling = first_node->leftmost_child;
			first_node->leftmost_child = second_node;
		}
		return first_node;
	}
	else
	{
		if (second_node->leftmost_child == NULL)
			second_node->leftmost_child = first_node;
		else
		{
			first_node->next_sibling = second_node->leftmost_child;
			second_node->leftmost_child = first_node;
		}
		return second_node;
	}
}

void Pairing_Heap::insert(int v)
{
	Node* nod = new Node(v, NULL, NULL);
	this->root = this->merge(this->root, nod);
}

void Pairing_Heap::del()
{
	//Node* nod = this->root;
	this->root = merge_del(this->root->leftmost_child);
}

Node* Pairing_Heap::merge_del(Node* nod)
{
	if (nod == NULL || nod->next_sibling == NULL)
		return nod;
	Node* a = nod;
	Node* b = nod->next_sibling;
	Node* c = nod->next_sibling->next_sibling;

	a->next_sibling = NULL, b->next_sibling = NULL;
	return merge(merge(a, b), merge_del(c));
}

void Pairing_Heap::increase_key(Node*& nod, int v)
{
	if (nod->value > v) return;
	nod->value = v;
	if (nod != root)
	{
		Node* temp = nod;
		nod = nod->next_sibling;
		temp->next_sibling = NULL;
		this->root = merge(this->root, temp);
	}
}

int main()
{
	vector<Pairing_Heap>Heapuri;
	int N, Q, k, l;
	fin >> N >> Q;
	int op;
	Heapuri.resize(N + 1);
	for (int i = 0; i < Q; ++i)
	{
		fin >> op>>k;
		switch (op)
		{
		case 1: {
			fin >> l;
			Heapuri[k].insert(l);
		}
			  break;
		case 2: {
			fout << Heapuri[k].get_max() << '\n';
			Heapuri[k].del();
		}
			  break;
		case 3: {
			fin >> l;
			Heapuri[k].merge(Heapuri[l]);
		}
			  break;
		}
	}

	return 0;
}