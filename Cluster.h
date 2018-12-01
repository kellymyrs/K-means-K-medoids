#ifndef CLUSTER
#define CLUSTER
#include "Item.h"

class Cluster
{
	private:
		struct Item<double>* cent; 
		vector <Item<double>* > cl;
	public:
		Cluster(Item<double>* c);
		~Cluster();
		struct Item<double>* get_centroid() { return cent; }
		void Insert(struct Item<double>* it);	
};

#endif
