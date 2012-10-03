#include "utils.cpp"
#include "Topk.cpp"

using namespace std;
using namespace cds_utils;
using namespace cds_static;

int main(int argc, char *argv[]) {

    if(argc<2) {
        cout << "Top-K document retrieval" << endl << endl;
        cout << "usage: " << argv[0] << " <file1> <file2> <file3> ...  <fileN>" << endl;
        return 0;
    }

    ifstream file_list(argv[1]);
    string file_s;
    vector<string> files;
    while(getline(file_list,file_s)) {
        files.push_back(file_s);
    }
    // if (argc > 3)
    // {
    // 	size_t *file_sizes = mergeFiles(files,files.size());
    // 	return 0;
    // }

    size_t *file_sizes = mergeFiles(files,files.size());
    char file[] = "merged";
    Topk *tk = new Topk(file,file_sizes,files.size());
    ifstream query_list(argv[2]);

    string line;
    vector<string> qs;
    while (getline(query_list,line)) {
        qs.push_back(line);
    }

    tk->getSize();

    uchar **queries = new uchar*[qs.size()];
    for (int j = 0 ; j < qs.size(); j++) {
        queries[j] = (uchar*)strdup(qs[j].c_str());
    }

    for (int i = 0 ; i < qs.size()-1;i++) {
    	cout << "-----------------------------" << endl;
    	cout << "query[" << i << "]" << " = " << queries[i] << endl;
    	cout << tk->query(queries[i],qs[i].length()) << endl;
    	cout << "-----------------------------" << endl;
    }

    // for (int i = 0 ; i < qs.size()-1;i++)
    //     free(queries[i]);
   // delete [] queries;

    
    // delete tk;
    // delete [] file_sizes;
    //delete tk;
}
