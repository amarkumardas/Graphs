#include<stdio.h>//most of the algo. DFS is better than BFS ie.efficient but in only some cases 
#include<stdlib.h>  
struct graph      //video->BFS and DFS algorithm for Graph QUICK
{
	int edge,vertex;                            //pre order traversal**
	int **adj;
};
int top=-1;
void pushintostack(int *stackpointer,int vertex);
void popfromstack(void);
int peepreturn_top_vertex(int *stackpointer);
struct graph* Createadjacencymatrix(void);
void display(struct graph *);
void DFS(struct graph *,int *stackpointer);
int main()
{
	int option,*stack;
	struct graph *wholegraphmatrix;
   do
	 {
	 	printf("\n1.Create adjacency matrix\n2.DFS");
	 	printf("\nEnter your option: ");
	 	scanf("%d",&option);
	 	switch(option)//we cant declare variable in switch case only statement is allowed
	 	{
	 		case 1:wholegraphmatrix=Createadjacencymatrix();
	 		       display(wholegraphmatrix);
	 		break;
//we dont need linked list stack because size of stack will be exactly equal to number of vertex
           
	 case 2:stack=(int*)malloc(sizeof(int)*wholegraphmatrix->vertex);//we cant make global because
		DFS(wholegraphmatrix,stack);//vertex value is inside main func we need vertex value first so
	 		break;            // case 2                                               it is after
		 }
	 }while(option<1000);
  return 0;	
}
struct graph* Createadjacencymatrix()
{
	int u,v,edges,i;
	struct graph *g=(struct graph*)malloc(sizeof(struct graph));//one node of graph
	if(g==NULL)
	{
		printf("\nMemory not allocated");
		exit(0);
	}
printf("IFnode is startingfrom 1 thenenter total node+1 or if nodestarting is0 thenenter exactnode");
	printf("\nEnter total number of Nodes /or vertex:");
	scanf("%d",&g->vertex);
	printf("\nEnter total number of Edges:");
	scanf("%d",&g->edge); //sizeof(int*) give me size of int pointer
	g->adj=(int**)malloc(sizeof(int*)*g->vertex);//double pointer created and assigned to g->adj
	for(u=0;u<g->vertex;u++)
	{//since we want initialize with 0 so using calloc
		g->adj[u]=(int*)calloc(g->vertex,sizeof(int));//so here no need 2 forloop
	}
	 printf("\nEnter pair edge number that connect vertex: ");
	  for(i=0;i<g->edge;i++)//edge is total number of edges
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

void pushintostack(int *stackpointer,int vertex)
{
	stackpointer[++top]=vertex;//for this code this is enough
	
   /*	if(top==MAX-1)
	{
		printf("stack overflow");
	}
	else//here stackoverflow will never occur because stack size  will be exactly equal to vertex
	{
	   stackpointer[++top]=vertex;		
	}*/
}
void popfromstack(void)
{
	 top--;//for this code this is enough
	
	/*if(top==-1)
	{
		printf("Stack underflow");
	}
	else
	return stackpointer[top--];*/ 
}
int peepreturn_top_vertex(int *stackpointer)
{
	return stackpointer[top];//for this code this is enough
	/*if(top==-1)
	{
	   printf("no vertex");
	}
	else
	return stackpointer[top];*/
}
void DFS(struct graph *wholegraphmatrix,int *stackpointer)//preorder traversal
{//video BFS and DFS algorithm for GRAPHS in Data Structures
	 int node,i,j,flag; 
//we want visited array that is size of vertex and initialize to 0 so calloc is best function
   int *visitedarray=(int*)calloc(wholegraphmatrix->vertex,sizeof(int));
   
   printf("\nEnter starting vartex to start traversal: ");
   scanf("%d",&node);
   pushintostack(stackpointer,node);
   visitedarray[node]=1;
   printf(" %d",node);//if you want to print alphabet then add 65 + node formet %c
   
   while(top!=-1)//checking stack is not empty
   {
   	flag=0;
   	 node=peepreturn_top_vertex(stackpointer);//return top of stack value
   	  for(i=0;i<wholegraphmatrix->vertex;i++)//wholegraphmatrix->vertex column
   	  {
   	  	  if(wholegraphmatrix->adj[node][i]==1 && visitedarray[i]==0)//visitedarray[i]==0 not visited
   	  	  {
   	  	  	 flag=1;
   	  	  	 pushintostack(stackpointer,i);
   	  	  	 printf(" %d",i);//if you want to print alphabet then add 65 +i formet %c
             visitedarray[i]=1;
             break;//we have to push any one vertex into stack
		  }
	  }//instead of flag we can check i==wholegraphmatrix->vertex so flag variable not needed
	  if(flag==0)//when the node neighbours all visited then this will work
	  {
	  	popfromstack();
	  }
   }	
}
/*Data structure	BFS uses Queue to find the shortest path.DFS uses Stack to find the shortest path.
Source	BFS is better when target is closer to Source.	DFS is better when target is far from source.
Suitablity for decision tree As BFS considers allneighbour so it is not suitable for decision tree used
in puzzle games.DFS is more suitable for decision tree.As with onedecision,we need to traverse further
to augment the decision. If we reach the conclusion, we won.
****Speed	BFS is slower than DFS.	DFS is faster than BFS.
Time Complexity	Time Complexity of BFS =O(V+E) where V is vertices and E isedges.Time Complexity of DFS
is also O(V+E) where V is vertices and E is edges.

Applications of Depth-First Search Algorithm
Depth-first search is useful for:
? Finding a path between two specified nodes, u and v, of an unweighted graph.
? Finding a path between two specified nodes, u and v, of a weighted graph.
? Finding whether a graph is connected or not.
? Computing the spanning tree of a connected graph

Space complexity The space complexity of a depth-first search is lower than that of a breadthfirst
search.
 
Time complexity The time complexity of a depth-first search is proportional to the number of
vertices plus the number of edges in the graphs that are traversed. The time complexity can be
given as (O(|V| + |E|)).

In directed graph it is used to find reachibility  the nodes which are reachable from the node x.*/
