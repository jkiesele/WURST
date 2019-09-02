/*
 * particle.h
 *
 *  Created on: 2 Sep 2019
 *      Author: jkiesele
 */

#ifndef INCLUDE_PARTICLE_H_
#define INCLUDE_PARTICLE_H_

#include "TLorentzVector.h"
#include <vector>


//base class for all algorithms whether sim or reco
//for sim: getProb returns one-hot encoded output
//         getP4 returns 0 expect for right pdgID
class particle{
public:

    enum particleType{electron=0, photon=1, chargedpion=2}; //...

    static particleType pdgIDToType(int pdgid);

    static constexpr size_t nparticletypes=3;

    particle();
    particle(const TLorentzVector& trueP4,
            int truePdgID,
            const std::vector<float>& idprobs,
            std::vector<TLorentzVector> recoP4s);

    particleType getMaxProb() const{
        return maxprob_;
    }

    const TLorentzVector& getP4(particleType t)const{
        return p4s_.at(t);
    }

    const float& getProb(particleType t)const{
        return prob_.at(t);
    }

    const TLorentzVector& getTrueP4()const{
        return trueP4_;
    }

    const int& getTruePdgID()const{
        return truePdgId_;
    }


private:


    std::vector<float> prob_;
    std::vector<TLorentzVector> p4s_;
    TLorentzVector trueP4_;
    int truePdgId_;

    particleType maxprob_;
};



#endif /* INCLUDE_PARTICLE_H_ */
