#include <rmq.h>

using namespace rmq_space;
RMQ::RMQ(int *A,int n)
{
	this->n = n ;
	this->bitmap = buildrmq(A,n);
	this->t = new tree_ff(this->bitmap,2*(n+1),OPT_FAST_LCA | OPT_FAST_PREORDER_SELECT | OPT_FAST_LEAF_SELECT);
	//delete[] A;
}

RMQ::~RMQ()
{
		free(this->bitmap);
		delete this->t;
}


unsigned int RMQ::query(int i,int j)
{
	uint v1 = this->t->Preorden_Select(i+2);
	uint v2 = this->t->Preorden_Select(j+2);
	uint v = this->t->Lca(v1,v2);	
 	if (v==v1) return i;
	uint d1 = this->t->Depth(v);
	uint d2 = this->t->Depth(v2);
	uint vv = this->t->Level_Ancestor(v2,-(d2-d1)+1);
	return this->t->Preorder_Rank(vv - 1) - 1;
}

size_t RMQ::getSize()
{
	cout << "rmq size = " << this->t->size() << endl;
	return this->t->size();
}


int RMQ::mapTree (unsigned int *bitmap, Tree *T, int i)
{
	  if (T == NULL) return i;
	   i = mapTree (bitmap, T->prevSibl, i);
	   bitmap[i/W] &= ~(1<<(i%W)); i++; // parentesis[i++] = 0;
	   // bitmap[i/W] |= (1u<<31) >> (i%W); i++; // parentesis[i++] = 1;
	   i = mapTree (bitmap, T->lastChild, i);
	   bitmap[i/W] |= 1<<(i%W); i++; // parentesis[i++] = 1;
	   // bitmap[i/W] &= ~((1u<<31)>>(i%W)); i++; // parentesis[i++] = 0;
	   return i;
}


unsigned int *RMQ::buildrmq (int *A, int n)
{
	  Tree *T = new Tree();
	  Path *P = new Path(); // lista bottom up del rightmost path
	  int i;
	  unsigned int *bitmap;
	 
	  //T = (Tree)malloc (sizeof(struct sTree));
	  T->prevSibl = T->lastChild = NULL;
	  T->pos = -1; // fake root
	  
	  //P = (Path)malloc (sizeof(struct sPath));
	  P->node = T;
	  P->next = NULL;

	  for (i=0;i<n;i++) // ubicar A[i] en el rightmost path
	  {
	      Path *p;
		  Tree *t;
		  while ((P->node->pos != -1) && (A[P->node->pos] >= A[i]))
	    {
	        p = P->next;
		      delete P;
		      P = p;
	    }
			// found the insertion point
		  t = new Tree(); //(Tree)malloc(sizeof(struct sTree));
		  t->pos = i;
		  t->lastChild = NULL;
		  t->prevSibl = P->node->lastChild;
		  P->node->lastChild = t;
	  //  printf ("A[%i]=%i se cuelga de A[%i]=%i\n",i,A[i],P->node->pos,A[P->node->pos]);
		  p = new Path(); //(Path)malloc(sizeof(struct sPath));
		  p->node = t;
		  p->next = P;
		  P = p;
	  }
	// finished T; free P and convert T into parentheses
	  while (P != NULL)
	  {
	    Path *p = P->next;
	    delete P;//free(P);
	    P = p;
	  }
	  bitmap = (unsigned int*)malloc (sizeof(unsigned int) * ((2*(n+1)+W-1)/W));
	  mapTree (bitmap,T,0);
	  delete T;
	  // delete t;
	  return bitmap;
}
/*
bool testRMQ(int n)
{
	int *A = new int[n];
	int *B = new int[n];
	for (int i = 0 ; i < n;i++)
	{
		//cout << "rand = " << rand()%100;
		A[i] = rand()%100;
		B[i] = A[i];
	}
	
	int i;
	RMQ *rmq = new RMQ(B,n);
	int min = 0;
	for (int i = 0 ; i <n;i++)
	{
		min = i;
		for (int j = i+1;j<n;j++)
		{
			if (A[min] >= A[j])
				min = j;
			int rmq_min = rmq->query(i,j);
			if (rmq_min != min)
			{
				cout << "(" << i << " , " << j << " ) wrong -> " << rmq_min << " vs " << min << endl;
			//	return false;
			}
		}
		
	}
	cout << "RMQ test completed..." << endl;
	cout << "RMQ size = " << rmq->getSize() << endl;
	return true;
}*/