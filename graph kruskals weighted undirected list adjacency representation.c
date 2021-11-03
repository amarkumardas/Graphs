/*Kruskal's algorithm is use to find minimum cost spanning tree for a weighted undirected
graph using greedy approach.

Prim's and Kruskal's algorithms are used to find the minimum spanning tree of a graph that is connected
and undirected.

This algorithm treats the graph as a forest and every node it has as an individual tree. A tree
connects to another only and only if, it has the least cost among all available options and
does not violate MST(Minimum Spanning Tree) properties.

A spanning tree of a graph is just a subgraph that contains all the vertices and is a tree with
no cycle. A graph may have many spanning trees.
A spanning tree of a graph with minimum cost is called ‘minimum cost spanning tree’.

Kruskal’s Algorithm:
Step 1: Remove all the loops (Any edge that starts and ends at the same vertex is loop)
Step 2: Remove all parallel edges between two vertices except the one with least weight.
Step 3: Arrange all edges in their increasing order of weight
(for all vertices repeat step 4)
Step 4: Add the edge which has the least weight and with no cycle.*/

/*does prims and kruskals work with negative weight?
The concept of MST allows weights of an arbitrary sign. The two most popular 
algorithms for finding MST (Kruskal's and Prim's) work fine with negative edges/weight****/

//Prim's and Kruskal's algorithm works only for undirected weighted graphs**********

/*video to find union-> DAA- Find and Union implementation of Kruskal Algorithm Meenakshi Malhotra
->video ->1.12 Disjoint Sets Data Structure - Weighted Union and Collapsing Find

->priority queue will be more efficent if wemake using fibonacci heap insertion will become fast O(1)
 and finding minimum node O(log n) here we have made priority queue using linked list

->to find cycle we can also do using linked but it would be not efficient so we are doing using array
which is efficient to find cycle in graph and save space in this code we are using is
weighting rank rules, collapsing rules . **which makes more efficient to detect cycle O(1)

Weighting rule: if the number of nodes in the tree with root i is less than the number in
the tree with root j, then make j the parent of i; otherwise make I the parent of j.(merge)

Collapsing rule: if j is a node on the path from I to its root and p[i]  root[i] then set p[j]
to root[i]. 

//to make disjoint set we can either use array or linked list so to improve performance
there are two ways 1.Union by rank (or weight rule) 2.path compression(collapsing rule) 
in this code we are doing .Union by rank (or weight rule) and path compression(collapsing rule)
for better performance*/

