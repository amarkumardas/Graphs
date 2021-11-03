//to search element in fibonscci heap time complexity is O(n) n=no. of elements
#include<stdio.h>//fibonacci heap can be make min heap or max heap that follow exactlyheap property
#include<stdlib.h>//itis collectionof trees if itis min heap then child willbe greater & parent will
#include<math.h>//video                                                                //be smaller
//DAA52: Fibonacci Heap Operations| Extract min in fibonacci heap| FIB-HEAP-EXTRACT-MIN(H) in Hindi
struct node
{
	int element,degree;  
	struct node *parent,*left,*right,*anychild;
	char mark;// Black or white indicate mark of the node and itsave space as char data isof 1 byte
	char c;//it will help while finding element in heap means reduce time.it indicate last node
	                                                    //due to doubly linked list we need this
};
struct stack//stack using linked list
{
 struct node *address;
 struct stack *next;	
};
int count;
struct stack *top=NULL;
void push(struct node *node_address);
void pop(void);//her pop operation is little bit different it will pop once all the node
int count_nodes=0;//to get log value
struct node *min=NULL;
void insert_into_fiboheap(int element);
void displayheap();
void find_minimumnode_inheap(void);
struct node *extract_minimum_node(void);
void cosolidate(void);//cosolidate means taking action to make someting strong 
int count_degree(void);//means number of children
void fibo_link(struct node *min,struct node *arr_degreeptr);
void set_minpointer_to_minvalue(void);
void update_everynode_parent(struct node *child);//when child node will be added to rooted 
                                  //doubly link list then its parent should be set to NUL
