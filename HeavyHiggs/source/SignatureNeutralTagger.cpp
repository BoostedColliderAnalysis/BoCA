# include "SignatureNeutralTagger.hh"

heavyhiggs::SignatureNeutralTagger::SignatureNeutralTagger()
{
    //   DebugLevel = kDebug;
    Print(kNotification , "Constructor");
    set_tagger_name("SignatureNeutral");
    heavy_higgs_semi_reader_.set_tagger(heavy_higgs_semi_tagger_);
    jet_pair_reader_.set_tagger(jet_pair_tagger_);
    DefineVariables();
}

void heavyhiggs::SignatureNeutralTagger::DefineVariables()
{
    Print(kNotification, "Define Variables");
    AddVariable(branch_.Mass, "Mass");
    AddVariable(branch_.Pt, "Pt");
    AddVariable(branch_.Rap, "Rap");
    AddVariable(branch_.Phi, "Phi");
    AddVariable(branch_.Ht, "Ht");
    AddVariable(branch_.DeltaPt, "DeltaPt");
    AddVariable(branch_.DeltaHt, "DeltaHt");
    AddVariable(branch_.DeltaM, "DeltaM");
    AddVariable(branch_.DeltaRap, "DeltaRap");
    AddVariable(branch_.DeltaPhi, "DeltaPhi");
    AddVariable(branch_.DeltaR, "DeltaR");
    AddVariable(branch_.HiggsMass, "HiggsMass");
    AddVariable(branch_.PairRap, "PairRap");
    AddVariable(branch_.BottomBdt, "BottomBdt");
    AddVariable(branch_.PairBottomBdt, "PairBottomBdt");
    AddVariable(branch_.PairBdt, "PairBdt");
    AddVariable(branch_.HiggsBdt, "HiggsBdt");
    AddVariable(branch_.HardTopPt, "HardTopPt");
    AddVariable(branch_.SoftTopPt, "SoftTopPt");
    AddVariable(branch_.Bdt, "Bdt");
    AddSpectator(branch_.Tag, "Tag");
    Print(kNotification, "Variables defined");
}

heavyhiggs::OctetNeutralBranch heavyhiggs::SignatureNeutralTagger::GetBranch(const Octet62 &octet) const
{
    Print(kInformation, "FillPairTagger", octet.Bdt());
    OctetNeutralBranch branch;
    branch.Fill(octet);
    return branch;
}

