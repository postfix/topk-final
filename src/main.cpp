#include "utils.cpp"
#include "Topk.cpp"

using namespace std;
using namespace cds_utils;
using namespace cds_static;

int main(int argc, char *argv[]) {

    if(argc<2) {
        cout << "Top-K document retrieval" << endl << endl;
        cout << "usage: " << argv[0] << " <file_list> <query list> " << endl;
        return 0;
    }
    ifstream file_list(argv[1]);
    string file_s;
    vector<string> files;
    while(getline(file_list,file_s)) {
        files.push_back(file_s);
    }

    size_t *file_sizes = mergeFiles(files,files.size());
    char file[] = "merged";
    Topk *tk = new Topk(file,file_sizes,files.size());

    ifstream query_list(argv[2]);
    string line;
    vector<string> qs;
    while (getline(query_list,line)) {
        qs.push_back(line);
    }

    
    for (int i = 0;i<qs.size();i++) {
        vector<string> qreal;
        ifstream qlist(qs[i]);
        while(getline(qlist,line)) {
            qreal.push_back(line);
        }       
        
        uchar **queries = new uchar*[qreal.size()];
        for (int j = 0 ; j < qreal.size(); j++) {
            queries[j] = (uchar*)strdup(qreal[j].c_str());
        }

        double result = 0.00000;
        for (int i = 0 ; i < qreal.size()-1;i++) {
            // cout << "qreal = " << queries[i] << endl;
            // cout << "qlength = " << qreal[i].length() << endl;
            result += tk->query(queries[i],qreal[i].length());      
        }

        cout << qreal[0].length() << "\t" << (double)(result*1.00/(qreal.size()*1.00)) << endl;
        // for (int i = 0 ; i < qreal.size()-1;i++)
        //     free(queries[i]);
       //delete [] queries;
    }

    tk->getSize();



    
    //delete tk;
    delete [] file_sizes;
    delete tk;
}