struct node* search_elementinheap(int element);
struct node* reducetime_andfind_element(int element,struct node *node);
struct node* decrease_element(int element,int elementdecrease);
void cut(struct node *search_element,struct node *parent);
void cascading_cut(struct node *parent);
void delete_element(void);
int main()                         
{
	int option,element,elementdecrease;
	struct node *search_element,*minimumnode,*address_ofdecreasenode;
	do
	{
	    printf("\n\n1.create FibonacciHEAP\n2.Minimum Node in heap");
		printf("\n3.Extract minimum node.\n4.Find element in heap.");
		printf("\n5.Display all element.\n6.Decrease element");
		printf("\n7.Delete element");
		printf("\nEnter your option: ");
		scanf("%d",&option);
		switch(option)
		{
			case 1: printf("\nEnter -1 to STOP:");
			        printf("\nEnter elements: ");
			        scanf("%d",&element);
			        while(element!=-1)
			        {
			         insert_into_fiboheap(element);
			         printf("\nEnter elements: ");
			         scanf("%d",&element);
			        }
			        printf("\nNumber of nodes: %d",count_nodes);
			break;
			case 2: find_minimumnode_inheap();//or show top node of heap
			break;
		    case 3: minimumnode=extract_minimum_node();
		             if(minimumnode != NULL)//NULL indicate heap is empty
		             {
		             	printf("\nMinimum node: %d",minimumnode->element);
					 }
			break;
			case 4: if(min!=NULL)
                   {
			        printf("Enter element to be searched: ");
			        scanf("%d",&element);
			        search_element=search_elementinheap(element);//function will return address
			        if(search_element==0)
			        {
			        	printf("\nElement %d not found in heap",element);
					}
					else
			        printf("\nFound element %d",search_element->element);
			       }
			       else
			       {
			       	printf("\nHeap is empty");
				   }
			        break;
			case 5 :displayheap();
			        break;
			case 6 :printf("Enter element that is present in heap to Decrease: ");
                    scanf("%d",&element);
                    printf("\nEnter decrease value to replace element %d with: ",element);
   	                scanf("%d",&elementdecrease);
			        address_ofdecreasenode=decrease_element(element,elementdecrease);
			        if(address_ofdecreasenode != NULL)
			        {
			        	printf("\nUpdated to %d",address_ofdecreasenode->element);
					}
			        break;
			case 7 :delete_element();
			        break;
			    
		}
	}while(option<1000);
	return 0;
}
void insert_into_fiboheap(int element)//we have to insert newnode left of min node always
{
  struct node *newnode=(struct node*)malloc(sizeof(struct node));
  	newnode->element=element;
  	newnode->mark='W';//w for white means not marked it is required for func. Decreasing key
  	newnode->c='N';//it will heplp while finding element in heap means reduce time in find func.
	newnode->parent=NULL;
  	newnode->left=newnode;//point to itself due to double linked list
  	newnode->right=newnode;//point to itself due to doubly linked list
  	newnode->anychild=NULL;
  	newnode->degree=0;//0 means no degree updated
  	if(min!=NULL)
  	{
  	   min->left->right=newnode;//tricky code
  	   newnode->right=min;       //doubly linked
  	   newnode->left=min->left;   //follow in sequence order
  	   min->left=newnode;
		 if(min->element > newnode->element)//shifting min pointer according to minimum value
		 {//>= not used because if it is equal while inserting it will at top so no need to
		  //shift min pointer
		 	min=newnode;
		 }	
	}
	else
	{
		min=newnode;
	}
	++count_nodes;//it count number of nodes 
}
void find_minimumnode_inheap(void)//or show top node O(1)
{
	if(min!=NULL)
	{
		printf("\nMinimum node in heap is O(1): %d ",min->element);	
	}
	else
	{
		printf("\nHeap is empty");
	}
 
}
struct node* extract_minimum_node(void)//means delete min or find min node O(log n)
{
if(min !=NULL)//if min is null means heap is empty
{
 struct node *holdmin_node=min,*hold_leftnode,*hold_rightnode ;
 if(min->left==min && min->right==min)//meansthere is only one node because it is pointing to itself
 {//there are two cases
	if(min->anychild!=NULL)//means it contain child
	{
	  min=min->anychild;//now min can either have 1 node or 2 node if min has only one node then 
	                    //return holdmin_node->element; will work if 2 node then consolidate
	  min->parent=NULL;//if min has only 1 node then parent will be updated as it is added to
	                                                                //rooted doubly linked list**
	  if(min->left!=min && min->right!=min)//means there are more then two nodes or only two nodes
	  {
	   update_everynode_parent(min);//updating parent of every node since it has more than 2 node 
	   cosolidate();//when there is 2 or more than 2 node then only cosolidate function work
      }
	}
	else if(min->anychild==NULL)//means no child that means only one node is in heap so set min=NULL
	{//when there is 1 node then no need to consolidate so just returning 
	  min->parent=NULL;//since it is only one node in heap***
	  min=NULL;//heap is empty
	}
	--count_nodes;//keep track of number of nodes
   return holdmin_node;//min and holdmin_node are same this is not required because at last
 }                              //same satement is written
 else if(min->left!=min && min->right!=min)//means there are more then two nodes or only two nodes
 {                                           //if it has one child then also it work
	if(min->anychild!=NULL)//means it contain children if it not contain any child then else if work
	{                             
	  update_everynode_parent(min->anychild);//since it contain child so updating parent of every
	                                    //node as it will be added to rooted doubly linked list
	  hold_rightnode=min->right;
	  hold_leftnode=min->left;
	  /*this algo is like connecting two circle it can be done with using two pointer variable*/  	
	  hold_rightnode->left=min->anychild->left;//this line is written first to avoid creating
	  min->anychild->left->right=hold_rightnode;                                    //newnode
	  hold_leftnode->right=min->anychild;
	  min->anychild->left=hold_leftnode;
	  
	  --count_nodes;//one node is removed from heap so number of node is decreased
	 /*this above code is optimised and below code uses extra pointer ie.holdnode so we have
	 remove extra pointer in above code but both works just below code require extra pointer
	 hold_leftnode->right=min->anychild;
	 holdnode=min->anychild->left;//hold child left pointer
	 min->anychild->left=hold_leftnode;
	 hold_rightnode->left=holdnode;
	 holdnode->right=hold_rightnode;*/
	 }
	 else if(min->anychild==NULL)//when min node does not contain any child then it will work
	 {/*suppose if there are two nodes and each node dont have child then this function will
	  make 2 nodes as 1 node then cosolidate func. should not work when there is only 1 node 
	  in heap also we dont know weather it has 2 or more than 2 child due to this function
	  cosolidate(); function is under if statement with condition ckecking more then 2 child*/
	  //here no need to update parent node because since it has no child then nothing is added
	   hold_rightnode=min->right;//to rooted doubly linked list 
	   hold_leftnode=min->left;//it can be done with using two pointer variable like hold_rightnode&
	   hold_leftnode->right=hold_rightnode;                                         //hold_rightnode
	   hold_rightnode->left=hold_leftnode;
	   
	   --count_nodes;//here also one node is removed from heap so number of node is decreased
	 }  
		min=min->right;//min node have move to next node now it is pointing to next node min is
	                 //updated and it is global pointer so no need to pass to cosolidate() func
   if(min->left!=min && min->right!=min)//means there are more then two nodes or only two nodes
	{                                      //in heap
	   cosolidate();//when there is 2 or more than 2 node then only cosolidate function work
    }
 }
 return holdmin_node;//holdmin_node contain minpointer which should be deleted but we are
}//if close bracket                    // not deleting we are returning element  so it is returned
else
{
	printf("\nHeap is empty");
	return NULL;//indicate heap is empty
}
}//end of functtion

