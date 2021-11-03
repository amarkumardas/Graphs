#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
struct graph//here this is datatype when datatype is created no memory is allocated
{           //when variable is created then only memeory is allocated
	int edge,vertex;
	int **adj;
};//-> is use to access struct members when struct pointer variable is created ie.struct graph *p;
  //p->edge. dot (.) is use when normal struct variable is created ie.struct graph p
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
	int u,v,i;
	struct graph *g=(struct graph*)malloc(sizeof(struct graph));//graph node created
	if(!g)//or if(g==NULL)
	{
		printf("Memory not allocated");
		exit(0);//since memory not allocated then program should terminate
	}
	printf("\nEnter number of Nodes/vertex:");
	scanf("%d",&g->vertex);
	printf("\nEnter number of Edges:");
	scanf("%d",&g->edge);
	
	//sizeof(int*) we get size pointer type itself 
	//sizeof(*p) we get size of content that p point at.
	
	g->adj=(int **)malloc(sizeof(int*)*g->vertex);//here we allocate double pointer array
	  
	    for(i=0;i <g->vertex;i++)//creating 1D array and initializing 2D array
      {
    	 g->adj[i]=(int *)malloc(sizeof(int)*g->vertex);//this for loop  can be avoided
	  }
	  
  //we want matrix to be initialze with 0 so we can use calloc in this case calloc will
  // give better performance then malloc 
                                          
    for(u=0;u<g->vertex;u++)//initializing 2D array to zero 0
    {//g->adj[u]=(int *)malloc(sizeof(int)*g->vertex);// can be written to avoid upper forloop
    	for(v=0;v<g->vertex;v++)
    	{
    		g->adj[u][v]=0;
		}
	}
	printf("\nEnter pair edge number that connect vertex: ");
	for(i=0;i<g->edge;i++)
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
void deletegraph(struct graph *wholegraphmatrix)
{
	int i;
	for(i=0;i<wholegraphmatrix->vertex;i++)
	{
		free(wholegraphmatrix->adj[i]);//we have created 1d array so deleting address
	}
	free(wholegraphmatrix->adj);//we have created 2d array so deleting address
	wholegraphmatrix->adj=NULL;//and initializing to null struct member adj
}
