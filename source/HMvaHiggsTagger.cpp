# include "HMvaHiggsTagger.hh"

hanalysis::HMvaHiggsTagger::HMvaHiggsTagger()
{
  //     DebugLevel = hanalysis::HObject::HDebug;

  Print(HNotification, "Constructor");
//   SetBranchName("Higgs");
}

hanalysis::HMvaHiggsTagger::HMvaHiggsTagger(const BottomTagger &NewBottomTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");

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

hanalysis::HMvaHiggsTagger::~HMvaHiggsTagger()
{
    Print(HNotification, "Destructor");
    // delete Branch;
//     delete BottomReader;
    //delete JetTag;
}

void hanalysis::HMvaHiggsTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

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

    Print(HNotification, "Variables defined");

}

void hanalysis::HMvaHiggsTagger::FillBranch(HHiggsBranch *const HiggsBranch, const HDoublet &Doublet)
{
    Print(HInformation, "FillPairTagger", Doublet.Bdt());

    HiggsBranch->Mass = Doublet.Jet().m();
    HiggsBranch->PtSum = Doublet.Jet().pt();
    HiggsBranch->PtDiff = Doublet.DeltaPt();
    HiggsBranch->DeltaR = Doublet.DeltaR();
    HiggsBranch->DeltaRap = Doublet.DeltaRap();
    HiggsBranch->DeltaPhi = Doublet.DeltaPhi();
    HiggsBranch->BottomBdt = Doublet.Bdt();
    HiggsBranch->Pull1 = Doublet.PullAngle1();
    HiggsBranch->Pull2 = Doublet.PullAngle2();
    HiggsBranch->Pull = Doublet.PullAngle();
    HiggsBranch->HiggsTag = Doublet.Tag();

}


struct SortPairByMass {
    inline bool operator()(const hanalysis::HDoublet &Pair1, const hanalysis::HDoublet &Pair2) {
        return (Pair1.MassDifferenceTo(hanalysis::HObject::HiggsId) > Pair2.MassDifferenceTo(hanalysis::HObject::HiggsId));
    }
};


std::vector<HHiggsBranch *> hanalysis::HMvaHiggsTagger::GetBranches(HEvent &Event, const HObject::Tag State)
{

    Print(HInformation, "Get Higgs Tags");

    JetTag.HeavyParticles = {CpvHiggsId, HiggsId, TopId};
    Jets jets = Event.GetJets()->GetStructuredTaggedJets(JetTag);

    Jets HiggsJets;
    Jets OtherJets;
    for (Jets::iterator Jet = jets.begin(); Jet != jets.end();) {
        if (std::abs((*Jet).user_index()) == MixedJetId) {
            Jet = jets.erase(Jet);
        } else {
            HJetInfo *JetInfo = new HJetInfo;
//             BottomTagger.FillBranch(*Jet); // FIXME Broken
            JetInfo->SetBdt(BottomReader.Bdt());
            (*Jet).set_user_info(JetInfo);
            if ((*Jet).user_info<HJetInfo>().MaximalId() == HiggsId || (*Jet).user_info<HJetInfo>().MaximalId() == CpvHiggsId) {
                HiggsJets.emplace_back(*Jet);
            } else {
                OtherJets.emplace_back(*Jet);
            }
            ++Jet;
        }
    }


    std::vector<HDoublet> Doublets;

    if (State == kSignal) {
        Print(HInformation, "Higgs Jets", HiggsJets.size());
        for (Jets::iterator Jet1 = HiggsJets.begin(); Jet1 != HiggsJets.end(); ++Jet1) {
            for (Jets::iterator Jet2 = Jet1 + 1; Jet2 != HiggsJets.end(); ++Jet2) {
                HDoublet Doublet((*Jet1), (*Jet2));
                Doublet.SetTag(1);
                Doublets.emplace_back(Doublet);
            }
        }
        std::sort(Doublets.begin(), Doublets.end(), SortPairByMass());
        if (Doublets.size() > 1) {
            Print(HDebug, "Number of Higgses", Doublets.size());
            for (const auto & Doublet : Doublets) Print(HDebug, "Higgs Mass", Doublet.Jet().m());
            Doublets.erase(Doublets.begin() + 1, Doublets.end());
        }
    }

    if (State == kBackground) {
        for (Jets::iterator Jet1 = OtherJets.begin(); Jet1 != OtherJets.end(); ++Jet1) {
            for (Jets::iterator Jet2 = Jet1 + 1; Jet2 != OtherJets.end(); ++Jet2) {
                HDoublet JetPair((*Jet1), (*Jet2));
                JetPair.SetTag(0);
                Doublets.emplace_back(JetPair);
            }
        }
        for (Jets::iterator Jet1 = OtherJets.begin(); Jet1 != OtherJets.end(); ++Jet1) {
            for (Jets::iterator Jet2 = HiggsJets.begin(); Jet2 != HiggsJets.end(); ++Jet2) {
                HDoublet JetPair((*Jet1), (*Jet2));
                JetPair.SetTag(0);
                Doublets.emplace_back(JetPair);
            }
        }
    }

    Print(HInformation, "Number of Jet Pairs", Doublets.size());

    std::vector<HHiggsBranch *> HiggsBranches;
    for (const auto & JetPair : Doublets) {
        HHiggsBranch *HiggsBranch = new HHiggsBranch();
        FillBranch(HiggsBranch, JetPair);
        HiggsBranches.emplace_back(HiggsBranch);
    }

    return HiggsBranches;

}

void hanalysis::HMvaHiggsTagger::FillBranch(const HDoublet &Pair)
{
    Print(HInformation, "FillPairTagger", Pair.Bdt());

    FillBranch(&Branch, Pair);

}

std::vector<HParticleBranch *> hanalysis::HMvaHiggsTagger::GetConstituentBranches()
{

    Print(HInformation, "Get Higgs Tags");

    std::vector<HDoublet> JetPairs;

    Print(HInformation, "Number of Jet Pairs", JetPairs.size());

    std::vector<HParticleBranch *> ConstituentBranches;
    for (const auto & JetPair : JetPairs) {
        for (const auto & Constituent : JetPair.Constituents()) {
            HParticleBranch *ConstituentBranch = new HParticleBranch();
            FillBranch(ConstituentBranch, Constituent);
            ConstituentBranches.emplace_back(ConstituentBranch);
        }
    }

    return ConstituentBranches;

}

void hanalysis::HMvaHiggsTagger::FillBranch(const HKinematics &Vector)
{
    Print(HInformation, "FillPairTagger", Vector.GetPt());

    FillBranch(Vector);

}

void hanalysis::HMvaHiggsTagger::FillBranch(HParticleBranch *const ConstituentBranch, const HKinematics &Vector)
{
    Print(HInformation, "Fill Constituent Branch");

    ConstituentBranch->Pt = Vector.GetPt();
    ConstituentBranch->Rap = Vector.GetRap();
    ConstituentBranch->Phi = Vector.GetPhi();

}
