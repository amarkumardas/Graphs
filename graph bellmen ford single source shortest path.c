/*video-> Bellman Ford Algorithm - Single Source Shortest Path - Dynamic Programming
  video->Bellman Ford Algorithm to Calculate Shortest Paths Example tutorials point
  video Shortest Path Algorithms (Dijkstra and Bellman-Ford) - Simplified
video-> Bellman Ford Algorithm Explained With Solved Example in Hindi l Design And Analysis Of Algorithm 

Bellman ford algorithm ->it fails when graph has negative cycle 
in case of Bellman ford algorithm we have to know total number of vertex
**if sum of all edge of cycle is negative then it fails otherwise it prduce right result

Bellman-Ford can be considered to fail. The main problem with a negative cycle is that we can just
keep traversing it, reducing the cost of the path, thus there exists no finite shortest path to some
vertices so it fails even though it can dtech negative cycle

DRAWBACK
Both DIJKSTRA AND BELLMEN FORD Fails when there is negative weight CYCLE,but bellmen dont fail when
there is negative edge whereas DIJKSTRA fails when there is negative edge
***********************************************************************************
Bellman-Ford
1.Finds shortest path from source node to all other nodes

2.works with negative weight and can detect negative weight cycle(if sum of edges of cycle is -ve 
then it is called negative weight cycle.To detect negative weight cycle after relaxing n-1 time just
tryto relax 1 more time if anydistance get relaxed then it indicate presence of negative weightcycle 

3.Works with directed graphs and with only those undirected graph which do not have negative weights.
 If undirected graph has a negative weight then it acts as a negative CYCLE dueto both side direction
 ->if graph is undirected then best way is to replace each UNDIRECTED edge by two directed edges
 
4.Time complexity O(VE) OR n^2 in case of complete graph( means everynode connected to each other) if
  number of edges are V*(V-1)/2 and then the TIME complexity becomes O(V^3).
5.Uses dynamic programming
6.Easier to implement in distributed environment.

************************************************************************************
DIjkstra algorithm
1.Finds shortest path from source node to all other nodes
2.Does not WORK with negative weights*****
3.Works with directed and undirected graph both.
4.Time complexity O(V^2) when algorithm does not use priority queue
  When algorithm uses FIBONACCI heap as priority queue TIME complxity O(E+V log V)
  When algorithm uses binary heap as priority queue TIME Complexity O(E log V)
5.Uses greedy approach
6.Difficult to implement in distributed environment.
*/
#include<stdio.h>
#include<stdlib.h>
#define INFINITY 99
struct node     //disadvantage it takes more time then digkastra
{
  int source,weight,destination;
  struct node *next;	
};
struct graph
{
	int totalvertex;
	 struct node **list;	
}*g;//g globle graph pointer created and initialize to 0 automatically due to global declaration
void creategraphadjacentlist(void);
void display(void);
void bellmenfordalgo(void);
void display_path_and_distance(int *parent,int*distance,int source);
int check_negative_weightcycle(int *distance);
int main()
{
	int option;
	do
	{
	    printf("\n\n1.create graph adjacent list\n2.Display graph.");
		printf("\n3.Bellman ford algorithm single source shortest path");
		printf("\nEnter your option: ");
		scanf("%d",&option);
		switch(option)
		{
			case 1: creategraphadjacentlist();
			break;
			case 2:display();
			break;
			case 3:bellmenfordalgo();
			break;
		}
	}while(option<1000);
	return 0;	
}
void creategraphadjacentlist(void)
{
 int vertex,i,neighbour,weight,totalconnectedneighbours;
 struct node *newnode,*holdpreviousnode;
 g=(struct graph*)malloc(sizeof(struct graph));//graph node createdand addresss assigned to g pointer
 printf("\nEnter Total number of vertex: ");
 scanf("%d",&g->totalvertex);
 
/*sizeof(struct node *) we get size pointer type itself 4
sizeof(*p) we get size of content that p point at.here we allocate doublepointer** array*/

 g->list=(struct node **)calloc(g->totalvertex,sizeof(struct node*));//double pointer created
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
	 if(g->list[vertex]==0)
	 {
	 	newnode=(struct node*)malloc(sizeof(struct node));
	 	newnode->source=vertex;
	 	newnode->weight=weight;
	 	newnode->destination=neighbour;
	 	newnode->next=NULL;
	 	g->list[vertex]=newnode;
	 }
	 else
	 {
	    newnode=(struct node*)malloc(sizeof(struct node));
	 	newnode->source=vertex;
	 	newnode->weight=weight;
	 	newnode->destination=neighbour;
		newnode->next=NULL;	
	 	holdpreviousnode->next=newnode;//joining
	 }
	 holdpreviousnode=newnode;
   }
 }
}
void display(void)
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
void bellmenfordalgo(void)
{//how it is working first set distance array source =0 and all node to infinity and start
//relaxing all edge edge can be taken randomly 
 int vertex,i,source;
 struct node *ptr;
 int *distance=(int*)malloc(sizeof(int)*g->totalvertex);
 int *parent=(int*)malloc(sizeof(int)*g->totalvertex);//to get path
 for(i=0;i<g->totalvertex;i++)//initializing all distance to infinity
 {
 	distance[i]=INFINITY;
 	parent[i]=-1;//initializing all vertex as parent
 	
  /*if we dont initialize then func. display_path_and_distance will produce error because first
  iteration parent array should be updated sometimes also at last iteration parent array not get updated
  so parent array will contain garbage value which will be positive value then in this function
  display_path_and_distance while loop will terminate only at -ve value but parent array contain garbage
  positive value so illegat operation will be performed so initializing -1 to all parent array */
 }
 printf("\nEnter source NODE/Vertex to start finding single source shortest path: ");
 scanf("%d",&source);
 if(source >= g->totalvertex)
 {
 	printf("\nThere is no vertex %d",source);
 	return;//just returnmeans control will directly go to calling func without executing below code
 }
 distance[source]=0;//source distance is 0 and all node is infity
printf("\nLast Iteration is final distance array.\n");//for information important
 for(vertex=0;vertex < g->totalvertex-1;vertex++)//now we wil relax all edges till n-1 times
 {
   for(i=0;i<g->totalvertex;i++)
   {
   	 ptr=g->list[i];
   	 while(ptr!=NULL)
   	 {
/****/if(distance[ptr->source]!=INFINITY)//if infinity + 2 is=infinity so no need to update vertex
		{//it would be useless but this statement is very important while checking -ve weight cycle
   	 	if(distance[ptr->source] + ptr->weight < distance[ptr->destination])
   	 	 {
   	    //printf("\n%d + %d <= %d",distance[ptr->source],ptr->weight,distance[ptr->destination]);
   	 	 	distance[ptr->destination] = distance[ptr->source] + ptr->weight;
   	 	 	parent[ptr->destination]=i;//to get the parent
		 }
	    }
		 ptr=ptr->next;
	 }
   }
 
   	for(i=0;i<g->totalvertex;i++)//information
 {
 	printf(" %d",distance[i]);//1st iteration distance
 }
 printf("\n");	
 }
 if(check_negative_weightcycle(distance)==1)//if it return 0 means no -ve weighted cycle
 {
 printf("\nThis graph contain negative weight cycle so out put will be wrong algo. terminated");
}
 else
 {
 display_path_and_distance(parent,distance,source);
 }
 
 free(distance);//due to dynamically created
 free(parent);//due to dynamically created
}

