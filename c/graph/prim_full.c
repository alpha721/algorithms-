#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

struct list_node{
	int dest;
	int weight;
	struct list_node* next;
};

struct list{
	struct list_node* head;
};

struct graph{
	int v;	
	struct list* array;
};

struct list_node* new_list_node(int dest,int weight)
{
	struct list_node* n = (struct list_node*)malloc(sizeof(struct list_node));	
	n->dest = dest;
	n->weight = weight;
	n->next = NULL;
	return n;
}

struct graph* create_graph(int v)
{
	struct graph* g = (struct graph*)malloc(sizeof(struct graph*));
	g->v = v;	
	g->array = (struct list*)malloc(v * sizeof(list));
	int i;
	for ( i = 0; i < v; i++)
		g->array[i] = NULL;
	return g;
}

void add_edge(struct graph* g,int src,int dest,int weight)
{
	struct list_node* n = create_node(dest);
	n->next = g->array[src].head;
	g->array[src].head = n;

	n = create_node(src);
	n->next = g->array[dest].head;
	g->array[dest].head = n;
}

/* heap data structure */

struct heap_node{
	int v;
	int key;
};

struct heap{
	int size;
	int capacity;
	int* pos;
	struct heap_node** array;
};

struct heap_node* new_heap_node(int v,int key)
{
	struct heap_node* n  = (struct heap_node*)malloc(sizeof(struct heap_node));
	n->v = v;
	n->key = key;
	return n;
}

struct heap* create_heap(int capacity)
{
	struct heap* h = (struct heap*)malloc(sizeof(struct heap));
	h->capacity = capacity;
	h->size = 0;
	h->array = (struct heap_node**)malloc(v * sizeof(struct heap_node*));
	h->pos = (int*)malloc(v * sizeof(int));
	return h;
}

void swap_heap_node(struct heap_node** a,struct heap_node** b)
{
	struct heap_node* t = *a ;
	*a = *b;
	*b = t;
}

void min_heapify(struct heap* h,int i)
{
	int l = 2* i + 1;
	int r = 2* i + 2;
	int smallest = i;
	if ( l < h->size && h->array[l]->key < h->array[smallest]->key)
	smallest = l;
	if ( r < h->size && h->array[r]->key < h->array[smallest]->key)
	smallest = r;
	
	if ( smallest != i)
	{
		struct heap_node* smallest_node = h->array[smallest];
		struct heap_node* id_node = h->array[i];
		
		h->pos[smallest_node->v] = i;
		h->pos[id_node->v] = smallest;
		
		swap_heap_nodes(&(h->array[smallest]), &(h->array[i]));
		min_heapify(h,smallest);
	}
}

int is_empty(struct heap* h)
{
	return heap->size == 0;
}


struct heap_node* extract_min(struct heap* h)
{
	if ( is_empty(h))
		return NULL;
	
	struct heap_node* root = h->array[0];
	struct heap_node* last_node = h->array[h->size - 1];
	h->array[0] = last_node;	
	h->pos[root->v] = h->size - 1;
	h->pos[last_node->v] = 0;
	h->size--;
	min_heapify(h,0);
	return root;
}

void decrease_key(struct heap* h,int v,int key)
{
	int i = h->pos[v];
	h->array[i]->key = key;
	
	while ( i && h->array[i]->key < h->array[(i-1)/2]->key)
	{
		h->pos[h->array[i]->v] = (i-1)/2;
		h->pos[h->array[(i-1)/2]->v] = i;
		swap_heap_node(&(h->array[i]),&(h->array[(i-1)/2]));
		
		i = (i-1)/2;
	}
}

int is_in_heap(struct heap* h,int v)
{
	if ( h->pos[v] < h->size)	
		return 1;
	return 0;
}

void print_arr(int arr[],int n)
{
	int i;
	for ( i = 0; i < n; i++)
		printf("%d - %d\n",arr[i],i);
}

/* prim mst algorithm */

void prim(struct graph* g)
{
	int v = g->v;
	int parent[v];
	int key[v];
	
	struct heap* h = create_heap(v);
	
	int i;
	for (i = 1; i < v; i++)
	{
		parent[i] = -1;
		key[i] = INT_MAX;
		h->array[i] = new_heap_node(v,key[v]);
		h->pos[i] = i;
	}
	
	key[0] = 0;
	h->array[0] = new_heap_node(0,key[0]);
	h->pos[0] = 0;
	
	h->size = v;
	
	while ( !is_empty(h))
	{
		struct heap_node* n = extract_min(h);
		int u = n->v;
		
		struct list_node* temp = g->array[u].head;
		
		while ( temp != NULL)
		{
			int x = temp->dest;
			if ( is_in_heap(h,x) && temp->weight < key[x])
			{
				key[v] = temp->weight;
				parent[x] = u;
				decrease_key(h,v,key[v]);
			}
			temp = temp->next;
		}
	}
	
	print_arr(parent);
}




