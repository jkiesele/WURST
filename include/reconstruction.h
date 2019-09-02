/*
 * reconstruction.h
 *
 *  Created on: 2 Sep 2019
 *      Author: jkiesele
 */

#ifndef INCLUDE_RECONSTRUCTION_H_
#define INCLUDE_RECONSTRUCTION_H_

#include "particle.h"
#include "jet.h"
#include "TRandom3.h"

#include "fastjet/JetDefinition.hh"

class reconstruction{
public:

    reconstruction();

    //input is a truth particle - make check that's true
    particle reconstruct(const particle&) const{return particle();}
    particle createFake() const{return particle();}

    //void setDetectorSetting(const detector& ){}

    std::vector<jet> makeJets(const std::vector<particle>& parts,
            std::vector<jet>& genjets, bool wurst) const;


private:
    TRandom3 rand_;

    fastjet::JetDefinition jetDef_;

    double minjetpt_;

    //and a few helpers

};



#endif /* INCLUDE_RECONSTRUCTION_H_ */
