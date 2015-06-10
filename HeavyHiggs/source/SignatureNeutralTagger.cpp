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


int heavyhiggs::SignatureNeutralTagger::Train(analysis::Event &event, const Tag tag)
{
    Print(kInformation, "event Tags");
    float Mass = event.mass();
    std::vector<analysis::Sextet> sextets = heavy_higgs_semi_reader_.Multiplets<HeavyHiggsSemiTagger>(event);
    if (sextets.empty())Print(kInformation, "No sextets", sextets.size());

    analysis::Jets HiggsParticles = event.Partons().GenParticles();
    analysis::Jets Even = RemoveIfWrongAbsFamily(HiggsParticles, HeavyHiggsId, GluonId);
    analysis::Jets Odd = RemoveIfWrongAbsFamily(HiggsParticles, CPOddHiggsId, GluonId);
    HiggsParticles = Even;
    HiggsParticles.insert(HiggsParticles.end(), Odd.begin(), Odd.end());
    fastjet::PseudoJet HiggsBoson;
    if (tag == kSignal) {
        if (HiggsParticles.size() == 1) HiggsBoson = HiggsParticles.front();
        else Print(kError, "Where is the Higgs?", HiggsParticles.size());
        std::sort(sextets.begin(), sextets.end(), analysis::MinDeltaRTo(HiggsParticles.front()));
        if (sextets.size() > 1) sextets.erase(sextets.begin() + 1, sextets.end());
    }

    std::vector<analysis::Doublet> doublets = jet_pair_reader_.Multiplets<analysis::JetPairTagger>(event);

    std::vector<analysis::Doublet> Finaldoublets;
    analysis::Jets Particles = event.Partons().GenParticles();
    if (tag == kSignal) {
        Particles = RemoveIfWrongAbsFamily(Particles, BottomId, GluonId);
        if (Particles.size() == 2) {
            for (const auto & doublet : doublets) {
                if ((doublet.SingletJet1().delta_R(Particles.at(0)) < detector_geometry().JetConeSize && doublet.SingletJet2().delta_R(Particles.at(1)) < detector_geometry().JetConeSize) || (doublet.SingletJet1().delta_R(Particles.at(1)) < detector_geometry().JetConeSize && doublet.SingletJet2().delta_R(Particles.at(0)) < detector_geometry().JetConeSize)) Finaldoublets.emplace_back(doublet);
            }
        }
    }
    if (tag == kBackground) Finaldoublets = doublets;

    std::vector<analysis::Octet62> octets;
    for (const auto & doublet : Finaldoublets) {
        for (const auto & sextet : sextets) {
            if (tag == kSignal && sextet.Jet().m() < Mass / 2)continue;
            if (tag == kSignal && sextet.Jet().m() > Mass * 3 / 2)continue;
            analysis::Octet62 octet(sextet, doublet);
            if(octet.Overlap()) continue;
            octet.SetTag(tag);
            octets.emplace_back(octet);
        }
    }
    if (octets.empty())Print(kInformation, "No octets", octets.size());

    if (tag == kSignal && octets.size() > 1) {
        Print(kInformation, "more than one event", octets.size());
        std::sort(octets.begin(), octets.end());
        octets.erase(octets.begin() + 1, octets.end());
    }

    return SaveEntries(octets);

}


std::vector<analysis::Octet62> heavyhiggs::SignatureNeutralTagger::Multiplets(analysis::Event &event, const TMVA::Reader &reader)
{
    Print(kInformation, "event Tags");

    std::vector<analysis::Doublet> doublets = jet_pair_reader_.Multiplets<analysis::JetPairTagger>(event);
    std::vector<analysis::Sextet> sextets = heavy_higgs_semi_reader_.Multiplets<HeavyHiggsSemiTagger>(event);
    std::vector<analysis::Octet62> octets;
    for (const auto & doublet : doublets) {
        for (const auto & sextet : sextets) {
            analysis::Octet62 octet(sextet, doublet);
            if(octet.Overlap()) continue;
            branch_ = branch(octet);
            octet.SetBdt(Bdt(reader));
            octets.emplace_back(octet);
        }
    }
    return ReduceResult(octets);
}
