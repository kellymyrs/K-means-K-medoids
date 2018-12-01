#ifndef C_HT
#define C_HT
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
#include "Cosine_G.h"
#include "Item.h"


using namespace std;

class Cosine_Hash_Member{
	private :
		struct Item<int>* item;
	public:
		struct Item<int> * get_item() { return item; }

		Cosine_Hash_Member(Item<int>* it);
		~Cosine_Hash_Member();
		struct Item<int>* Combine(vector<int>& c,double& temp_dist);
};

class Cosine_Hashtable{
	private :
		Cosine_G* g_h;
		unordered_map<int,vector <Cosine_Hash_Member*>> hashtable;
	public :
		Cosine_Hashtable(int& k,int& d);
		~Cosine_Hashtable();
		void Insert_Hashtable(struct Item<int>* item,uint32_t& t_size);
		struct Item<int>* NN_Hashtable(vector<int>& c,uint32_t& t_size,double& dist);
		void Range_Hashtable(vector<int>& c,uint32_t& t_size,double& R,vector<struct Item <int>*>& range);
};

#endif