#include<stdio.h>
#include<stdlib.h>   
struct graph //since kruskals work better for sparse graph so using adjaceny list that will save space 
{    
	int totalvertex;        //**this full code not  in youtube
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
void kruskals_minimumspanningtree(struct graph *);
void insert_into_priorityqueue(struct node *addressofnode);
struct node *give_minimum_weight_node_from_priorityqueue(void);
int findparent(int vertex,int *);
void union_merge(int i,int j,int *);//Weighting rule
void collapsing_rule(int i,int *);
int main()
{
	int option;
	struct graph *holdgraphnode;
	do
	{
	    printf("\n\n1.create graph adjacent list\n2.Display graph\n3.Delete graph");
	    printf("\n4.Kruskals minimum spanning tree");
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
			case 4:kruskals_minimumspanningtree(holdgraphnode);
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

void display(struct graph *holdgraphnode)//graph
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
void deletegraph (struct graph *holdgraphnode)//graph
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
	free(holdgraphnode->list);
	holdgraphnode->list=NULL;
	printf("\nDeleted successfully");
   }
   else
   {
   	printf("\nNo graph");
   }
}
void kruskals_minimumspanningtree(struct graph *holdgraphnode)
{
  struct node *ptr,*temp;
  int i,j,k,edgecounter=0,minimumcost=0;
  int *visitedarr=(int*)malloc(sizeof(int)*holdgraphnode->totalvertex);
  int *parentarray=(int*)malloc(sizeof(int)*holdgraphnode->totalvertex);//to trace path
  for(i=0;i<holdgraphnode->totalvertex;i++)//initializing parent array to -1 
	{
		parentarray[i]=-1;//initializing with -1 is important -1 indicate parent
	}
	
  for(i=0; i < holdgraphnode->totalvertex; i++)//inserting edges into priority queue
  {
  	visitedarr[i]=1;
  	ptr=holdgraphnode->list[i];
  	 while(ptr!=0)
  	 {//we are not inserting visited vertex only non visited vertex is inserted into priority queue
  	 	if(visitedarr[ptr->destination]!=1)//if we insert visited vertex then it would be useless
  	 	{
	     /*In undirected garph theres is path from A to B and B to A so no need to insert both edge
	only one edge we have to insert into priority queue if we insert both edges it would be useless*/
	
  	 		insert_into_priorityqueue(ptr);// will sort in increasing order by weight
		}
  	   ptr=ptr->next;	
	 } 
  }
  ptr=start; //start is pointer of priority queue for information
  printf("\nALL sorted edges in priority ");//for information
  while(ptr!=0)//for information to print all weight in increasing order from priority queue	
  {
  	printf("\n%d %d w=%d",ptr->source,ptr->destination,ptr->weight); 
  	ptr=ptr->next;
  }
  printf("\n");//for information	
  
	while(1) 
  {                  
  	temp=give_minimum_weight_node_from_priorityqueue();
  	
  	j= findparent(temp->source,parentarray);//it will return parent vertex O(logn) dueto path compression
  	k= findparent(temp->destination,parentarray);//itwill return parentvertex O(logn) dueto pathcompression
  	
  	if(j != k)//if both parents or set are equal then we discard that edge because both are from 
  	{ //same set which will form cycle.if both are different then we print and union (merge) both sets
  	 
  	   union_merge(j,k,parentarray);
		 	
  	   printf("\nS=%d D=%d W/cost=%d",temp->source,temp->destination,temp->weight);
  	   minimumcost=minimumcost+temp->weight;
  	   //here first we are merging two parent then applying collapsing_rule 
  	   collapsing_rule(temp->source,parentarray);//do not pass i and j otherwise collapsing_rule
  	   collapsing_rule(temp->destination,parentarray);//will not work pass source and destination
  	   ++edgecounter;                   
	}
//to form MST we need edges n-1(n=no.ofvertex)so ++edgecounter will keep track of edges to stop algo
	if(edgecounter == holdgraphnode->totalvertex-1)//n-1
	{
		break;//terminate while loop
	}//when edgecounter become 1 less than totalvertex that means MST is formed so stop the algorithm
  }
  printf("\nMinimum cost using Kruskals ago = %d\n",minimumcost);
  printf("\nParent array : ");
  for(i=0;i<holdgraphnode->totalvertex;i++)//for information
  {
  	printf(" %d",parentarray[i]);
  }
}
int findparent(int vertex,int *parentarray)//finding parent of vertex  O(logn) due topath compression
  {    
  	int p=vertex;
  	 while(parentarray[p] >= 0)//it will terminate when negative value appears 
  	 {                     
  	     p=parentarray[p]; 	
	 }
	 return p;//returning parent of vertex 
  }
  
/*Weighting rule: if the number of nodes in the tree with root i is less than the number in
the tree with root j, then make j the parent of i; otherwise make I the parent of j.Tis is done so that
height remain same we should not increase the height.this is applied to this function ->union_merge*/
void union_merge(int i,int j,int *parentarray)//weighted rank or union byrank Timecomplexity maybe O(1)
   { //video->1.12 Disjoint Sets Data Structure - Weighted Union and Collapsing Find
   
 /*Why union by rank and not by height?
 Because initially Rank is same as height,But due to PATH compression height may change but its
RANK remain same so union by rank */

      int temp;
      temp=parentarray[i]+parentarray[j];
   	  if(parentarray[i] >  parentarray[j])//parent which have more nodes and parent with less node
   	  {                                   //will merge with parent which have more nodes**********
   	  	parentarray[j]=temp;//updating no. of nodes
	  	parentarray[i]=j;//making j as parent of i because j has more nodes then i
	  }
	  else if(parentarray[i] <  parentarray[j])//this condition is opposite ie. -2 and-3 so here -3 
	  {                   //is greater because there are 3 nodes and -2 is smaller becouse of 2 nodes
	  	parentarray[i]=temp;//updating no. of nodes
   	  	parentarray[j]=i;//making i as parent of j because i has more nodes then j
	  }
else//else if(parentarray[i] == parentarray[j])//both have same nodes then any  node can be merged
	  {
	  	 parentarray[i]=temp;//or parentarray[j]=temp; any node can be merged
	  	 parentarray[j]=i;//or parentarray[i]=j;
	  }
   }
void collapsing_rule(int i,int *parentarray)//path compression for better performance
{//video-> Collapsing Find Algorithm tutorials point

/*1.Path compression reduce height of tree,2.Rank of tree remains same exactly.3.It leads to O(log n)
   performance for FIND and UNION. UNION operation may be O(1) because we are just changing parent*/
	int r=i,s,counter=0;
	while(parentarray[r]>=0)//this will find root node of i
	{
		r=parentarray[r];
		counter++;
	}
 /*we have to avoid executing when count value is 1 or 0.when count is 1 it means only 1 node is present
 so no need to execute.when count is 0 it means i itself is rootnode so no nend to execute*/
 
	//if(counter > 1) or  
	if(counter!=1 && counter!=0 )//counter!=1 this means root contain more than one node 
	{                            //counter!=0 means i itself is not root node  
	  while(i!=r)
	  {
		s=parentarray[i];//s is to hold the node that will be proceed next
		parentarray[i]=r;//updating root to that node r is root or parent
		i=s;
	  }
    }
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
given 1 as pri then then this will execute.it checks only first element we are not using >= because 
when user enter same pri then else statement will execute so that same pri will come down not first */
	    {
	 	    newnode->next=start;//or newnode->next=temp;
	 	    start=newnode;
	    }
	   else
	    {                           //advance checking 
	     	while(temp->next!=NULL && temp->next->weight <= newnode->weight)
	 	    {
	 		  temp=temp->next;
		    }
		  newnode->next=temp->next;
		  temp->next=newnode;
	    }
     }
 }
 struct node *give_minimum_weight_node_from_priorityqueue(void)//means deque
 {
 	struct node *temp;
 	 if(start==NULL)//this will never occur
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
 
 /*Why Kruskal’s Algorithm fails for directed graph ?
In Kruskal’s algorithm In each step, it is checked that if the edges form a cycle with the spanning-tree
formed so far. But Kruskal’s algorithm fails to detect the cycles in a directed graph as there are cases
when there is no cycle between the vertices but Kruskal’s Algorithm assumes it to cycle and don’t take 
consider some edges due to which Kruskal’s Algorithm fails for directed graph..
Example->link=https://www.geeksforgeeks.org/why-prims-and-kruskals-mst-algorithm-fails-for-directed-graph/
  
when kruskals algo is prefered to use ?************
it is preferred when graph is sparse that means when there are less number of edges in graph like E=O(V)
OR WHEN THE EDGES ARE ALREADY SORTED or can be sorted in linear time
  
Difference 
1.prims algo while making MST always remain same
2.prims will grow solution from random vertex by adding next cheapest vertex to existing tree
3.it is faster for dense graph means more number of edges
4.itis faster then kruskalsalgorithem because it doesnot required to sort edges and keep track of cycle
  
1.kruskals algo while making MST usually remain disconnected when MST is made compltely it
  becomes connected. 
2.it will grow solution from the cheapest edge by adding next cheapest edge to existing tree/forest
3.it is faster for sparse graph
4.it is slower than prims algo becaue kruskals neeed to sort and keep track of cycles
  
*If the graph is not connected, then it finds a minimum spanning forest. Note that a forest
is a collection of trees.Similarly a minimum spanning forest is a collection of minimum
spanning trees
   
Does Kruskal work with negative weights?

Yes. Negative edge weights are no problem for Prim's algorithm and Kruskal's algorithm. ...
So even if your MST algorithm fails in the presence of negative edge weights, you can avoid
this problem very easily, just by adding a sufficiently large constant to all edge weights.*/
