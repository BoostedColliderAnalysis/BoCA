# include "HMva.hh"

# include "TObjArray.h"
# include "TClonesArray.h"


# include "ExRootAnalysis/ExRootTreeReader.h"
# include "ExRootAnalysis/ExRootTreeWriter.h"

# include "JetInfo.hh"
# include "Event.hh"
# include "Analysis.hh"

HObservable::HObservable(float &value, const std::string &expression, const std::string &title, const std::string &unit, const std::string &latex)
{
    value_ = &value;
    expression_ = expression;
    title_ = title;
    unit_ = unit;
    if (value == int(value)) type_ = 'I';
    else type_ = 'F';
}

float *HObservable::value() const
{
    return value_;
}

std::string HObservable::expression() const
{
    return expression_;
}

std::string HObservable::title() const
{
    return title_;
}

std::string HObservable::unit() const
{
    return unit_;
}

char HObservable::type() const
{
    return type_;
}

/**
 * @brief Constructor
 *
 *
 * choose HDetectorType according to LHC or 100TeV
 *
 * LHC: CMS
 * 100TeV: Spp
 *
 */

analysis::HMva::HMva() : detector_geometry()
{

//   DebugLevel = kNotification;
    Print(kInformation, "Constructor");
    cut_method_name_ = "Cut";
    bdt_method_name_ = "Bdt";
    cut_ = "";
    weight_branch_name_ = "Info";
    max_combi_ = 4;
//     MinCellResolution = .1;
}

float analysis::HMva::GetBdt(TObject *, const TMVA::Reader &)
{
    Print(kError, "Get Bdt", "should be implemented somewhere else");
    return -10;
}

HObservable analysis::HMva::NewObservable(float &value, const std::string &title) const
{
    Print(kInformation, "New Observable", title);
    const std::string expression = branch_name_ + "." + title;
    return HObservable(value, expression, title, "", "");
}

HObservable analysis::HMva::NewObservable(float &value, const std::string &title, const std::string &latex) const
{
    Print(kInformation, "New Observable", title);
    const std::string expression = branch_name_ + "." + title;
    return HObservable(value, expression, title, "", latex);

}

Jets analysis::HMva::GranulatedJets(const Jets &NewEFlowJets)
{
    // start of granularization of the hadronic calorimeter to redefine hadrons
    const float CellDeltaRap = detector_geometry.MinCellResolution;
    const float CellDeltaPhi = detector_geometry.MinCellResolution;
    const float PtCutOff = detector_geometry.MinCellPt;


    Jets EFlowJets = sorted_by_pt(NewEFlowJets);
    Jets NewGranulatedJets;
    NewGranulatedJets.push_back(EFlowJets[0]);

    for (std::size_t i = 1; i < EFlowJets.size(); ++i) {
        int NewJet = 0;

        for (std::size_t j = 0; j < NewGranulatedJets.size(); ++j) {

            const float CellDiffRap = std::abs(EFlowJets[i].pseudorapidity() - NewGranulatedJets[j].pseudorapidity()) / CellDeltaRap;
            float CellDiffPhi = std::abs(EFlowJets[i].phi() - NewGranulatedJets[j].phi());
            if (CellDiffPhi > Pi) CellDiffPhi = TwoPi - CellDiffPhi;
            CellDiffPhi = CellDiffPhi / CellDeltaPhi;

            if (CellDiffRap < 1 && CellDiffPhi < 1) {

                NewJet = 1;

                const float TotalEnergy  = EFlowJets[i].e() + NewGranulatedJets[j].e();
                const float RescaleFactor = sqrt(pow(EFlowJets[i].px() + NewGranulatedJets[j].px(), 2) + pow(EFlowJets[i].py() + NewGranulatedJets[j].py(), 2) + pow(EFlowJets[i].pz() + NewGranulatedJets[j].pz(), 2));
                const float RescaledPx = TotalEnergy * (EFlowJets[i].px() + NewGranulatedJets[j].px()) / RescaleFactor;
                const float RescaledPy = TotalEnergy * (EFlowJets[i].py() + NewGranulatedJets[j].py()) / RescaleFactor;
                const float RescaledPz = TotalEnergy * (EFlowJets[i].pz() + NewGranulatedJets[j].pz()) / RescaleFactor;

                fastjet::PseudoJet CombinedJet(RescaledPx, RescaledPy, RescaledPz, TotalEnergy);


                std::vector<Constituent> constituents;
                std::vector<Constituent> Newconstituents = EFlowJets[i].user_info<analysis::JetInfo>().constituents();
                constituents.insert(constituents.end(), Newconstituents.begin(), Newconstituents.end());
                Newconstituents = NewGranulatedJets[j].user_info<analysis::JetInfo>().constituents();
                constituents.insert(constituents.end(), Newconstituents.begin(), Newconstituents.end());

                CombinedJet.set_user_info(new JetInfo(constituents));

                NewGranulatedJets.erase(NewGranulatedJets.begin() + j);
                NewGranulatedJets.push_back(CombinedJet);
                break;

            }
        }

        if (NewJet != 1) {
            NewGranulatedJets.push_back(EFlowJets[i]);
            NewGranulatedJets = sorted_by_pt(NewGranulatedJets);
        }
    }


    for (std::size_t ii = 0; ii < NewGranulatedJets.size(); ++ii) {

        if ((NewGranulatedJets[ii].perp() < PtCutOff)) {
            NewGranulatedJets.erase(NewGranulatedJets.begin() + ii);
            --ii;
        }
    }

    return NewGranulatedJets;

}

