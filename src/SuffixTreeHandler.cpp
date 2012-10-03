using namespace std;
class SuffixTreeHandler
{

    #define W 32
    #define bitget(e,p) ((((e)[(p)/W] >> ((p)%W))) & 1)
    public:
        SuffixTree *cst;
        size_t size;

        SuffixTreeHandler(SuffixTreeY *&cst,size_t n) {
            cout << "constructing handler " << endl;
            cout << "size = " << n << endl;
            this->cst = cst;
            this->size = n;
        }


        void generateBitmapAux(pair <size_t,size_t> nodes,BitString *bitmap,uint &bitmap_pos,vector<pair<uint,uint> > &result) {
            pair <size_t,size_t> r;
            size_t pl_aux = nodes.first;
            size_t pr_aux = nodes.second;

            size_t next_vl,next_vr;
            size_t nsibling_l,nsibling_r;
            if (pr_aux - pl_aux != 1) {
                // cout << "entre!" << endl;
                if (pl_aux == pr_aux)  {
                    bitmap_pos++;
                    // cout << "(";
                    bitmap->setBit(bitmap_pos);    
                    // cout << ")";            
                    bitmap_pos++;
                    //return;
                }
                result.push_back(make_pair(pl_aux,pr_aux));
            }
            cst->FChild(pl_aux, pr_aux, &next_vl, &next_vr);
            cst->NSibling(pl_aux,pr_aux,&nsibling_l,&nsibling_r);
            r = make_pair(next_vl,next_vr);
            if (next_vl != (size_t)-1 && next_vr != (size_t)-1) {
                if (next_vl == next_vr)  {
                    generateBitmapAux(r,bitmap,bitmap_pos,result);
                } else { 
                    bitmap_pos++; // leave a 0
                    // cout << "(";
                    generateBitmapAux(r,bitmap,bitmap_pos,result);
                    // cout << ")";
                    bitmap->setBit(bitmap_pos);
                    bitmap_pos++;
                    pl_aux = next_vl;
                    pr_aux = next_vr;
                }
            }
            if (nsibling_l != (size_t)-1 && nsibling_r != (size_t)-1) {
                r = make_pair(nsibling_l,nsibling_r);
                if (nsibling_l == nsibling_r)  {
                    generateBitmapAux(r,bitmap,bitmap_pos,result);
                } else { 
                bitmap_pos++;
                // cout << "(";
                generateBitmapAux(r,bitmap,bitmap_pos,result);
                 // cout << ")";
                bitmap->setBit(bitmap_pos);
                bitmap_pos++;
                }

            }
        }
   
        pair<BitString *,uint> generateBitmap(size_t length,vector<pair<uint,uint> > &nodes ) {
            uint bitmap_pos = 0;
            BitString *bitmap = new BitString(length);
            size_t a,b;
            cst->Root(&a,&b);
            bitmap_pos++;
            // cout << "(" ;
            generateBitmapAux(make_pair(a,b),bitmap,bitmap_pos,nodes);
            bitmap->setBit(bitmap_pos);
            bitmap_pos++;
            // cout << ")";
            // cout << "nodes.size() = " << nodes.size() << endl;
            BitString *new_bitmap = new BitString(bitmap->getData(),bitmap_pos);
            // for (int i = 0 ; i < nodes.size();i++) {
            //     cout << nodes[i].first << endl;
            // }
            // cout << "=========== tree ==========" << endl;
            // for (int i = 0 ;i < bitmap_pos;i++) {
            //     if (bitmap->getBit(i)) 
            //         cout << ")";
            //     else 
            //         cout << "(";
            // }
            // cout << endl;

            return make_pair(new_bitmap,bitmap_pos);
        }

        // vector <pair<size_t,size_t> > getChildsNodes(size_t pl,size_t pr) {
        //     vector <pair<size_t,size_t> > result;
        //     vector <pair<size_t,size_t> > n;
        //     n.push_back(make_pair(pl,pr));
        //     size_t next_vl,next_vr;
        //     size_t level = 0;
        //     while (n.size() != 0) {
        //         size_t pl_aux = n.front().first;
        //         size_t pr_aux = n.front().second;
        //         //size_t level_aux = n.front()->level;
        //         //result.push_back(make_pair(pl_aux,pr_aux));
        //         n.erase(n.begin());
        //         cst->FChild(pl_aux, pr_aux, &next_vl, &next_vr);
        //         if (next_vl != (size_t)-1 && next_vr != (size_t) - 1) {
        //             n.push_back(make_pair(next_vl,next_vr));
        //             while(1) {
        //                 cst->NSibling(next_vl, next_vr, &pl_aux, &pr_aux);
        //                 if (pl_aux != (size_t) - 1 && pr_aux != (size_t) - 1) {
        //                     next_vl = pl_aux;
        //                     next_vr = pr_aux;
        //                     n.insert(n.begin(),make_pair(pl_aux,pr_aux));
        //                 }
        //                 else {
        //                     break;
        //                 }
        //             }
        //         }
        //         else {
        //             result.push_back(make_pair(pl_aux,pr_aux));
        //             //	cout << "adding : " << pl_aux << " , " << pr_aux << endl;
        //         }
        //     }

        //     return result;
        // }

 // vector< pair<size_t,size_t> > getAllNodes(size_t pl,size_t pr) {
        //     vector <pair<size_t,size_t> > result;
        //     vector <pair<size_t,size_t> > n;
        //     n.push_back(make_pair(pl,pr));
        //     size_t next_vl,next_vr;
        //     size_t level = 0;
        //     while (n.size() != 0) {
        //         size_t pl_aux = n.front().first;
        //         size_t pr_aux = n.front().second;
        //         //size_t level_aux = n.front()->level;
        //         result.push_back(make_pair(pl_aux,pr_aux));
        //         n.erase(n.begin());
        //         cst->FChild(pl_aux, pr_aux, &next_vl, &next_vr);
        //         if (next_vl != (size_t)-1 && next_vr != (size_t) - 1) {
        //             n.insert(n.end(),make_pair(next_vl,next_vr));
        //             while(1) {
        //                 cst->NSibling(next_vl, next_vr, &pl_aux, &pr_aux);
        //                 if (pl_aux != (size_t) - 1 && pr_aux != (size_t) - 1) {
        //                     next_vl = pl_aux;
        //                     next_vr = pr_aux;
        //                     n.insert(n.end(),make_pair(pl_aux,pr_aux));
        //                 }
        //                 else {
        //                     break;
        //                 }
        //             }
        //         }
        //     }
        //     //generateBitmap();
        //     return result;
        // }

};
