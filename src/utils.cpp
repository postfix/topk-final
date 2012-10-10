#ifndef _UTILS__CPP
#define _UTILS__CPP

#include <TextIndex.h>
#include <SuffixTree.h>
#include <algorithm>
#include <time.h>
#define pivot_index() (begin+(end-begin)/2)
#define swap_rkonow(a,b,t) ((t)=(a),(a)=(b),(b)=(t))

//typedef unsigned int uint
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
  std::sort(vec.begin(), vec.end());
  uint *tmp = new uint[n];
  permute_values(array, tmp, vec, n);
  permute_values(array2, tmp, vec, n);
  permute_values(array3, tmp, vec, n);
  delete [] tmp;
}

SuffixTree * saveLoad(SuffixTree * bs) {
	ofstream ofs("cst.tmp");
	bs->save(ofs);
	ofs.close();
	ifstream ifs("cst.tmp");
	SuffixTree * ret = SuffixTree::load(ifs);
	ifs.close();
	return ret;
}

TextIndex * saveLoad2(TextIndex * bs) {
    ofstream ofs("textindex.tmp");
    bs->save(ofs);
    ofs.close();
    ifstream ifs("textindex.tmp");
    TextIndex * ret = TextIndex::load(ifs);
    ifs.close();
    return ret;
}

bool testSuffixTree(SuffixTree *s1){
	/*add any test you want*/
	return true;
}


// auxilary functions
size_t *mergeFiles(vector<string> files, size_t n)
{
	FILE * faux;
	faux = fopen("merged","w");
	size_t *sizes = new size_t[n];

	for (int i = 1 ; i < n+1 ; i++)
	{
		FILE * pFile;
		long size;
		char * buffer;
    size_t result;

 //   cout << "reading " << files[i-1] << endl;
		pFile = fopen(files[i-1].c_str(),"rb");
		if (pFile==NULL) perror ("file");
		else
		{
			fseek (pFile, 0, SEEK_END);
		  size=ftell (pFile);
	    sizes[i-1] = size;
		  rewind (pFile);
		  buffer = new char[size];
 			if (buffer == NULL) {fputs ("Memory error",stderr); exit (2); }
 			result = fread (buffer,1,size,pFile);
      //buffer[size] = 0;
 			// cout << " size is = " << size << endl;
 			// cout << " size of buffer = " << sizeof(buffer) << endl;
  		if (result != size) {fputs ("Reading error",stderr); exit (3);}
		  // printf ("Size of file %i ,  %ld bytes.\n",i,size);
			fwrite (buffer , 1 , size, faux );
      char c = 0;
      fwrite (&c , 1 , 1, faux );
      c = 255;
      fwrite (&c , 1 , 1, faux );
      sizes[i-1] = size+2;
      delete [] (buffer);
   		fclose (pFile);	
		}
	}
  char c = 255;
  fwrite (&c , 1 , 1, faux );
      
  
	fclose(faux);
	return sizes;
}

vector<string> generateQueries(char *file, int length, int num) {
  vector<string> result;
  ifstream fs;
  int total_length = 0;
  fs.open(file,ios::binary);
  fs.seekg(0,ios::end);
  total_length = fs.tellg();
  fs.seekg(0,ios::beg);  
  int count = 0;
  while(count < num) {
    char *buffer = new char[length+1];
    int pos = rand()%(total_length-length-10);
    //cout << "pos  "  << pos << endl;
    fs.seekg(pos);
    fs.read(buffer,length);
    bool next = false;
    for (int i = 0 ; i < length;i++ ) {
      if (buffer[i] == '\n' || buffer[i] < 10 || buffer[i] > 127) {
        next = true;
        delete[] buffer;
        break;
      }
    }
    if (next == true) 
      continue;

    buffer[length] = '\0';
    count++;
    string s(buffer);
    cout << "adding s=" << s << endl;
    result.push_back(s);
  }
  return result;

}

double diffclock(clock_t clock1,clock_t clock2)
{
  double diffticks=clock1-clock2;
  double diffms=(long double)((double)(diffticks*1000.0000)/(double)(CLOCKS_PER_SEC+0.0000));
  return diffms;
} 
#endif
