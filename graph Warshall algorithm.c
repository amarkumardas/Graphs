/*Floyd Warshall algorithm is different from Warshall’s algorithm both is given in pdf
Warshall’s algorithm will just tell us that there is path or not from one node to other node if
there is path from one node to any other node then path matrix will be 1 otherwise 0 means
there is no path**********************

it works both directed and undirected graph with no weight.If graph is weighted then modification
is needed like to make it unweighted we can just set 1 in matrix where there is weight*******

video-> Warshall's Algorithm to Find Path Matrix tutorials point <<<<<<<<<<<<<<<<<<<
Warshall’s algorithm finds PATH matrix of a given graph and that matrix will be of type boolean that
means at the row r at the column c if the value is true or 1 it indicates that from every row to column
there is a path either direct path or through some other nodes and if the path does not exist then that 
particular location will be filled up with 0 or false that means warshalls algorithm GIVE US THE PATH 
MATRIX AND THE MATRIX WILL BE OF BOLLEAN(0 1) SO IT WILL TELL US WHETHER FROM THIS PARTICULAR SOURCE 
VERTEX OR NODE CAN I REACH TO OUR TARGET VETREX so that ans will be obtained at the respective location of
the matrix so this part matrix will be obtained at the end of the execution of warshalls agorithm 

What is transitiVe closure of a graph?*****************************88
A transitive closure of a graph is constructed to answer reachability questions. That is, is there a path
from a node A to node E in one or more hops(path) so this algorithm is used to find transitive colsure
and time complxity is O(v^3) using warshall algo to reduce time we can use DFS traversal to find reachability
and time complexity reduce to O(v^2) code:
 for(i=0;i<n;i++)
 {
 DFS();//we have to check do DFS of every vertex and mark 1 when encounter any node in matrix
 }

Where and Why is it Needed?
1.Finding the transitive closure of a directed graph is an important problem in the following
computational tasks:
2.Transitive closure is used to find the reachability analysis of transition networks representing
distributed and parallel systems.
3.It is used in the construction of parsing automata in compiler construction.
Recently, transitive closure computation is being used to evaluate recursive database queries
(because almost all practical recursive queries are transitive in nature). */
#include<stdio.h>
#include<stdlib.h>//transitive closure alog that is warshall algaorthmm
#define MAX 50
int main(){
	int adjmatrix[MAX][MAX],pathmatrix[MAX][MAX]; 
	int numberofvertex,row,column,k;
	printf("\nEnter number of vertex: ");
	scanf("%d",&numberofvertex);
	printf("\nEnter adjanceny matrix:");
	for(row=0;row<numberofvertex;row++)
    {
    	for(column=0;column<numberofvertex;column++)
    	{
    		printf("\nadjmatrix[%d][%d]:  ",row,column);
    		scanf(" %d",&adjmatrix[row][column]);
		}
	}
for(k=0;k<numberofvertex;k++)//no.of matrix
	{                                     //here path matrix is processed
		for(row=0;row<numberofvertex;row++)
		{
			for(column=0;column<numberofvertex;column++)
			{             //formula
 adjmatrix[row][column]=adjmatrix[row][column] || (adjmatrix[row][k] && adjmatrix[k][column]);
			}      //pathmatrix[row][column] this is directly connected to vertex 
		}
	}
	printf("\nPath matrix are: if 1 that means there is path and 0 means no path \n");
	for(row=0;row<numberofvertex;row++)
    {
    	for(column=0;column<numberofvertex;column++)
    	{
    		printf(" %d ",adjmatrix[row][column]);
		}
		printf("\n");
	}
return 0;}


