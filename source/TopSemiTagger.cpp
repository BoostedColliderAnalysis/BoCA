#include "TopSemiTagger.hh"
#include "Event.hh"
#include "Debug.hh"

namespace analysis
{

TopSemiTagger::TopSemiTagger()
{
    Note();
    top_mass_window_ = (Mass(Id::top) - Mass(Id::W)) / 2;
    DefineVariables();
}

int TopSemiTagger::Train(const Event &event, PreCuts &pre_cuts, const Tag tag) const
{
    Info("Top Tags");
    Jets jets = bottom_reader_.Multiplets(event);

    std::vector<Triplet> triplets;
    if (!boost_) {
        std::vector<Doublet> doublets = w_semi_reader_.Multiplets(event);
        Note("doublet number", doublets.size());
        for (const auto & jet : jets) {
            for (const auto & doublet : doublets) {
                Triplet triplet(doublet, jet);
                triplet.SetTag(tag);
                if (Problematic(triplet, pre_cuts, tag)) continue;
                triplets.emplace_back(triplet);
            }
        }
    } else {
        Jets leptons = event.Leptons().leptons();
        Note("leptons number", leptons.size());
        for (const auto & jet : jets) {
            for (const auto & lepton : leptons) {
                Doublet doublet(lepton);
                Triplet triplet(doublet, jet);
                triplet.SetTag(tag);
                if (Problematic(triplet, pre_cuts, tag)) continue;
                triplets.emplace_back(triplet);
            }
        }
    }

    Jets top_particles = event.Partons().GenParticles();
    top_particles = CopyIfAbsParticle(top_particles, Id(TopSemiId(event)));
    Note("Number of semi tops", top_particles.size());
    return SaveEntries(BestMatches(triplets,top_particles,tag));
}


bool TopSemiTagger::Problematic(const Triplet &triplet, PreCuts &pre_cuts, const Tag tag) const
{
    Info("Problematic");
    if (pre_cuts.PtLowerCut(Id::top) > 0 && triplet.Jet().pt() <  pre_cuts.PtLowerCut(Id::top)) return true;
    if (pre_cuts.PtUpperCut(Id::top) > 0 && triplet.Jet().pt() >  pre_cuts.PtUpperCut(Id::top)) return true;
    switch (tag) {
    case Tag::signal :
        if (std::abs(triplet.Jet().m() - Mass(Id::top)) > top_mass_window_) return true ;
        if (triplet.Rho() < 0.5 || triplet.Rho() > 2) return true ;
        break;
    case Tag::background :
        break;
    }
    return false;
}

std::vector<Triplet>  TopSemiTagger::Multiplets(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const
{
    Info("Bdt");

    Jets jets = bottom_reader_.Multiplets(event);
    std::vector<Doublet> doublets = w_semi_reader_.Multiplets(event);

    std::vector<Triplet> triplets;
    if (!boost_) {
        for (const auto & Jet : jets) {
            for (const auto & doublet : doublets) {
                Triplet triplet(doublet, Jet);
                triplet.SetBdt(Bdt(triplet, reader));
                triplets.emplace_back(triplet);
            }
        }
    } else {
        for (const auto & Jet : jets) {
            for (const auto & Predoublet : doublets) {
                Doublet doublet(Predoublet.SingletJet1());
                Triplet triplet(doublet, Jet);
                triplet.SetBdt(Bdt(triplet, reader));
                triplets.emplace_back(triplet);
            }
        }
    }
    return ReduceResult(triplets);
}

}
