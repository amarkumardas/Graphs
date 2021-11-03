/*Floyd Warshall algo works for negative edge but not on negative cycle, whereas Dijkstra’s algorithm
 don’t work for negative edges.Floyd Warshall Algorithm is an example of all-pairs shortest path
 algorithm meaning it computes the shortest path between all pair of nodes.TIME COMPLEXITY O(n^3)n=nodes
 
 It will aslo work on unweighted undirected graph but code have to be modified but it is useless
->This algorithm works for both the directed and undirected weighted graphs. But, it does not work 
  for the graphs with negative cycles (where the sum of the edges in a cycle is negative)

video->4.2 All Pairs Shortest Path (Floyd-Warshall) - Dynamic Programming
video->/6.15 Floyd Warshall Algorithm All Pair Shortest Path algorithm | data structures and algorithms
 
Floyd-Warshallalgo can alsobe implemented using dijkastraalgo but time willincrease from O(n*2) to O(n^3)
when graph is dence means not sparse then this algorithm is better to use or if graph is not dence
means sparse then dijkstra algorithm is better to use if graph does not contain negative weight.*/
#include<stdio.h>
#include<stdlib.h>      //**it is also known as all pair shortest path.It is dynamic programming*******
#define INF 99       
struct garph
{
	int totalvertex,totaledge;
	int **adjmatrix;
}*g;//global pointer graph by default it is initilized to NULL
void createadjmatrixofgraph(void);
void display(void);
void deletegraph(void);
void floyedwarshallmodified(void);
int main(){	
	int option;
	do
	{
printf("\n\n1.Create Graph\n2.Display\n3.Delete graph\n4.Floyedwarshallmodified or allpair shortestpath");
		printf("\nEnter your option: ");
		scanf("%d",&option);
		switch(option)
		{
		case 1:createadjmatrixofgraph();break;case 2:display();	break;case 3:deletegraph();break;
		case 4:floyedwarshallmodified();break;	
		}
	}while(option<10);
	getch();
	return 0;}
void createadjmatrixofgraph(void){
	int i,u,v,weight;
  g=(struct garph*)malloc(sizeof(struct garph));//graph node is created
  printf("\nEnter total number of vertex: ");
  scanf("%d",&g->totalvertex);
  printf("\nEnter total number of edges: ");
  scanf("%d",&g->totaledge); 
/*sizeof(int*) we get size pointer type itself 
sizeof(*p) we get size of content that p point at*/

  g->adjmatrix=(int**)malloc(sizeof(int*)*g->totalvertex);//double pointer created
  for(u=0;u < g->totalvertex ;u++)//initializing 2D array to INFINITY
  {
g->adjmatrix[u]=(int*)malloc(sizeof(int)*g->totalvertex);//creating 1Darray and initializing 2Darray
  	  for(v=0;v<g->totalvertex;v++)
  	  {
  	  	if(u==v)
		{
		  g->adjmatrix[u][v]=0;//diagonals will have to be 0 because no self loops	
		}
		else
		{
  	  	g->adjmatrix[u][v]=INF;//initializing matrix to INFinity except diagonals.when vertex isconnected
  	    }//then weight will be place and not connected vertex automaticallyinfinity will be placed due to
	  }                                                                                  //this statement
  }
  	for(i=0;i<g->totaledge;i++)
	{
		printf("\nEnter %d.edge pair like(0 1)number that connect vertex: ",i+1);
		scanf("%d %d",&u,&v);
		printf("\nEnter weight of edge %d %d = ",u,v);//for weighted graph only here is different
		scanf("%d",&weight);
		g->adjmatrix[u][v]=weight;//to make directed graph then  remove next line
	//	g->adjmatrix[v][u]=weight;//to make  undirected graph just use this two line
	}
}
void display(void){
	if(g->adjmatrix!=NULL){
	int i,j;
	printf("Matrix: \n");
	for(i=0;i<g->totalvertex;i++)
	{
		for(j=0;j<g->totalvertex;j++)
		{
			printf(" %d",g->adjmatrix[i][j]);
		}
		printf("\n");
	}
    }
    else{
    	printf("\nNo Graph create graph");
	}
}
void deletegraph(void){
	int i;
	if(g->adjmatrix!=NULL)
	{
	for(i=0;i<g->totalvertex;i++)
	{
		free(g->adjmatrix[i]);//we have created 1d array so deleting address
	}
	free(g->adjmatrix);//we have created 2d array so deleting address
	g->adjmatrix=NULL;//and initializing to null struct member adj
    }
    else{
    	printf("\nNO graph to delete");
	}
}
void floyedwarshallmodified(void)
{//video->4.2 All Pairs Shortest Path (Floyd-Warshall) - Dynamic Programming
int row,column,k;
	for(k=0;k<g->totalvertex;k++)
	{
		for(row=0;row<g->totalvertex;row++)
		{
		 for(column=0;column<g->totalvertex;column++)
		 {//which is minimum that will be inserted into  matrix
		   if(g->adjmatrix[row][column] <= g->adjmatrix[row][k] + g->adjmatrix[k][column])
			{//if 7 <= 10; then 7 will be inserted in matrix same 
			  g->adjmatrix[row][column] = g->adjmatrix[row][column];	
			}
		   else
			{
			  g->adjmatrix[row][column] = g->adjmatrix[row][k] + g->adjmatrix[k][column];
			}
		 }
		}
	}
	printf("\nShortest path matrix are:\n");
	for(row=0;row<g->totalvertex;row++)
	{
		for(column=0;column<g->totalvertex;column++)
		{
			printf(" %d",g->adjmatrix[row][column]);
		}
		printf("\n");
	}
}

