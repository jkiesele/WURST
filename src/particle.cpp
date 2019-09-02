/*
 * particle.cpp
 *
 *  Created on: 2 Sep 2019
 *      Author: jkiesele
 */

#include "../include/particle.h"


particle::particleType particle::pdgIDToType(int pdgid){

    //TBI FIXME

    return electron;
}

particle::particle(){

    prob_.resize(nparticletypes);
    p4s_.resize(nparticletypes, TLorentzVector(0,0,0,0));

    trueP4_ = TLorentzVector(0,0,0,0);
    truePdgId_ = 0;

    maxprob_=electron;

}
particle::particle(const TLorentzVector& trueP4,
        int truePdgID,
        const std::vector<float>& idprobs,
        std::vector<TLorentzVector> recoP4s):
                prob_(idprobs),
                p4s_(recoP4s),
                trueP4_(trueP4),
                truePdgId_(truePdgID) {

    float maxprob=0;
    for(size_t i=0;i<nparticletypes;i++){
        if(prob_.at(i)>maxprob){
            maxprob = prob_.at(i);
            maxprob_=(particleType)i;
        }
    }

}