void cosolidate(void)//this function will work when ther is more than two node or exactly two node
{                     //if node is only one this function fails not possible to consolidate 1 node
   int i,k,degree;
   struct node *arr_degreeptr;
    i=log2(count_nodes);//with base 2
    i=i+1;//if i value is 3 then we want array index 0 to 3 so 1 is added extra to get index 3
	struct node *arr[i];//array of pointers
	for(k=0;k<i;k++)
	{
	  arr[k]=NULL;//initializing array of pointers to NULL 	
	}
	do
	{
	degree=count_degree();//while counting degree min node is not changed but node degree is updated
	while(arr[degree]!=NULL)
	{
		 arr_degreeptr=arr[degree];	 
    /* we have used here  <= and >=  and also in fibolink function so if there is duplicate number
	it will consolidate and give us right ans even if there is same number present in fibo heap*/
	 
		 if(min->element <= arr_degreeptr->element)//when min is smaller then no need to move min
		 {                                 //pointer operation is performed with same minpointer
		    fibo_link(min,arr_degreeptr);//if we dont pass min pointer then also work because it is
			arr[degree]=NULL;                                                     //global pointer
			degree=count_degree();//updating degree of min pointer
		 }
		 else if(min->element >= arr_degreeptr->element)//when min is greater then have to move min
		 {                                                                               //pointer
		 	fibo_link(min,arr_degreeptr);
		 	arr[degree]=NULL;
		 	min=arr_degreeptr;//changing min pointer because min node is greater so min pointer
		 	degree=count_degree();//updating degree of min point     //should point to low value
		 }	 
	}          //all node by default degree is 0**********
	arr[degree]=min;
	min=min->right;//when arr is NULL then  min pointer is moved to next node
   }while(min!=arr[min->degree]);//whenever arr pointer match with min then terminate otherwise	it
                       //will run infinite.It means there is no root with same degree so terminate
                       
  set_minpointer_to_minvalue();//after consolidate min pointer would not be at low value so this
}                           //function search smallest value and set min pointer to that low value
void fibo_link(struct node *min,struct node *arr_degreeptr)
{//we can make this code shorter
	struct node *holdchild;
   if(min->element <= arr_degreeptr->element)
   {//since min node is smaller so arr_degreeptr node is made as child 
   
   arr_degreeptr->right->left=arr_degreeptr->left;//updating root doubly linked list
   arr_degreeptr->left->right=arr_degreeptr->right;
   arr_degreeptr->right=arr_degreeptr;//after removing it should point to itself
   arr_degreeptr->left=arr_degreeptr;//pointing to itself
   
	  if(min->anychild!=NULL)//means min node has child node is needed to to link like doubly link
	  {//this code is just like adding newnode in fibonacci heap like insertion check insertionfunc
	  
		holdchild=min->anychild;//here holdchild is like min node and arr_degreeptr is like newnode
		arr_degreeptr->parent=min;//updating arr_degreeptr parent as it will be down the root node
		holdchild->left->right=arr_degreeptr;//its like insertion in fibonacci heap tricky 
		arr_degreeptr->right=holdchild;
		arr_degreeptr->left=holdchild->left;
		holdchild->left=arr_degreeptr;
	  }
	  else if(min->anychild==NULL)//means min node has no child
	  {
	  	min->anychild=arr_degreeptr;//since in has no child so updating min child
	  	arr_degreeptr->parent=min;//updating parent
	  }
   }
   else if(min->element >= arr_degreeptr->element)
   {//since min node is greater so arr_degreeptr node is made parent and min node as child
   
   min->right->left=min->left;//updating root doubly linked list
   min->left->right=min->right;
   min->right=min;//after removing it should point to itself
   min->left=min;//pointing to itself
   
   	 if(arr_degreeptr->anychild!=NULL)//means it contain child
   	 {//here holdchild is like min node and min node is like newnode
   	 	holdchild=arr_degreeptr->anychild;
   	 	min->parent=arr_degreeptr;//updating parent
   	 	holdchild->left->right=min;
   	 	min->right=holdchild;
   	 	min->left=holdchild->left;
   	 	holdchild->left=min;
	 }
	 else if(arr_degreeptr->anychild==NULL)//it does not contain child
	 {
	 	arr_degreeptr->anychild=min;//making min as child
	 	min->parent=arr_degreeptr;//updating min parent
	 }
   }	
}
int count_degree(void)
{
	int countdegree=1;//if min node contain 1 child then while condition fails and directly return 1
	struct node *nextnode;
	 nextnode=min->anychild;
	if(min->anychild!=NULL)//means it contain child
	{
	  	while(nextnode->right!=min->anychild)
	  	{
	  	  countdegree++;//updating count
		  nextnode=nextnode->right;		
		}
		min->degree=countdegree;//updating degree of min pointer 
		return countdegree;
	}
	else if(min->anychild==NULL)//means min does not contain anychild
	{//not required else if because we have set every child as 0 while creating heap so
	  //same thing is doing again so not required but have to return something
		min->degree=0;
		return 0;//0 degree means no child
	}//if u remove else if statement then add this line else return 0;
}
void set_minpointer_to_minvalue(void)
{/*this function will set min pointer to min value because after cosolidation min pointer
  would not be at min value so it will set at right smallest value.it works even there is
  only one node */
   	 struct node *holdminode=min,*minimum_node=min;
   	 do
   	 {//at first it will fail because it will check like 3 > 3 which is false
   	 	if(minimum_node->element > holdminode->element)
   	 	{
   	 	  minimum_node = holdminode;
		}
		holdminode=holdminode->right;
	 }while(holdminode != min);
	 
	 min=minimum_node;//updating min pointer
}
void update_everynode_parent(struct node *child)
{//this function is required so that decreasing key funtion work correctly because
 //in that function parent node is checked so this function update parent when node 
 //is added to rooted doubly linked list because rooted liked list is at top so parent=NULL
  	struct node *holdchild_node;
  	child->parent=NULL;/*initially this node is updated if this node is not linked to other
    node then this indicate it is only one node so while loop condition will fail but this
    child parent is updated as it will be added to rooted doubly linked list*/ 
  	holdchild_node=child->right;
  	while(holdchild_node != child)
  	{
  		holdchild_node->parent=NULL;//UPdating parent=NULL
  		holdchild_node=holdchild_node->right;
	}
}

