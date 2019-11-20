#include<stdio.h>
#include<stdlib.h>
#include<time.h>


#define INFINITY 999
#define MAX_N 100

typedef struct _node
{
	int data;
	struct _node *next;
}node;


node *createNode(int data)
{
	node *new = (node*)malloc(sizeof(node));
	new->data = data;
	new->next = NULL;

return new;
}


void priorityPush(node **head, int data )
{
	node *iter = (*head);
	node *newNode = createNode(data);
	
	if((*head)->data > data)
	{
		newNode->next = (*head);
		*head = newNode;
		return;
	}
	else
	{
		while(iter->next != NULL &&
			iter->next->data < data)
				iter = iter->next;

		newNode->next = iter->next;
		iter->next = newNode;
		return;
	}
}

int priorityPop(node **head)
{
	int value = (*head)->data;
	node *tmp = (*head)->next;
	free(*head);
	*head = tmp;

	return value;
}

void printQ(node *head)
{
	for(node *tmp = head;
		tmp != NULL;
		printf("%i ",tmp->data),
		tmp = tmp->next);
}

typedef struct _vertex
{
	int id;
	int N_neighbours;
	int neighbours[MAX_N][2];
	int visited;
}vertex;


vertex *getVertex(vertex *Graph, int N, int id)
{
	for (int i = 0; i < N; ++i)
		if(Graph[i].id == id)
			return &Graph[i];
	
}


void addEdge(vertex *Graph, int N, int from, int to, int edgeWeight)
{
	int flag = 0;

	vertex *current;
	current = getVertex(Graph,N, from);

	for(int i = 0; i < current->N_neighbours; ++i)
		if(current->neighbours[i][0] == to)
			flag = 0;

	srand(time(NULL));
	if(!flag){
		current->neighbours[current->N_neighbours][0] = to;
		current->neighbours[current->N_neighbours++][1] = edgeWeight;
	}
	

	flag = 0;
	current = getVertex(Graph, N, to);

	for(int i = 0; i < current->N_neighbours; ++i)
		if(current->neighbours[i][0] == from)
			flag = 1;

	if(!flag){
		current->neighbours[current->N_neighbours][0] = from;
		current->neighbours[current->N_neighbours++][1] = edgeWeight;
	}
}

void djikstra(vertex *Graph, int source)
{
	int distance[6];
	int previous[6];

	node *head = createNode(source);

	for (int i = 0; i < 6; ++i)
	{
		//vertex *current = getVertex(Graph, 6 , source + i);
		distance[i] = INFINITY; 
		previous[i] = -1;

		if(Graph[i].id != source)
			priorityPush(&head, Graph[i].id);
	}
	distance[0] = 0;
	previous[0]= 1;

	while(head != NULL)
	{
		int vertexU = priorityPop(&head);
		vertex *current = getVertex(Graph, 6, vertexU);

		for(int i = 0; i < current->N_neighbours; ++i)
		{
			int tmpDistance = distance[(current->id)-1] + current->neighbours[i][1];

			if(tmpDistance < distance[(current->neighbours[i][0]-1)])
			{
				distance[(current->neighbours[i][0]-1)] = tmpDistance;
				previous[(current->neighbours[i][0]-1)] = vertexU;
			}

		}

	}

	for (int i = 0; i < 6; ++i){
		printf("%i: ", i+1);
		printf("%i ",distance[i] );
		printf("%i \n ",previous[i] );
	}

}

int main()
{
	node *head=createNode(1);

	vertex Graph[6];

	for (int i = 0; i < 6; ++i)
	{
		Graph[i].id = i+1;
		Graph[i].visited = 0;
		Graph[i].N_neighbours = 0;
	}

	addEdge(Graph, 6, 1, 2, 3);
	addEdge(Graph, 6, 1, 4, 7);
	addEdge(Graph, 6, 2, 4, 1);
	addEdge(Graph, 6, 2, 3, 5);
	addEdge(Graph, 6, 4, 5, 8);
	addEdge(Graph, 6, 3, 5, 4);
	addEdge(Graph, 6, 3, 6, 3);
	addEdge(Graph, 6, 5, 6, 2);


	djikstra(Graph, Graph[0].id);


	/*for (int i = 1; i < 7; i++)
	{
		vertex *current = getVertex(Graph, 6, i);
		printf("%d: ", current->id);
		for (int j = 0; j < current->N_neighbours; j++)
			{
				printf("%d ", current->neighbours[j][0]);
				printf("udaljenost do toga verteksa je%i \n ", current->neighbours[j][1]);
		printf("\n");
		}
	}
*/
return 0;
}