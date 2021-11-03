#include<stdio.h>//it is both directed and undirected graph just enter edges
#include<stdlib.h>
struct node
{               //code is made by taking idea of pdf question
	int vertex;
	struct node *next;
};
struct graph
{
	int vertexs;
	struct node **list;//to make array of pointer then *arr[5] we have to mention size
};                     //but we want to create  dynamically so avoid this 
struct graph *creategraphadjacentlist(void);
void display(struct graph*);
void deletegraph (struct graph*);
int main(){
	int option;
	struct graph *holdgraphnode;
	do{
		printf("\n\n1.create graph adjacent list\n2.Display graph\n3.Delete");
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
		}
	}while(option<1000);
return 0;}
struct graph *creategraphadjacentlist(void)
{
	int noofvertex,totalconnectedneighbours,i,neighbour;
	struct node *holdpreviousaddress,*newnode;
	struct graph *graphnode=(struct graph *)malloc(sizeof(struct graph));//graph node created
	printf("\nEnter total no. of vertexes: ");
	scanf("%d",&graphnode->vertexs);
/*sizeof(struct node *) we get size pointer type itself 4
 sizeof(struct node ) we get size 8 because int is 4 and pointer is 4 check struct node
sizeof(*p) we get size of content that p point at.here we allocate doublepointer** array*/
	graphnode->list=(struct node **)malloc(sizeof(struct node *)*graphnode->vertexs);
	//how memory is allocated????
/*malloc created block of memory and(struct node **) typecast into double pointer
suppose user enter vertex 4 so sizeof(struct node *)*graphnode->vertexs will return 16 bit
sizeof(struct node *) will return pointer size ie. 4 because * is use after struct node if
 we dont use then 8 byte would return  because int is 4 and pointer is 4 check struct node
so 4 row will be created list is pointer type of struct node so 16 bit /4 byte=4 byte*/
	for(i=0;i<graphnode->vertexs;i++)
	{
		graphnode->list[i]=NULL;//initializing all pointer to null so if statement work
	}
	for(noofvertex=0;noofvertex < graphnode->vertexs;noofvertex++)
	{
		printf("\nEnter Total no. of neighbours connected to Vertex/node %d: ",noofvertex);
		scanf("%d",&totalconnectedneighbours);
		for(i=0;i<totalconnectedneighbours;i++)//this loop help to make like linked list
		{
			printf("\nEnter neighbour no. %d connected to Vertex \"%d\": ",i+1,noofvertex);
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
			  newnode->vertex=neighbour;
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
 	for(i=0;i<holdgraphnode->vertexs;i++)
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
void deletegraph (struct graph *holdgraphnode)
{//whatever we have created dynamically deleting
	int i;
	struct node *ptr,*temp;
	if(holdgraphnode->list!=NULL)
	{
	for(i=0;i<holdgraphnode->vertexs;i++)
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
//video Graph - 19: Prim's Algo | Minimum Spanning Tree in weighted Graph 
 //VIDEO Graph Representation part 03 - Adjacency List mycodeschool
/*Adjacency list is preferred for representing sparse graphs in the computer’s memory otherwise,
 an adjacency matrix is a good choice when graph is not sparse means more edges
 Example face book has 10^9 billion users then row size=10^9.i have 1000 friends then number of 1s
= 1000 and no. of 0 zeros =10^9 - 1000.Most of the real world graph is sparse.Space consumption of
adjacency matrix is O(v^2) whare as list is O(E) that means E is smaller then v^2 so adjacency list
is better when graph is sparse.
Time complexity finding adjacent node using matrix =O(v) and using list =O(V) wors case
Time complexity finding if two nodes are connected using matrix =O(1) and using list = O(v)
Adjacency list take lesstime 10 miliseconds to find adjacent nodes where as matrix take moretime
 like 16 miniuts and finding if two node are connected matrix is faster then list but list takes
 time in seconds **so overall list is better in terms of space and time
 */

