#include "Assignment.h"

void lloyds(vector<struct Item <double>*> items,int& n_clusters,int& N,vector<Cluster* > &clusters,int &m){
	double d,min;
	cout << "Lloyd's" << endl;

	//loop for every point
	for(int i = 0 ; i < N ; i++ ){

		//find the minimum distance from all the centroids
		if( m == 0 ){
			items[i]->Distance(clusters[0]->get_centroid()->coordinates,min);
		}
		else{
			items[i]->Cosine_Distance(clusters[0]->get_centroid()->coordinates,min);
		}
		items[i]->cluster_id = 0; //assign the first cluster to the point

		//loop for every cluster 
		//check if the other clusters are closer to the point
		for (int j = 1 ; j < n_clusters ; j++){
			
			//find the distance from the current centroid
			if( m == 0){
				items[i]->Distance(clusters[j]->get_centroid()->coordinates,d);
			}
			else{
				items[i]->Cosine_Distance(clusters[j]->get_centroid()->coordinates,d);
			}

			//check if the current centroid is closer to the point
			if( d < min ){
				min = d;
				items[i]->cluster_id = j;				
			}

		}

		//instert the point to the closest cluster
		clusters[items[i]->cluster_id]->Insert(items[i]);
	}
}