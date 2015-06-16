# include "TopSemiTagger.hh"

namespace analysis
{

TopSemiTagger::TopSemiTagger()
{
//     debug_level_ = kDebug;
    Print(kNotification, "Constructor");
    set_tagger_name("TopSemi");
    top_mass_window_ = (Mass(TopId) - Mass(WId)) / 2;
    bottom_reader_.set_tagger(bottom_tagger_);
    w_semi_reader_.set_tagger(w_semi_tagger_);
    DefineVariables();
}

int TopSemiTagger::Train(Event &event, PreCuts &pre_cuts, const Object::Tag tag)
{
    Print(kInformation, "Top Tags");
    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);

    std::vector<Triplet> triplets;
    if (!boost_) {
        std::vector<Doublet> doublets = w_semi_reader_.Multiplets<WSemiTagger>(event);
        Print(kNotification, "doublet number", doublets.size());
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
        Print(kNotification, "leptons number", leptons.size());
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
    Print(kInformation, "triplet size", triplets.size());


    Jets top_particles = event.Partons().GenParticles();
    top_particles = copy_if_abs_particle(top_particles, TopSemiId(event));
    Print(kNotification, "Number of semi tops", top_particles.size());
    switch (tag) {
    case kSignal :
        BestMatch(triplets, top_particles);
        break;
    case kBackground  :
        RemoveBestMatch(triplets, top_particles);
        break;
    }

    return SaveEntries(triplets);
}


bool TopSemiTagger::Problematic(const Triplet &triplet, PreCuts &pre_cuts, const Tag tag)
{
    Print(kInformation, "Problematic");
    if (pre_cuts.PtLowerCut(TopId) > 0 && triplet.Jet().pt() <  pre_cuts.PtLowerCut(TopId)) return true;
    if (pre_cuts.PtUpperCut(TopId) > 0 && triplet.Jet().pt() >  pre_cuts.PtUpperCut(TopId)) return true;
    switch (tag) {
    case kSignal :
        if (std::abs(triplet.Jet().m() - Mass(TopId)) > top_mass_window_) return true ;
        if (triplet.Rho() < 0.5 || triplet.Rho() > 2) return true ;
        //         if (triplet.Jet().delta_R(TopQuark) > detector_geometry().JetConeSize) return true;
        break;
    case kBackground :
        //         if (triplet.Jet().delta_R(TopQuark) < detector_geometry().JetConeSize) return true;
        break;
    }
    return false;
}

std::vector<Triplet>  TopSemiTagger::Multiplets(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    Print(kInformation, "Bdt");

    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    std::vector<Doublet> doublets = w_semi_reader_.Multiplets<WSemiTagger>(event);

    std::vector<Triplet> triplets;
    if (!boost_) {
        for (const auto & Jet : jets) {
            for (const auto & doublet : doublets) {
                Triplet triplet(doublet, Jet);
//                 if (std::abs(triplet.Jet().m() - Mass(TopId)) > top_mass_window_) continue;
                triplet.SetBdt(Bdt(triplet, reader));
                triplets.emplace_back(triplet);
            }
        }
    } else {
        for (const auto & Jet : jets) {
            for (const auto & Predoublet : doublets) {
                Doublet doublet(Predoublet.SingletJet1());
                Triplet triplet(doublet, Jet);
//             if (std::abs(triplet.Jet().m() - Mass(TopId)) > TopWindow) continue; // reactivate this check
                triplet.SetBdt(Bdt(triplet, reader));
                triplets.emplace_back(triplet);
            }
        }
    }
    return ReduceResult(triplets);
}

}