Jets analysis::HMva::GetJets(analysis::Event &event, HJetTag &JetTag)
{
    Print(kInformation, "JetTag", JetTag.HeavyParticles.size());
    return GetJets(event);
}

Jets analysis::HMva::GetJets(analysis::Event &event)
{
//   fastjet::ClusterSequence *ClusterSequence = new fastjet::ClusterSequence(GranulatedJets(event.hadrons().GetStructuredEFlowJets()), fastjet::JetDefinition(fastjet::cambridge_algorithm, detector_geometry.JetConeSize));
    fastjet::ClusterSequence *ClusterSequence = new fastjet::ClusterSequence(GranulatedJets(event.hadrons().GetStructuredEFlowJets()), detector_geometry.JetDefinition);
    Jets jets = fastjet::sorted_by_pt(ClusterSequence->inclusive_jets(detector_geometry.JetMinPt));
    if (jets.size() < 1) {
        delete ClusterSequence;
        return jets;
    }
    ClusterSequence->delete_self_when_unused();
    for (auto & Jet : jets)  {
        std::vector<Constituent> constituents;
        for (const auto & constituent : Jet.constituents()) {
            std::vector<Constituent> Newconstituents = constituent.user_info<JetInfo>().constituents();
            constituents.insert(constituents.end(), Newconstituents.begin(), Newconstituents.end());
        }
        Jet.set_user_info(new JetInfo(constituents));
    }
    return jets;
}

Jets analysis::HMva::GetSubJets(const fastjet::PseudoJet &Jet, const int SubJetNumber)
{
    Print(kInformation, "Get Sub Jets");
    Jets Pieces;
    if (!Jet.has_constituents()) {
        Print(kError, "Pieceless jet");
        return Pieces;
    }
    if (!Jet.has_user_info<JetInfo>()) {
        Print(kError, "Get Sub Jets", "No Jet Info");
        return Pieces;
    }
//     fastjet::ClusterSequence *ClusterSequence = new fastjet::ClusterSequence(Jet.constituents(), fastjet::JetDefinition(fastjet::kt_algorithm, detector_geometry.JetConeSize));
    fastjet::ClusterSequence *ClusterSequence = new fastjet::ClusterSequence(Jet.constituents(), detector_geometry.SubJetDefinition);
    Jets NewPieces = ClusterSequence->exclusive_jets_up_to(SubJetNumber);
    ClusterSequence->delete_self_when_unused();

    for (auto & Piece : NewPieces) {
        std::vector<Constituent> constituents;
        for (const auto & Piececonstituent : Piece.constituents()) {
            if (!Piececonstituent.has_user_info<JetInfo>()) {
                Print(kError, "Get Sub Jets", "No Piece constituent Info");
                continue;
            }
            std::vector<Constituent> Newconstituents = Piececonstituent.user_info<JetInfo>().constituents();
            constituents.insert(constituents.end(), Newconstituents.begin(), Newconstituents.end());
        }
        Piece.set_user_info(new JetInfo(constituents, Jet.user_info<JetInfo>().BTag()));
        Pieces.push_back(Piece);
    }
    return Pieces;
}

fastjet::PseudoJet analysis::HMva::GetMissingEt(analysis::Event &event)
{
    Jets granulated_jets = GranulatedJets(event.hadrons().GetStructuredEFlowJets());
    fastjet::PseudoJet jet_sum = std::accumulate(granulated_jets.begin(), granulated_jets.end(), fastjet::PseudoJet());
    return fastjet::PseudoJet(-jet_sum.px(), -jet_sum.py(), -jet_sum.pz(), jet_sum.e());
}
