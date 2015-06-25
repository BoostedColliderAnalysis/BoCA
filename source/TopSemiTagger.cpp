# include "TopSemiTagger.hh"

namespace analysis
{

TopSemiTagger::TopSemiTagger()
{
//     debug_level_ = Severity::Debug;
    Print(Severity::Notification, "Constructor");
    set_tagger_name("TopSemi");
    top_mass_window_ = (Mass(Id::Top) - Mass(Id::W)) / 2;
    bottom_reader_.SetTagger(bottom_tagger_);
    w_semi_reader_.SetTagger(w_semi_tagger_);
    DefineVariables();
}

int TopSemiTagger::Train(Event &event, PreCuts &pre_cuts, const Tag tag)
{
    Print(Severity::Information, "Top Tags");
    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);

    std::vector<Triplet> triplets;
    if (!boost_) {
        std::vector<Doublet> doublets = w_semi_reader_.Multiplets<WSemiTagger>(event);
        Print(Severity::Notification, "doublet number", doublets.size());
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
        Print(Severity::Notification, "leptons number", leptons.size());
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
    top_particles = copy_if_abs_particle(top_particles, Id(TopSemiId(event)));
    Print(Severity::Notification, "Number of semi tops", top_particles.size());
    return SaveEntries(BestMatches(triplets,top_particles,tag));
}


bool TopSemiTagger::Problematic(const Triplet &triplet, PreCuts &pre_cuts, const Tag tag)
{
    Print(Severity::Information, "Problematic");
    if (pre_cuts.PtLowerCut(Id::Top) > 0 && triplet.Jet().pt() <  pre_cuts.PtLowerCut(Id::Top)) return true;
    if (pre_cuts.PtUpperCut(Id::Top) > 0 && triplet.Jet().pt() >  pre_cuts.PtUpperCut(Id::Top)) return true;
    switch (tag) {
    case Tag::Signal :
        if (std::abs(triplet.Jet().m() - Mass(Id::Top)) > top_mass_window_) return true ;
        if (triplet.Rho() < 0.5 || triplet.Rho() > 2) return true ;
        break;
    case Tag::Background :
        break;
    }
    return false;
}

std::vector<Triplet>  TopSemiTagger::Multiplets(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    Print(Severity::Information, "Bdt");

    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    std::vector<Doublet> doublets = w_semi_reader_.Multiplets<WSemiTagger>(event);

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
