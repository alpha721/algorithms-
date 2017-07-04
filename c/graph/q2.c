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

struct q{
	struct node* front;	
	struct node* rear;
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
	g->array = (struct list*)malloc( v* sizeof(struct list));
	int i;
	for ( i = 0; i < v; i++)
	g->array[i].head = NULL;
	return g;
}

struct q* create_q()
{
	struct q* q = (struct q*)malloc(sizeof(q));
	q->front = NULL;
	q->rear = NULL;
	return q;
}

void push(struct q* q,int info)
{
	struct node* n = create_node(info);
	if ( q->front == NULL && q->rear == NULL)
	{
		q->front = n;
		q->rear = n;
		return ;
	}
	q->rear->next = n;
}

int pop(struct q* q)
{
	if ( q->front == NULL && q->rear == NULL)
	return INT_MIN;
	struct node* temp = q->front;
	int x = q->front->dest;
	q->front = q->front->next;
	temp->next = NULL;
	if ( q->front == NULL)
	q->rear = NULL;
	free(temp);
	return x;
}
	

void add_edge(struct graph* g,int src,int dest)
{
	struct node* n = create_node(dest);
	n->next = g->array[src].head;
	g->array[src].head = n;

	n = create_node(src);
	n->next = g->array[dest].head;
	g->array[dest].head = n;
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
		int i ;
		printf("enter the edges : \n");
		for( i = 0; i < e; i++)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			add_edge(g,x,y);
		}
	}
	
	return g;
}

void print_graph(struct graph* g)
{
	int i;
	for ( i = 0;i < g->v; i++)
	{
		struct node* temp = g->array[i].head;
		printf("%d : ",i);
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

void bfs(struct graph* g,int s)
{
	struct q* q = create_q();
	int visited[g->v];
	int i;
	for( i = 0; i < g->v; i++)
	visited[i] = 0;
	visited[s] = 1;
	push(q,s);
	while ( q->front != NULL)
	{
		s = pop(q);
		printf("%d ",s);
		struct node* temp = g->array[s].head;
		while ( temp != NULL)
		{
			if ( visited[temp->dest] == 0)
			{
				visited[temp->dest] = 1;
				push(q,temp->dest);
			}
			temp = temp->next;
		}
	}
}
		
			
	
int main()
{
	struct graph* g = read_graph();
	print_graph(g);
	printf("bfs : \n");
	bfs(g,0);
	return 0;
}
