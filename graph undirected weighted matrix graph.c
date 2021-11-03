#include<stdio.h>//for weighted graph only little change required 95% same as adjacency matrix
#include<stdlib.h>
struct graph
{
	int vertex,edge;
	int **matrix;
};
#define INFINITY 77
struct graph *createadjmatrixofgraph(void);
void display(struct graph *);
void deletegraph(struct graph *);
int main()
{
  	struct graph *wholegraphmatrix;
	int option;
	do
	{
		printf("\n1.Create Graph\n2.Display\n3.Delete");
		printf("\nEnter oyur option: ");
		scanf("%d",&option);
		switch(option)
		{
			case 1:wholegraphmatrix=createadjmatrixofgraph();
			break;
			case 2:display(wholegraphmatrix);
			break;
			case 3:deletegraph(wholegraphmatrix);
			break;
		}
	}while(option<10);
	getch();
	return 0;	
}
struct graph *createadjmatrixofgraph(void)
{
	int u,v,i,weight;
	struct graph *g=(struct graph*)malloc(sizeof(struct graph));
	printf("\nEnter Total number of Nodes/vertex: ");
	scanf("%d",&g->vertex);
	printf("\nEnter Total number of Edges:");
	scanf("%d",&g->edge);
	
		
	//sizeof(int*) we get size pointer type itself 
	//sizeof(*p) we get size of content that p point at.
	g->matrix=(int**)malloc(sizeof(int*)*g->vertex);//here we allocate double pointer array
	/*for(i=0;i<g->vertex;i++)
	{
		g->matrix[i]=(int*)malloc(sizeof(int)*g->vertex);
	}*/
	
     for(u=0;u<g->vertex;u++)//initializing 2D array to INFINITY
      {
	    g->matrix[u]=(int *)malloc(sizeof(int)*g->vertex); //creating 1D array and initializing 2D array
    	for(v=0;v<g->vertex;v++)
    	{
    		g->matrix[u][v] = INFINITY;
		}
	  }  
	for(i=0;i<g->edge;i++)
	{
		printf("\nEnter %d.pair edge number that connect vertex: ",i+1);
		scanf("%d %d",&u,&v);
		printf("\nEnter weight of edge %d %d = ",u,v);//for weighted graph only here is different
		scanf("%d",&weight);
		g->matrix[u][v]=weight;//to make directed graph then  remove next line
		g->matrix[v][u]=weight;//to make  undirected graph just use this two line
	}
	return g;
}
void display(struct graph *wholegraphmatrix)
{
	int i,j;
	if(wholegraphmatrix->matrix==NULL)
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
		  printf(" %d",wholegraphmatrix->matrix[i][j]);
		}
		printf("\n");
	}
   }
}
void deletegraph(struct graph *wholegraphmatrix)
{
	int i;
	for(i=0;i<wholegraphmatrix->vertex;i++)
	{
		free(wholegraphmatrix->matrix[i]);//we have created 1d array so deleting address
	}
	free(wholegraphmatrix->matrix);//we have created 2d array so deleting address
	wholegraphmatrix->matrix=NULL;//and initializing to null struct member adj
}
