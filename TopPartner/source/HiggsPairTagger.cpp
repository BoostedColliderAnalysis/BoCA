#include "HiggsPairTagger.hh"
#include "plotting/Font.hh"
#include "Debug.hh"
#include "Exception.hh"

namespace boca
{

namespace naturalness
{

int HiggsPairTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    INFO0;
    return SaveEntries(Quartets(event, [&](Quartet22 & quartet) {
        quartet.SetTag(tag);
        return quartet;
    }), Particles(event, tag), tag);
}

std::vector<Quartet22> HiggsPairTagger::Multiplets(Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const
{
    INFO0;
    return ReduceResult(Quartets(event, [&](Quartet22 & quartet) {
        quartet.SetBdt(Bdt(quartet, reader));
        return quartet;
    }));
}

std::vector<Particle> HiggsPairTagger::Particles(Event const& event, Tag tag) const
{
    std::vector<Particle> higgs_pair = UnorderedPairs(higgs_reader_.Particles(event), [&](Particle const & particle_1, Particle const & particle_2) {
        Member mother_1 = particle_1.Info().Family().Member(Relative::mother);
        Member mother_2 = particle_2.Info().Family().Member(Relative::mother);
        Member step_mother_1 = particle_1.Info().Family().Member(Relative::step_mother);
        Member step_mother_2 = particle_2.Info().Family().Member(Relative::step_mother);
        INFO(mother_1.Position(), mother_2.Position(), step_mother_1.Position(), step_mother_2.Position());
        if (mother_1.Position() + step_mother_2.Position() != mother_2.Position() + step_mother_1.Position()) throw Overlap(); // FIXME this is fragile
        return Particle(particle_1 + particle_2);
    });
    CHECK(tag == Tag::signal && higgs_pair.size() == 1, higgs_pair.size());
    return higgs_pair;
}

std::vector<Quartet22> HiggsPairTagger::Quartets(Event const& event, std::function<Quartet22(Quartet22&)> const& function) const
{
    INFO0;
    return UnorderedPairs(higgs_reader_.Multiplets(event), [&](Doublet const & doublet_1, Doublet const & doublet_2) {
        Quartet22 quartet(doublet_1, doublet_2);
        if (quartet.Overlap()) throw Overlap();
        return function(quartet);
    });
}

std::string HiggsPairTagger::Name() const
{
    return "HiggsPair";
}

std::string HiggsPairTagger::LatexName() const
{
    return Formula("hh");
}

}

}
