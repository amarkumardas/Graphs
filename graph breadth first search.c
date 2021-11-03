#include<stdio.h>//traversal may be different it depend on which neighbour we are taking first
#include<stdlib.h>//but here if you enter starting node same always then traversal will be same
struct graph      //if you enter different starting node then thraversal will be different
{
	int edge,vertex;   //it is like level order traversal**********
	int **adj;
};
#define MAX 5//for giving array size
/*fast and works if length is not made to be changed at run-time. Use macro #define before main()
 to define length and in main() your initialization will work:
 
 Macros are run before the actual compilation and length will be a compile-time constant 
  It will actually substitute length with 10 before compilation.*/

 
int queue[MAX];//circular queue advantage of circular
int front=-1,rear=-1;//last=rear
void enque(int);
int deque(void);
struct graph * Createadjacencymatrix(void );
void display(struct graph *);
void BFS(struct graph *);
int main()
{
	 int option;
	 struct graph *wholegraphmatrix; 
	 do
	 {
	 	printf("\n1.Create adjacency matrix\n2.BFS");
	 	printf("\nEnter your option: ");
	 	scanf("%d",&option);
	 	switch(option)
	 	{
	 		case 1:wholegraphmatrix=Createadjacencymatrix();
	 		      display(wholegraphmatrix);
	 		break;
	 		case 2:BFS(wholegraphmatrix);
	 		break;
		 }
	 }while(option<1000);
  return 0;	
}
struct graph * Createadjacencymatrix( )
{
	int u,v,edges,i;
	struct graph *g=(struct graph*)malloc(sizeof(struct graph));
	if(!g)//or if(g==NULL)
	{
		printf("Memory not allocated");
		exit(0);//since memory not allocated then program should terminate
	}
printf("IFnode is startingfrom 1 thenenter total node+1 or if nodestarting is0 thenenter exactnode");
	printf("\nEnter total number of Nodes /or vertex:");
	scanf("%d",&g->vertex);
	printf("\nEnter total number of Edges:");
	scanf("%d",&g->edge); 
	
	
	g->adj=(int**)malloc(sizeof(int*)*g->vertex);
	 for(u=0;u<g->vertex;u++)
	 {
	 	g->adj[u]=(int*)malloc(sizeof(int)*g->vertex);//here we can use calloc to avoid initilize with 0
	 	for(v=0;v<g->vertex;v++)
	 	{
	 		g->adj[u][v]=0;//initializing double pointer to 0
		 }
	 }
	 printf("\nEnter pair edge number that connect vertex: ");
	 for(i=0;i<g->edge;i++)//edge is total number of edge
	 {
	 	scanf("%d %d",&u,&v);
	 	 g->adj[u][v]=1;//to make directed graph then  remove next line
	 	g->adj[v][u]=1;//to make  undirected graph just use this two line
	 }
 return g;
}
void display(struct graph *wholegraphmatrix)
{
 	int i,j;
	if(wholegraphmatrix->adj==NULL)
	{
		printf("NO graph create graph");
	}
	else
	{
	printf("Matrix: \n");
	for(i=0;i<wholegraphmatrix->vertex;i++)
	{
		for(j=0;j<wholegraphmatrix->vertex;j++)
		{
		  printf("%d",wholegraphmatrix->adj[i][j]);
		}
		printf("\n");
	}
   }
}
void BFS(struct graph *wholegraphmatrix)
{
   int node,i,j; 
  //we want visited array that is size of vertex and initialize to 0 so calloc is best function
   int *visitedarray=(int*)calloc(wholegraphmatrix->vertex,sizeof(int));
   
   printf("\nEnter starting vartex to start traversal: ");
   scanf("%d",&node);
   enque(node);
   
   visitedarray[node]=1;
   while(front!=-1)//checking queue is not empty
   {
   	 node=deque();
   	 printf(" %d",node); //if you want to print alphabet then add 65 + node formet %c
   	  for(i=0;i<wholegraphmatrix->vertex;i++)
   	  {
   	  	if(wholegraphmatrix->adj[node][i]==1 && visitedarray[i]==0)
   	  	{
   	  		//printf("\n %d neighbour is %d",node,i);
   	  	    enque(i);//enque all its neighbour
		    visitedarray[i]=1;	
	    }
	  }
   }   	
}

void enque(int vertex)//circular queue
{
	
	if(rear==-1 && front==-1)
	{
		front=rear=0;
		queue[rear]=vertex;
	}
    else if((rear+1)%MAX==front)
     {
     	printf("\nQueue is full increase size of queue overflow");
     	exit(0);
	 }
	 else
	 {
	 	rear=(rear+1)%MAX;
	 		queue[rear]=vertex;
	 }
	 //printf("enque %d",vertex);
}
int deque(void)
{
	int temp;
	if(front==-1 && rear==-1)
	{
		printf("\nNo data in queue underflow");
	}
	if(front==rear)
	{
		temp=front;
		front=rear=-1;
		//printf("deque %d",queue[temp]);
		return queue[temp];
	}
	else
	{
		temp=front;
		front=(front+1)%MAX;
			// printf("deque %d",queue[temp]);
		return queue[temp];
	}	
}

/*To find shortest path using BFS
video->Shortest Path by BFS Method for unweighted graph Arup Majumdar

 **time complexity can also be expressed as O( | E | + | V | ), since every vertex and
every edge will be explored in the worst case.

Applications of Breadth-First Search Algorithm
Breadth-first search can be used to solve many problems such as:
? Finding all connected components in a graph G.
? Finding all nodes within an individual connected component.
? Finding the shortest path between two nodes, u and v, of an unweighted graph.
? Finding the shortest path between two nodes, u and v, of a weighted graph.

Space complexity In the breadth-first search algorithm, all the nodes at a particular level must
be saved until their child nodes in the next level have been generated. The space complexity is
therefore proportional to the number of nodes at the deepest level of the graph. Given a graph with
branching factor b (number of children at each node) and depth d, the asymptotic space complexity
is the number of nodes at the deepest level O(bd).

If the number of vertices and edges in the graph are known ahead of time, the space complexity
can also be expressed as O ( | E | + | V | ), where | E | is the total number of edges in G and
| V | is the number of nodes or vertices.
*/
 

