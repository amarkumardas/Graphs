#include<stdio.h>//it is done using adjacency list because there wil be  less edges due 
#include<stdlib.h>//Directed acyclic graph so matrix will consume more space
struct node//linked list node
{
	int vertex;
	struct node *next;   //in book it is done  using matrix
};
struct graph          //**the graph should be DAG then only it will work properly***
{
	int vertex;
	struct node **list;
};
int front=-1,rear=-1;
void enque(int vertex);
int deque(void);
struct graph *creategraphadjacentlist(void);
void display(struct graph *holdgraphnode);
void topologicalsort(struct graph *holdgraphnode);
int indegreeofavertex(int node);
int main()
{
	int option;
	struct graph *holdgraphnode;
	do
	{
		printf("\n\n1.create graph adjacent list\n2.Display graph\n3.Topological sort");
		printf("\nEnter your option: ");
		scanf("%d",&option);
		switch(option)
		{
			case 1:holdgraphnode=creategraphadjacentlist();
			break;
			case 2:display(holdgraphnode);
			break;
			case 3:topologicalsort(holdgraphnode);
			break;
		 
		}
	}while(option<1000);
	return 0;
}
struct graph *creategraphadjacentlist(void)
{
	int noofvertex,totalconnectedneighbours,i,neighbour;
	struct node *holdpreviousaddress,*newnode;
	struct graph *graphnode=(struct graph*)malloc(sizeof(struct graph));//graph node created
	printf("\nEnter total number of vertices: ");
	scanf("%d",&graphnode->vertex);
/*sizeof(struct node *) we get size pointer type itself 4
sizeof(struct node ) we get size 8 because int is 4 and pointer is 4 check struct node
sizeof(*p) we get size of content that p point at.here we allocate doublepointer** array*/
	graphnode->list=(struct node**)calloc(graphnode->vertex,sizeof(struct node*));
	if(graphnode->list==NULL)//so no need to initiallize with 0
	{
		printf("\nMemory not allocated.");
		exit(0);
	}
	for(noofvertex=0;noofvertex < graphnode->vertex;noofvertex++)//execute till number of vertex
	{
		printf("\nEnter Total no. of neighbours of  Vertex/node %d: ",noofvertex);
		scanf("%d",&totalconnectedneighbours);
		for(i=0;i<totalconnectedneighbours;i++)//this loop help to make like linked list
		{
			printf("\nEnter neighbour no. %d of Vertex \"%d\": ",i+1,noofvertex);
			scanf("%d",&neighbour);
			if(graphnode->list[noofvertex]==NULL)
			{
			    newnode=(struct node*)malloc(sizeof(struct node));
				newnode->vertex=neighbour;//newnode already created on top
			    newnode->next=NULL;
			    graphnode->list[noofvertex]=newnode;//updated part	
			}
			else
			{
			    newnode=(struct node*)malloc(sizeof(struct node));
				newnode->vertex=neighbour;//newnode already created on top
			    newnode->next=NULL;
				holdpreviousaddress->next=newnode;	
			}
				holdpreviousaddress=newnode;//it helps to attach newpointer to last we r not
			        //attaching newnode to front  
		}
	}
	return graphnode;	
}
void display(struct graph *holdgraphnode)
{
	int i;
	struct node  *ptr;
	if(holdgraphnode->list!=NULL)
	{
	printf("\nData are:");
 	for(i=0;i<holdgraphnode->vertex;i++)
 	{
 		printf("\nvertex %d neighbours are: ",i);
 		ptr=holdgraphnode->list[i];
 		while(ptr!=NULL)
 		{
 			printf(" %d",ptr->vertex);
 			ptr=ptr->next;
		 }
	 }
   }
   else
   {
   	printf("\nNo graph");
   }
}
void topologicalsort(struct graph *holdgraphnode)
{    
   //dynamically created 1D array for queue
int *arr=(int*)malloc(sizeof(int)*holdgraphnode->vertex);//it is here so function can access
void enque(int vertex)
{
  if(front==-1 && rear==-1)
  {
  	front=rear=0;
  	arr[rear]=vertex;//this func is inside topologicalsort func so it can access arr array
  }	
  else
  {
  	arr[++rear]=vertex;
  }
}
int deque(void)
{
	return arr[front++];
}
 int indegreeofavertex(int node)//to find indegree of a node
 {
    int i,countindegree=0;
    struct node *ptr;
	for(i=0;i<holdgraphnode->vertex;i++)//execute till no.of vertex
	{
		if(i != node)//no need to check vertex which is same because to find indegree of vertex
		{             //it will be present in other vertex
			ptr=holdgraphnode->list[i];//address of linked list
			while(ptr!=NULL)
			{//to find indegree we have to check each list that node is present or not 
				if(ptr->vertex == node)//if node is present then count will increase
				{
					countindegree++;
				}
				ptr=ptr->next;
			}
		}
	}
	return countindegree;	
 }
 
 int i,vertex;
 struct node *ptr;
  //dynamically created 1D array
  int *indegree_of_all_vertexes=(int*)malloc(sizeof(int)*holdgraphnode->vertex);
  
  for(i=0;i<holdgraphnode->vertex;i++)//Find the in–degree of each node
  {
    indegree_of_all_vertexes[i]= indegreeofavertex(i);//i is vertex storing indegree in 
  	if(indegree_of_all_vertexes[i]==0)                //indegree_of_all_vertices
  	{
  	  	enque(i);//i is vertex
	}
  }
  printf("\nIn degree of each node at first: ");
  for(i=0;i<holdgraphnode->vertex;i++)//for information not needed
  {
  	printf(" %d",indegree_of_all_vertexes[i]);
  }
  printf("\n");
  
  while(front <= rear)//algo will stop when queue will become empty
  {
  	vertex=deque();
  	//printf(" %c",vertex+65);to print alphabet ans
  	printf(" %d",vertex);
  	ptr=holdgraphnode->list[vertex];//**here we get address of deleted vertex neighbour***
  	while(ptr!=NULL)
  	{  //since vertex is deleted so neighbour of deleted vertex indegree should be updated so 
  	   //substracting -1 to all the neighbour of deleted vertex
		 indegree_of_all_vertexes[ptr->vertex]=	indegree_of_all_vertexes[ptr->vertex]-1;
		 if(indegree_of_all_vertexes[ptr->vertex]==0)
		 {
		 	enque(ptr->vertex);//since indegree is updated to all the neighbour of deleted vertex
		 }          //so indegree  0 vertex will occur surely here due to graph is adjacency list 
		 ptr=ptr->next;
	}
  }	 	
}
/*Topological Sorting vs Depth First Traversal (DFS):
In DFS, we print a vertex and then recursively call DFS for its adjacent vertices.In topological sorting
we need to print a vertex before its adjacent vertices. For example, in the given graph, the vertex ‘5’
should be printed before vertex ‘0’, but unlike DFS, the vertex ‘4’ should also be printed before
vertex ‘0’. So Topological sorting is different from DFS.

Note that topological sort is possible only on directed acyclic graphs that do not have any cycles.

For a DAG that contains cycles, no linear ordering of its vertices is possible.

In simple words, a topological ordering of a DAG G is an ordering of its vertices such that
any directed path in G traverses the vertices in increasing order.


Application
Topological sorting is widely used in scheduling applications, jobs, or tasks.

The jobs that have to be completed are represented by nodes, and there is an edge
from node u to v if job u must be completed before job v can be started.

A topological sort of such a graph gives an order in which the given jobs must be performed.

*/


