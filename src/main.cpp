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
    vector<vector<string> > general_queries;
    for (int i = 1 ; i < 10;i++) {
        vector<string> queries = generateQueries(file,i,10);
        general_queries.push_back(queries);
    }
    
    Topk *tk = new Topk(file,file_sizes,files.size());

    
    
    for (int i = 0;i<general_queries.size();i++) {
        vector<string> qreal = general_queries[i];            
        uchar **queries = new uchar*[qreal.size()];
        double time_wt = 0.0000;
        int count_wt = 0;
        double time_csa = 0.0000;
        int count_csa =0;    
        for (int j = 0 ; j < qreal.size(); j++) {
            //cout << "length= " << qreal[0].length() << endl;
            queries[j] = new uchar[qreal[0].length()+1];
            for (int k = 0;k < qreal[0].length();k++) {
                queries[j][k] = qreal[j][k];
            }
            queries[j][qreal[0].length()] = '\0';
            //queries[j] = (uchar*)strdup(qreal[j].c_str());
          // cout << "query[" << i << "] = " << queries[j] << endl;
            pair<double,double> result;
        	result = tk->query(queries[j],qreal[0].length());      
     	    if (result.first != 0) {
     	       time_wt += result.first*1.0000;
               count_wt++;
    	    }
    	    if (result.second != 0) { 
                time_csa += result.second*1.0000;
                count_csa++;
    	    }
        }
        cout << qreal[0].length() << "\t" << (double)(time_wt*1.00/(double)(count_wt*1.00)) << "\t" << (double)(time_csa*1.00)/(double)(count_csa*1.00) << endl;
        cout << qreal[0].length() << "\t time_wt = " << (double)(time_wt*1.00000) << " \t count = " << count_wt << endl;
        cout << qreal[0].length() << "\t time_csa = " << (double)(time_csa*1.00000) << "\t count = " << count_csa <<  endl;

    }
            
     

    tk->getSize();



    
    //delete tk;
    delete [] file_sizes;
    delete tk;
}
