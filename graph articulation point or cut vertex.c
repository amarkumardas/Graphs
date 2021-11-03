/*function inside an another function is known as “nested function
Nested function is not supported by C because we cannot define a function within another function 
in C. We can declare a function inside a function, but it’s not a nested function.*/
//video-> Articulation Point in Graph Algorithm Detail | Graph Theory #20

#include<stdio.h>
#include<stdlib.h>   //code is perfectly correct not in youtube 
struct graph  
{//DFS traversal can be start from any vertex  and backedge matrix will produce  right
	int totalvertex,totaledges; //it is undirected graph for directed graph some modification is needed
	int **adjmatrix;
}*g;//global graph pointer
int top=-1;//for stack
void Createadjacencymatrix(void);
void display(void);
void DFSand_creatingmatrixwith_edge(void);
//void pushintostack(int vertex);//since we havedefine inside DFSfunction then no need here to declare
//void popfromstack(void);
//int peepreturn_top_vertex(void);
void articulation_point(int *dfn,int startnode,int**matrixwithbackedge);
int minimum(int *dfn,int i,int **matrixwithbackedge,int *low);
int minof_dfnvalue_ofback_edge(int node,int dfni,int *dfnarr,int **matrixwithbackedge,int *low);
int min_oflow_valuesof_children(int node,int dfni,int *dfnarr,int **matrixwithbackedge,int *low);
int return_dfn_of_valuelinearsearch(int *dfnarr,int value);
int  check_i_haschild_or_not(int i,int **matrixwithbackedge,int *dfnarr);
int main()
{
	int option,*stack;
   do
	 {
	 	printf("\n\n1.Create adjacency matrix.");
	    printf("\n2.Do DFS and create new matrix with back edge and find Articulation point");
	 	printf("\nEnter your option: ");
	 	scanf("%d",&option);
	 	switch(option)//we cant declare variable in switch case only statement is allowed
	 	{
	 		case 1: Createadjacencymatrix();
	 		        display();
	 		break;
            case 2: DFSand_creatingmatrixwith_edge(); 
	 		break;
		 }
	 }while(option<1000);
  return 0;	
}
void Createadjacencymatrix()
{
	int u,v,i;
  	g=(struct graph*)malloc(sizeof(struct graph));//graph node created
  	printf("\nEnter total number of vertex: ");
  	scanf("%d",&g->totalvertex);
  	printf("\nEnter total number of edges: ");
  	scanf("%d",&g->totaledges);
  	/*sizeof(int*) we get size pointer type itself 
    sizeof(*p) we get size of content that p point at.*/ 
  	g->adjmatrix=(int**)malloc(sizeof(int*)*g->totalvertex);
  	for(u=0;u<g->totalvertex;u++)
  	{	//since we want to initialize with 0 so using calloc function
  		g->adjmatrix[u]=(int*)calloc(g->totalvertex,sizeof(int));
	}
	printf("\nEnter pair edge number that connect vertex: "); 
	for(i=0;i<g->totaledges;i++)
	{
		scanf("%d %d",&u,&v);
		g->adjmatrix[u][v]=1;//to make directed graph then  remove next line
		g->adjmatrix[v][u]=1;//to make  undirected graph just use this two line
	}	
}
void display(void)
{
	int i,j;
	if(g->adjmatrix==NULL)
	{
		printf("NO graph create graph");
	}
	else
	{
	printf("Created Matrix: \n");
	for(i=0;i<g->totalvertex;i++)
	{
		for(j=0;j < g->totalvertex;j++)
		{
		  printf(" %d",g->adjmatrix[i][j]);
		}
		printf("\n");
	}
   }
}
void DFSand_creatingmatrixwith_edge(void)//it is preorder traversal
{
//we dont need linked list stack because size of stack will be exactly equal to number of vertex
	int *stackarray=(int*)malloc(sizeof(int)*g->totalvertex);
	
	void pushintostack(int vertex)
{
   	stackarray[++top]=vertex;//for this code this is enough
	
   /*	if(top==MAX-1)
	{
		printf("stack overflow");
	}
	else//here stackoverflow will never occur because stack size  will be exactly equal to vertex
	{
	   stackarray[++top]=vertex;		
	}*/
}
void popfromstack()
{
  top--;//for this code this is enough
	
	/*if(top==-1)
	{
		printf("Stack underflow");
	}
	else
	return stackarray[top--];*/ 	
}
int peepreturn_top_vertex()
{
   return stackarray[top];//for this code this is enough
	/*if(top==-1)
	{
	   printf("no vertex");
	}
	else
	return stackarray[top];*/	
}
int startnode,top_node_instack,flag,i,j,increment=0;;	
//we want visited array that is size of vertex and initialize to 0 so calloc is best function
	int *visitedarray=(int*)calloc(g->totalvertex,sizeof(int));
	int *dfnarr=(int*)malloc(sizeof(int)*g->totalvertex);//it will store sequence of traversal node
	
	int **dfsmatrix=(int**)malloc(sizeof(int*)*g->totalvertex);//creating 2d array
	for(i=0;i<g->totalvertex;i++)
	{//since we want to initialize with 0 so using calloc function
		dfsmatrix[i]=(int*)calloc(g->totalvertex,sizeof(int));
	}
	
	printf("\nEnter starting vartex to start traversal: ");
    scanf("%d",&startnode);
    pushintostack(startnode);
    visitedarray[startnode]=1;//it means visited
    //printf(" %d",startnode);//if you want to print traversal node then we can use it to see
    dfnarr[increment++]=startnode;//here in dfnarray node is stored according to dfs traversal
	
    while(top!=-1)//checking stack is empty or not
    {
      flag=0;
      top_node_instack=peepreturn_top_vertex();
      for(i=0;i<g->totalvertex;i++)
      {                                      // visitedarray[i]==0 which means node is not visited
      	if(g->adjmatrix[top_node_instack][i]==1 && visitedarray[i]==0)
      	{
      	  flag=1;
      	  //printf(" %d",i);//if you want to print traversal node then we can use it to see
      	  dfsmatrix[top_node_instack][i]=1;//mean edgeis conectedduring traversal we are makingmatrix
      	  dfsmatrix[i][top_node_instack]=1;//means edge is connected since it is directed graph
      	  dfnarr[increment++]=i;//here in dfnarray node is stored according to dfs traversal
      	  pushintostack(i);
          visitedarray[i]=1;//it means visited
          break;//terminate for loop we have to push any one vertex into stack from graph
		}
	  }
	  //instead of flag we can check i==wholegraphmatrix->vertex so flag variable not needed
	  if(flag==0)
	  {
	  	popfromstack();//when the node neighbours all visited then this will work
	  }
	}
	printf("\nDFS matrix after traversal\n");//for information
	for(i=0;i<g->totalvertex;i++)
	{
	  for(j=0;j<g->totalvertex;j++)
	  {
		printf(" %d",dfsmatrix[i][j]);
      }	
      printf("\n");
	}
	printf("\nValue in dfnarra according to DFS traversal we have to take in reverse order ");
	for(i=0;i<g->totalvertex;i++)     //for checking by hand
	{
		printf(" %d", dfnarr[i]);
	}
	//from here new matrix will be created
	//Back edge are those edge that are not present in DFS traversal but present in original matrix 
	for(i=0;i<g->totalvertex;i++)//this will update the backedge
	{
		for(j=0;j<g->totalvertex;j++)
	{
/*when matrix is not matched thatmeans in dfsmatrix edge is missingso that edge is filled using which
dfn is greater dfnarray store node accordingly to dfs traversal that indicate which node come first*/

	if(g->adjmatrix[i][j] != dfsmatrix[i][j])//comparing two matrix and producing new matrix
	{
	//return_dfn_of_valuelinearsearch function will return dfn of any value it will find 
	 //occurate dfn no.   	                //for information                
	if( return_dfn_of_valuelinearsearch(dfnarr,i) > return_dfn_of_valuelinearsearch(dfnarr,j) )
	  {
	  //>=not required because it will be different due to vertex is different
	//we should use > greater than because back edge iscreated bycomparing which dfnarray is greater
	      printf("\n Back edge location(row %d column %d)", i,j);//thiwil tell edge location
		  dfsmatrix[i][j]=7;//7 indicate  backedge                          
	  }                	
    }
	}
	}
	printf("\n\nUpdated matrix with edge value 7 indicate backedge\n");
	for(i=0;i<g->totalvertex;i++)//for informataion
	{
	  for(j=0;j<g->totalvertex;j++)
	  {
		printf(" %d",dfsmatrix[i][j]);
      }	
      printf("\n");
    
      
	}
	articulation_point(dfnarr,startnode,dfsmatrix);//dfsmatrix is matrix with backedge
}
int return_dfn_of_valuelinearsearch(int *dfnarr,int value)
{//this function will return position of value that is dfn of value
 int i;
 for(i=0;i<g->totalvertex;i++)//only linear search algo to find node dfn value if we use binary
 {                            //search then nodes will be arranged so this will give wrong dfn vslue
 	if(value==dfnarr[i])
 	{
 	    return i;	
	 }
 }	
}

