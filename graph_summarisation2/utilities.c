#include "functions.h"
extern int modv;
int h(int a,int b,int x) 
{
	int s=0;
	

	s=(a*x)+b;

	s=abs(s);
	
	return s%modv;
} 


struct que * createque()
{
	struct que* q=(struct que *)malloc(sizeof(struct que));
	q->rear=q->front=NULL;
	return q;
}
void enque(struct que *q,int k)
{
	struct node *temp=newnode1(k);
	if(q->rear==NULL)
	{
		q->rear=q->front=temp;
		return;
	}
	q->rear->next=temp;
	q->rear=temp;
}
struct node *deque(struct que *q)
{
	if(q->front==NULL)
	return NULL;
	struct node *temp=q->front;
	q->front=q->front->next;
	
	if(q->front==NULL)
	q->rear=NULL;

	return temp;
}
bool isempty(struct que *q)
{
	if(q->rear==NULL)
	return true;
	else
	return false;
} 
int maxn(int a,int b)
{
	if(a>b)
	return a;
	else
	return b;
}
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition (int arr[], int low, int high)
{
    int pivot = arr[high];  
    int i = (low - 1);  
 
    for (int j = low; j <= high- 1; j++)
    {
        
        
        if (arr[j] <= pivot)
        {
            i++;    
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
 
 
void quickSort(int arr[],int low,int high)
{
    if (low < high)
    {
         
        int pi = partition(arr, low, high);
 
        
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
int search(int arr[],int l,int r,int key)
{
	if(l<=r)
	{
		int mid=l+(r-l)/2;
		if(arr[mid]==key)
		return mid;
		else if(arr[mid]<key)
		return search(arr,mid+1,r,key);
		else
		return search(arr,l,mid-1,key);
	}
	return -1;
}
void js(double **mat,int *elem,int n,graph *g)
{
	int j,k;
	for(k=0;k<n;k++)
	{
		for(j=0;j<n;j++)
		{
			mat[k][j]=jsv(g->arr[elem[k]].head,g->arr[elem[j]].head);
		}
	}

	for(k=0;k<n;k++)
	{
		for(j=0;j<n;j++)
		printf("%lf\t",mat[k][j]);

		printf("\n");
	}
}					
 
void printList(struct node *ptr)
{
	printf("\n");
	while(ptr!=NULL)
	{
		printf("%d,",ptr->vertex);
		ptr=ptr->next;
	}
	printf("\n");
}
void push(struct node** head_ref, int new_data)
{
    
    struct node* new_node =
        (struct node*) malloc(sizeof(struct node));
 
    
    new_node->vertex = new_data;
 
    
    new_node->next = (*head_ref);
 
    
    (*head_ref) = new_node;
}

int isPresent(struct node *head, int data)
{
    struct node *t = head;
    while (t != NULL) 
    {
        if (t->vertex == data)
            return 1;
        t = t->next;
    }
    return 0;
}
int isPresentInSortedList(struct node *head, int data)
{
    struct node *t = head;
    while (t != NULL && data <=t->vertex)
    {
        if (t->vertex == data)
            return 1;
        t = t->next;
    }
    return 0;
}
 
/*struct node *getIntersection(struct node *head1, 
                              struct node *head2)
{
    struct node *result = NULL;
    struct node *t1 = head1;
 
     
    while (t1 != NULL)
    {
        if (isPresent(head2, t1->vertex))
            push (&result, t1->vertex);
        t1 = t1->next;
    }
 
    return result;
}*/

int getno(struct node *head)
{
	int cnt=0;
	struct node *ptr=head;
	while(ptr!=NULL)
	{
		cnt++;
		ptr=ptr->next;
	}

	return cnt;
}
double jsv(struct node *head1,struct node *head2)
{
	struct node *temp;
	int t1,t2;
	double res;

	temp=getIntersection(head1,head2);
	t1=getno(temp);

	temp=merge(head1,head2);
	t2=getno(temp);

	res=(double)t1/t2;

	return res;

}
int posn(int *elements,int n,int key)
{
	int i;
	for(i=0;i<n;i++)
	{
		if(elements[i]==key)
		return i;
	}
	return -1;
}
struct adjmat * create_adjmat(struct bin *bin,graph *g,int visited[],int k)
{
		int n1=0,i,j;
		
		struct node *ptr,*nptr;
		ptr=bin->a[k].head;
		while(ptr!=NULL)
		{
			if(visited[ptr->vertex]==0 && g->arr[ptr->vertex].comp_score!=1)
			{
				visited[ptr->vertex]=1;
				n1++;
				nptr=g->arr[ptr->vertex].head;
				while(nptr!=NULL)
				{
					if(nptr->vertex<g->v)
					{
						if(!visited[nptr->vertex] && g->arr[nptr->vertex].comp_score!=1)
						{
							n1++;
							visited[nptr->vertex]=1;
						}
					}
					nptr=nptr->next;
				}
			
			}
			ptr=ptr->next;
		}
		struct adjmat *adjmat=(struct adjmat *)malloc(sizeof(struct adjmat));
		adjmat->n1=n1;
		adjmat->mat=(int **)malloc(sizeof(int *)*n1);

		for(i=0;i<n1;i++)
		adjmat->mat[i]=(int *)malloc(sizeof(int)*n1);

		 

		adjmat->elements=(int *)malloc(sizeof(int)*n1);
		int cnt=0;
		 
		for(i=0;i<g->v;i++)
		{
			if(visited[i]==1)
			{
				 adjmat->elements[cnt++]=i;
			}
		}

		 

	 

		for(i=0;i<n1;i++)
		{
			for(j=0;j<n1;j++)
			adjmat->mat[i][j]=0;
		}

	
		for(i=0;i<n1;i++)
		{
			ptr=g->arr[adjmat->elements[i]].head;
			while(ptr!=NULL)
			{
		
				for(j=0;j<n1;j++)
				{
					if(ptr->vertex==adjmat->elements[j])
					{
						adjmat->mat[i][j]=1;
						break;
					}
				}
				ptr=ptr->next;
			}
		}

		return adjmat;
}
		







				


 
struct inter *intersection(struct inter *mat,int *a,int pos,int n1)
{
	int i,k,xor1,flaga=0,p1;
	int visited[n1];
	for(i=0;i<n1;i++)
	visited[i]=0;

	for(i=0;i<n1;i++)
	{
		xor1= mat->a[pos][i] ^ a[i];
		if(xor1==1)
		{
			if(mat->a[pos][i]==1)
			{
				visited[i]=1;
				flaga=1;
				mat->a[pos][i]=0;
			}
		}
	}
	
	if(flaga==1)
	{
		mat->size=mat->size+1;
		mat->a=(int **)realloc(mat->a,(sizeof(int *)*mat->size));
		p1=mat->size-1;
		mat->a[p1]=(int *)malloc(sizeof(int)*n1);
		
		for(i=0;i<n1;i++)
		mat->a[p1][i]=visited[i];

	}

	return mat;
}
 

 
bool isListSorted(struct node *head)
{
	struct node *ptr=head;
	while(ptr->next!=NULL)
	{
		if(ptr->vertex < ptr->next->vertex)
			return false;

		ptr=ptr->next;
	}

	return true;
}
struct node* getIntersection(struct node* a, struct node* b)
{
  struct node* result = NULL;
  struct node** lastPtrRef = &result;
  
  /* Advance comparing the first nodes in both lists.
    When one or the other list runs out, we're done. */
  while (a!=NULL && b!=NULL)
  {
    if (a->vertex == b->vertex)
    {
      /* found a node for the intersection */
      push(lastPtrRef, a->vertex);
      lastPtrRef = &((*lastPtrRef)->next);
      a = a->next;
      b = b->next;
    }
    else if (a->vertex > b->vertex)
      a=a->next;       /* advance the smaller list */   
    else   
      b=b->next;    
  }
  return(result);
}

struct node *merge(struct node *n1,struct node *n2)
{
	
	struct node *res=NULL;
	struct node *tail=NULL;
	if(n1==NULL)
	res=n2;
	else if(n2==NULL)
	res= n1;
	else
	{
		while(n1!=NULL && n2!=NULL)
		{
			if(n1->vertex > n2->vertex)
			{
				res=pushToLast(res,n1->vertex,&tail);
				n1=n1->next;
			}
			else if(n1->vertex <n2->vertex)
			{
				res=pushToLast(res,n2->vertex,&tail);
				n2=n2->next;
			}
			else
			{
				res=pushToLast(res,n1->vertex,&tail);
				n1=n1->next;
				n2=n2->next;
			}
		}
		while(n1!=NULL)
		{
			res=pushToLast(res,n1->vertex,&tail);
			n1=n1->next;
		}
		while(n2!=NULL)
		{
			res=pushToLast(res,n2->vertex,&tail);
			n2=n2->next;
		}
	}
	return res;
	
}
struct node* pushToLast(struct node *head,int data,struct node **tail)
{
	struct node *newnode=(struct node *)malloc(sizeof(struct node));
	newnode->vertex=data;
	newnode->next=NULL;
	if(head==NULL)
	{
		*tail=newnode;
		head=newnode;
	}
	else
	{
		(*tail)->next=newnode;
		*tail=newnode;
	}
	return head;
}
void reverse(struct node** head_ref)
{
    struct node* prev   = NULL;
    struct node* current = *head_ref;
    struct node* next;
    while (current != NULL)
    {
        next  = current->next;  
        current->next = prev;   
        prev = current;
        current = next;
    }
    *head_ref = prev;
}
void nodesCompressed(struct node *head,graph *g)
{
	while(head!=NULL)
	{
		g->arr[head->vertex].flag+=1;
		head=head->next;
	}
}


struct node *mergeNormal(struct node *head1, struct node *head2)
{
    struct node *result = NULL;
    struct node *t1 = head1, *t2 = head2;
 
    // Insert all elements of list1 to the result list
    while (t1 != NULL)
    {
        push(&result, t1->vertex);
        t1 = t1->next;
    }
 
    // Insert those elements of list2 which are not
    // present in result list
    while (t2 != NULL)
    {
        if (!isPresent(result, t2->vertex))
            push(&result, t2->vertex);
        t2 = t2->next;
    }
 
    return result;
}
 
/* Function to get intersection of two linked lists
  head1 and head2 */
struct node *getIntersectionNormal(struct node *head1, 
                              struct node *head2)
{
    struct node *result = NULL;
    struct node *t1 = head1;
 
    // Traverse list1 and search each element of it in
    // list2. If the element is present in list 2, then
    // insert the element to result
    while (t1 != NULL)
    {
        if (isPresent(head2, t1->vertex))
            push (&result, t1->vertex);
        t1 = t1->next;
    }
 
    return result;
}
	
bool isSortedArray(int arr[],int n)
{
	int i,j;
	for(i=0;i<n-1;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(arr[j]<arr[i])
			return false;
		}
	}
	return true;
}
struct node* addlinkToLast(struct node *head,int v)
{
	struct node *temp=newnode1(v);
	struct node *ptr=head;
	if(ptr==NULL)
	return temp;
	while(ptr->next!=NULL)
	{
		ptr=ptr->next;
	}
	ptr->next=temp;
	return head;
}
 

