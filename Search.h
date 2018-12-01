#ifndef SRCH
#define SRCH
#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <sstream>
#include <string>
#include <random>
#include <cstdint>
#include <time.h>
#include "Item.h"
#include "Cosine_G.h"
#include "G.h"

using namespace std;

void Range(vector<int>& c,unordered_map<int,vector <Item<int>*>>& h,int& metric,double& R,int& M,int& probes,Cosine_G* cg,G* g,vector<struct Item <int>*>& range);
struct Item<int>* NN(vector<int>& c,unordered_map<int,vector <Item<int>*>>& h,int& metric,int& M,int& probes,Cosine_G* cg,G* g,double& min_dist);

#endif