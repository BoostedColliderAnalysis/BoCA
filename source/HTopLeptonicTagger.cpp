# include "HTopLeptonicTagger.hh"

analysis::HTopLeptonicTagger::HTopLeptonicTagger()
{
  //     DebugLevel = analysis::Object::kDebug;

  Print(kNotification, "Constructor");
  set_tagger_name("TopLeptonic");


}

analysis::HTopLeptonicTagger::HTopLeptonicTagger(const BottomTagger &NewBottomTagger)
{
//     DebugLevel = analysis::Object::kDebug;

    Print(kNotification, "Constructor");

    bottom_tagger_ = NewBottomTagger;
    BottomReader.set_tagger(bottom_tagger_);
    set_tagger_name("TopLeptonic");
    DefineVariables();
}

analysis::HTopLeptonicTagger::~HTopLeptonicTagger()
{
    Print(kNotification, "Destructor");
}

void analysis::HTopLeptonicTagger::DefineVariables()
{

    Print(kNotification , "Define Variables");

    AddVariable(Branch.Mass, "Mass");
    AddVariable(Branch.Pt, "Pt");
    AddVariable(Branch.Rap, "Rap");
    AddVariable(Branch.Phi, "Phi");

    AddVariable(Branch.BottomPt, "BottomPt");
    AddVariable(Branch.LeptonPt, "LeptonPt");

    AddVariable(Branch.DeltaPhi, "DeltaPhi");
    AddVariable(Branch.DeltaRap, "DeltaRap");
    AddVariable(Branch.DeltaR, "DeltaR");

    AddVariable(Branch.Bdt, "Bdt");
    AddSpectator(Branch.Tag, "Tag");

    Print(kNotification, "Variables defined");

}

analysis::HTopLeptonicBranch analysis::HTopLeptonicTagger::GetBranch(const analysis::Doublet &doublet)
{
    Print(kInformation, "Fill Top Tagger", doublet.Bdt());

    HTopLeptonicBranch TopLeptonicBranch;
    TopLeptonicBranch.Mass = doublet.Jet().m();
    TopLeptonicBranch.Pt = doublet.Jet().pt();
    TopLeptonicBranch.Rap = doublet.Jet().rap();
    TopLeptonicBranch.Phi = doublet.Jet().phi();

    TopLeptonicBranch.BottomPt = doublet.Singlet1().pt();
    TopLeptonicBranch.LeptonPt = doublet.Singlet2().pt();

    TopLeptonicBranch.DeltaR = doublet.DeltaR();
    TopLeptonicBranch.DeltaRap = doublet.DeltaRap();
    TopLeptonicBranch.DeltaPhi = doublet.DeltaPhi();

    TopLeptonicBranch.Bdt = doublet.Bdt();
    TopLeptonicBranch.Tag = doublet.Tag();
    return TopLeptonicBranch;

}

std::vector<analysis::HTopLeptonicBranch> analysis::HTopLeptonicTagger::GetBranches(Event &event, const Object::Tag Tag)
{

    Print(kInformation, "Top Tags");

//     jet_tag.HeavyParticles = {TopId};
    Jets jets = event.hadrons().Jets();
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader); // TODO reenable this
    Print(kInformation, "Jet Number", jets.size());

    Jets Leptons = event.leptons().leptons();
    Print(kInformation, "Lepton Number", Leptons.size());

    std::vector<Doublet> doublets;
    for (const auto & Lepton : Leptons)
        for (const auto & Jet : jets) {
            Doublet doublet(Jet, Lepton);
            doublet.SetTag(GetTag(doublet));
            if (doublet.Tag() != Tag) continue;
            if (Tag == kSignal && doublet.Jet().m() > Mass(TopId)) continue;
            doublets.emplace_back(doublet);
        }


    Print(kInformation, "Number JetPairs", doublets.size());

    if (Tag == kSignal && doublets.size() > 1) {
        std::sort(doublets.begin(), doublets.end(), SortByMass(Mass(TopId)));
        doublets.erase(doublets.begin() + 1, doublets.end());
    }

    std::vector<HTopLeptonicBranch> TopLeptonicBranches;
    for (const auto & doublet : doublets) TopLeptonicBranches.emplace_back(GetBranch(doublet));

    return TopLeptonicBranches;

}

analysis::Object::Tag analysis::HTopLeptonicTagger::GetTag(const Doublet &doublet)
{
    Print(kInformation, "Triple Tag", Name(doublet.Singlet1().user_index()), Name(doublet.Singlet2().user_index()));

    JetInfo Bjet_info = doublet.Singlet1().user_info<JetInfo>();
    Bjet_info.ExtractFraction(BottomId);
    JetInfo Ljet_info = doublet.Singlet2().user_info<JetInfo>();
    Ljet_info.ExtractFraction(WId);

    if (std::abs(Ljet_info.MaximalId()) != WId) return kBackground;
    if (std::abs(Bjet_info.MaximalId()) != BottomId) return kBackground;
    if (sgn(Bjet_info.MaximalId()) != sgn(Ljet_info.MaximalId())) return kBackground;

    return kSignal;
}

std::vector<analysis::Doublet>  analysis::HTopLeptonicTagger::GetBdt(const Jets &jets, Jets &Leptons, const analysis::Reader & Reader)
{

    Print(kInformation, "Bdt");
    std::vector<Doublet> doublets;
    for (const auto & Lepton : Leptons) {
        for (const auto & Jet : jets) {
            Doublet doublet(Jet, Lepton);
            Branch = GetBranch(doublet);
            doublet.SetBdt(Reader.Bdt());
            doublets.emplace_back(doublet);
        }
    }

    std::sort(doublets.begin(), doublets.end());
    doublets.erase(doublets.begin() + std::min(max_combi(), int(doublets.size())), doublets.end());

    return doublets;

}
