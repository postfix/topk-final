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
    // char *text;
    // size_t length;
    // loadText2(file,&text,&length);
    // int n = length-1;
    // int  *x, *p,*p2,*p3;
    // int  k, l;
    // uchar *x2;
    // l = 0;
    // k=UCHAR_MAX+1;
    // p= (int *)malloc((n+1)*sizeof *p);
    // p2= (int *)malloc((n+1)*sizeof *p2);
    // p3= (int *)malloc((n+1)*sizeof *p3);
    // x2 = (uchar *)malloc((n+1)*sizeof *x2);
    // x= (int *)malloc((n+1)*sizeof *x);

    // for (int i = 0 ; i < n;i++) {
    //     cout << "text[i] = " << text[i] << endl;
    //     x[i] = text[i];
    //     x2[i] = x[i];
    // }
    // suffixsort(x, p, n, k, l);
    // cout << "------qsufsort---" << endl;
    // for (int i = 0 ; i < n+1;i++) {
    //     cout << "p[" << i << "] = " << p[i] << endl;
    // }

    // p[0] = n;
    // for (int i=0; i<=n; ++i) p[i]++;

    // cout << "------------ sadakane modification ---------" << endl;

    // for (int i = 0 ; i < n+1;i++) {
    //     cout << "p[" << i << "] = " << p[i] << endl;
    // }
    // divsufsort(x2,p2,n);

    // cout << "------------ divsufsort ---------" << endl;
    // for (int i = 0 ; i < n+1;i++) {
    //     cout << "p[" << i << "] = " << p2[i] << endl;
    // }

    // for (int i = 0 ;i < n +1;i++) {
    //     p3[i+1] = p2[i];
    // }
    // p3[0] = n;
    // for (int i=0; i<=n; ++i) p3[i]++;
    // cout << "------------ divsufsort' ---------" << endl;
    // for (int i = 0 ; i < n+1;i++) {
    //     cout << "p[" << i << "] = " << p3[i] << endl;
    // }

    // for (int i = 0 ; i < n+1;i++) {
    //     if (p[i] != p3[i]) 
    //         cout << "Error on " << i << "(" << p[1] << " != " << p3[i] << ")" << endl;
    // }
 
    
    vector<vector<string> > general_queries;
    cout << "generating queries..." << endl;
    for (int i = 1 ; i < 70;i++) { 
        vector<string> queries = generateQueries(file,i,1000);
        general_queries.push_back(queries);
        if (i%10 == 0 ) {
            cout << "queries " << i << " done " << endl;
        }
    }
    cout << "end!" << endl;

    
    Topk *tk = new Topk(file,file_sizes,files.size());

    
    for (int kk = 10;kk<1000;kk+=10) {
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
            cout << kk << "\t" << qreal[0].length() << "\t" << (double)(time_wt*1.00/(double)(count_wt*1.00)) << "\t" << (double)(time_csa*1.00)/(double)(count_csa*1.00) << "\t" <<  (time_csa+time_wt)/(double)(count_wt+0.000+count_csa+0.0000) << endl;
            cout << kk << "\t" << qreal[0].length() << "\t time_wt = " << (double)(time_wt*1.00000) << " \t count = " << count_wt << endl;
            cout << kk << "\t" << qreal[0].length() << "\t time_csa = " << (double)(time_csa*1.00000) << "\t count = " << count_csa <<  endl;

        }
    }
            
     

    tk->getSize();



    
    //delete tk;
    delete [] file_sizes;
    delete tk;

}
