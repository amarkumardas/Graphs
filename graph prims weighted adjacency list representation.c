//No, Prim's and Kruskal's algorithm works only for undirected graphs
/*does prims and kruskals work with negative weight?
The concept of MST allows weights of an arbitrary sign. The two most popular 
algorithms for finding MST (Kruskal's and Prim's) work fine with negative edges/weight****/
#include<stdio.h>//Prim's algorithm only works on undirected graphs************
#include<stdlib.h>//Prim's algorithm can handle negative edge weights. video this concept is used
//graph - 19: Prim's Algo | Minimum Spanning Tree in weighted Graph (Min Distance to cover all nodes)
struct graph
{                //**remember graph should not contain loops or parallel edges there is no code to
	int totalvertex; //remove this .and graph should be connected
	struct node **list;	
};
struct node
{
	int source,destination,weight;
	struct node *next;
};
struct node* start=NULL;
struct graph *creategraphadjacentlist(void);
void display(struct graph*);
void deletegraph (struct graph*);
void prims_minimumspanningtree(struct graph *);
void insert_into_priorityqueue(struct node *addressofnode);//we canmake priority que in heap using 
struct node *give_minimum_weight_node_from_priorityqueue(void);//linked list
int main()
{
	int option;
	struct graph *holdgraphnode;
	do
	{
	    printf("\n\n1.create graph adjacent list\n2.Display graph\n3.Delete graph");
	    printf("\n4.Prims minimum spanning tree");
		printf("\nEnter your option: ");
		scanf("%d",&option);
		switch(option)
		{
			case 1:holdgraphnode=creategraphadjacentlist();
			break;
			case 2:display(holdgraphnode);
			break;
			case 3:deletegraph(holdgraphnode);
			break;
			case 4:prims_minimumspanningtree(holdgraphnode);
			break;
		}
	}while(option<1000);
	return 0;
}
struct graph *creategraphadjacentlist(void)
{
	int noofvertex,totalconnectedneighbours,i,neighbour,weight;
	struct node *holdpreviousaddress,*newnode;
	struct graph *g=(struct graph*)malloc(sizeof(struct graph));
	printf("\nEnter Total no. of vertex: ");
	scanf("%d",&g->totalvertex);
	/*sizeof(struct node *) we get size pointer type itself 4
    sizeof(struct node ) we get size 8 because int is 4 and pointer is 4 check struct node
    sizeof(*p) we get size of content that p point at.here we allocate doublepointer** array*/
    
	g->list=(struct node **)calloc(g->totalvertex,sizeof(struct node *));
 	for(noofvertex=0;noofvertex < g->totalvertex ;noofvertex++)
 	{
 		printf("\nEnter Total no. of neighbours connected to Vertex/node %d: ",noofvertex);
		scanf("%d",&totalconnectedneighbours);
		for(i=0;i<totalconnectedneighbours;i++)
		{
		    printf("\nEnter neighbour no. %d connected to Vertex \"%d\": ",i+1,noofvertex);
			scanf("%d",&neighbour);
		
			if(g->list[noofvertex]==NULL)
			{
				
			    newnode=(struct node *)malloc(sizeof(struct node ));
			    printf("\nEnter WEIGHT of  no. %d connected to Vertex \"%d\": ",i+1,noofvertex );
			    scanf("%d",&weight);
			    newnode->weight=weight;
			    newnode->destination=neighbour;
			    newnode->next=NULL;
			    newnode->source=noofvertex;//starting point
			    g->list[noofvertex]=newnode;
			}
			else
			{
			    newnode=(struct node *)malloc(sizeof(struct node ));
			    printf("\nEnter WEIGHT of  no. %d connected to Vertex \"%d\": ",i+1,noofvertex);
			    scanf("%d",&weight);
			    newnode->weight=weight;
			    newnode->destination=neighbour;
			    newnode->source=noofvertex;//starting point
			    newnode->next=NULL;
			    holdpreviousaddress->next=newnode;		
			}
			holdpreviousaddress=newnode;//it helps to attach newpointer to last we r not
			        //attaching newnode to front
		}
	 }

return g;	
}