struct node* search_elementinheap(int element)//Find element in heap it is like inorder traversal
{/*disadvantage when searchelement is greater then all element inheap then time= O(n) it will search
 all element present in heap and at last program terminate as element not found.
search_element in heap Time complexity is O(logn)*/
 
  struct node *node=min;
if(element >= min->element)//search element should begreater then min element inheap if searchelement
{//is smaller then min element then it indicate there is no node in heap.so directly terminate
//the program and return 0 element not found.if we dont terminate then only rooted doubly list will
//be traverse and at last program will terminate as element not found.

  if(node->element >= element)//element should be greater if element is not greater then no need
    {//to traverse further sothis function will execute reducetime_andfind_element and reduce time
	 node=reducetime_andfind_element(element,node);
	}
	
/*this function reducetime_andfind_element return found element address so checking return address
is search element or not. node!=NULL is placed because node may contain address or null. if NULL is
retruned then excessing node->element will be illegal so it is checked first using && operator*/   
  if(node!=NULL && element == node->element )  
  { 
  pop();//itwill pop & update c to 'N' allelement atonce sothat nexttime search func performcorrectly
  	return node;//element found so returning address of that node	
  }
  else if(node==NULL)//it is added because when node is NULL then illegal operation may perform
  {//here needed this condition.if node is null then this node->c='Y' statement will execute illegaly
  pop();//itwill pop & update c to 'N' allelement atonce sothat nexttime search func performcorrectly
  	return 0;//no element found
  }
  
  node->c='Y';//to indicate staring node
  push(node);//into stack to keep track of updated node c='Y'
  
  while(1)
  {
//node->anychild->c !='Y' when node is at rooted doubly list then it will block to reenter same heap
	while(node->anychild !=NULL && node->anychild->c !='Y')//traversing  child first
	{
		node=node->anychild;
	if(node->element >= element)//element should be greater if element is not greater then no need
     {//to traverse further sothis function will execute reducetime_andfind_element and reduce time
		node=reducetime_andfind_element(element,node);
	 }
     if(node!=NULL && element == node->element )  
     {
  pop();//itwill pop & update c to 'N' allelement atonce sothat nexttime search func performcorrectly   
  	  return node;//element found so returning address of that node	
     }
	 else if(node==NULL)//it is added because when node is NULL then illegal operation may perform
     {                  //here needed this condition
  pop();//itwill pop & update c to 'N' allelement atonce sothat nexttime search func performcorrectly
  	  return 0;//no element found
     }
     
    node->c='Y';//to indicate staring node
    push(node);//into stack to keep track of updated node c='Y'
	}
	
	if(node->right->c == 'Y' && node->anychild == NULL)//means node is at last node with no child
	{
	  node=node->parent;/*it return null in situation when only single rooted doubly linked list is
	present and that search element not present in heap then only it will return NULL and perform 
	illegal operation so this condition is placed if(node ==NULL).it is important otherwise next
	will execute illegaly */
	if(node==NULL)
	{
  pop();//itwill pop & update c to 'N' allelement atonce sothat nexttime search func performcorrectly
  	 return node;//element found so returning address of that node	 	
	}
	}
	
	if(node->right->c !='Y')//means it is not end node
	{
		node=node->right;//then move next node
		
	if(node->element >= element)//element should be greater if element is not greater then no need
     {//to traverse further sothis function will execute reducetime_andfind_element and reduce time
	   node=reducetime_andfind_element(element,node);
	 }   
     if(node!=NULL && element == node->element )  
     {
  pop();//itwill pop & update c to 'N' allelement atonce sothat nexttime search func performcorrectly
  	  return node;//element found so returning address of that node	
     }
     else if(node==NULL)//it is added because when node is NULL then illegal operation may perform
     {                    //here needed this condition
  pop();//itwill pop & update c to 'N' allelement atonce sothat nexttime search func performcorrectly
  	  return 0;//no element found
     }
	}
	else//when search element value is greater then all element in heap then it will help to get 
	{  //parent also in situation when there is parent and only one node is present in that doubly
	//list which is mark y then all condition will fail then this else statement will work.it also
	//work when heap is skrew tree to get parent
	
		node=node->parent;/*it return null in situation when only single rooted doubly linked list is
	present and that search element not present in heap then only it will return NULL and perform 
	illegal operation so this condition is placed if(node ==NULL) */
	if(node==NULL)
	{
  pop();//itwill pop & update c to 'N' allelement atonce sothat nexttime search func performcorrectly
  	 return node;//element found so returning address of that node
	}
	}
  }
}
else
{
	printf("\nElement is smaller then min element in heap so it indicate not present in heap");
	return 0;
}
}

