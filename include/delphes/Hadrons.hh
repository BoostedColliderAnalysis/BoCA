#pragma once

#include "../Hadrons.hh"
#include "TClonesArray.h"

namespace analysis
{

namespace delphes
{

/**
 * @brief Delphes jets
 *
 */
class Hadrons : public analysis::Hadrons
{

public:

    /**
     * @brief constructor
     *
     */
    Hadrons();

    analysis::Jets Jets() {
        NewEvent(*clones_arrays_);
        switch (DetectorGeometry().jet_type) {
        case JetType::jet :
          return DelphesJets(JetDetail::structure);
        case JetType::gen_jet :
            return GenJets();
        case JetType::e_flow_jet :
          return ClusteredJets();
        }
    }

    float ScalarHt();

    fastjet::PseudoJet MissingEt();

protected:

     std::string NameSpaceName() const {
        return "delphes";
    }

private:

    void DoubleCounting();

    analysis::Jets GranulatedJets(const analysis::Jets &jets);

    analysis::Jets ClusteredJets();

    analysis::Jets DelphesJets(const JetDetail jet_detail);

    analysis::Jets EFlowJets(const JetDetail jet_detail);

    analysis::Jets GenJets();

    template <typename Clone>
    JetInfo JetId(const Clone &clone) {
        Print(Severity::detailed, "Jet Id", clone.Particles.GetEntriesFast());
        JetInfo jet_info;
//         if(clone.IsA() == ::delphes::Jet::Class()) jet_info.SetDelphesTags(clone);
        for (const int ParticleNumber : Range(clone.Particles.GetEntriesFast())) {
            const Family family = BranchFamily(*clone.Particles.At(ParticleNumber));
            Print(Severity::debug, "MotherId", family.particle().Id, family.mother_1().Id);
            jet_info.AddConstituent(Constituent(const_cast<Clone &>(clone).P4(), family));
        }
        jet_info.PrintAllInfos(Severity::debug);
        return jet_info;
    }


    template<typename Particle, typename EFlow>
    bool GetIsolation(const EFlow &e_flow, const TClonesArray &clones_array) const {
        bool Isolated = true;
        for (int particle_number = 0; particle_number < clones_array.GetEntriesFast(); ++particle_number) {
            Particle &particle = static_cast<Particle &>(*clones_array.At(particle_number));
            Isolated = CheckIsolation(e_flow, particle);
        }
        return Isolated;
    }

    analysis::Jets EFlowTrack(const JetDetail);

    analysis::Jets EFlowPhoton(const JetDetail);

    analysis::Jets EFlowHadron(const JetDetail);

    analysis::Jets EFlowMuon(const JetDetail);

    fastjet::PseudoJet StructuredJet(const ::delphes::Jet &JetClone, const JetDetail jet_detail);

    fastjet::PseudoJet ConstituentJet(TObject &Object, const JetDetail jet_detail, const SubDetector sub_detector = SubDetector::none);

};

}

}
