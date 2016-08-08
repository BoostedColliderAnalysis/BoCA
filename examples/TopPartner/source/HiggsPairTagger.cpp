#include "boca/generic/Exception.hh"
#include "boca/HiggsPairTagger.hh"
// #define INFORMATION
#include "boca/generic/DEBUG.hh"

namespace boca
{

namespace toppartner
{

int HiggsPairTagger::Train(Event const& event, PreCuts const&, Tag tag)
{
    INFO0;
    return SaveEntries(Quartets(event, [&](Quartet22 & quartet) {
        quartet.SetTag(tag);
        return quartet;
    }), Particles(event, tag), tag);
}

std::vector<Quartet22> HiggsPairTagger::Multiplets(Event const& event, boca::PreCuts const&, TMVA::Reader const& reader)
{
    INFO0;
    return Quartets(event, [&](Quartet22 & quartet) {
        quartet.SetBdt(Bdt(quartet, reader));
        return quartet;
    });
}

std::vector<std::pair<Particle, Particle>> HiggsPairTagger::Particles(Event const& event, Tag tag) const
{
    auto higgs_pairs = UnorderedPairs(higgs_reader_.Particles(event), [&](Particle const & particle_1, Particle const & particle_2) {
        auto part_1 = particle_1.Info().Family().Member(Relative::particle);
        auto part_2 = particle_2.Info().Family().Member(Relative::particle);
        auto mother_1 = particle_1.Info().Family().Member(Relative::mother);
        auto mother_2 = particle_2.Info().Family().Member(Relative::mother);
        auto step_mother_1 = particle_1.Info().Family().Member(Relative::step_mother);
        auto step_mother_2 = particle_2.Info().Family().Member(Relative::step_mother);
        INFO(part_1.Position(), part_2.Position());
        INFO(mother_1.Position(), mother_2.Position(), step_mother_1.Position(), step_mother_2.Position());
//         if (mother_1.Position() + step_mother_2.Position() != mother_2.Position() + step_mother_1.Position()) throw Overlap(); // FIXME this is fragile
        if (step_mother_1.Position() == Member::EmptyPosition() || step_mother_2.Position() == Member::EmptyPosition()) throw Overlap();
        return std::make_pair(particle_1, particle_2);
        INFO(mother_1.Name(), mother_2.Name(), step_mother_1.Name(), step_mother_2.Name());
    });
    if (tag == Tag::signal) CHECK(higgs_pairs.size() == 1, higgs_pairs.size());
    if (tag == Tag::signal) {
        auto higgs1 = higgs_pairs.front().first;
        auto higgs2 = higgs_pairs.front().second;
        auto angle = higgs1.DeltaRTo(higgs2);
        INFO(higgs1.Pt(),  higgs2.Pt(), angle);
    }
    return higgs_pairs;
}

std::vector<Quartet22> HiggsPairTagger::Quartets(Event const& event, std::function<Quartet22(Quartet22&)> const& function)
{
    INFO0;
    auto higgses = higgs_reader_.Multiplets(event, 16);
    auto pair = UnorderedPairs(higgses, [&](Doublet const & doublet_1, Doublet const & doublet_2) {
        Quartet22 quartet(doublet_1, doublet_2);
        if (quartet.Overlap()) throw Overlap();
        return function(quartet);
    });
    INFO(pair.size());
    return pair;
}

std::string HiggsPairTagger::Name() const
{
    return "HiggsPair";
}

latex::String HiggsPairTagger::LatexName() const
{
    return {"hh", true};
}

}

}
