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
#include <complex> 


using namespace std;


int main(int argc,char* argv[]){

	string d = "-0.041663746140279";
	size_t offset = 0; 
    double m = stod(&d[0], &offset); //So we want to get the value "5.9568
    cout << offset << endl;
    //double b = stod(&d[offset + n]);
	cout << m << endl;
}