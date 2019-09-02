/*
 * runReco.cpp
 *
 *  Created on: 2 Sep 2019
 *      Author: jkiesele
 */

#include <iostream>
#include "TString.h"

void coutHelp(){
    std::cout << "\nUSAGE: runReco <options> \n";
}


int main(int argc, char* argv[]){

    for(int i=1;i<argc;i++){
        TString targv=argv[i];
        if(targv == ("--help") || (targv.BeginsWith("-") && targv.Contains("h"))){
            coutHelp();
            return 0;
        }
    }


    //do stuff


}
