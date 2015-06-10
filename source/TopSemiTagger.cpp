# include "TopSemiTagger.hh"

analysis::TopSemiTagger::TopSemiTagger()
{
    //     DebugLevel = analysis::Object::kDebug;
    Print(kNotification, "Constructor");
    set_tagger_name("TopSemi");
    top_mass_window_ = (Mass(TopId) - Mass(WId)) / 2;
    bottom_reader_.set_tagger(bottom_tagger_);
    w_semi_reader_.set_tagger(w_semi_tagger_);
    DefineVariables();
}

void analysis::TopSemiTagger::DefineVariables()
{
    Print(kNotification , "Define Variables");
    AddVariable(branch_.Mass, "Mass");
    AddVariable(branch_.Rap, "Rap");
    AddVariable(branch_.Phi, "Phi");
    AddVariable(branch_.Pt, "Pt");
    AddVariable(branch_.Ht, "Ht");
    AddVariable(branch_.BottomPt, "BottomPt");
    AddVariable(branch_.WPt, "WPt");
    AddVariable(branch_.DeltaPt, "DeltaPt");
    AddVariable(branch_.DeltaM, "DeltaM");
    AddVariable(branch_.DeltaHt, "DeltaHt");
    AddVariable(branch_.DeltaPhi, "DeltaPhi");
    AddVariable(branch_.DeltaRap, "DeltaRap");
    AddVariable(branch_.DeltaR, "DeltaR");
    AddVariable(branch_.WBdt, "WBdt");
    AddVariable(branch_.BBdt, "BBdt");
    AddVariable(branch_.Bdt, "Bdt");
    AddSpectator(branch_.Tag, "Tag");
}

int analysis::TopSemiTagger::Train(analysis::Event &event, PreCuts &pre_cuts, const analysis::Object::Tag tag)
{
    Print(kInformation, "Top Tags");

    Jets top_particles = event.Partons().GenParticles();
    top_particles = copy_if_particle(top_particles, TopSemiId(event));

    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    std::vector<analysis::Doublet> doublets = w_semi_reader_.Multiplets<WSemiTagger>(event);

    Jets leptons = event.Leptons().leptons();
    Print(kInformation, "Lepton Number", leptons.size());

    std::vector<Triplet> triplets;
    if (!boost_) {
        for (const auto & jet : jets) {
            for (const auto & doublet : doublets) {
                Triplet triplet(doublet, jet);
                triplet.SetTag(tag);
                std::vector<Triplet> pre_triplets = CleanTriplets(triplet,top_particles,pre_cuts,tag);
                if(!pre_triplets.empty()) triplets.emplace_back(pre_triplets.front());
            }
        }
    } else {
        for (const auto & jet : jets) {
            for (const auto & lepton : leptons) {
                Doublet doublet(lepton);
                Triplet triplet(doublet, jet);
                triplet.SetTag(tag);
                std::vector<Triplet> pre_triplets = CleanTriplets(triplet,top_particles,pre_cuts,tag);
                if(!pre_triplets.empty()) triplets.emplace_back(pre_triplets.front());
            }
        }
    }

    if (tag == kSignal && triplets.size() > top_particles.size()) {
        triplets = SortedByMassTo(triplets, Mass(TopId));
        triplets.erase(triplets.begin() + top_particles.size(), triplets.end());
    }
    Print(kInformation, "Number triplets", triplets.size());

    return SaveEntries<TopSemiBranch>(triplets);
}

std::vector<analysis::Triplet> analysis::TopSemiTagger::CleanTriplets(const Triplet &triplet, Jets TopQuarks, PreCuts &pre_cuts, const Tag tag) {
    std::vector<analysis::Triplet> triplets;
    for(const auto particle : TopQuarks) JoinVectors(triplets,CleanTriplet(triplet,particle,pre_cuts,tag));
    return triplets;
}

std::vector<analysis::Triplet> analysis::TopSemiTagger::CleanTriplet(const Triplet &triplet, fastjet::PseudoJet TopQuark, PreCuts& pre_cuts, const Tag tag) {
    std::vector<analysis::Triplet> triplets;
    if (tag == kSignal && std::abs(triplet.Jet().m() - Mass(TopId)) > top_mass_window_) return triplets ; // should be enabled again
    if (tag == kSignal && triplet.Jet().pt() <  pre_cuts.PtLowerCut(TopId)) return triplets;
    if (tag == kSignal && triplet.Jet().pt() >  pre_cuts.PtUpperCut(TopId)) return triplets;
    if (tag == kSignal && triplet.Jet().delta_R(TopQuark) > detector_geometry().JetConeSize) return triplets;
    if (tag == kBackground && triplet.Jet().delta_R(TopQuark) < detector_geometry().JetConeSize) return triplets;
    triplets.push_back(triplet);
    return triplets;
}

std::vector<analysis::Triplet>  analysis::TopSemiTagger::Multiplets(Event &event, const TMVA::Reader &reader)
{
    Print(kInformation, "Bdt");

    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    std::vector<analysis::Doublet> doublets = w_semi_reader_.Multiplets<WSemiTagger>(event);

    std::vector<Triplet> triplets;
    if (!boost_) {
        for (const auto & Jet : jets) {
            for (const auto & doublet : doublets) {
                Triplet triplet(doublet, Jet);
                if (std::abs(triplet.Jet().m() - Mass(TopId)) > top_mass_window_) continue;
                branch_ = branch<TopSemiBranch>(triplet);
                triplet.SetBdt(Bdt(reader));
                triplets.emplace_back(triplet);
            }
        }
    } else {
        for (const auto & Jet : jets) {
            for (const auto & Predoublet : doublets) {
                Doublet doublet(Predoublet.SingletJet1());
                Triplet triplet(doublet, Jet);
//             if (std::abs(triplet.Jet().m() - Mass(TopId)) > TopWindow) continue; // reactivate this check
                branch_ = branch<TopSemiBranch>(triplet);
                triplet.SetBdt(Bdt(reader));
                triplets.emplace_back(triplet);
            }
        }
    }
    return ReduceResult(triplets);
}
