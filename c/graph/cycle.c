#include<stdio.h>
#include<stdlib.h>

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

/* dfs to detect cycle in a directed graph */

int dfs_util(struct graph* g, int u,int visited[])
{
	visited[u] = 1;
	struct node* temp = g->array[u].head;
	while ( temp != NULL)
	{
		if ( visited[temp->dest] == 1)
			return 1;
		else if ( visited[temp->dest] == 0 && dfs_util(g,temp->dest,visited))
			return 1;
		temp = temp->next;
	}
	visited[u] = 2;
	return 0;
}

int dfs(struct graph* g)
{
	int i;
	int visited[g->v];
	for ( i = 0; i < g->v; i++)
	visited[i] = 0;
	for( i = 0; i< g->v; i++)
	{
		if (visited[i] == 0)
		if(dfs_util(g,i,visited))
			return 1;
	}
	return 0;
	
}
int main()
{
	struct graph* g = read_graph();
	print_graph(g);
	int x = dfs(g);
	if ( x == 0)
	printf("no cycle \n");
	else printf("cycle detected\n");
	return 0;
}

