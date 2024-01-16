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
    fstream imageService;
    string imageContents;
    bool intFlag = 0;
    string xInput;
    
    while(state != CLOSE_STATE){
        switch(state){
            case INIT_STATE:
                state = RUNNING_STATE;
                cout << "Waiting for image-service.txt to be populated.." << endl;
            break;
            
            case RUNNING_STATE:
                imageService.open("image-service.txt", ios::in);
                if(imageService.is_open()){
                    while(getline(imageService, imageContents)){
                        //Do nothing, just buffering into imageContents
                    }
                    imageService.close();
                } else {
                    //Do nothing. Just to catch If
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
                }
                else if(stoi(imageContents) >= 0 && stoi(imageContents) <= 255){
                    cout << "Please write X to continue program. Demonstrate program to recording here." << endl;
                    while(xInput.compare("X")!=false){
                        cin >> xInput;
                    }
                    xInput = "hello";
                    cout << "Contents found. Number: " << imageContents << endl;
                    imageService.open("image-service.txt", ios::out);
                    if(imageService.is_open()){
                        imageService << "../images/" << imageContents << ".jpg";
                        imageService.close();
                        cout << "Wrote path to image associated with " << imageContents << endl;
                    } else{
                        //Do nothing. just to catch
                    }
                    state = INIT_STATE;
                } else {
                    //Do nothing
                }
            break;
            
            case CLOSE_STATE:
                state = CLOSE_STATE;
            break;
            
            default:
                state = CLOSE_STATE;
            break;
        }
        usleep(1000000);
    }
    
    return 0;
}