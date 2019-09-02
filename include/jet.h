/*
 * jet.h
 *
 *  Created on: 2 Sep 2019
 *      Author: jkiesele
 */

#ifndef INCLUDE_JET_H_
#define INCLUDE_JET_H_

#include "particle.h"

//just the same, but no ambiguities
class jet{
public:
    jet();
    jet(const TLorentzVector& trueP4,
            const TLorentzVector& recoP4):
                truep4_(trueP4),recop4_(recoP4){
        setTrueP4(trueP4);
    }

    const TLorentzVector& p4()const{
        return recop4_;
    }

    const TLorentzVector& trueP4()const{
        return truep4_;
    }

    void setTrueP4(const TLorentzVector& trueP4){
        truep4_ = trueP4;
        truept_ = truep4_.Pt();
        recopt_ = recop4_.Pt();
    }

    inline float deltaTruth()const{
        return recopt_-truept_;
    }

    const float& pt()const{
        return recopt_;
    }

    const float& truePt()const{
        return truept_;
    }

    bool genMatched()const{
        return truept_>0.1;
    }

private:
    TLorentzVector truep4_, recop4_;
    float truept_,recopt_;

};





#endif /* INCLUDE_JET_H_ */
