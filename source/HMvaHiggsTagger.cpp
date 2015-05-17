# include "HMvaHiggsTagger.hh"

analysis::HMvaHiggsTagger::HMvaHiggsTagger()
{
  //     DebugLevel = analysis::Object::kDebug;

  Print(kNotification, "Constructor");
//   SetBranchName("Higgs");
}

analysis::HMvaHiggsTagger::HMvaHiggsTagger(const BottomTagger &NewBottomTagger)
{
//     DebugLevel = analysis::Object::kDebug;

    Print(kNotification, "Constructor");

    bottom_tagger_ = NewBottomTagger;
    BottomReader.set_tagger(bottom_tagger_);

    set_tagger_name("Higgs");
//     SignalNames = {"Higgs"};
//     BackgroundNames = {"NotHiggs"};
//     SetBranchName("Higgs");

//     Branch = new HHiggsBranch();
    //JetTag = new HJetTag();

    DefineVariables();
}

analysis::HMvaHiggsTagger::~HMvaHiggsTagger()
{
    Print(kNotification, "Destructor");
    // delete Branch;
//     delete BottomReader;
    //delete JetTag;
}

void analysis::HMvaHiggsTagger::DefineVariables()
{

    Print(kNotification , "Define Variables");

    AddVariable(Branch.Mass, "Mass");
    AddVariable(Branch.PtSum, "PtSum");
    AddVariable(Branch.PtDiff, "PtDiff");
    AddVariable(Branch.DeltaPhi, "DeltaPhi");
    AddVariable(Branch.DeltaRap, "DeltaRap");
    AddVariable(Branch.DeltaR, "DeltaR");
    AddVariable(Branch.Pull1, "Pull1");
    AddVariable(Branch.Pull2, "Pull2");
    AddVariable(Branch.Pull, "Pull");
    AddVariable(Branch.BottomBdt, "BottomBdt");

    AddSpectator(Branch.HiggsTag, "HiggsTag");

    Print(kNotification, "Variables defined");

}

void analysis::HMvaHiggsTagger::FillBranch(HHiggsBranch *const HiggsBranch, const Doublet &doublet)
{
    Print(kInformation, "FillPairTagger", doublet.Bdt());

    HiggsBranch->Mass = doublet.Jet().m();
    HiggsBranch->PtSum = doublet.Jet().pt();
    HiggsBranch->PtDiff = doublet.DeltaPt();
    HiggsBranch->DeltaR = doublet.DeltaR();
    HiggsBranch->DeltaRap = doublet.DeltaRap();
    HiggsBranch->DeltaPhi = doublet.DeltaPhi();
    HiggsBranch->BottomBdt = doublet.Bdt();
    HiggsBranch->Pull1 = doublet.PullAngle1();
    HiggsBranch->Pull2 = doublet.PullAngle2();
    HiggsBranch->Pull = doublet.PullAngle();
    HiggsBranch->HiggsTag = doublet.Tag();

}


struct SortPairByMass {
    inline bool operator()(const analysis::Doublet &Pair1, const analysis::Doublet &Pair2) {
        return (Pair1.MassDifferenceTo(analysis::Object::HiggsId) > Pair2.MassDifferenceTo(analysis::Object::HiggsId));
    }
};


