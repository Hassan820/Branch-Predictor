
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <cmath>
#include <bitset>

using namespace std;

struct config
{
    int size1;
};

int main(int argc, char* argv[])
{
    config branchconfig;
    ifstream branch_params;
    branch_params.open(argv[1]);
    
    while(!branch_params.eof())  // read config file
    {
        branch_params>>branchconfig.size1;
    }
    
    long x = pow(2,branchconfig.size1);
    int A[x-1];
    
    for(int i =0;i<x;i++)
    {
        A[i] = 3;
    }
    
    int misprediction =0;
    int total =0;
    int correct =0;
    ifstream traces;
    ofstream tracesout;
    string outname;
    outname = string(argv[2]) + ".out";
    int j = 0;
    traces.open(argv[2]);
    tracesout.open(outname.c_str());
    
    int m = 32-branchconfig.size1;
    int bit;
    string line;
    string hexa;
    unsigned int integeraddress;
    bitset<32> bitaddress;
    bitset<32> index;

    if (traces.is_open()&&tracesout.is_open()){
        while (getline (traces,line)){   // read mem access file and access Cache
            
            istringstream iss(line);
            
            if (!(iss >> hexa >> bit)){
                break;
            }
            stringstream saddr(hexa);            
            saddr >> std::hex >> integeraddress;
            total ++;
            bitaddress = bitset <32> (integeraddress);
            index = (bitset<32>((bitaddress.to_string().substr(m,31))).to_ulong());
            int arr_index = index.to_ulong();
            
            if (bit == 0){    
             
                 if(A[arr_index]==0){
                     A[arr_index]=0;
                     correct++;
                     j = 0;
                 }
                 else if(A[arr_index]==1){
                     A[arr_index]=0;
                     correct++;
                     j = 0;
                 }
                 else if(A[arr_index]==2){
                     A[arr_index]=0;
                     misprediction++;
                     j = 1;
                 }
                 else if (A[arr_index]==3)
                     A[arr_index]=2;
                     misprediction++;
                     j = 1;
                 }
            }
            else{    
                 if(A[arr_index]==3){
                        A[arr_index]=3;
                        correct++;
                        j = 1;
                 }
                 else if(A[arr_index]==2){
                        A[arr_index]=3;
                        correct++;
                        j = 1;
                            
                 }
                 else if(A[arr_index]==1){
                        A[arr_index]=3;
                        misprediction++;
                        j = 0;
                 }
                 else if (A[arr_index]==0){
                                A[arr_index]=1;
                                misprediction++;
                               j = 0;
                 }
           }
           tracesout<<j<<endl;
             
        }
        cout<<"Mispredicted is " <<misprediction <<"\t";
        cout<<"correct is "<< correct <<"\n";
        cout<<"total" << total <<"\n";
        float xx = (float(misprediction) / float(total)) * 100 ;
        cout<<"misprediction rate " << xx <<" \n";
        traces.close();
        tracesout.close(); 
    }
    else cout<< "Unable to open trace or traceout file ";

    return 0;
}
