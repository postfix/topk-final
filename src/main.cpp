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

 
    
    cout << "constructing topk" << endl;
    Topk *tk = new Topk(file,file_sizes,files.size());
    vector<vector<string> > general_queries;

    tk->getSize();
/*    cout << "generating queries..." << endl;
    int h = 1;
    while(h<=70) { 
        vector<string> queries = generateQueries(file,h,4000);
        general_queries.push_back(queries);
    	if (h >= 10)
        	h+=10;
    	else
        	h++;
       if (h%10 == 0 ) 
            cout << "queries " << h << " done " << endl;        
    }
    cout << "end!" << endl;


    int increase = 10;
   for (int kk = 10;kk<=1000;kk+=increase) {
	if (kk>=100) { increase = 100; }
        for (int i = 0;i<general_queries.size();i++) {
            vector<string> qreal = general_queries[i];            
            uchar **queries = new uchar*[qreal.size()];
            double time_wt = 0.0000;
            int count_wt = 0;
            double time_csa = 0.0000;
            int count_csa =0;    
//	    cout << "query size = " << qreal[0].length() << endl;
            for (int j = 0 ; j < qreal.size(); j++) {
                //cout << "length= " << qreal[0].length() << endl;
                queries[j] = new uchar[qreal[0].length()+1];
                
    		for (int k = 0;k < qreal[0].length();k++) {
                        queries[j][k] = qreal[j][k];
                    }
	        queries[j][qreal[0].length()] = '\0';
            pair<double,double> result;
          	result = tk->query(queries[j],qreal[0].length(),kk);      
       	    if (result.first < (double)0) { 
                time_csa += result.second*1.0000;
                count_csa++;
            } else {
    	        time_csa += result.second*1.000;
    	      	count_csa++;
                time_wt += result.first*1.0000;
                count_wt++;   
            }
        }
        cout << qreal[0].length();
        cout << "," << kk;
        cout << "," << time_wt;
        cout << "," << time_csa;
        cout << "," << count_wt;
        cout << "," << count_csa << endl;
        }
    }
        
    delete [] file_sizes;
    delete tk;
*/
}
