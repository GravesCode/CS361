#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <unistd.h>

#define INIT_STATE      0
#define RUNNING_STATE   1
#define CLOSE_STATE     2

using namespace std;

int main(void){
    
    int state = INIT_STATE;
    fstream prngService;
    string prngContents;
    //Provide a seed value for PRNG
    srand((unsigned) time(NULL));
    int random;
    int warningFlag = 0;
    string xInput;

    while(state!= CLOSE_STATE){
        
        switch(state){
            
            case INIT_STATE:
                cout << "Waiting for prng-service.txt to be populated..." << endl;
                state = RUNNING_STATE;
            break;
            
            case RUNNING_STATE:
                //TODO: READ prng-service.txt
                if(warningFlag == 0){
                    cout << "Reading prng-service.txt.." << endl;
                    warningFlag = 1;
                }
                
                prngService.open("prng-service.txt", ios::in);
                if(prngService.is_open()){
                    while(getline(prngService, prngContents)){
                        //Do nothing, just buffering into prngContents
                    }
                    prngService.close();
                }

                if(prngContents.compare("run") == 0){
                    cout << "Please write X to continue program. Demonstrate program to recording here." << endl;
                    while(xInput.compare("X")!=false){
                            cin >> xInput;
                    }
                    xInput = "hello";
                    cout << "Run command received. Generating a random number." << endl;
                    prngService.open("prng-service.txt", ios::out);
                    if(prngService.is_open()){
                        
                        //Generate PRNG and add to prngService
                        random = (rand() % 255);
                        prngService << random;
                        prngService.close();
                        cout << "Random number generated. Writing: " << random << endl;
                    }
                    
                    state = INIT_STATE;
                } else {
                    //Do nothing
                }            
            break;
            
            case CLOSE_STATE:
                //Should not reach here, but just in case some compiler nonsense
                //TODO: Reinitialize instead of close
                cout << "Program finished. Closing." << endl;
                warningFlag = 0;
                state = CLOSE_STATE;
            break;
            
            default:
                //Should not end here - close anyway
                state = CLOSE_STATE;
            break;
        }
        
        usleep(1000000);
    }

    return 0;
}