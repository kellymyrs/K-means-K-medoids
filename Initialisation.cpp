#include "Initialisation.h"

void random_selection(vector<struct Item <double>*> items,int& n_clusters,int& N,vector<Cluster* > clusters){

	int i,c;
	Cluster* cluster;

	cout << "Random Selection of "<< n_clusters << " points !" << endl;

	for( i = 0 ; i < n_clusters ; i++){

		c = rand() % N + 1;
		while( items[c-1]->cluster_id == 0 ){ //case the point is already a centroid
			c = rand() % N + 1;
		}
		
			
		items[c-1]->cluster_id = 0; //means that this oint is a centroid

		cluster = new Cluster(items[c-1]);
		clusters.push_back(cluster);

	}

}

void kmeans(vector<struct Item <double>*> items,int& n_clusters,int& N,vector<Cluster* > clusters){
	
}