struct node* reducetime_andfind_element(int element,struct node *node)
{
 if(element==node->element)
  {/*initially checking because whenthis condition if(node->right->c != 'Y') istrue then it skip one
    elementas node=node->right; so before element willbe skipped so this statement will check first
    that before element.if this statement is not there and this if(node->right->c != 'Y') condition
    fails then else if statement will directly initialize node with parent as node=node->parent;
	in elseif statement which is wrong so this statement is important*/
	
  	return node;//element found so returning address of that node
  }
  
  node->c='Y';//it helps to indicate starting node due to doubly linked list
  push(node);//into stack to keep track of updated node c='Y'
  if(node->right->c != 'Y')//checking in advance starting node
  {
  	node=node->right;
  	  if(node->element >= element) 
		{
		  while(node->element >= element)
		  {
		  	if(element==node->element)
		  	{
		  	  return node;//element found so returning address of that node	
			}
			else if(node->right->c != 'Y')
			{
			  node=node->right;	
			}
			else if(node->right->c == 'Y')//means it is last node
			{
				node=node->parent;//it may return null
				break;//terminate while loop
			}
		  }	
		}
	return node;//when while loop terminate or ifcondition becomefalse if(node->element >= element)
   }
	else if(node->right->c == 'Y')//means it is last node so initialize with parent and return
	{
      node=node->parent;//it may return null
	}	 
}

