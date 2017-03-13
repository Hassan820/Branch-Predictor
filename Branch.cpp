// Referenced from the cache simulator lab 2

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
    
   // cout<<"\n"<<branchconfig.size1<<" \n";
  
    long x = pow(2,branchconfig.size1);
    //cout<<x<<"\n";
    int A[x-1];
    
    for(int i =0;i<x;i++)
    {
        A[i] = 3;
    }
    /*
    for(int i =0;i<x;i++)
    {
        cout<<A[i][0]<<"\n";
    }*/
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
    //int arr_index;
    if (traces.is_open()&&tracesout.is_open()){
        while (getline (traces,line)){   // read mem access file and access Cache
            
            istringstream iss(line);
            if (!(iss >> hexa >> bit)) {break;}
            stringstream saddr(hexa);
            
            //cout<<bit<<" ";
            
            saddr >> std::hex >> integeraddress;
            total ++;
            
            
            bitaddress = bitset <32> (integeraddress);
            //cout<<bitaddress<<" ";
            index = (bitset<32>((bitaddress.to_string().substr(m,31))).to_ulong());
           // cout<<index<<" ";
            int arr_index = index.to_ulong();
            //cout<<arr_index<<" ";
            
             if (bit == 0)
             {    
                  //cout<<"Not Taken \t";
                
                 if(A[arr_index]==0)
                 {
                     A[arr_index]=0;
                     correct++;
                     //cout<< "CORRECT";
                     j = 0;

                 }
                 else if(A[arr_index]==1)
                        {
                            A[arr_index]=0;
                       //     cout<< "CORRECT";
                            correct++;
                            j = 0;

                        }
                        else if(A[arr_index]==2)
                            {
                                A[arr_index]=0;
                                misprediction++;
                                j = 1;
                     //           cout<< "MISPREDICTION";
                            }
                else if (A[arr_index]==3)
                        {
                            A[arr_index]=2;
                            misprediction++;
                            j = 1;
                   //         cout<< "MISPREDICTION";
                        }
                 
                 
                 
                 
            }
             else 
             {    
                   //Implement by you:
                 //cout<<"Taken \t";
                 if(A[arr_index]==3)
                    {
                        A[arr_index]=3;
                        correct++;
                      //  cout<< "Correct ";
                        j = 1;
                        

                    }
                 else if(A[arr_index]==2)
                        {
                            A[arr_index]=3;
                            correct++;
                            //cout<< "Correct ";
                            j = 1;
                            
                        }
                    else if(A[arr_index]==1)
                            {
                                A[arr_index]=3;
                                misprediction++;
                                j = 0;
                               // cout<< "MISPREDICTION";
                                
                            }
                        else if (A[arr_index]==0)
                            {
                                A[arr_index]=1;
                                misprediction++;
                               // cout<< "MISPREDICTION";
                               j = 0;
                                
                            }
                 
                 
                 
                 
                 
                  }
                                // tracesout<< x<< endl;
          //  cout<<" CA"<<A[arr_index] <<" \n";
                                //cout<<hexa<<" \n";
            tracesout<<j<<endl;
          // output here if anything
             
        }
        cout<<"Mispredicted is " <<misprediction <<"\t";
        cout<<"correct is "<< correct <<"\n";
        cout<<"total" << total <<"\n";
   //     cout<<"works nah  \n";
        float xx = (float(misprediction) / float(total)) * 100 ;
        cout<<"misprediction rate " << xx <<" \n";
        traces.close();
        tracesout.close(); 
    }
    else cout<< "Unable to open trace or traceout file ";


   
    
  

   
    return 0;
}