int check_negative_weightcycle(int *distance)
{//if sum of all edge of cycle is -ve then it is called -ve weight cycle  
//to detech -ve cycle we just have to run once so it will run once all edge
  //if any vertex get updated or relax then it indicate  -ve weight cycle 
	int i;
	struct node *ptr;
   for(i=0;i<g->totalvertex;i++)
   {
   	 ptr=g->list[i];
   	 while(ptr!=NULL)
   	 {
		if(distance[ptr->source]!=INFINITY)//if infinity + 2=infinity so no need to update vertex
		{ /*it would be useless but this statement is very important while checking -ve weight cycle
	       because if we dont give it will update vertex which is useless and report -ve cycle which
		   is wrong.*/                                                               
   	 	if(distance[ptr->source] + ptr->weight < distance[ptr->destination])
   	 	 {
            printf("\n%d + %d <= %d\n",distance[ptr->source],ptr->weight,distance[ptr->destination]);
            distance[ptr->destination]=distance[ptr->source] + ptr->weight;//for information
            printf("\nLast iteration distance changed:");
            for(i=0;i<g->totalvertex;i++)//for information
            {
              printf(" %d",distance[i]);//iteration distance changed
            }
            printf("\nONE edge of negative weight cycle is (%d,%d)",ptr->source,ptr->destination);
              return 1;//means -ve weight cycle is present
   	 	 	//parent[ptr->destination]=i;// if it finds -ve weight cycle that means output will
		 }                                // be wrong so no need to find parent algo will stop
		 }                                
		 ptr=ptr->next;
	 }
   }
   return 0;	
}

void display_path_and_distance(int *parent,int *distance,int source)
{
	int p,i;
	for(i=0;i<g->totalvertex;i++)
	{ 
	   printf("\nPath from source %d to %d:",source,i);
	    p=i;
	    if(parent[p] >= 0)//printing parent
	    {
		while(parent[p] >=0)
		{
			printf(" %d<-%d,",p,parent[p]);
			p=parent[p];
		}
		printf("\nCheap cost= %d",distance[i]);
		printf("\n");
	   }
	   else
	   {
	   	if(i==source)
	   	{
	   		printf("It is source vertex\n");
		}
		else
		{//when vertex not connected to any node the this execute
	   	printf(" No path to Destination %d\n",i);
	    }
	   }
   }
	printf("\nALL distance:");//for information
	for(i=0;i<g->totalvertex;i++)
	{
		printf(" %d",distance[i]);
	}
}

