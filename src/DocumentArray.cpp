#include <iostream>
#include <stdlib.h>
#include <WaveletTree.h>
#include <Sequence.h>
#include <Mapper.h>
#include <BitSequenceRG.h>
#include <BitSequenceDArray.h>
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
            this->doc_array = new uint[this->n + 1];
            for (size_t i = 0 ; i <= vr;i++) {
                this->doc_array[i] = 0;
            }
            for (size_t i = 0 ; i <= vr;i++) {
                size_t locate2 = s1->getSA(i);
                if (locate2 <= this->n) {
                     this->doc_array[i] = d->rank1(locate2);
                }
            }

            Array *A = new Array(this->doc_array,this->n);
            MapperNone * map = new MapperNone();
            BitSequenceBuilder * bsb = new BitSequenceBuilderRG(20);
            this->doc_sequence = new WaveletTreeNoptrs(*A, bsb, map);
            delete A;
        }

        int * createCArray() {
            int * Carray = new int[n];
            int pos = 0;
            for (int i = 0 ; i < n ; i++) {
                uint occ_symbol = doc_sequence->rank(doc_array[i],i);
                if (occ_symbol-1 == 0) {
                    pos = -1;
                } else  {
                    pos = doc_sequence->select(doc_array[i],occ_symbol-1);
                }
                if (pos >= (uint)-1) {
                    pos = -1;
                }
                Carray[i] = pos;
            }
            delete []this->doc_array;
            return Carray;
        }

        size_t countRange(uint symbol,size_t i,size_t j) {
            return this->doc_sequence->rank(symbol,j) - (i>0?this->doc_sequence->rank(symbol,i-1):0);
        }

        pair<size_t, size_t> selectDocument(uint doc,size_t num) {
            pair<size_t, size_t> pp = make_pair(this->doc_sequence->select(doc,num), this->doc_sequence->select(doc,num+1));
            // cout << "fucking pair for document " << doc << " and num " << num << " is (" << pp.first << ", " << pp.second << ")" << endl;
            return pp;
        }

        ~DocumentArray() {
            delete this->doc_sequence;
        }
};


BitSequenceRG * buildBs(size_t *file_sizes,size_t length,size_t n) {
    uint sum = 0;
    BitString *bs = new BitString(length+3);
    for (int i = 1;i<n;i++) {
        sum += file_sizes[i-1];
        bs->setBit(sum);
    }
    BitSequenceRG *bsrg = new BitSequenceRG(*bs,20);
    delete bs;
    return bsrg;
}
