#ifndef UT
#define UT
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
#include <math.h>
#include <utility>
#include <cmath>
#include <unordered_map>
#include <fstream>
#include <complex> 
#include <chrono>
#include <ctime>
#include <limits>
#include <iomanip>
#include "Item.h"
#include "Cluster.h"
#include "Initialisation.h"
#include "Assignment.h"
#include "Update.h"
#include "Evaluation.h"

using namespace std;

void com_line_parser(int argc,char* argv[],ifstream& input_file,ifstream& conf_file,ofstream& output_file,string& metric);
void read_input(ifstream &input_file,vector<struct Item <double>*> &items,int &m,int &N,int &d);
void read_conf(ifstream& conf_file, int& k, int & L, int& n_clusters );
int read_prompt(int& in,int& as,int& up);
void run(int &k,int &d,int &L,int &N,int &m,vector<struct Item <double>*> &items,int &n_clusters,vector<Cluster* > &clusters);


#endif