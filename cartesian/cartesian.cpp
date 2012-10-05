#include <iostream>
#include <utility>
#include <stdlib.h>
#include <vector>
#include <tree_ff.h>
#include <BitString.h>

using namespace std;
namespace rmq_cartesian {
    class CartesianNode {
    public:
        CartesianNode *left;
        CartesianNode *right;
        size_t array_pos;
        size_t array_value;

        CartesianNode(size_t a,size_t b) {
            this->array_pos = a;
            this->array_value = b;
            this->left = NULL;
            this->right = NULL;
        }
        CartesianNode() {
            this->left = NULL;
            this->right = NULL;
            this->array_pos = (size_t)-1;
        };    
    };
    class CartesianQueue {
    public:
        CartesianNode *n;
        size_t ini;
        size_t fin; 
        CartesianQueue(CartesianNode *n,size_t ini, size_t fin) {
            this->ini = ini;
            this->fin = fin;
            this->n = n;
        }
    };

    class CartesianTree {
    public: 
        size_t *array;
        size_t n;
        CartesianNode *root;
        tree_ff *t;


            pair<size_t,size_t> findMax(size_t ini,size_t fin) {
                size_t max = this->array[ini];
                size_t max_pos = ini;
                for (size_t i = ini + 1; i < fin;i++) {
                    if (max < this->array[i]) {
                        max = this->array[i];
                        max_pos = i;
                    }
                }
                return make_pair(max_pos,max);
            }
            void buildTree(vector<pair<CartesianNode*,pair<size_t,size_t> > > *q) {
                while(!q->empty()) {        
                    pair<CartesianNode*,pair<size_t,size_t> > r = q->back();
                    CartesianNode *node = r.first;
                    q->erase(q->end());
                    size_t ini = r.second.first;
                    size_t fin = r.second.second;
            	    if (fin == (size_t)-1) continue;         
            	    if (ini == fin) continue;
                    
            	    cout << "entered with:" << ini << "," << fin << endl;
                    pair<size_t,size_t> max = findMax(ini,fin);
            	    cout << "max is = " << max.second << endl;
            	    cout << "pos is = " << max.first << endl;
                    if (node->array_pos == (size_t)-1) {
                        node->array_pos = max.first;
                        node->array_value = max.second;
                        node->left = new CartesianNode();
                        node->right = new CartesianNode();              

                        pair<CartesianNode*,pair<size_t,size_t> > aux_right = make_pair(node->right,make_pair(max.first+1,fin));
                        q->push_back(aux_right);
                        pair<CartesianNode*,pair<size_t,size_t> > aux_left = make_pair(node->left,make_pair(ini,max.first));
                        q->push_back(aux_left);
                    }
            }
        }


            void preorder() {
                vector<CartesianNode*> q;
                q.push_back(this->root);
                while (!q.empty()) {
                    CartesianNode *n = q.back();
                    q.pop_back();
                    if (n->array_pos == (size_t)-1) continue;
                    cout << n->array_pos << endl;
                    q.push_back(n->right);
                    q.push_back(n->left);
                }
            }

            void preorder_normal(CartesianNode *n) {
                if (n->array_pos == (size_t)-1 ) {
                    // cout << "()";
                    return;
                }
                //cout << n->array_pos << endl;
                
                cout << "(" ; 
                preorder_normal(n->left);
                preorder_normal(n->right);
                cout << ")";
            }

            tree_ff *buildCompactTree() {
                vector<pair<bool,CartesianNode*> > q;
                q.push_back(make_pair(false,this->root));
                cds_utils::BitString *bs = new  cds_utils::BitString(2*(this->n));
                uint pos = 0;
                while (!q.empty()) {
                    CartesianNode *n = q.back().second;
                    bool closing = q.back().first;
                    q.pop_back();
                    if (closing) {
                        bs->setBit(pos);
                        cout << ")";
                        pos++;      
                    } else {
                        pos++;
                        cout << "(";
                        q.push_back(make_pair(true, n));
                        if (n->right->array_pos != (size_t)-1)
                          q.push_back(make_pair(false, n->right));
                        if (n->left->array_pos != (size_t)-1)
                           q.push_back(make_pair(false, n->left));    
                    }
                    
                }
     
                cout << "tree->" << endl;     
                for (int i = 0 ; i < 2*(this->n) ; i++ ) {
                    if (bs->getBit(i) == 0 ) cout << "(";
                    else cout << ")";
                }  
                cout << endl;
                this->t = new tree_ff(bs->getData(),2*(n),OPT_FAST_LCA | OPT_FAST_PREORDER_SELECT | OPT_FAST_LEAF_SELECT);
            }
            CartesianTree(size_t *array,size_t n) {
                this->array = array;
                this->root = new CartesianNode();
            	this->n = n;
                vector<pair<CartesianNode*,pair<size_t,size_t> > >  *ranges = new vector<pair<CartesianNode*,pair<size_t,size_t> > > ();
                ranges->push_back(make_pair(this->root,make_pair(0,n)));
                buildTree(ranges);
                preorder();
                cout << "---------" << endl;
                preorder_normal(this->root);
                cout << "end tree" << endl;
                buildCompactTree();

            }

            uint query(uint i, uint j) {
                uint v1 = this->t->Preorden_Select(i+1);
                uint v2 = this->t->Preorden_Select(j+1);
                uint v = this->t->Lca(v1,v2);   
                if (v==v1) return i;
                uint d1 = this->t->Depth(v);
                uint d2 = this->t->Depth(v2);
                uint vv = this->t->Level_Ancestor(v2,-(d2-d1)+1);
                return this->t->Preorder_Rank(vv-1)-1;
            }

            bool testRMQ(int n) { 
            size_t *A = new size_t[n];
            size_t *B = new size_t[n];
            for (int i = 0 ; i < n;i++)
            {
                //cout << "rand = " << rand()%100;
                A[i] = rand()%100;
                B[i] = A[i];
            }
            
            int i;
            //RMQ *rmq = new RMQ(B,n);
            CartesianTree * ct = new CartesianTree(B,n);
            int min = 0;
            for (int i = 0 ; i <n;i++){
                min = i;
                for (int j = i+1;j<n;j++) {
                    if (A[min] >= A[j])
                        min = j;
                    int rmq_min = ct->query(i,j);
                    if (rmq_min != min) {
                        cout << "(" << i << " , " << j << " ) wrong -> " << rmq_min << " vs " << min << endl;
                    //  return false;
                    } else {
                        cout << "(" << i << " , " << j << " ) RIGHT -> " << rmq_min << " vs " << min << endl;
                    }
                }
                
            }
            cout << "RMQ test completed..." << endl;
          //  cout << "RMQ size = " << rmq->getSize() << endl;
            return true;
        }

    };
};

using namespace rmq_cartesian;
int main() {
	size_t n = 10;
	size_t *a = new size_t[n];
	for (size_t i = 0 ; i < n;i++) {
		a[i] = rand()%10;
	}
	CartesianTree * ct = new CartesianTree(a,n);
    ct->testRMQ(10);
}
