#include <algorithm>

#include <iostream>
#include <WaveletTreeRMQ.h>
#include <Sequence.h>
#include <Mapper.h>
#include <BitSequenceRG.h>
#include <BitString.h>
#include "rmq.cpp"
using namespace cds_utils;
using namespace cds_static;
//using namespace std;

class mycomparison
{
  bool reverse;
public:
  mycomparison(const bool& revparam=false)
    {reverse=revparam;}
  bool operator() (const int& lhs, const int&rhs) const
  {
    if (reverse) return (lhs>rhs);
    else return (lhs<rhs);
  }
};

void setBit(uint &d,uint pos) {
	d = d | (1<<pos);
}

uint getBit(uint d,uint pos) {
	if(d & (1<<pos))
		return 1;
	else 
		return 0;
}

uint prefix(uint d,uint g) {
	uint prefix = 0;
	for (uint i = 0 ; i < 32;i++) {
		if (getBit(d,i) > 0 && getBit(g,i) > 0) setBit(prefix,i);
		else if (getBit(d,i) < 1 && getBit(g,i) < 1) setBit(prefix,i);
		else return prefix ;
	}
	return prefix;
}
void printBits(uint d) {
	for (uint i = 0 ; i < 32;i++) 	{
		if (getBit(d,i)) {
			cout << 1;
		} else {
			cout << 0;
		}
	}
	cout << endl;
}

uint lastBit(uint d) {
	uint count_bits=0;
	int aux = d;
	while(getBit(aux, count_bits++)==0) {
		if (count_bits > 32)
		return 1;
	}
	return count_bits; 
}

uint createMask(uint i,uint j) {
	uint aux = ~((~0u << j) & (~0u >> i));
	return aux;
}


void permute_values(uint *array, uint *tmp, vector<pair<uint, uint> > &v, int n) {
  for(uint i=0; i<n; i++) {
    tmp[i] = array[v[i].second];
  }
  for(uint i=0; i<n; i++) {
    array[i] = tmp[i];
  }
}

void sort(uint array[], uint array2[], uint array3[], uint n) {
  vector<pair<uint, uint> > vec(n);
  for (uint i=0; i < n; i++) {
    vec[i] = make_pair(array[i], i);
  }
  std::stable_sort(vec.begin(), vec.end());
  uint *tmp = new uint[n];
  permute_values(array, tmp, vec, n);
  permute_values(array2, tmp, vec, n);
  permute_values(array3, tmp, vec, n);
  delete [] tmp;
}

int main()
{
	int n = 10;
	
	int array[10] = {0,1,1,1,2,2,3,3,4,4};
	int Warray[10] = {1,2,3,4,5,6,7,8,9,10};
	

	uint array2[10] = {2,3,2,3,1,3,2,1,1,0};
	uint array3[10] = {5,6,3,4,2,1,9,3,2,5};
	
	uint sym = 0;
	setBit(sym,3);
	//setBit(sym,2);
	//setBit(sym,1);

	//setBit(sym,0);
	uint height = 4;
	uint level = lastBit(sym)-1;

	uint d = createMask(3,5);
	printBits(d);
	cout << "Last bit = " << lastBit(sym) << endl;
	uint max_symbol_right = 0;
   	cout << "level = " << level << endl;
    printBits(sym);
    uint mask = createMask(0,level);
    printBits(mask);
    max_symbol_right = sym  | mask;
   
    uint min_symbol_right = sym;

    cout << "max_symbol_right = " << max_symbol_right << endl;
    printBits(max_symbol_right);

 
    cout << "min_symbol_right = " << min_symbol_right << endl;
	printBits(min_symbol_right);   

	// uint test = 0;
	// uint test2 = 16;

	// uint result = prefix(test,test2);
	// printBits(test);
	// printBits(test2);
	// printBits(result);
	// cout << "last_bit = " << lastBit(test2);
	// cout << endl;
	//cout << "common prefix:=" << prefix(test,test2) << endl;

	Array *A = new Array((uint*)array,n);
	MapperNone * map = new MapperNone();
	BitSequenceBuilder * bsb = new BitSequenceBuilderRG(30);
	WaveletTreeRMQ *sequence = new WaveletTreeRMQ(*A, bsb, map,(uint*)Warray);
	uint x0,x1;
	uint y0,y1;

	 sort((uint*)array,(uint*)Warray,array3,10);
	// RMQ *r = new RMQ(Warray,10);
	// for (int i = 0 ; i < 10;i++)
	// {
	// 	cout << array[i] << " | " << Warray[i] << endl;
	// }


	x0 = 0;
	x1 = 3;
	y0 = 0;
	y1 = 6;
	
	vector<pair<uint,uint> > v;
	v = sequence->range_call(x0,x1,y0,y1,10);
	for (int i = 0 ; i < v.size();i++)	{
		cout << "v[" << i << "].weight = " << v[i].first << endl;
		cout << "v[" << i << "].pos = " << v[i].second << endl;
	}

 //  	typedef priority_queue<int,vector<int>,mycomparison> mypq_type;
 //  	mypq_type pq (mycomparison(true));
	// int heap_capacity = 6;
	// uint min = (uint)-1;
	// int count = 0;
	// for (int i = 0;i< v.size();i++)
	// {
	// 	if (count == heap_capacity)
	// 	{
	// 		if (Warray[v[i]] > min)
	// 		{
	// 			min = Warray[v[i]];
	// 			pq.pop();
	// 			pq.push(Warray[v[i]]);
	// 		}
	// 		else
	// 			continue;
	// 	}
	// 	else
	// 	{
	// 		if (min > Warray[v[i]])
	// 			min = Warray[v[i]];

	// 			pq.push(Warray[v[i]]);
	// 			count++;
	// 	}
	// }
	// while (!pq.empty())
	// {
	// 	cout << pq.top() << endl;
	// 	pq.pop();
	// }

}	