void push(struct node *node_address)
{
/*stack is created only to update member c as 'N' so that next time when search function is called
it perform correctly. stack size will kepp changing depend on input mostly size is n/2 is = O(n)
stack size will may become no.of elements ie.O(n) when heap is skrew tree.find function is O(log n)*/
struct stack *newnode=(struct stack*)malloc(sizeof(struct stack));
              newnode->address=node_address;
			  newnode->next=top;
  	          top=newnode;//top is updated	  
  	          count++;
}
void pop(void)//it will pop all element at once
{
	printf("\nNumber of elemnts in stack %d",count);
	count=0;
	struct stack *temp;
	while(top!=NULL)
	{
		top->address->c='N';//updated member c so next time find operation can perform correctly
		temp=top;
		top=top->next;
		free(temp);//freeing memory created	
	}
}
void displayheap(void)//traversal is similar like searching element
{
	struct node *node=min;
if(min!=NULL)
{
	printf("\nToatl Element in heap are %d\n",count_nodes);
	printf(" %d",node->element);
	node->c='Y';
	push(node);
while(1)
{ 	
//node->anychild->c !='Y' when node is at rooted doubly list then it will block to reenter same heap
	while(node->anychild !=NULL && node->anychild->c !='Y')//traversing  child first 
	{
		node=node->anychild;
		printf(" %d",node->element);
		node->c='Y';
		push(node);
	}
	if(node->right->c == 'Y' && node->anychild == NULL)//means node is at last node with no child
	{
	  node=node->parent;
	  if(node==NULL)//it is importent it prevent illegal operation
  	  {
  	  	pop();//next time perform correctly
  		return;//terminate function
	  }
	}
	
	if(node->right->c !='Y')//means it is not end node
	{
		node=node->right;
		printf(" %d",node->element);
	}
	else
	{
	  node=node->parent;
	  if(node==NULL)//it is importent it prevent illegal operation
  	  {
  	  	pop();//next time perform correctly
  		return;//terminate function
	  }	
	}	
}
}
else
{
	printf("\nHeap is empty");
}
}
struct node *decrease_element(element,decrease_element)//amortised time O(1)
{
if(min!=NULL)
{
	struct node *search_element,*parent;
	//int element,decrease_element;
  /*printf("Enter element that is present in heap to Decrease: ");
  scanf("%d",&element);*/ //we can also use here
  search_element=search_elementinheap(element);//function will return address
  if(search_element==0)
  {
	printf("\nElement %d not found in heap",element);
	return NULL;
  }
  else
   {
   /*printf("\nEnter decrease value to replace element %d with: ",element);
   	scanf("%d",&decrease_element);*//we can also use here
   	if(decrease_element > search_element->element)//here weare decreasing elementso decrease_element
   	{                //should be smaller than element present in heap if it is equal then no problem
   	  printf("\nDecrease element is greater it should be smaller wrong input");
	  return NULL;	
	}
	search_element->element=decrease_element;//if decreaseelement is smaller then onlyit will update
	parent=search_element->parent;//getting decrease_element parent
	if(parent!=NULL && (search_element->element < parent->element))//this voilate heap property
	{/*heap property is parent should be smaller or equal then their children.Parent should not be
	  greater thentheir children in minheap.Hereit voilateso cut and cascaading operation performed*/
		cut(search_element,parent);//remove element and add to rooted doubly linked list
		cascading_cut(parent);
	}
	if(min->element > search_element->element)//after decreasing value checking min element is 
	{ //greater or not.if it is greter then update because min pointer shoud point to smaller value
		min=search_element;
	}
   	return search_element;
   }
}
else
{
	printf("\nHeap is empty");
	return NULL;
}
}
void cut(struct node *search_element,struct node *parent)
{
if(search_element->right==search_element && search_element->left==search_element)//meansonly one node
 {                                                                                    // is present
   parent->anychild=NULL;/*since it contain only one child so that child will be added to rooted 
                          doublylinked list so updating its child parent->anychild=NULL;because here
                          search_element not pointing to any node so it is only one child*/
   search_element->parent=NULL;//since it will be added to rooted doubly linked list then it should
                               //not have parent so search_element->parent=NULL;
   search_element->mark='W';//updating to W means white not mark and B is black
 //adding left to min rooted doubly linked list
   min->left->right=search_element;
   search_element->right=min;
   search_element->left=min->left;
   min->left=search_element;                                                                 
 }
if(search_element->right!=search_element && search_element->left!=search_element) 
{//means more then one children is present
 if(parent->anychild == search_element)//if it is equal then indicate that parent ispointing to that
 {//child that isgoing tobe add torooted doublylist sothat parent need tobe updated with other child
  //if condition is false then no need to update parent child because it is pointing to other child.
 	parent->anychild=search_element->right;//updating with other child.	
 }
 search_element->parent=NULL;//since it will be added to rooted doubly linked list then it should
                               //not have parent so search_element->parent=NULL;
 search_element->mark='W';//updating to W means white not mark and B is black
 search_element->right->left=search_element->left;//taking out element form doubly linked list
 search_element->left->right=search_element->right;
 //adding left to min rooted doubly linked list
   min->left->right=search_element;
   search_element->right=min;
   search_element->left=min->left;
   min->left=search_element;          	
}
}
void cascading_cut(struct node *parent)//iterative way
{
 struct node *parent_parent;
 parent_parent=parent->parent;
 while(parent_parent!=NULL)//it will run until parent not equal to NULL
 {
	if(parent->mark == 'W' )//W means not marked
	{
	 parent->mark='B';//B means marked so updating node as marked
	 break;//terminate while loop or just return statement	
	}
	else//if it is marked
	{
	 cut(parent,parent_parent); 	
	}
	parent=parent_parent;
	parent_parent=parent_parent->parent;	
 }
}
/*Marked Nodes
An important part of the Fibonacci Heap is how it marks nodes within the trees. The decrease key
operation marks a node when its child is cut from a tree, this allows it to track some history
about each node. Essentially the marking of nodes allows us to track whether:
Case 1: PTR was a root node.
Case 2: Then PTR was linked to another node.
Case 3: The two children of PTR were removed by the Cut procedure.*/
void delete_element(void)
{
/*to delete element we have to decrease that element to smallest so that extract_minimum_node
function extract that address and finally we free that address */
if(min != NULL)
{
 int element;
 struct node *minimumnode,*address_ofdecreasenode;
 printf("\nEnter element to delete: ");
 scanf("%d",&element);
 address_ofdecreasenode=decrease_element(element,-9999);/*decrease value have to give -infinity 
 so that extract_minimum_node() function extract min value because we have decrease to -infinity
 so min pointer point to min value*/
 if(address_ofdecreasenode != NULL)//if it is false then indicate element not found or heap is empty
 {                            //pointer minimumnode not needed reuse pointer address_ofdecreasenode
  minimumnode=extract_minimum_node();
  printf("\nElement %d deleted successfully",element);
  free(minimumnode);//releasing node address that has to be deleted address_ofdecreasenode can also	
 }                   //be used to free memory
}
else
{
 	printf("\nHeap is empty");
}
}
/*Real world example 
Suppose you have a hospital in which patients are attended based on their ages. The oldest are always 
attended first, no matter when he/she got in the queue.

You can't just keep track of the oldest one because if you pull he/she out, you don't know the next 
oldest one. In order to solve this hospital problem, you implement a max heap. This heap is, by 
definition, partially ordered. This means you cannot sort the patients by their age, but you know
that the oldest ones are always in the top, so you can pull a patient out in constant time O(1) 
and re-balance the heap in log time O(log N).

Fibonacciheaps are especially desirable when the number of extract-minimum and delete operations 
is small relative to the number of other operations performed*/
