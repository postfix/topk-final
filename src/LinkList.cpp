#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;
class LinkList
{

	public:
		vector<vector<pair<uint,uint> > >  list;
		vector<uint> sizes;
		int n;
		int m;

	LinkList(int n)
	{
		this->n = n;
		this->list.reserve(n);
		//this->sizes.reserve(m);
		for (size_t i = 0 ; i < n;i++)
		{
			vector<pair <uint,uint> >  dummy;
			this->list.push_back(dummy);
			this->sizes.push_back(0);
		}
	}

	void insert(size_t pos,size_t v, size_t w)
	{
		// cout << "inserting node = " << pos << endl;
		this->sizes[pos]++;
		this->list[pos].push_back(make_pair(v,w));
	}

	pair<uint,uint> getValue(size_t pos, size_t index)
	{
		if (index >= this->sizes[pos])
		{
			//cout << "WTF!!!!!!!!!!!!!!" << endl;
			return make_pair((uint)-1,(uint)-1);
		}
		return this->list[pos][index];
	}
	
	
	~LinkList()
	{
		for (int i = 0 ; i < this->n;i++)
		{
			this->list[i].clear();
		}
		this->list.clear();
	}
};

