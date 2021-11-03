/*First of all remove all parallel edge and self loop.if from one node there is two path to reach 
other node called parallel edge

/*Time Complexity of the implementation is O(V^2). If the input graph is represented using adjacency
list,it can be reduced to O(E log V) with the help of binary heap
Dijkstra’s shortest-path algorithm what to do if there are "paths with same distance" in Dijkstra’s
algorithm ?ans:Then no need to relax

//video code concept-> Algorithms | Dijkstra's algorithm | Part - 1 KNOWLEDGE GATE ******* 

Difference between Dijkstra’s Algorithm and Minimum Spanning Tree?
Minimum spanning tree algorithm is used to traverse a graph in the most efficient manner, but
Dijkstra’s algorithm calculates the distance from a given vertex to every other vertex inthe graph
The point where these algorithms differ is that while Prim’s algorithm stores a minimum cost
edge, Dijkstra’s algorithm stores the total cost from a source node to the current node

second time also this code will work correctly just user have to press option 3
Dijkstra work for both directed and undirected graph and weight should be positive.
it works for graphs with cycles to as long as there are no negative cycles*******
here we are not using priority heap because to update it again dont have idea
if weight is negative and graph is diconnectedthen it will not work properly****** 

*video->Problem With Dijkstra Algorithm l Negative Weight Cycle l Design And Analysis Of Algorithm
 Course.
why dijkstra fails when there is  -ve edge?******************************************************
Actually it may fail or may not fail but it will not give proper result and also it will fail when
 there is negative weight cycle.if sum of all edges of cycle =negative then it is -ve weight cycle
 
 DIjkstra algorithm
1.Finds shortest path from source node to all other nodes
2.Does not WORK with negative weights*****
3.Works with directed and undirected graph both.
4.Time complexity O(V^2) when algorithm does not use priority queue
 When algorithm uses FIBONACCI heap as priority queue TIME complxity O(E+V log V) same as O(E log V)
 When algorithm uses binary heap as priority queue TIME Complexity O(E log V)
5.Uses greedy approach
6.Difficult to implement in distributed environment.

DRAWBACK 
Dijkstra's always gives shortest path when the edge costs are all positive. However,
it can fail when there are negative edge costs because Dijkstra cannot detect negative weight
cycle so it fails ******
 
Differences from the Dijkstra algorithm
The Dijkstra algorithm works only with positive weighted graphs with positive cycles, while
the Bellman – Ford algorithm works with graphs with positive and negative-weighted
edges and non-negative cycles.*/

#include<stdio.h> 
#include<stdlib.h>  
#define infinity 99//if graph is adjacencylist time isreduced to O(E logV) with thehelp of binaryheap
struct node            
{                    //also known as single source shortest path. it is GREEDY algorithm
	int source,destination,weight;
	struct node *next;
};
struct graph
{
	int totalvertex;
	struct node **list;
}*g;//globally declared so we can access graph from any where
 
