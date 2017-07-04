#include<stdio.h>
#include<stdlib.h>

struct node{
	int dest;
	int weight;
	struct node* next;
};

struct list{
	struct node* head;
};

struct graph{
	int v;
	struct list* array;
};

struct node* create_node(int dest,int weight)
{
	struct node* n = (struct node*)malloc(sizeof(struct node));
	n->dest = dest;
	n->next = NULL;
	n->weight = weight;
	return n;
}

struct graph* create_graph(int v)
{
	struct graph* g = (struct graph*)malloc(sizeof(struct graph));
	g->v = v;
	g->array = (struct list*)malloc(v * sizeof(struct list));
	int i;
	for ( i= 0 ; i < v; i++)
	g->array[i].head = NULL;
	return g;
}
	

void add_edge(struct graph* g, int src, int dest,int weight)
{
	struct node* n = create_node(dest,weight);
	n->next = g->array[src].head;
	g->array[src].head = n;

	n = create_node(src,weight);
	n->next = g->array[dest].head;
	g->array[dest].head = n;
}

void print_graph(struct graph* g)
{
	int i;
	for ( i = 0; i < g->v; i++)
	{
		struct node* temp = g->array[i].head;
		printf("%d :", i );
		if ( temp != NULL)
		{
			while ( temp->next != NULL)
			{
				printf("%d-->",temp->dest);
				temp = temp->next;
			}
			printf("%d\n",temp->dest);	
		}
	}
}

struct graph* read_graph()
{
	int v,e;
	printf("enter the no of vertices : ");
	scanf("%d",&v);
	struct graph* g = create_graph(v);
	printf("enter the no of edges : ");
	scanf("%d",&e);
	if ( e != 0)
	{
		printf("enter the edges: \n");
		int i;
		for ( i= 0; i < e; i++)
		{
			int x,y,weight;
			scanf("%d%d%d",&x,&y,&weight);
			add_edge(g,x,y,weight);
		}
	}
	return g;
}

/* min heap */

struct heap_node{
	int v;
	int key;
};

struct heap{
	int heap_size;
	int capacity;
	struct heap_node** array;
};

struct create_heap_node(int v,int key)
{
	struct heap_node* n = (struct heap_node*)malloc(sizeof(struct heap_node));
	n->v = v;
	n->key = key;
	return n;
}

struct heap* create_heap(int capacity)
{
	struct heap* h = (struct heap*)malloc(sizeof(struct heap));
	h->capacity = capacity;
	h->heap_size = 0;
	h->array = (struct heap_node**)malloc( capacity * sizeof(struct heap_node*));
	return h;
}

void swap(struct heap_node** a,struct heap_node** b)
{
	struct heap_node* t = *a;
	*a = *b;
	*b = t;
}

void min_heapify(struct heap* h,int i)
{
	int l = 2* i + 1;
	int r = 2*i + 2;
	int smallest = i;
	if ( l < h->heap_size && h->array[l] < h->array[i])
	smallest = l;
	if ( r < h->heap_size && h->array[r] < h->array[smallest])
	smallest = r;
	if ( smallest != i)
	{
		swap(&(h->array[i]),&(h->array[smallest]));	
		min_heapify(h,smallest);
	}
}

void insert(struct heap* h,int info)
{
	if ( h->heap_size == h->capacity)
	{
		printf("overflow\n");
		return;
	}
	h->heap_size++;
	int i = h->heap_size - 1;
	h->array[i] = info;
	
	while ( i != 0 && h->array[(i-1)/2] > h->array[i])
	{
		swap(&(h->array[(i-1)/2]),&(h->array[i]));
		i = (i-1)/2;
	}
}

 extract_min(struct heap* h)
{
	if ( h->heap_size == 0)
		return NULL;
	struct heap_node* root = h->array[0];
	h->array[0] = h->array[h->heap_size - 1];
	h->heap_size--;
	min_heapify(h,0);
	return root;
}

void prim(struct graph* g)
{
	int parent[g->v];
	int key[v];
	struct heap* h = create_heap(v);
	int i;
	for ( i = 0; i < v;i++)
	{
		parent[i] = -1;
		key[i] = INT_MAX;
		min
	}
	
		
	
	

int main()
{
	struct graph* g = read_graph();
	print_graph(g);
	return 0;
}

