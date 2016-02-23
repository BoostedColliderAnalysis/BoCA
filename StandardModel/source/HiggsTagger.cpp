/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "fastjet/tools/MassDropTagger.hh"
#include "fastjet/tools/Filter.hh"

#include "multiplets/Doublet.hh"
#include "Event.hh"
#include "ClusterSequence.hh"
#include "Types.hh"
#include "HiggsTagger.hh"
#include "MomentumRange.hh"
#include "Exception.hh"
#include "Debug.hh"

namespace boca
{

namespace standardmodel
{

HiggsTagger::HiggsTagger()
{
    INFO0;
    higgs_mass_window = 70_GeV;
}

int HiggsTagger::Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const
{
    INFO0;
   std::vector<Lepton> leptons = event.Leptons().leptons();
    return SaveEntries(Doublets(event, [&](Doublet & doublet) {
        return SetTag(doublet, leptons, pre_cuts, tag);
    }), Particles(event), tag, Id::higgs);
}

std::vector<Doublet> HiggsTagger::Doublets(Event const& event, std::function<boost::optional<Doublet>(Doublet&)> const& function) const
{
    INFO0;
   std::vector<Jet> jets =  event.Hadrons().Jets();
    MomentumRange jet_range(Id::higgs, Id::higgs);
    std::vector<Doublet> doublets = UnorderedPairs(jet_range.SofterThanMax(jets), [&](Jet const & jet_1, Jet const & jet_2) {
        Doublet doublet(jet_1, jet_2);
        if (!jet_range.BelowUpperBound(doublet)) throw boca::Problematic();
        if (boost::optional<Doublet> optional_doublet = function(doublet)) return *optional_doublet;
        throw boca::Problematic();
    });
    for (auto const & jet : jet_range.HarderThanMin(jets)) {
        MomentumRange sub_jet_range((SubJet(Id::higgs)), (SubJet(Id::higgs)));
        if (sub_jet_range.BelowUpperBound(jet)) try {
               std::vector<Jet> pieces = Tagger::SubJets(jet, 2);
                Doublet doublet(pieces.at(0), pieces.at(1));
                if (boost::optional<Doublet> optional_doublet = function(doublet)) doublets.emplace_back(*optional_doublet);
            } catch (std::exception const&) {}
        if (sub_jet_range.AboveLowerBound(jet)) {
            Doublet doublet(jet);
            if (boost::optional<Doublet> optional_doublet = function(doublet)) doublets.emplace_back(*optional_doublet);
        }
    }
    return doublets;
}

std::vector<Particle> HiggsTagger::Particles(Event const& event) const
{
    INFO0;
    return CopyIfParticles(event.Partons().GenParticles(), Id::higgs, Id::CP_violating_higgs);
}

boost::optional<Doublet> HiggsTagger::SetTag(Doublet& doublet, std::vector<Jet>& leptons, PreCuts const& pre_cuts, Tag tag) const
{
    INFO0;
    doublet = PrepareDoublet(doublet, leptons);
    if (Problematic(doublet, pre_cuts, tag)) return boost::none;
    doublet.SetTag(tag);
    return doublet;
}

Doublet HiggsTagger::PrepareDoublet(Doublet& doublet, std::vector<Jet>& leptons) const
{
    INFO0;
    //     doublet = MassDrop(doublet);
    Jet jet_1 = doublet.Singlet1().Jet();
    Jet jet_2 = doublet.Singlet2().Jet();
    doublet = Doublet(bottom_reader_.Multiplet(jet_1), bottom_reader_.Multiplet(jet_2));
    SetClosestLepton(doublet, leptons);
    return doublet;
}

bool HiggsTagger::Problematic(Doublet const& doublet, PreCuts const& pre_cuts, Tag tag) const
{
    INFO0;
    if (Problematic(doublet, pre_cuts)) return true;
    switch (tag) {
    case Tag::signal :
        if (pre_cuts.NotParticleRho(doublet)) return true;
        if (boost::units::abs(doublet.Mass() - MassOf(Id::higgs)) > higgs_mass_window) return true;
//         if (doublet.Singlet1().Bdt() < 0 || doublet.Singlet2().Bdt() < 0) return true;
        break;
    case Tag::background :
        break;
    }
    return false;
}

bool HiggsTagger::Problematic(Doublet const& doublet, PreCuts const& pre_cuts) const
{
    INFO0;
    if (pre_cuts.ApplyCuts(Id::higgs, doublet)) return true;
    return false;
}

std::vector<Doublet> HiggsTagger::Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    INFO0;
   std::vector<Lepton> leptons = event.Leptons().leptons();
    return ReduceResult(Doublets(event, [&](Doublet & doublet) {
        return Multiplet(doublet, leptons, pre_cuts, reader);
    }));
}

boost::optional<Doublet> HiggsTagger::Multiplet(Doublet& doublet, std::vector<Jet>& leptons, PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    INFO0;
    doublet = PrepareDoublet(doublet, leptons);
    if (Problematic(doublet, pre_cuts)) return boost::none;
    doublet.SetBdt(Bdt(doublet, reader));
    return doublet;
}

Doublet HiggsTagger::MassDrop(Doublet const& doublet) const
{
    INFO0;
    InfoRecombiner info_recombiner;
    fastjet::JetDefinition jet_definition(fastjet::cambridge_algorithm, (doublet.DeltaR() + 2. * DetectorGeometry::JetConeSize()) /rad, &info_recombiner);

    unsigned jet_number = 1;
    ClusterSequence cluster_sequence(doublet.Jet().constituents(), jet_definition);
    std::vector<Jet> exclusive_jets = cluster_sequence.ExclusiveJets(jet_number);
    if (exclusive_jets.empty()) throw Empty();
    fastjet::MassDropTagger mass_drop_tagger(0.667, 0.09);
    Jet mass_drop_jet = mass_drop_tagger(exclusive_jets.front());
    if (mass_drop_jet == 0) throw Empty();

    Angle radius = Jet(mass_drop_jet.pieces().at(0)).DeltaRTo(mass_drop_jet.pieces().at(1));
    radius = std::min(radius / 2., .3_rad);
    fastjet::Filter filter(fastjet::JetDefinition(fastjet::cambridge_algorithm, radius / rad, &info_recombiner), fastjet::SelectorNHardest(3));
    Jet filtered_jet = filter.result(mass_drop_jet);
    if (!filtered_jet.has_pieces()) throw Empty();
     std::vector<Jet> pieces = SortedByPt(JetVector(filtered_jet.pieces()));
    if (pieces.size() < 2) throw Empty();
    return Doublet(bottom_reader_.Multiplet(pieces.at(0)), bottom_reader_.Multiplet(pieces.at(1)));
}

std::string HiggsTagger::Name() const
{
    return "Higgs";
}

std::string HiggsTagger::LatexName() const
{
    return "h";
}

}

}
