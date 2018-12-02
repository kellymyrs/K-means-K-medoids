#include "utils.h"
#include "Cluster.h"
#include "Initialisation.h"
#include "Assignment.h"
#include "Update.h"
#include "Evaluation.h"

using namespace std;

int main(int argc,char* argv[]){
	ifstream input_file, conf_file;
	ofstream output_file;
	int i,j,k = 4 ,L = 5, N,d,n_clusters,in,as,up; // N = number of items(lines) in the file, d = number of coordinates (dimension)
	char* com;
	string line,temp_str;
	int ident;
	vector<struct Item <double>*> items,range;
	struct Item <double>* item,* nn = NULL;
	string metric;
	vector<Cluster* > clusters;
	vector<Cluster* > old_clusters;

	srand (time(NULL));

	//command line parsing
	com_line_parser(argc,argv,input_file,conf_file,output_file,metric);
    int m;
    if (!metric.compare("euclidean")){
        m = 0;
        cout << "Euclidean" << endl;
    }
    else if(!metric.compare("cosine")){
        m = 1;
        cout << "Cosine" << endl;
    }

	//read input and create table items
	read_input(input_file,items,m,N,d);

	//read configuration file
	read_conf(conf_file,k,L,n_clusters);

	//read from prompt
	read_prompt(in,as,up);

	//INITIALISIATION
	if( in != -1){
		if( in == 0 ){
			random_selection(items,n_clusters,N,clusters);
		}
		else{
			kmeansplus(items,n_clusters,N,clusters,m);
		}
	}
	while(1){
		//ASSIGNMENT
		if( as != -1){
			if( as == 0 ){
				lloyds(items,n_clusters,N,clusters,m);
			}
			else if(as == 1){
				lsh_search(k,d,L,N,m,items,n_clusters,clusters);
			}
			else{
				cube_search(k,d,L,N,m,items,n_clusters,clusters);
			}		
		}

		old_clusters = clusters;

		//UPDATE
		if( up != -1 ){
			if( up == 0 ){
				kmeans(items,n_clusters,N,clusters,m,d);
			}
			else{
				pam(items,n_clusters,N,clusters,m);
			}
		}

		int b = 0;
		for (i = 0; i < n_clusters ; i++){
			if(old_clusters[i]->cent->id == clusters[i]->cent->id){
				b++;
			}
		}	
		if( b == n_clusters ){
			break;
		}	
	}


	if( in == -1){
		run(k,d,L,N,m,items,n_clusters,clusters);
	}

	// //INITIALISIATION
	// //random_selection(items,n_clusters,N,clusters);
	// kmeansplus(items,n_clusters,N,clusters,m);

	// //ASSIGNMENT
	// lloyds(items,n_clusters,N,clusters,m);
	// //lsh_search(k,d,L,N,m,items,n_clusters,clusters);
	// //cube_search(k,d,L,N,m,items,n_clusters,clusters);

	// //UPDATE
	// //pam(items,n_clusters,N,clusters,m);
	// //kmeans(items,n_clusters,N,clusters,m,d);

	//EVALUATION
	silhouette(items,n_clusters,N,clusters,m,d);


	for ( i = 0 ; i < clusters.size() ; i++ ){
		//cout << "Destroying item" << i << endl;
		delete clusters[i];
	}

	//destroy items
	cout << "Destroying array items "<< endl;
	for ( i = 0 ; i < N ; i++ ){
		//cout << "Destroying item" << i << endl;
		delete items[i];
	}
	items.clear();

	output_file.close();

	return 0;

}