std::vector<heavyhiggs::OctetNeutralBranch> heavyhiggs::SignatureNeutralTagger::GetBranches(analysis::Event &event, const Object::Tag Tag)
{
    Print(kInformation, "Get event Tags");
    float Mass = event.mass();
    std::vector<analysis::Sextet> sextets = static_cast<analysis::HeavyHiggsSemiTagger &>(heavy_higgs_semi_reader_.tagger()).Sextets(event, heavy_higgs_semi_reader_.reader());
    if (sextets.empty())Print(kInformation, "No sextets", sextets.size());

    Jets HiggsParticles = event.partons().Generator();
    Jets Even = RemoveIfWrongAbsFamily(HiggsParticles, HeavyHiggsId, GluonId);
    Jets Odd = RemoveIfWrongAbsFamily(HiggsParticles, CPOddHiggsId, GluonId);
    HiggsParticles = Even;
    HiggsParticles.insert(HiggsParticles.end(), Odd.begin(), Odd.end());
    fastjet::PseudoJet HiggsBoson;
    if (Tag == kSignal) {
        if (HiggsParticles.size() == 1) HiggsBoson = HiggsParticles.front();
        else Print(kError, "Where is the Higgs?", HiggsParticles.size());
        std::sort(sextets.begin(), sextets.end(), analysis::MinDeltaRTo(HiggsParticles.front()));
        if (sextets.size() > 1) sextets.erase(sextets.begin() + 1, sextets.end());
    }

    std::vector<analysis::Doublet> doublets = static_cast<analysis::JetPairTagger &>(jet_pair_reader_.tagger()).Doublets(event,jet_pair_reader_.reader());

    std::vector<analysis::Doublet> Finaldoublets;
    Jets Particles = event.partons().Generator();
    if (Tag == kSignal) {
        Particles = RemoveIfWrongAbsFamily(Particles, BottomId, GluonId);
        if (Particles.size() == 2) {
            for (const auto & doublet : doublets) {
                if ((doublet.Singlet1().delta_R(Particles.at(0)) < detector_geometry().JetConeSize && doublet.Singlet2().delta_R(Particles.at(1)) < detector_geometry().JetConeSize) || (doublet.Singlet1().delta_R(Particles.at(1)) < detector_geometry().JetConeSize && doublet.Singlet2().delta_R(Particles.at(0)) < detector_geometry().JetConeSize)) Finaldoublets.emplace_back(doublet);
            }
        }
    }
    if (Tag == kBackground) Finaldoublets = doublets;

    std::vector<Octet62> octets;
    for (const auto & doublet : Finaldoublets) {
        for (const auto & sextet : sextets) {
            if (Tag == kSignal && sextet.Jet().m() < Mass / 2)continue;
            if (Tag == kSignal && sextet.Jet().m() > Mass * 3 / 2)continue;
            if (sextet.triplet1().singlet().delta_R(doublet.Singlet1()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet1().singlet().delta_R(doublet.Singlet2()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet2().singlet().delta_R(doublet.Singlet1()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet2().singlet().delta_R(doublet.Singlet2()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet2().doublet().Singlet1().delta_R(doublet.Singlet1()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet2().doublet().Singlet1().delta_R(doublet.Singlet2()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet2().doublet().Singlet2().delta_R(doublet.Singlet1()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet2().doublet().Singlet2().delta_R(doublet.Singlet2()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet2().doublet().Jet().delta_R(doublet.Singlet1()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet2().doublet().Jet().delta_R(doublet.Singlet2()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet2().Jet().delta_R(doublet.Singlet1()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet2().Jet().delta_R(doublet.Singlet2()) < detector_geometry().JetConeSize) continue;
            Octet62 octet(sextet, doublet);
            octet.SetTag(Tag);
            octets.emplace_back(octet);
        }
    }
    if (octets.empty())Print(kInformation, "No octets", octets.size());

    if (Tag == kSignal && octets.size() > 1) {
        Print(kInformation, "more than one event", octets.size());
        std::sort(octets.begin(), octets.end());
        octets.erase(octets.begin() + 1, octets.end());
    }

    std::vector<heavyhiggs::OctetNeutralBranch> octetBranches;
    for (const auto & octet : octets) octetBranches.emplace_back(GetBranch(octet));
//     if (octetBranches.empty())Print(kError, "No octetBranches", octetBranches.size());
    return octetBranches;
}


std::vector<Octet62> heavyhiggs::SignatureNeutralTagger::Octets(analysis::Event &event, const TMVA::Reader &reader)
{
    Print(kInformation, "Get event Tags");

    std::vector<analysis::Doublet> doublets = static_cast<analysis::JetPairTagger &>(jet_pair_reader_.tagger()).Doublets(event,jet_pair_reader_.reader());
    std::vector<analysis::Sextet> sextets = static_cast<analysis::HeavyHiggsSemiTagger &>(heavy_higgs_semi_reader_.tagger()).Sextets(event, heavy_higgs_semi_reader_.reader());
    std::vector<Octet62> octets;
    for (const auto & doublet : doublets) {
        for (const auto & sextet : sextets) {
            if (sextet.triplet1().singlet().delta_R(doublet.Singlet1()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet1().singlet().delta_R(doublet.Singlet2()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet2().singlet().delta_R(doublet.Singlet1()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet2().singlet().delta_R(doublet.Singlet2()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet2().doublet().Singlet1().delta_R(doublet.Singlet1()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet2().doublet().Singlet1().delta_R(doublet.Singlet2()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet2().doublet().Singlet2().delta_R(doublet.Singlet1()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet2().doublet().Singlet2().delta_R(doublet.Singlet2()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet2().doublet().Jet().delta_R(doublet.Singlet1()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet2().doublet().Jet().delta_R(doublet.Singlet2()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet2().Jet().delta_R(doublet.Singlet1()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet2().Jet().delta_R(doublet.Singlet2()) < detector_geometry().JetConeSize) continue;
            Octet62 octet(sextet, doublet);
            branch_ = GetBranch(octet);
            octet.SetBdt(Bdt(reader));
            octets.emplace_back(octet);
        }
    }

    if (octets.size() > 1) std::sort(octets.begin(), octets.end());
    octets.erase(octets.begin() + std::min(max_combi(), int(octets.size())), octets.end());
    Print(kInformation, "event Number", octets.size());


    return octets;
}
