/*
 * reconstruction.cpp
 *
 *  Created on: 2 Sep 2019
 *      Author: jkiesele
 */



#include "fastjet/ClusterSequence.hh"
#include "fastjet/PseudoJet.hh"
#include "../include/reconstruction.h"


reconstruction::reconstruction():
jetDef_(fastjet::JetDefinition(fastjet::antikt_algorithm, 0.4)),
minjetpt_(15.)
{

}


std::vector<jet> reconstruction::makeJets(const std::vector<particle>& parts, std::vector<jet>& genjets, bool wurst)const{
    //...

    genjets.clear();

    std::vector<fastjet::PseudoJet> fjinputs, fjgeninputs;
    for(const auto& p: parts){
        if(wurst){
            for(size_t i=0;i<particle::nparticletypes;i++){
                auto  p4 = p.getP4((particle::particleType)i);
                p4 = p4*p.getProb((particle::particleType)i);
                fjinputs.push_back(fastjet::PseudoJet(p4.Px(), p4.Py(), p4.Pz(), p4.E()));
            }
        }
        else{
            const auto&  p4 = p.getP4(p.getMaxProb());
            fjinputs.push_back(fastjet::PseudoJet(p4.Px(), p4.Py(), p4.Pz(), p4.E()));
        }
        if(p.getTruePdgID()!=0){ //no fake, neutrinos where already killed in reconstruction matrix
            const auto& p4 = p.getTrueP4();
            fjgeninputs.push_back(fastjet::PseudoJet(p4.Px(), p4.Py(), p4.Pz(), p4.E()));
        }
    }

    fastjet::ClusterSequence seq(fjinputs, jetDef_);
    auto fjrecojets(fastjet::sorted_by_pt(seq.inclusive_jets(minjetpt_)));//min pt

    std::vector<jet> recojets;
    for(const auto j:fjrecojets){
        TLorentzVector fakegen(1,1,0,0);
        fakegen.SetPtEtaPhiE(0,0,0,0);
        jet njet(fakegen, TLorentzVector(j.px(),j.py(),j.pz(),j.e()));
        recojets.push_back(njet);
    }
    //match


    fastjet::ClusterSequence genseq(fjgeninputs, jetDef_);
    auto fjgenjets(fastjet::sorted_by_pt(genseq.inclusive_jets(minjetpt_)));//min pt

    //simple matching
    //can be improved IMPROVEMENT POSSIBLE
    for(const auto genj:fjgenjets){
        TLorentzVector genp4(genj.px(),genj.py(),genj.pz(),genj.e());
        double genpt = genp4.Pt();
        double mindr=0.1;
        for(auto& j:recojets){
            double dr = j.p4().DeltaR(genp4);
            if(dr<mindr && fabs(j.pt() - genpt)/genpt < 0.5 ){ //matchin criterion
                dr=mindr;
                j.setTrueP4(genp4);
            }

        }
    }

    return recojets;

}
