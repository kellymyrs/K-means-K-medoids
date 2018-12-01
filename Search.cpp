#include "Search.h"

void Range(vector<int>& c,unordered_map<int,vector <Item<int>*>>& hashtable,int& metric,double& R,int& M,int& probes,Cosine_G* cg,G* g,vector<struct Item <int>*>& range){
	struct Item <int>* temp_item = NULL;
	double temp_dist;
    uint32_t concat;
    int p = 1,h; //p = number of vertxes exploired
    vector<int64_t> g_m;

	//cout << "Range Search" << endl;

    //cosine
    if ( metric == 1){
        concat = cg->Calculate_G(c);            
    }   
    //euclidean
    if( metric == 0){
        g->Calculate_G(c,g_m);
        concat = 0;

        //cout << "H = ";
        for(int j = 0 ; j < g_m.size() ; j++){
            h = g_m[j] % 2;
            //cout << h << " " ;

            concat = (concat << 1) | h;            
        }
        //cout << endl;
    }

	//search bucket
	auto search = hashtable.find(concat);
	if(search != hashtable.end()){

		//cout << "Searching bucket" << endl;
		int i = 0;
		while(i < search->second.size() && i < M ){

			//cout << "Combining" << endl;
			temp_item = search->second[i];
			if(metric){
				temp_item->Cosine_Distance(c,temp_dist);
			}
			else{
				temp_item->Distance(c,temp_dist);
			}

			// cout << "Temp Item coordinates : ";
			// for (int j = 0; j < temp_item->coordinates.size() ; j++){
			// 	cout << temp_item->coordinates[j] << " " ;
			// }
			// cout << endl;

			//cout <<"Found distance : "<< temp_dist << endl;

			if (temp_dist < R){
				int flag = 1;
				//cout << "Adding an item to the range list" << endl;

				if(!range.empty()){ //avoid dublicates
					for( int j = 0 ; j < range.size() ; j++){
						if( range[j]->id == temp_item->id ){
							flag = 0;
						}
					}
				}
				
				if(flag){
					range.push_back(temp_item);
				}
			}
			i++;
			if( i == search->second.size() && i < M && p < probes ){
				//change vertex
				if(metric){
					concat = cg->Change_Bit(c,p);
				}
				else{
					for(int j = 0 ; j < g_m.size() ; j++){
					    h = g_m[j] % 2;
				        if(i == g_m.size()-p){
				            if(h == 0){
				                h = 1;
				            }
				            else{
				                h = 0;
				            }
				        }
					    concat = (concat << 1) | h;            
					}
				}
				search = hashtable.find(concat);
				if(search == hashtable.end()){
					cout << "Empty bucket" << endl;
				}
				p++;
			}
		}
	}
	else{
		cout << "Empty bucket" << endl;
		return;
	}

}


struct Item<int>* NN(vector<int>& c,unordered_map<int,vector <Item<int>*>>& hashtable,int& metric,int& M,int& probes,Cosine_G* cg,G* g,double& min_dist){
	struct Item <int>* temp_item = NULL ,* min_item = NULL;
	double temp_dist;
    uint32_t concat;
    int p = 1,h; //p = number of vertxes exploired
    vector<int64_t> g_m;

    //cout << "NN search" << endl;

    //cosine
    if ( metric == 1){
        concat = cg->Calculate_G(c);            
    }   
    //euclidean
    if( metric == 0){
        g->Calculate_G(c,g_m);
        concat = 0;

        //cout << "H = ";
        for(int j = 0 ; j < g_m.size() ; j++){
            h = g_m[j] % 2;
            //cout << h << " " ;

            concat = (concat << 1) | h;            
        }
        //cout << endl;
    }

	//search bucket
	auto search = hashtable.find(concat);
	if(search != hashtable.end()){

		//cout << "Searching bucket" << endl;
		int i = 0; 
		while(i < search->second.size() && i < M ){

			//cout << "Combining" << endl;
			temp_item = search->second[i];
			if(metric){
				temp_item->Cosine_Distance(c,temp_dist);
			}
			else{
				temp_item->Distance(c,temp_dist);
			}
			

			//cout << "Temp Item coordinates : ";
			//for (int j = 0; j < temp_item->coordinates.size() ; j++){
			//	cout << temp_item->coordinates[j] << " " ;
			//}
			//cout << endl;

			//cout <<"Found distance : "<< temp_dist << endl;
			//cout <<"Min distance : "<< dist << endl;
			if (temp_dist < min_dist){
				//cout << "Change minimum" << endl;
				min_dist = temp_dist;
				min_item = temp_item;

				//cout << "Min Item coordinates : ";
				//for (int j = 0; j < min_item->coordinates.size() ; j++){
				//	cout << min_item->coordinates[j] << " " ;
				//}
				//cout << endl;
			}
			i++;
			if( i == search->second.size() && i < M && p < probes ){
				//change vertex
				if(metric){
					concat = cg->Change_Bit(c,p);
				}
				else{
					for(int j = 0 ; j < g_m.size() ; j++){
					    h = g_m[j] % 2;
				        if(i == g_m.size()-p){
				            if(h == 0){
				                h = 1;
				            }
				            else{
				                h = 0;
				            }
				        }
					    concat = (concat << 1) | h;            
					}
				}
				search = hashtable.find(concat);
				if(search == hashtable.end()){
					cout << "Empty bucket" << endl;
				}
				p++;
			}
		}
		return min_item;
	}
	else{
		cout << "Empty bucket" << endl;
		return NULL;
	}
}