void articulation_point(int*dfnarr,int startnode,int**matrixwithbackedge)//passdouble pointerbecause
{                                                           //dfsmatrix is double pointer 
int *low=(int*)malloc(sizeof(int)*g->totalvertex);
int i,j,dfnof_j,root=0,counter=0,flag;

for(i=g->totalvertex-1;i>=0;--i)//all low value will be collected in low array
{
	low[i]=minimum(dfnarr,i,matrixwithbackedge,low);//this func will fill low value to low array
}

printf("\nreverse back low: ");//information
for(i=g->totalvertex-1;i>=0;--i)
{
	printf(" %d",low[i]);
}
 
printf("\nArtuculation point: ");
 for(i=0;i<g->totalvertex;i++)//this will find root has how many child if root has 1 child then
 {//root will have ateast 1 child for loop will run n-2 times if root has 2 child then loop will
 	if(matrixwithbackedge[startnode][i]==1)                                       // run n-1
 	{
 	     counter++;
		 if(counter==2)	
		 {
		 	break;
		 }	 
	 }
 }
 if(counter==1)
 {
 	root=1;
 	printf("\nroot has only one child");
 }
 else// if (counter >= 2)
 {
 	root=0;
 	printf("\nRoot has 2 child");
 }   /*if root has 1 child then skip and if node has no child then also skip because it would not
       be an articulation*/
for(i=g->totalvertex-1;i>=root;--i)//root value this will skip if root has only one child 
{
  flag=check_i_haschild_or_not(i,matrixwithbackedge,dfnarr);//global func it will return 0 or 1 
  /*if node has no child then we can skip that node because that node will definately not be an
   articulation point and which save time so when flag ==1 then it means node has atlest 1 child*/
  if(flag==1)
  {
   for(j=0;j<g->totalvertex;j++)//dfnarr[i] it will retrun what node is stored in that index i 
	{
	   dfnof_j =return_dfn_of_valuelinearsearch(dfnarr,j);//it return dfn of ant node here j is node
	   if(matrixwithbackedge[dfnarr[i]][j]==1 && i < dfnof_j )//dfnof_j is dfn of j i is also dfn 
 	  {	             //checking children with dfn value                             //of dfnarr[i]
  	     if(i<=low[dfnof_j])//we are checking dfn of i with it child low value
 	     {
 	      //printf("\ni=%d <= %d low[k]",i,low[k]);
	     printf("\nA= %d",dfnarr[i]);//dfnarr[i] it will retrun what node is stored in that index i 
	                                   //and that wil be articulation point
	      break;//if it has two child and two child satisfy i<=low[dfnof_j] then it will produce two 
		                  //same articulation point so to produce only one point break is used.
	     }
	   }
    }
   }
}
}
int minimum(int *dfnarr,int dfnof_u,int **matrixwithbackedge,int *low)
{
	int a,b,c,min;
	a=dfnof_u;
	b=min_oflow_valuesof_children(dfnarr[dfnof_u],dfnof_u,dfnarr,matrixwithbackedge,low);
	c=minof_dfnvalue_ofback_edge(dfnarr[dfnof_u],dfnof_u,dfnarr,matrixwithbackedge,low);
	printf("\n%d %d %d",a,b,c);//information tells which one is minimum
	 if(a<=b &&a<=c)//<= is mportant becaue when a=0 b=0 c=99 then 99 will be taken as low value when
	 {                                     // we dont ues =  so to avoid this <= is important to give
	 	min=a;
	 }
	 else if(b<=a&&b<=c)
	 {
	 	min=b;
	 }
	 else
	 {
	 	min=c;
	 }
	return min;
}
int min_oflow_valuesof_children(int node,int dfnof_u,int *dfnarr,int **matrixwithbackedge,int *low)
{//if there r more then 1 children then minimum low values is taken
 int i,flag=0,min=99,holddfn;//min should be infinity
 for(i=0;i<g->totalvertex;i++)
 {//[node][i]==1 means there is children.dfnof_u is dfn of node
   holddfn=return_dfn_of_valuelinearsearch(dfnarr,i);
 	if(matrixwithbackedge[node][i]==1 && dfnof_u < holddfn )//dfnarr[i] it will give dfn of i node
 	{
 		flag=1;
 		if(min > low[holddfn])//smallest number
 		{
 			min=low[holddfn];//smallest low number will be taken
		} 
	 }
 }
 if(flag==1)
 {
 	return min;
 }
 if(flag==0)
 {
 	return 99;//infinity
 }	
}
int minof_dfnvalue_ofback_edge(int node,int dfnof_u,int *dfnarr,int **matrixwithbackedge,int *low)
{//when there are two back edge then only minimum dfn is taken 
int i,flag=0,min=99,holddfn;
 for(i=0;i<g->totalvertex;i++)
 {
 	if(matrixwithbackedge[node][i]==7 )//7 indicate that it is backedge
 	{
 		flag=1;
 		holddfn=return_dfn_of_valuelinearsearch(dfnarr,i);
 		if(min >  holddfn)//dfnarr[i] it will give dfn number
 		{
 			min=holddfn;
		 }	 
	 }
 }
 if(flag==1)
 {
 	return  min;
 }
 if(flag==0)
 {
 	return 99;//infinity
 }		
}
int  check_i_haschild_or_not(int i,int **matrixwithbackedge,int *dfnarr)
{
	int j,k,flag=0 ;
	for(j=0;j < g->totalvertex;j++)
	{
		if(matrixwithbackedge[dfnarr[i]][j]==1 && i < return_dfn_of_valuelinearsearch(dfnarr,j) )
		{
			 flag=1;
	//printf("\ni=%d has child %d so it will execute",i,j);//for information it will tell child
			 break;	
		}
	}
	if(flag==1)
	{
		return 1;// means i has child and it is not leaf node
	}
	else//if(flag==0) means i is leaf node
	{
		return 0;
	}
}
/*
Articulation point is vertex and bridges is edges
Bridges in a graph
An edge in an undirected connected graph is a bridge iff removing it disconnects the graph. 
For a disconnected undirected graph, definition is similar, a bridge is an edge removing
which increases number of disconnected components.
Like Articulation Points, bridges represent vulnerabilities in a connected network and are
useful for designing reliable networks. For example, in a wired computer network, an
articulation point indicates the critical computers and a bridge indicates the critical 
wires or connections.*/


