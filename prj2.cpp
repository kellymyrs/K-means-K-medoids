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
	vector<struct Item <double>*> items,range;
	struct Item <double>* item,* nn = NULL;
	string metric;
	vector<Cluster* > clusters;
	vector<Cluster* > old_clusters;
	int t;

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

	output_file << "Algorithm : " ;

	//INITIALISIATION
	if( in != -1){
		if( in == 0 ){
			random_selection(items,n_clusters,N,clusters);
			if (t == 0){
				output_file << "Random Selection x ";
			}
		}
		else{
			kmeansplus(items,n_clusters,N,clusters,m);
			if(t == 0){
				output_file << "K means++  x ";
			}
		}
	}
	t = 0;
	while(1){
		//ASSIGNMENT
		if( as != -1){
			if( as == 0 ){
				lloyds(items,n_clusters,N,clusters,m);
				if( t == 0 ){
					output_file << "Lloyd's x ";
				}
			}
			else if(as == 1){
				lsh_search(k,d,L,N,m,items,n_clusters,clusters);
				if(t == 0){
					output_file << "Lsh Search x ";
				}
			}
			else{
				cube_search(k,d,L,N,m,items,n_clusters,clusters);
				if(t == 0){
					output_file << "Hypercube Search x ";
				}
			}		
		}

		old_clusters = clusters;

		//UPDATE
		if( up != -1 ){
			if( up == 0 ){
				kmeans(items,n_clusters,N,clusters,m,d);
				if(t == 0){
					output_file << "K means";
				}
			}
			else{
				pam(items,n_clusters,N,clusters,m);
				if(t == 0){
					output_file << "PAM ";
				}
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
		t++;
	}

	if( in == -1){
		run(k,d,L,N,m,items,n_clusters,clusters);
	}

	output_file << endl;
	output_file << "Metric" << metric << endl;

	for (i = 0; i < n_clusters; ++i){
		output_file << "Cluster-" << i << " { size : " << clusters[i]->cl.size() << " , centroid : " << clusters[i]->cent->id << " }"<<endl;		
	}

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