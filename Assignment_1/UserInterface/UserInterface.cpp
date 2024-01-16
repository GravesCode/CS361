#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <unistd.h>

#define INIT_STATE          0
#define PRNG_READ           1
#define IMAGE_SERVICE_READ  2
#define CLOSE_STATE         3

using namespace std;

int main(void){
    
    int state = INIT_STATE;
    fstream prngService;
    fstream imageService;
    string userCommand;
    string prngContents;
    string imageContents;
    int warningFlag = 0;
    int intFlag = 0;
    
    while(state != CLOSE_STATE){
        switch(state){
            case INIT_STATE:
                cout << "Welcome to the program. Please type your command." << endl;
                cout << "Options: 'run' to execute program or 'exit' to quit." << endl;
                cin >> userCommand;
                if(userCommand.compare("run") == 0){
                    state = PRNG_READ;
                    prngService.open("../PRNGService/prng-service.txt", ios::out);
                    if(prngService.is_open()){
                        prngService << "run";
                        prngService.close();
                    }
                }
                else if(userCommand.compare("exit") == 0){
                    state = CLOSE_STATE;
                }
                //TODO: WRITE 'run' to prng-service.txt
                
            break;
            
            case PRNG_READ:
                if(warningFlag == 0){
                    cout << "Waiting for PRNG population..." << endl;
                    warningFlag = 1;
                } else {
                    //Do nothing
                }
                
                prngService.open("../PRNGService/prng-service.txt", ios::in);
                if(prngService.is_open()){
                    while(getline(prngService, prngContents)){
                        //Do nothing, just buffering into prngContents
                    }
                    prngService.close();
                    if(prngContents.compare("run")==0){
                        //Do nothing. Still being populated.
                    }
                    else if(stoi(prngContents) >= 0 && stoi(prngContents) <= 255){
                        cout << "Caught number. Reading: " << prngContents << endl;
                        
                        /* 4.	UI writes the pseudo-random number to image-service.txt*/
                        state = IMAGE_SERVICE_READ;
                        warningFlag = 0;
                        imageService.open("../ImageService/image-service.txt", ios::out);
                        if(imageService.is_open()){
                            imageService << prngContents;
                            imageService.close();
                        }
                    }
                
                //TODO: Timeout after 3 minutes    
            }
            break;
            
            case IMAGE_SERVICE_READ:
                if(warningFlag==0){
                    cout << "Waiting for image service to populate.." << endl;
                    warningFlag=1;
                } else {
                    //Do nothing. Warning issued once already
                }
                
                imageService.open("../ImageService/image-service.txt", ios::in);
                if(imageService.is_open()){
                    while(getline(imageService, imageContents)){
                        //Do nothing, just buffering into prngContents
                    }
                    imageService.close();
                }
                
                for(int i = 0; i < imageContents.length(); i++){
                    if(isdigit(imageContents[i])){
                        //Do nothing
                    } else{
                        intFlag = 1;
                    }
                }

                if(intFlag == 1){
                    //Resetting flag for next pass
                    intFlag = 0;

                    cout << imageContents << endl;

                    state = INIT_STATE;
                }
                else if(stoi(imageContents)!=stoi(prngContents)){
                    //Do nothing until next pass
                } else {
                    //Image service has not written anything yet. Continue to wait.
                }
            break;
            
            case CLOSE_STATE:
                state = CLOSE_STATE;
            break;
            
            default:
                //Shouldn't go here. just close
                state = CLOSE_STATE;
            break;
        }
        usleep(1000000);
    }
    return 0;
}