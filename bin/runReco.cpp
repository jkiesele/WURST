/*
 * runReco.cpp
 *
 *  Created on: 2 Sep 2019
 *      Author: jkiesele
 */

#include <iostream>
#include "TString.h"

#include "generator.h"
#include "reconstruction.h"

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

    generator gen;
    reconstruction reco;

    for(size_t event=0;event<10;event++){

        auto genparticles = gen.generateEvent();

      //  std::cout << "gen particles " << std::endl;
        for(const auto& p:genparticles){
       //     std::cout << p.getTruePdgID() << " : " << p.getTrueP4().Pt() << std::endl;
        }

        //just for fun, run jet reco

        std::vector<jet> dummy;
        auto genjets =reco.makeJets(genparticles,dummy,false);

        std::cout << "genjets " << std::endl;
        for(const auto& jet: genjets){
            std::cout << jet.pt() << " " << jet.p4().Eta() << std::endl;
        }

        auto metp4 = reco.calculateMet(genparticles, false);
        std::cout << "genmet " << std::endl;
        std::cout << metp4.Pt() << " " << metp4.Px() << " " << metp4.Py()<< std::endl;

    }

}
