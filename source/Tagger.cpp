# include "Tagger.hh"

# include "TObjArray.h"
# include "TClonesArray.h"


# include "ExRootAnalysis/ExRootTreeReader.h"
# include "ExRootAnalysis/ExRootTreeWriter.h"

# include "HJetInfo.hh"
# include "HEvent.hh"
# include "HAnalysis.hh"

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

hanalysis::Tagger::Tagger() : DetectorGeometry()
//, reader_(*this)
{

//   DebugLevel = HNotification;
    Print(HInformation, "Constructor");
    cut_method_name_ = "Cut";
    bdt_method_name_ = "Bdt";
    cut_ = "";
    weight_branch_name_ = "Info";
    max_combi_ = 4;
//     MinCellResolution = .1;

}

float hanalysis::Tagger::GetBdt(TObject *, const TMVA::Reader &)
{
    Print(HError, "Get Bdt", "should be implemented somewhere else");
    return -10;
}

HObservable hanalysis::Tagger::NewObservable(float &value, const std::string &title) const
{
    Print(HInformation, "New Observable", title);
    const std::string expression = GetBranchName() + "." + title;
    return HObservable(value, expression, title, "", "");
}

HObservable hanalysis::Tagger::NewObservable(float &value, const std::string &title, const std::string &latex) const
{
    Print(HInformation, "New Observable", title);
    const std::string expression = GetBranchName() + "." + title;
    return HObservable(value, expression, title, "", latex);

}

HJets hanalysis::Tagger::GranulatedJets(const HJets &NewEFlowJets)
{
    // start of granularization of the hadronic calorimeter to redefine hadrons
    const float CellDeltaRap = DetectorGeometry.MinCellResolution;
    const float CellDeltaPhi = DetectorGeometry.MinCellResolution;
    const float PtCutOff = DetectorGeometry.MinCellPt;


    HJets EFlowJets = sorted_by_pt(NewEFlowJets);
    HJets NewGranulatedJets;
    NewGranulatedJets.push_back(EFlowJets[0]);

    for (size_t i = 1; i < EFlowJets.size(); ++i) {
        int NewJet = 0;

        for (size_t j = 0; j < NewGranulatedJets.size(); ++j) {

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


                std::vector<HConstituent> Constituents;
                std::vector<HConstituent> NewConstituents = EFlowJets[i].user_info<hanalysis::HJetInfo>().Constituents();
                Constituents.insert(Constituents.end(), NewConstituents.begin(), NewConstituents.end());
                NewConstituents = NewGranulatedJets[j].user_info<hanalysis::HJetInfo>().Constituents();
                Constituents.insert(Constituents.end(), NewConstituents.begin(), NewConstituents.end());

                CombinedJet.set_user_info(new HJetInfo(Constituents));

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


    for (size_t ii = 0; ii < NewGranulatedJets.size(); ++ii) {

        if ((NewGranulatedJets[ii].perp() < PtCutOff)) {
            NewGranulatedJets.erase(NewGranulatedJets.begin() + ii);
            --ii;
        }
    }

    return NewGranulatedJets;

}

HJets hanalysis::Tagger::GetJets(hanalysis::HEvent &Event, HJetTag &JetTag)
{
    Print(HInformation, "JetTag", JetTag.HeavyParticles.size());
    return GetJets(Event);
}

HJets hanalysis::Tagger::GetJets(hanalysis::HEvent &Event)
{
//   fastjet::ClusterSequence *ClusterSequence = new fastjet::ClusterSequence(GranulatedJets(Event.GetJets()->GetStructuredEFlowJets()), fastjet::JetDefinition(fastjet::cambridge_algorithm, DetectorGeometry.JetConeSize));
    fastjet::ClusterSequence *ClusterSequence = new fastjet::ClusterSequence(GranulatedJets(Event.GetJets()->GetStructuredEFlowJets()), DetectorGeometry.JetDefinition);
    HJets Jets = fastjet::sorted_by_pt(ClusterSequence->inclusive_jets(DetectorGeometry.JetMinPt));
    if (Jets.empty()) {
        delete ClusterSequence;
        return Jets;
    }
    ClusterSequence->delete_self_when_unused();
    for (auto & Jet : Jets) {
        std::vector<HConstituent> Constituents;
        for (const auto & Constituent : Jet.constituents()) {
            std::vector<HConstituent> NewConstituents = Constituent.user_info<HJetInfo>().Constituents();
            Constituents.insert(Constituents.end(), NewConstituents.begin(), NewConstituents.end());
        }
        Jet.set_user_info(new HJetInfo(Constituents));
    }
    return Jets;
}

HJets hanalysis::Tagger::GetSubJets(const fastjet::PseudoJet &Jet, const int SubJetNumber)
{
    Print(HInformation, "Get Sub Jets");
    HJets Pieces;
    if (!Jet.has_constituents()) {
        Print(HError, "Pieceless jet");
        return Pieces;
    }
    if (!Jet.has_user_info<HJetInfo>()) {
        Print(HError, "Get Sub Jets", "No Jet Info");
        return Pieces;
    }
//     fastjet::ClusterSequence *ClusterSequence = new fastjet::ClusterSequence(Jet.constituents(), fastjet::JetDefinition(fastjet::kt_algorithm, DetectorGeometry.JetConeSize));
    fastjet::ClusterSequence *ClusterSequence = new fastjet::ClusterSequence(Jet.constituents(), DetectorGeometry.SubJetDefinition);
    HJets NewPieces = ClusterSequence->exclusive_jets_up_to(SubJetNumber);
    ClusterSequence->delete_self_when_unused();

    for (auto & Piece : NewPieces) {
        std::vector<HConstituent> Constituents;
        for (const auto & PieceConstituent : Piece.constituents()) {
            if (!PieceConstituent.has_user_info<HJetInfo>()) {
                Print(HError, "Get Sub Jets", "No Piece Constituent Info");
                continue;
            }
            std::vector<HConstituent> NewConstituents = PieceConstituent.user_info<HJetInfo>().Constituents();
            Constituents.insert(Constituents.end(), NewConstituents.begin(), NewConstituents.end());
        }
        Piece.set_user_info(new HJetInfo(Constituents, Jet.user_info<HJetInfo>().BTag()));
        Pieces.push_back(Piece);
    }
    return Pieces;
}

fastjet::PseudoJet hanalysis::Tagger::GetMissingEt(hanalysis::HEvent &Event)
{
    HJets granulated_jets = GranulatedJets(Event.GetJets()->GetStructuredEFlowJets());
    fastjet::PseudoJet jet_sum = std::accumulate(granulated_jets.begin(), granulated_jets.end(), fastjet::PseudoJet());
    return fastjet::PseudoJet(-jet_sum.px(), -jet_sum.py(), -jet_sum.pz(), jet_sum.e());
}