std::vector<HHiggsBranch *> analysis::HMvaHiggsTagger::GetBranches(Event &event, const Object::Tag State)
{

    Print(kInformation, "Get Higgs Tags");

    JetTag.HeavyParticles = {CpvHiggsId, HiggsId, TopId};
    Jets jets = event.hadrons().GetStructuredTaggedJets(JetTag);

    Jets HiggsJets;
    Jets OtherJets;
    for (Jets::iterator Jet = jets.begin(); Jet != jets.end();) {
        if (std::abs((*Jet).user_index()) == MixedJetId) {
            Jet = jets.erase(Jet);
        } else {
            JetInfo *jet_info = new JetInfo;
//             BottomTagger.FillBranch(*Jet); // FIXME Broken
            jet_info->SetBdt(BottomReader.Bdt());
            (*Jet).set_user_info(jet_info);
            if ((*Jet).user_info<JetInfo>().MaximalId() == HiggsId || (*Jet).user_info<JetInfo>().MaximalId() == CpvHiggsId) {
                HiggsJets.emplace_back(*Jet);
            } else {
                OtherJets.emplace_back(*Jet);
            }
            ++Jet;
        }
    }


    std::vector<Doublet> doublets;

    if (State == kSignal) {
        Print(kInformation, "Higgs Jets", HiggsJets.size());
        for (Jets::iterator Jet1 = HiggsJets.begin(); Jet1 != HiggsJets.end(); ++Jet1) {
            for (Jets::iterator Jet2 = Jet1 + 1; Jet2 != HiggsJets.end(); ++Jet2) {
                Doublet doublet((*Jet1), (*Jet2));
                doublet.SetTag(1);
                doublets.emplace_back(doublet);
            }
        }
        std::sort(doublets.begin(), doublets.end(), SortPairByMass());
        if (doublets.size() > 1) {
            Print(kDebug, "Number of Higgses", doublets.size());
            for (const auto & doublet : doublets) Print(kDebug, "Higgs Mass", doublet.Jet().m());
            doublets.erase(doublets.begin() + 1, doublets.end());
        }
    }

    if (State == kBackground) {
        for (Jets::iterator Jet1 = OtherJets.begin(); Jet1 != OtherJets.end(); ++Jet1) {
            for (Jets::iterator Jet2 = Jet1 + 1; Jet2 != OtherJets.end(); ++Jet2) {
                Doublet JetPair((*Jet1), (*Jet2));
                JetPair.SetTag(0);
                doublets.emplace_back(JetPair);
            }
        }
        for (Jets::iterator Jet1 = OtherJets.begin(); Jet1 != OtherJets.end(); ++Jet1) {
            for (Jets::iterator Jet2 = HiggsJets.begin(); Jet2 != HiggsJets.end(); ++Jet2) {
                Doublet JetPair((*Jet1), (*Jet2));
                JetPair.SetTag(0);
                doublets.emplace_back(JetPair);
            }
        }
    }

    Print(kInformation, "Number of Jet Pairs", doublets.size());

    std::vector<HHiggsBranch *> HiggsBranches;
    for (const auto & JetPair : doublets) {
        HHiggsBranch *HiggsBranch = new HHiggsBranch();
        FillBranch(HiggsBranch, JetPair);
        HiggsBranches.emplace_back(HiggsBranch);
    }

    return HiggsBranches;

}

void analysis::HMvaHiggsTagger::FillBranch(const Doublet &Pair)
{
    Print(kInformation, "FillPairTagger", Pair.Bdt());

    FillBranch(&Branch, Pair);

}

std::vector<ParticleBranch *> analysis::HMvaHiggsTagger::GetconstituentBranches()
{

    Print(kInformation, "Get Higgs Tags");

    std::vector<Doublet> JetPairs;

    Print(kInformation, "Number of Jet Pairs", JetPairs.size());

    std::vector<ParticleBranch *> constituentBranches;
    for (const auto & JetPair : JetPairs) {
        for (const auto & constituent : JetPair.constituents()) {
            ParticleBranch *constituentBranch = new ParticleBranch();
            FillBranch(constituentBranch, constituent);
            constituentBranches.emplace_back(constituentBranch);
        }
    }

    return constituentBranches;

}

void analysis::HMvaHiggsTagger::FillBranch(const Kinematics &Vector)
{
    Print(kInformation, "FillPairTagger", Vector.GetPt());

    FillBranch(Vector);

}

void analysis::HMvaHiggsTagger::FillBranch(ParticleBranch *const constituentBranch, const Kinematics &Vector)
{
    Print(kInformation, "Fill constituent Branch");

    constituentBranch->Pt = Vector.GetPt();
    constituentBranch->Rap = Vector.GetRap();
    constituentBranch->Phi = Vector.GetPhi();

}
