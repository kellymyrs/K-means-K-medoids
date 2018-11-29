#ifndef INIT
#define INIT
#include "Item.h"
#include "Cluster.h"

void random_selection(vector<struct Item <double>*> items,int& n_clusters,int& N,vector<Cluster* > clusters);
void kmeans(vector<struct Item <double>*> items,int& n_clusters,int& N,vector<Cluster* > clusters);

#endif