void creategraphadjacentlist(void);
int get_index_with_minimum_distanceform_array(int *dublicatedistance);
void display(void);
void dijkstras(void);
int main()
{
	int option;
	do
	{
	    printf("\n\n1.create graph adjacent list\n2.Display graph\n3.Dijkstras shortest path");
	      
		printf("\nEnter your option: ");
		scanf("%d",&option);
		switch(option)
		{
			case 1: creategraphadjacentlist();
			break;
			case 2:display();
			break;
			case 3:dijkstras();
			break;
		}
	}while(option<1000);
	return 0;	
}
void creategraphadjacentlist(void)
{
	int vertex,i,neighbour,weight,totalconnectedneighbours;
	struct node *newnode,*holdpreviousnode;
	g=(struct graph*)malloc(sizeof(struct graph));//graph node created g is global pointer
	printf("\nEnter Total no. of vertex: ");
	scanf("%d",&g->totalvertex );
	/*sizeof(struct node *) we get size pointer type itself 4
    sizeof(*p) we get size of content that p point at.here we allocate doublepointer** array*/
    g->list=(struct node**)calloc(g->totalvertex,sizeof(struct node*));
    for(vertex=0;vertex < g->totalvertex;vertex++)
    {
    	printf("\nEnter Total no. of neighbours connected to Vertex/node %d: ",vertex);
		scanf("%d",&totalconnectedneighbours);
		for(i=0;i<totalconnectedneighbours;i++)
		{
			printf("\nEnter neighbour no. %d connected to Vertex \"%d\": ",i+1,vertex);
			scanf("%d",&neighbour);//neighbour is destination
			printf("\nEnter WEIGHT of  no. %d connected to Vertex \"%d\": ",i+1,vertex );
			scanf("%d",&weight);
			if(g->list[vertex]==NULL)
			{
			  newnode=(struct node*)malloc(sizeof(struct node));
			  newnode->destination=neighbour;
			  newnode->weight=weight;
			  newnode->source=vertex;
		    //newnode->distance=infinity;not needed because every neighbour has different node soif
			  newnode->next=NULL;// we want access distance from other node then we wound get it
			  g->list[vertex]=newnode;
			}
			else
			{
			  newnode=(struct node*)malloc(sizeof(struct node));
			  newnode->destination=neighbour;
			  newnode->weight=weight;
			  newnode->source=vertex;
			 // newnode->distance=infinity;
			  newnode->next=NULL;
			  holdpreviousnode->next=newnode; 	
			}
			holdpreviousnode=newnode;//it helps to attach newpointer to last we are not
			                        //attaching newnode to front
		}
	}   
}
void dijkstras(void)
{
	struct node *ptr;
	int source,i,index,p;
	int *distance=(int*)malloc(sizeof(int)*g->totalvertex);//at last all updated vertex distance willbe
	int *dublicatedistance=(int*)malloc(sizeof(int)*g->totalvertex);//stored inthis array distance
	
/*dublicatedistance it will contain distance since while relaxing distance same distance can be
again have to update so changes will be made in this duplicate array and original distance array will
also be updated.Dublicate distance array we are using because if westore distance in heap then we get
minimum distance but when distance isagain updated soto update distance in heap wehave to search that
node and update consume lot of time for updating distance. with dublicatedistance array requires O(1)
but for searching min distance requires O(n). After finding shortest path dublicatedistance array
will become infinity because every vertex is taken out so we have to set infinity when parent node
completely traverse its neighbour.Ifwe use Fibonacciheap then to update timecomplexity amortised O(1)
and to find min distance node time complexity O(log n) */

int*visitednode=(int*)calloc(g->totalvertex,sizeof(int));//it willhelp todetect which nodeis visited
	int *parentofnode=(int*)malloc(sizeof(int)*g->totalvertex);//it will give the path
	for(i=0;i<g->totalvertex;i++)
	{
	  dublicatedistance[i]=infinity;	//initializing all node distance to infinity
	  distance[i]=infinity;
	}
	printf("\nEnter Source/node to find shortpath to all other Destination/nodes: ");
	scanf("%d",&source);
	distance[source]=0;//updating distance since it is source node 
	dublicatedistance[source]=0;//updating dublicatedistance since it is source node 
	visitednode[source]=1;
	parentofnode[source]=-1;//-1 which meane this is parent and here only one node will be parent
	
for(i=0; i<g->totalvertex ;i++)
{  //it will traverse dublicatedistance array and find min distance with time O(n) complexity
	     //minimum index will be returned from dublicatedistance array
		index=get_index_with_minimum_distanceform_array(dublicatedistance);
	    
	ptr=g->list[index];//give the address of parent and by parent address we can get all neighbour
	if(ptr!=NULL)//if parent(ptr)doesnot have neighbour then ptr->source would be illegal so checking
	{
	 visitednode[ptr->source]=1;
	}	  
   while(ptr!=NULL)//every node contain source,distination,weight distination is itself node
  {                                                                      //means not visited
  if(distance[ptr->source]+ ptr->weight < distance[ptr->destination] && visitednode[ptr->destination]!=1)
	{
        distance[ptr->destination] = distance[ptr->source] + ptr->weight;//updating node distance
	    dublicatedistance[ptr->destination]= distance[ptr->source]+ptr->weight;//duplicatedistance
		parentofnode[ptr->destination] = ptr->source;//updating parent array to trace path
	}
			ptr=ptr->next;//it will traverse all neighbour
   }
}
       //printing of data
	printf("\nDistance and path From source to all destination: ");
	for(i=0;i<g->totalvertex;i++) 
	{//distance array contain all node distance
		printf("\nMinimum Distance from Source %d to destination %d = %d",source,i,distance[i]);
	}
	  	printf("\n");
	 for(i=0;i<g->totalvertex;i++)
	{ 
	   printf("\nPath from %d to source %d:",i,source);
	    p=i;
		while(parentofnode[p] >= 0)//parent node will contain negative value
		{
			printf(" %d<-%d,",p,parentofnode[p]);
			p=parentofnode[p];
		}
		printf("\n");
	}
	/*printf("\n\nFor information: ");
	printf("\nDistance");
	for(i=0;i<g->totalvertex;i++)//for information distance array
	{
		printf(" %d",distance[i]);
	}
	printf("\nparent node");
	for(i=0;i<g->totalvertex;i++)//for information parentofnode array
	{
		printf(" %d",parentofnode[i]);
	}
	printf("\nDublicate distance");//for information dublicatedistance array
	for(i=0;i<g->totalvertex;i++)
	{
		printf(" %d",dublicatedistance[i]);
	}
	printf("\nVisited:");
	for(i=0;i<g->totalvertex;i++)//for information visitednode array
	{
		printf(" %d",visitednode[i]);
	}*/
	free(distance);//if we dont want to print distance then distance array not needed
	free(parentofnode);
	free(dublicatedistance);
	free(visitednode);
/*we are deleting all the memory because this memory is created using malloc and calloc and this
memory is stored in heap so we have to explicitly delete it and pointer created in this func will
automatically get deleted after function ends because it is local variable next time when same 
function call then new pointer will be created.we are doing this so user can again call this func
and get result correctly*/
}
 
 int get_index_with_minimum_distanceform_array(int *dublicatedistance)
 {
 	int i,min=dublicatedistance[0],indexof_mindistance;//complexity O(n)  
 	for(i=0;i<g->totalvertex;i++)
 	{
 		if(dublicatedistance[i] <= min )//to get smallest element
 		{
 		  min=dublicatedistance[i]; 
 		  indexof_mindistance=i;
 	    }
	 }
	 dublicatedistance[indexof_mindistance]=infinity;
/*dublicatdistance[indexof_mindistance]=infinity setting to infinity because indexof_mindistance
is index of minimum distance so when second time same minimum index distance it should not return
 so setting to infinity for this reason only we required dublicatedistance array*/
	 return indexof_mindistance;
 }
void display( void)//list
{
	int i;
	struct node  *ptr;
	if(g->list!=NULL)
	{
	printf("\nData are: S=source D=destination");
 	for(i=0;i<g->totalvertex;i++)
 	{
 		printf("\nvertex %d (neighbours,weights)are: ",i);
 		ptr=g->list[i];
 		while(ptr!=NULL)
 		{
 		 
 			printf(" (%d,%d)",ptr->destination,ptr->weight);
 			ptr=ptr->next;
		 }
	 }
   }
   else
   {
   	printf("\nNo graph");
   }
}
