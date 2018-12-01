#ifndef HT
#define HT
#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <sstream>
#include <string>
#include <random>
#include <unordered_map>
#include <cstdint>
#include <time.h>
#include "G.h"
#include "Item.h"

#define W 300

using namespace std;

class Hash_Member{
	private :
		struct Item<int>* item;
		G* g_m;
	public:
		struct Item<int> * get_item() { return item; }

		Hash_Member(G* g_f,Item<int>* it);
		~Hash_Member();
		struct Item<int>* Combine(vector<int>& c,G *g_h,double& temp_dist);
};

class Hashtable{
	private :
		G* g_h;
		unordered_map<int,vector <Hash_Member*>> hashtable;
	public :
		Hashtable(int& k,int& d);
		~Hashtable();
		void Insert_Hashtable(struct Item<int>* item,uint32_t& t_size);
		struct Item<int>* NN_Hashtable(vector<int>& c,uint32_t& t_size,double& dist);
		void Range_Hashtable(vector<int>& c,uint32_t& t_size,double& R,vector<struct Item <int>*>& range);
};

#endif
