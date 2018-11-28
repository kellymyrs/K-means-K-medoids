#include "utils.h"

using namespace std;

int main(int argc,char* argv[]){
	ifstream input_file, conf_file;
	ofstream output_file;
	int i,j,k = 4 ,L = 5, N,d,clusters; // N = number of items(lines) in the file, d = number of coordinates (dimension)
	char* com;
	string line,temp_str;
	int ident;
	vector<struct Item <double>*> items,range;
	struct Item <double>* item,* nn = NULL;
	string metric;

	//srand (time(NULL));

	//command line parsing
	com_line_parser(argc,argv,input_file,conf_file,output_file,metric);
    int m;
    if (!metric.compare("euclidean")){
        m = 0;
    }
    else if(!temp_str.compare("cosine")){
        m = 1;
    }

	//read input and create table items
	read_input(input_file,items,m,N,d);

	//read configuration file
	read_conf(conf_file,k,L,clusters);

	//INITIALISIATION


	//destroy items
	cout << "Destroying array items "<< endl;
	for ( i = 0 ; i < N ; i++ ){
		//cout << "Destroying item" << i << endl;
		delete items[i];
	}
	items.clear();

	output_file.close();

}