void display(struct graph *holdgraphnode)
{
	int i;
	struct node  *ptr;
	if(holdgraphnode->list!=NULL)
	{
	printf("\nData are: S=source D=destination");
 	for(i=0;i<holdgraphnode->totalvertex;i++)
 	{
 		printf("\nvertex %d (neighbours,weights)are: ",i);
 		ptr=holdgraphnode->list[i];
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
void deletegraph (struct graph *holdgraphnode)
{//whatever we have created dynamically deleting
	int i;
	struct node *ptr,*temp;
	if(holdgraphnode->list!=NULL)
	{
	for(i=0;i<holdgraphnode->totalvertex;i++)
	{
		ptr=holdgraphnode->list[i];
		while(ptr!=NULL)
		{
			temp=ptr;
			ptr=ptr->next;
			free(temp);//deleting each neighbour
		 
		}
	}
	free(holdgraphnode->list);//deleting array of pointer
	holdgraphnode->list=NULL;
	printf("\nDeleted successfully");
   }
   else
   {
   	printf("\nNo graph");
   }
}
void prims_minimumspanningtree(struct graph *holdgraphnode)
{//we can find any MST from any source
	struct node *ptr,*temp;
	int j,k,i=0,totalminimumweight=0;//from where we want to start set i value
	int *visitedarr=(int*)calloc(holdgraphnode->totalvertex,sizeof(int));
	visitedarr[0]=1;//1 means visited
	for(k=1;k<holdgraphnode->totalvertex;k++)
	{
	 /*k=1 because it should run till no. of vertex so visitedarr[0]is already run so we have
       to decrease by 1 so k=1 not k=0;if we give k=0 then else statement will execute and
	    produce underflow so we have to stop algo.*/
		ptr=holdgraphnode->list[i];
		while(ptr!=0)
		{
			if(visitedarr[ptr->destination]!=1)//means not visited
			{
			  insert_into_priorityqueue(ptr);//edge which isnot visited adaddress stored to priority
			}                               // queue in increasing order of weight 
			ptr=ptr->next;
		}        
		temp=give_minimum_weight_node_from_priorityqueue();//minimum weight address 
		for(j=0;j < holdgraphnode->totalvertex;j++)//if cycle is found then this loop will
		{                                            //execute till no cycle found
		  if(visitedarr[temp->destination]!=1)//means not visited there will be no cycle edge
	    	{
			  printf(" \n%d->%d= weight%d",temp->source,temp->destination,temp->weight);
		      totalminimumweight=totalminimumweight+temp->weight;
		      i=temp->destination;//i will act as new source
		      visitedarr[i]=1;//making visited to those vertex whose weight is printed
		      break;//terminate forloop
		    }
		    else
		    { //if cycle formed then this will execute it will give another minimum weight
		      	temp=give_minimum_weight_node_from_priorityqueue();	
			}	   
	    }		
     }
     printf("\nTotal minimum weight using prims algo= %d",totalminimumweight);
 }
 void insert_into_priorityqueue(struct node *ptr)
 {//we can also use fibonacci heap for insertion O(1) and find minimum O(log n)
 
/*Linked list priority queueis arranged in assending order of elements based on their priority
This allow us to remove the lowest priority element in O(1) time. To insert an element we must
traverse the list and find the proper position to insert the node so that the overall order of
the priority queue is maintained. This makes the push() operation takes O(N) time. The pop() 
and peek() operations are performed in constant time.
*/
 	struct node *newnode=(struct node *)malloc(sizeof(struct node ));
 	struct node *temp;
 	    newnode->source=ptr->source;
	 	newnode->destination=ptr->destination;
	 	newnode->weight=ptr->weight;
     if(start==NULL)
	 {
	 	newnode->next=NULL;
	 	start=newnode;
	 }
	 else
	 {
	   temp=start;
	   if(temp->weight > newnode->weight)/*to change first priority if first pri is 2 and user has
given 1 as pri then this will execute.it checks only firstelement we are not using >= because when
user enter same pri then else statement will execute so that same pri will come down not first*/
	    {
	 	    newnode->next=start;//or newnode->next=temp;
	 	    start=newnode;
	    }
	   else
	    {                  //advance checking 
	     	while(temp->next!=NULL && temp->next->weight <= newnode->weight)
	 	    {
	 		  temp=temp->next;
		    }
		  newnode->next=temp->next;
		  temp->next=newnode;
	    }
     }
 }
 struct node *give_minimum_weight_node_from_priorityqueue(void)
 {//returning minimum node which is at top 
 	struct node *temp;
 	 if(start==NULL) 
	{
		printf("\nUNDERFLOW");
	}
	else
	{
		 temp=start;
		 start=start->next;
		 return temp;
	}	
 }
 /*will both algo produce same MST(prims amd kruskals?
 -> if all the edges are distinct(different) then both algo are gurranteed  to find same or
  unique MST but if edges are not distinct then it is not necessary that both algo will
   produce same MST BUT THE COST of MST produce would be same in both cases.
   
   Prims is greedy algorithm
   
   when PRIMS algo is prefered to use ?************
  it is preferred when graph is dence that is when there are large number of edges in graph
  ie.E=O(V^2) BECAUSE we dont have to pay much attention to cycles by adding on edges in
  Prims algo as we are primarialy dealing with vertexs
 
 The running time of Prim’s algorithm can be given as O(E log V) where E is the
number of edges and V is the number of vertices in the graph.
 
  TIME COMPLEXITY of prims is better than kruskals because in kruskals first we have to sort
  edges in increasing order of weights where as in prims we dont have to sort after that 
kruskals have to pay attention to cycles by adding on edge where as in prims it will randomly
choose any vertex and it will look to edges directly connected to it and it choose  with less
 weight so time is less in prims algo

Why Prim’s Algorithm Fails for Directed Graph ?
Prim’s algorithm assumes that all vertices are connected. But in a directed graph, every 
node is not reachable from every other node. So, Prim’s algorithm fails due to this reason.

  **Prim’s algorithm is significantly faster in the limit when you’ve got a really dense graph
with many more edges than vertices. Kruskal performs better in typical situations (sparse graphs)
   because it uses simpler data structures.
   
   Prim's and Kruskal's algorithm works only for undirected graphs.***************
   Prim’s - The graph must be : connected , weighted , undirected,not work for directed graph
   Kruskal’s - The graph must be : connected, weighted, undirected,not work for directed graph

**you cannot use Prim’s on a disconnected graph. The reasoning
is hidden in the details of the algorithm. Since it works by starting at an initial vertex and
 connecting minimum adjacent edges until the graph spans all verticies. It seems to me that we
would never be able to span all verticies if the graph contained even a single disconnected
vertex.*/
