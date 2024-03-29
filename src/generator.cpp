/*
 * generator.cpp
 *
 *  Created on: 2 Sep 2019
 *      Author: jkiesele
 */

#include "../include/generator.h"


generator::generator():
pythia_("/cvmfs/cms.cern.ch/slc7_amd64_gcc700/external/pythia8/240-nmpfii/share/Pythia8/xmldoc")
{
    pythia_.readString("WeakBosonAndParton:qg2Wq  = on"); //some met some recoil etc

    //pythia_.readString("WeakBosonExchange:ff2ff(t:gmZ) = on");

    pythia_.readString("Beams:eCM = 13000.");
    pythia_.readString("Init:showChangedParticleData = off");
    pythia_.readString("Init:showChangedSettings = on");
    pythia_.readString("Next:numberShowLHA = 0");
    pythia_.readString("Next:numberShowInfo = 0");
    pythia_.readString("Next:numberShowProcess = 0");
    pythia_.readString("Next:numberShowEvent = 0");
    pythia_.readString("PhaseSpace:pTHatMin = 10.");
    pythia_.readString("Main:numberOfEvents = 1");


    pythia_.init();

}


std::vector<particle> generator::generateEvent(){

    std::vector<particle>  outgen;

    unsigned iTry(0);
    while (true) {
        auto good = pythia_.next();
        if (!good) {
            if (++iTry < 10)
                continue;
            pythia_.stat();
            break;
        }
        else{
            break;
        }
    }

   /* const TLorentzVector& trueP4,
                int truePdgID,
                const std::vector<float>& idprobs,
                std::vector<TLorentzVector> recoP4s
*/


    /// neutrinos are excluded already here CHECK CHECK
    for (int i(0); i < pythia_.event.size(); ++i) {
        auto& part(pythia_.event[i]);
        if (part.isFinal() &&
                fabs(part.id())-12>0.5 &&
                fabs(part.id())-14>0.5 &&
                fabs(part.id())-16>0.5
        ){
            //create particle
            TLorentzVector p4(part.px(),part.py(),part.pz(),part.e());

            std::vector<float>  probs(particle::nparticletypes, 0);
            probs.at(0)=1.;
            std::vector<TLorentzVector> probp4s(particle::nparticletypes, TLorentzVector(0,0,0,0));
            probp4s.at(0)=p4;

            outgen.push_back( particle(p4, part.id(), probs,  probp4s));
        }
    }

    return outgen;

}
