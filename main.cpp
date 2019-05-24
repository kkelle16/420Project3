//
//  main.cpp
//  420project3
//
//  Created by Kelsey Kelley on 3/7/19.
//  Copyright © 2019 Kelsey Kelley. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>
#include <time.h>
#include <stdlib.h>

using namespace std;

//Function to intialize neuron vectors to have either 1 or -1 values
vector<int> initializeVector(vector<int> &v){

    int random;
    //srand((unsigned)(time(NULL)));
    for(int i = 0; i < 100; i++){
    
        random = rand()%20;
        
        if(random%2 == 0){
            
            v[i] = -1;
            
        }else{
            
            v[i] = 1;
        }
    }
    
    return v;
}

int main(int argc, const char * argv[]) {
 
    //setting up all variables
    map<int, vector<int> > neurons;
    map<int, vector<int> >::iterator nit;
    
    vector<int> v;
    vector<vector<double> > weights;
    double h = 0;
    vector<int> neuralNet;
    vector<double> counter;
    
    vector<double> stableProb;
    vector<double> unstableProb;
    
    vector<int> nextState;
    
    //initializing any variables that need it
    stableProb.resize(50);
    unstableProb.resize(50);
    counter.resize(50, 0);
    
    //creating all 50 vectors keyed on index number
    for(int i = 0; i < 50; i++){
        
        v.clear();
        v.resize(100,0);
        v = initializeVector(v);
        neurons.insert(make_pair(i, v));
        
    }
    
    //initializing the weights vector
    weights.resize(100);
    
    for(int i = 0; i < 100; i++){
        
        weights[i].resize(100,0);
        
    }
    
    //looping through all patterns p
    for(int p = 0; p < 50; p++){
        
        //looping through all elements in the neurons
        //in order to calculate the associated weights
        for(int i = 0; i < 100; i++){
            
            for(int j = 0; j < 100; j++){
                
                if(i == j){
                    
                    weights[i][j] = 0;
                    
                }else if(i != j){
                    
                    nit = neurons.find(p);
                    weights[i][j] = weights[i][j] + ((1/100) * ((nit->second[i] * nit->second[j])));
                }
                
            }
            
            //appropriately clearing and resizing variables as needed
            neuralNet.clear();
            neuralNet.resize(100);
            neuralNet = nit->second;
            nextState.clear();
            nextState.resize(100);
            
            for(int m = 0; m < 100; m++){
                
                //calculating the local field of the neuron to find the next state
                h = h + weights[i][m] * neuralNet[i];
                if(h < 0){
                        
                    nextState[i] = -1;
                        
                }else if(h >= 0){
                        
                    nextState[i] = 1;
                        
                }
                    
            }
            //comparing the 2 states and updating counter appropriately
            if(nextState[i] == neuralNet[i]){
                    
                counter[p] = counter[p]+1;
                    
            }
            
        }

        //calculating the stable and unstable probability for each pattern
        stableProb[p] = counter[p]/(50);
        unstableProb[p] = 1-stableProb[p];
        //clearing variables before next loop
        counter.clear();
        weights.clear();
        
        for(int v = 0; v < 100; v++){
            
            weights[v].clear();
            
        }
        
        //reinitializing needed variables
        counter.resize(50,0);
        weights.resize(100);
        
        for(int w = 0; w < 100; w++){
            
            weights[w].resize(100,0);
            
        }
        
        h = 0;
        
    }
    
    //printing out the 2 probabilities
    cout << "Stable Probability:" << endl;
    for(int j = 0; j < 50; j++){
        
        cout << stableProb[j] << endl;
        
    }
     
    cout << "Unstable Probability:" << endl;
    for(int i = 0; i < 50; i++){
        
        cout << unstableProb[i] << endl;
        
    }
    
    return 0;
    
}
