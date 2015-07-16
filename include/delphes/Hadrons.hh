#pragma once

#include "../Hadrons.hh"
#include "TClonesArray.h"
#include "JetInfo.hh"

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

    analysis::Jets Jets() const final {
        switch (DetectorGeometry::jet_type()) {
        case JetType::jet :
          return DelphesJets(JetDetail::structure);
        case JetType::gen_jet :
            return GenJets();
        case JetType::e_flow_jet :
          return ClusteredJets();
        }
    }
    analysis::Jets ClusteredJets();

    analysis::Jets DelphesJets(const JetDetail jet_detail);

    float ScalarHt() const final;

    fastjet::PseudoJet MissingEt() const final;

    analysis::Jets UniqueJets() const;


private:

    analysis::Jets UniqueConstituents(TObject &object, std::vector< TObject * > leptons) const;

    analysis::Jets GranulatedJets(const analysis::Jets &jets) const;

    analysis::Jets ClusteredJets() const;

    analysis::Jets DelphesJets(const analysis::JetDetail jet_detail) const;

    analysis::Jets EFlowJets(const JetDetail jet_detail) const;

    analysis::Jets GenJets() const;

    template <typename Clone>
    JetInfo JetId(const Clone &clone) const {
//         Detail("Jet Id", clone.Particles.GetEntriesFast());
        JetInfo jet_info;
//         if(clone.IsA() == ::delphes::Jet::Class()) jet_info.SetDelphesTags(clone);
        for (const int particle_number : Range(clone.Particles.GetEntriesFast())) {
            const Family family = BranchFamily(*clone.Particles.At(particle_number));
//             Debug("MotherId", family.particle().id(), family.mother_1().id());
            jet_info.AddConstituent(Constituent(const_cast<Clone &>(clone).P4(), family));
        }
        jet_info.PrintAllInfos(Severity::debug);
        return jet_info;
    }


    template<typename Particle, typename EFlow>
    bool Isolation(const EFlow &e_flow, const TClonesArray &clones_array) const {
        bool Isolated = true;
        for (int particle_number = 0; particle_number < clones_array.GetEntriesFast(); ++particle_number) {
            Particle &particle = static_cast<Particle &>(*clones_array.At(particle_number));
            Isolated = CheckIsolation(e_flow, particle);
        }
        return Isolated;
    }

    analysis::Jets EFlowTrack(const JetDetail) const;

    analysis::Jets EFlowPhoton(const JetDetail) const;

    analysis::Jets EFlowHadron(const JetDetail) const;

    analysis::Jets EFlowMuon(const analysis::JetDetail jet_detail) const;

    fastjet::PseudoJet StructuredJet(const ::delphes::Jet &jet, const analysis::JetDetail jet_detail) const;

    fastjet::PseudoJet ConstituentJet(TObject &Object, const JetDetail jet_detail, const SubDetector sub_detector = SubDetector::none) const;

};

}

}
