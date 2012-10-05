
#include <iostream>
#include <utility>
#include <stdlib.h>
using namespace std;
class CartesianNode {
public:
    CartesianNode *left;
    CartesianNode *right;
    size_t array_pos;
    size_t array_value;

    CartesianNode(size_t a,size_t b) {
        this->array_pos = a;
        this->array_value = b;
    }    
};
class CartesianTree {
public: 
    size_t *array;
    size_t n;
    CartesianNode *root;


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
    void buildTree(CartesianNode*& n, size_t ini,size_t fin) {
        if (n == NULL) {
	    if (fin == (size_t)-1) return;         
	    if (ini == fin) {
            //	n = new CartesianNode(ini,this->array[ini]);
		return;
	    }

//	    cout << "entered with:" << ini << "," << fin << endl;
            pair<size_t,size_t> max = findMax(ini,fin);
//	    cout << "max is = " << max.second << endl;
//	    cout << "pos is = " << max.first << endl;
            n = new CartesianNode(max.first,max.second);
            n->left = NULL;
            n->right = NULL;
	            
            buildTree(n->left,ini,max.first);
            buildTree(n->right,max.first+1,fin);
        }
    }
    void preorder(CartesianNode *&n) {
   	 if (n == NULL) return;
   	 cout << n->array_value;
         cout << "(";
	 preorder(n->left);
	 cout << ")";
	 cout << "(";
         preorder(n->right);
	 cout << ")";
    }
    CartesianTree(size_t *array,size_t n) {
        this->array = array;
        this->root = NULL;
	this->n = n;
        buildTree(root,0,n);
	cout << "(";
        preorder(root);
	cout << ")";
    }
};

int main() {
	size_t n = 10000000;
	size_t *a = new size_t[n];
	for (size_t i = 0 ; i < n;i++) {
		a[i] = rand()%3;
	}
	CartesianTree * ct = new CartesianTree(a,n);
}
