#include <iostream>
#include <stdlib.h>

using namespace std;
class LinkList
{

	public:
		int n;
		int m;
		size_t *value;
		size_t *prev_value;
		size_t *weight;
		size_t used;

	LinkList(int n,int m)
	{
		this->n = n;
		this->m = m;
		this->value = new size_t[n+m];
		this->prev_value = new size_t[n+m];
		this->weight = new size_t[n+m];
		this->used = n;
		for (size_t i = 0 ; i < n+m;i++)
		{
			this->value[i] = 0;
			this->prev_value[i] = 0;
			this->weight[i] = 0;
		}
	}

	void insert(size_t pos,size_t v, size_t w)
	{
		if (pos > n+m)
		{
	//		cout << "pos out of range " << " pos = " << pos << " size = " << n+m << endl;
			exit(0);
		}

		if(this->value[pos] == 0)
		{
//			cout << "adding a fresh new value in " << pos << " v = " << v << endl;
			this->value[pos] = v;
			this->weight[pos] = w;
			this->prev_value[pos] = pos;
		}
		else
		{

	//		cout << "adding an existing value ... to pos " << pos << " v = " << v  << endl;
			size_t aux = this->prev_value[pos];
			if (this->value[pos] == v)
			{
			//	this->weight[pos]++;
				return;
			}
			if (this->value[aux] == v)
			{
			//	this->weight[aux]++;
				return;
			}
				
//			cout << " aux is = " << aux;
			size_t aux_value = this->value[aux];
//			cout << "new_pos = " << this->used << endl;
	//		cout << "aux = " << aux << endl;
			this->value[this->used] = v;
			this->weight[this->used] = w;
			this->prev_value[pos] = this->used;
			this->prev_value[this->used] = aux;
			this->used++;
		}
	}

	void listValues(size_t pos)
	{
		size_t aux = pos;
		while(1)
		{
			if (this->prev_value[aux] == pos )
			{
				cout << this->value[aux] << " - > " << this->weight[aux] << endl;
//				cout << "list is empty" << endl;
				break;
			}
			else
			{
				cout << this->value[aux] << " - > " << this->weight[aux] << endl;
				aux = this->prev_value[aux];
			}
		}
	}
	pair<uint,uint> getValue(size_t pos, size_t index)
	{
		size_t aux = pos;
		size_t aux_index = 0;
		while(1)
		{
			if (this->prev_value[aux] == pos )
			{
				if (aux_index == index)
				{
					return make_pair(this->value[aux],this->weight[aux]);
				}
				else
				{
				//	return make_pair(this->value[aux],this->weight[aux]);
				//	cout << "Asking for invalid index" << endl;
					return make_pair(0,0);
				}
			}
			else
			{
				if (aux_index == index)
				{
					return make_pair(this->value[aux],this->weight[aux]);
				}
				else
				{
					aux_index++;
					aux = this->prev_value[aux];	
				}
			}
		}
	}
	size_t getSize()
	{
		return (sizeof(this->value[0]) + sizeof(this->weight[0]) + sizeof(this->prev_value[0]))*(n+m);
		//return 3*((this->m+this->n)*8); 
		
	}
	
	~LinkList()
	{
		delete[] this->value;
		delete[] this->prev_value;
		delete[] this->weight;
	}
};


void test()
{
	LinkList *l = new LinkList(1000000,1000000*50);
	for (int i = 1 ; i < 1000;i++)
	{
		for (int j = 1 ; j < 51;j++)
		{
			l->insert(i,j,j);
		}
	}
	l->listValues(45);
	cout << "size of linkList = " << l->getSize()/1024/1024 << endl;
	

	delete l;
//	cout << " value = " << endl;
//	cout << l->getValue(1,0) << endl;

//	l->listValues(1);
}