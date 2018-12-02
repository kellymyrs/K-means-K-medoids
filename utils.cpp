#include "utils.h"

void com_line_parser(int argc,char* argv[],ifstream& input_file,ifstream& conf_file,ofstream& output_file,string& metric){
	for( int i = 1 ; i < argc - 1 ; i++) {
		if(!strcmp(argv[i],"-i")){         //input file
			input_file.open(argv[i+1]);
	    	if(!input_file.is_open()){
	    		cout << "Don't have an input file" << endl ;
	    	}
    	}

		if(!strcmp(argv[i],"-c"))         //configuration file
			conf_file.open(argv[i+1]);

		if(!strcmp(argv[i],"-o"))        //output file
			output_file.open(argv[i+1]);

		if(!strcmp(argv[i],"-d"))      //metric
			metric = argv[i+1];			
	}
	//cout << "Metric used = " << metric << endl;
}

void read_input(ifstream &input_file,vector<struct Item <double>*> &items,int &m,int &N,int &d){
	string line,temp_str;
	vector<double> coordinates; //coordinates
	struct Item <double>* item;
    int i = 1,ident;

    while(getline(input_file,line)) {

        ident = i;
        
        istringstream curr_line(line);
        getline(curr_line, temp_str, ',');
        
        d = 1;
        while (getline(curr_line, temp_str, ',')) {

            //cout << stod(temp_str.c_str()) << " ";
            coordinates.push_back(atof(temp_str.c_str())); 
            d++;
        }
        //cout << endl;

        item = new struct Item<double>(ident , coordinates, -1);
        items.push_back(item);

        coordinates.clear();
        
        i++;
    }

    input_file.close();
    
    d--;
    N = i-1;

    // for( i = 0 ; i < N ; i++ ){
    //     items[i]->Print_Item();
    // }
    
    cout << "Number of points = " << N << endl;
    cout << "Dimension = " << d << endl;
        
}

void read_conf(ifstream& conf_file, int& k, int & L, int& n_clusters ){
	string line,temp_str;	

	while(getline(conf_file,line)){

        istringstream curr_line(line);

        getline(curr_line, temp_str, ' ');

        if(!temp_str.compare("number_of_clusters:")){
        	
        	getline(curr_line, temp_str, ' ');
            n_clusters = atoi(temp_str.c_str());
            
        }
        else if(!temp_str.compare("number_of_hash_functions:")){

        	getline(curr_line, temp_str, ' ');
            if(temp_str.compare("")){
        	   k = atoi(temp_str.c_str());
            }
        }
        else if(!temp_str.compare("number_of_hash_tables:")){

        	getline(curr_line, temp_str, ' ');
            if(temp_str.compare("")){
        	   L = atoi(temp_str.c_str());
            }
        }        
	}

	conf_file.close();

	cout << "Number of clusters = " << n_clusters << endl;
	cout << "Number of hash functions = " << k << endl;
	cout << "Number of Hashtables = " << L << endl;
	
}

int read_prompt(int& in,int& as,int& up){
    char* com = new char[100];
    cout << "Do you want to define the algorithms you want run?" << endl;
    cin >> com;
    if(!strcmp(com,"yes")){
        
        cout << "Tell me the algorithm you want to use for Initialisation!" << endl;
        cin >> com;
        
        if(!strcmp(com,"Random selection")){
            in = 0;
        }
        else if(!strcmp(com,"Kmeans")){
            in = 1;
        }
        else{
            cout << "Undefined algorithm" << endl;
            return 0;
        }

        cout << "Tell me the algorithm you want to use for Assignment!" << endl;
        cin >> com;

        if(!strcmp(com,"Lloyds")){
            as = 0;
        }
        else if(!strcmp(com,"Lsh")){
            as = 1;
        }
        else if(!strcmp(com,"Hypercube")){
            as = 2;
        }
        else{
            cout << "Undefined algorithm" << endl;
            return 0;
        }

        cout << "Tell me the algorithm you want to use for Update!" << endl;
        cin >> com;

        if(!strcmp(com,"Kmeans")){
            up = 0;
        }
        else if(!strcmp(com,"Pam")){
            up = 1;
        }
        else{
            cout << "Undefined algorithm" << endl;
            return 0;
        }

    }
    else{
        in = as = up = -1;
    }
    delete[] com;
    return 1;
}

void run(int &k,int &d,int &L,int &N,int &m,vector<struct Item <double>*> &items,int &n_clusters,vector<Cluster* > &clusters){
        for(int i = 0 ; i < 2 ; i++){

            for(int j = 0 ; j < 3 ; j++){
            
                for(int t = 0 ; t < 2 ; t++){

                    //INITIALISIATION
                    if(i == 0){
                        random_selection(items,n_clusters,N,clusters);
                    }
                    else{
                        kmeansplus(items,n_clusters,N,clusters,m);
                    }

                    //ASSIGNMENT
                    if(j == 0){
                        lloyds(items,n_clusters,N,clusters,m);
                    }
                    else if(j == 1){
                        lsh_search(k,d,L,N,m,items,n_clusters,clusters);
                    }
                    else{
                        cube_search(k,d,L,N,m,items,n_clusters,clusters);
                    }

                    //UPDATE
                    if(t == 0){
                        pam(items,n_clusters,N,clusters,m);
                    }
                    else{
                        kmeans(items,n_clusters,N,clusters,m,d);
                    }
                }

            }
        }    
} 

// // Add id to the already existed DataSet
// int add_id_to_data(ifstream &input_file,string name, string& new_input_fn) {
//     new_input_fn = name + "_id";

//     //ifstream input_file(input_fn);
//     ofstream new_file(new_input_fn);
//     string line;
//     string curr_line;
//     string new_line;
//     string temp_str;
//     uint32_t id = 1;
//     if (input_file.is_open() && new_file.is_open()) {
//         if (getline(input_file, line)) {
//             istringstream curr_line(line);

//             getline(curr_line, temp_str, ' ');

//             // If line has metric just copy it or radious
//             if (!temp_str.compare("euclidean")){
//                 //cout << "euclidean"<< endl;
//                 new_file << line;
//                 new_file << '\n';
//             }
//             else if(!temp_str.compare("cosine")){
//                 //cout << "cosine" << endl;
//                 new_file << line;
//                 new_file << '\n';
//             }
//             else if( temp_str.empty() ){
//                 //cout << "euclidean" << endl;
//                 new_file << line;
//                 new_file << '\n';            
//             }
//             else if(!temp_str.compare("Radius:")){
//                 //cout << "Radius" << endl;
//                 new_file << line;
//                 new_file << '\n';
//             }
//             else {
//             	new_file << '\n';
//             	 // If we are here mean that the line has a point
//             	new_line = "item_id" + std::to_string(id)  + ' ' + line + '\n';
//             	new_file << new_line;
//             	id++;
//             }
//         }
//     }
//     else return 1;

//     if (input_file.is_open() && new_file.is_open()) {
//         while (getline(input_file, line)) {
//             istringstream curr_line(line);

//             getline(curr_line, temp_str, ' ');

//             // If line has metric just copy it
//             if (temp_str.empty()) continue;

//             // If we are here mean that the line has a point
//             new_line = "item_id" + std::to_string(id)  + ' ' + line + '\n';
//             new_file << new_line;
//             id++;
//         }
//         new_file.close();
//         input_file.close();
//     }
//     else return 1;

//     return 0;
// }