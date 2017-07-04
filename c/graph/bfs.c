#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

struct node{
	int dest;
	struct node* next;
};

struct list{
	struct node* head;
};

struct graph{
	int v;
	struct list* array;
};

struct node* create_node(int dest)
{
	struct node* n = (struct node*)malloc(sizeof(struct node));
	n->dest = dest;
	n->next = NULL;
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
	

void add_edge(struct graph* g, int src, int dest)
{
	struct node* n = create_node(dest);
	n->next = g->array[src].head;
	g->array[src].head = n;

	n = create_node(src);
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
			int x,y;
			scanf("%d%d",&x,&y);
			add_edge(g,x,y);
		}
	}
	return g;
}

//------------------------**bfs**----------------------------------

struct q{
	struct node* front;
	struct node* rear;
};

struct q* create_q()
{
	struct q* q = (struct q*)malloc(sizeof(struct q));
	q->front = NULL;
	q->rear = NULL;
	return q;
}

void enq(struct q* q,int info)
{
	struct node* n = create_node(info);
	if ( q->front == NULL && q->rear == NULL)
	{
		q->front = n;
		q->rear = n;	
		return ;
	}
	q->rear->next = n;
	q->rear = n;
}

int deq(struct q* q)
{
	int x;
	if ( q->front == NULL  && q->rear == NULL)
	return INT_MIN;
	struct node* temp = q->front;
	x = q->front->dest;
	q->front = q->front->next;
	if ( q->front == NULL)
	q->rear = NULL;
	temp->next = NULL;
	free(temp);
	return x;
}

void bfs(struct graph* g,int s)
{
	int visited[g->v];
	int i;
	for( i = 0; i < g->v; i++)
	visited[i] = 0;
	struct q* q = create_q();
	enq(q,s);
	visited[s] = 1;
	int x;
	while ( q->front != NULL && q->rear != NULL)
	{
		x = deq(q);
		printf("%d ",x);
		struct node* temp = g->array[x].head;
		while ( temp != NULL)
		{
			if ( visited[temp->dest] == 0)
			{
				visited[temp->dest] = 1;
				enq(q,temp->dest);
			}
			temp = temp->next;
		}
	}
}		

int main()
{
	struct graph* g = read_graph();
	print_graph(g);
	bfs(g,0);
	return 0;
}

