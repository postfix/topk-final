#include <SuffixTree.h>
#include <map>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "DocumentArray.cpp"
#include "SuffixTreeHandler.cpp"
#include "utils.cpp"
#include <BitString.h>
#include "LinkList.cpp"
#include <cstdlib>
#include <libcdsTrees.h>
#include <TextIndex.h>
//#include <RMQ_succinct.h>
#include <factorization.h>
//#include <timing.h>

#include <WaveletTreeRMQ.h>
#include <tree_ff.h>

//#include "../dacs/src/dacs.h"
//#include "../dacs/src/dacs.c"

bool make_random_flag = false;
int rand_files = 3;
//class WaveletTreeRMQ;

class Topk
{
    public:
        char * file;
        size_t *file_sizes;
        int num_files;
        size_t  length;

        SuffixTreeY *cst;
        SuffixTreeHandler *stp;
        DocumentArray *da;
        LinkList * ll;
        TextIndex *ticsa;
        WaveletTreeRMQ *d_sequence;
        tree_ff *t;
        BitSequenceRG * d;

        Array *doc_array;
        factorization *freq_dacs;
        BitSequenceRG *bitsequence_map;
        BitSequenceRG *bitsequence_leaf;
        BitSequenceRG *bitmap_leaf;


        vector<pair<uint,uint>> preorder_vector;
        vector<uint> documents;
        map <pair<uint,uint>,uint> nodes_preorder;

        size_t number_of_nodes;
        uint* d_array;
        uint *freq_array;
        size_t pointer_size;
        uint max_freq;
        uint *gd_sequence;

        Topk(char * file,size_t *file_sizes, int num_files);
        void fillLinkList(uint num_files);
        void generateSequence();
        void constructAll(vector<uint> &freq_array,uint *depth_sequence);
        double query(uchar* q,uint size_q);
        size_t getSize();
        ~Topk();
};
