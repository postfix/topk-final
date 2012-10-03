#include <iostream>
#include <stdlib.h>
#include <WaveletTree.h>
#include <Sequence.h>
#include <Mapper.h>
#include <BitSequenceRG.h>
#include <BitString.h>

using namespace std;
using namespace cds_utils;
using namespace cds_static;

class DocumentArray
{
    public:
        uint *doc_array;
        size_t n;
        WaveletTreeNoptrs *doc_sequence;

        DocumentArray(SuffixTreeY *& cst,BitSequenceRG *& d,vector< pair<uint,uint> > nodes,TextIndex *&s1) {
            size_t vl,vr;
            cst->Root(&vl,&vr);
            this->n = vr;
            // cout << "size = " << this->n << endl;
            // cout << "vr = " << vr << endl;
            this->doc_array = new uint[this->n];
            for (size_t i = 0 ; i < vr;i++) {
                this->doc_array[i] = 0;
            }
            for (size_t i = 0 ; i < vr;i++) {
                size_t locate2 = s1->getSA(i);
                // cout << "locate = " << locate2 << endl;
                if (locate2 < this->n) {

                    // if (i % 1000 == 0 )
                    //     cout << (double)(i*1.0/vr*1.0) << endl;

                    this->doc_array[i] = d->rank1(locate2);
                     // cout << "doc_array[" << i << "]" << this->doc_array[i] << endl;
                }
            }
            // cout << "constructing wavelet tree" << endl;
            //uint *sequence = new uint[this->n];
            Array *A = new Array(this->doc_array,this->n);
            MapperNone * map = new MapperNone();
            BitSequenceBuilder * bsb = new BitSequenceBuilderRG(20);
            this->doc_sequence = new WaveletTreeNoptrs(*A, bsb, map);
            cout << "end!" << endl;
            delete A;
            //delete map;
            //delete bsb;
        }

        size_t countRange(uint symbol,size_t i,size_t j) {
            return this->doc_sequence->rank(symbol,j) - (i>0?this->doc_sequence->rank(symbol,i-1):0)+1;
        }

        pair<size_t, size_t> selectDocument(uint doc,size_t num) {
            pair<size_t, size_t> pp = make_pair(this->doc_sequence->select(doc,num), this->doc_sequence->select(doc,num+1));
            // cout << "fucking pair for document " << doc << " and num " << num << " is (" << pp.first << ", " << pp.second << ")" << endl;
            return pp;
        }

        ~DocumentArray() {
            delete this->doc_sequence;
            delete[] this->doc_array;
        }
        // void test()
        // {
        // 	cout << this->countRange(0,0,135) << endl;
        // 	size_t * pair = this->selectDocument(1,1);
        // //	cout << "pair[0] = " << pair[0] << " , pair[1] = " << pair[1] << endl;
        // }

};


BitSequenceRG * buildBs(size_t *file_sizes,size_t length,size_t n,bool random=false) {
    uint sum = 0;
    BitString *bs = new BitString(length+1);
    if (random) {
        srand ( time(NULL) );
        for (int i = 0 ; i < n;i++) {
            sum = rand() % (length);
            // cout << "Setting random bit " << sum << " to 1" << endl;
            bs->setBit(sum);
        }
    }
    else {
        for (int i = 1;i<n;i++) {
            sum += file_sizes[i-1];
             // cout << "setting bit " << sum << " to 1" << endl;
            bs->setBit(sum);
        }
    }
    BitSequenceRG *bsrg = new BitSequenceRG(*bs,20);
    delete bs;
    return bsrg;
}
