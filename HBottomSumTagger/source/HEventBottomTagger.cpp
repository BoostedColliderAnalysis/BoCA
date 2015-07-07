#include "HEventBottomTagger.hh"
#include "Doublet.hh"
#include "Event.hh"
#include "Debug.hh"

hbottomsumtagger::EventBottomTagger::EventBottomTagger()
{
  Note();
    DefineVariables();
}

void hbottomsumtagger::EventBottomTagger::DefineVariables()
{
  Note("Define Variables");
    AddVariable(branch().BottomBdt1, "BottomBdt1");
    AddVariable(branch().BottomBdt2, "BottomBdt2");
    AddVariable(branch().BottomBdt3, "BottomBdt3");
    AddVariable(branch().BottomBdt4, "BottomBdt4");
    AddVariable(branch().BottomBdt5, "BottomBdt5");
    AddVariable(branch().BottomBdt6, "BottomBdt6");
    AddVariable(branch().BottomBdt12, "BottomBdt12");
    AddVariable(branch().BottomBdt34, "BottomBdt34");
    AddVariable(branch().BottomBdt56, "BottomBdt56");
    AddVariable(branch().BottomBdt123, "BottomBdt123");
    AddVariable(branch().BottomBdt1234, "BottomBdt1234");
    AddVariable(branch().Bdt, "Bdt");
    AddSpectator(branch().Tag, "Tag");
}

int hbottomsumtagger::EventBottomTagger::Train(const analysis::Event &event, analysis::PreCuts &precuts, const analysis::Tag tag)
{
  Info("event Tags");

    analysis::Jets jets = bottom_reader_.Multiplets(event);


//     const int JetNumber = 2;
//     const int SignalBottomNumber = 2;
//     const int BackgroundBottomNumber = 0;
//     if (jets.size() < JetNumber) return eventSemiBranches;
//     Jets BottomJets;
//     Jets Particles = event.Partons().GenParticles();
//     Particles = RemoveIfWrongAbsParticle(Particles, Id::bottom);
//     for (const auto & Particle : Particles) {
//         std::sort(jets.begin(), jets.end(), MinDeltaR(Particle));
//         if (jets.front().delta_R(Particle) < detector_geometry().JetConeSize())
//             BottomJets.emplace_back(jets.front());
//     }
//
//     if (Tag == Tag::signal && BottomJets.size() < SignalBottomNumber)  return eventSemiBranches;
//     if (Tag == HBackground && BottomJets.size() < BackgroundBottomNumber)  return eventSemiBranches;

    if (!TruthLevelCheck(jets,event, tag)) return 0;


//     analysis::EventBranch eventMultiplet;
//     eventMultiplet.SetJets(jets);

//     eventMultiplet.SetTag(Tag);
//     std::vector<eventMultiplet>eventSemiBranches;
//     eventSemiBranches.emplace_back(eventMultiplet);

//     return SaveEntries(analysis::Doublet{});
    return 0;
}

bool hbottomsumtagger::EventBottomTagger::TruthLevelCheck(const analysis::Jets &NewJets,const analysis::Event &event, const analysis::Tag Tag)
{
    const unsigned JetNumber = 2;
    const unsigned SignalBottomNumber = 2;
    const unsigned BackgroundBottomNumber = 0;

    analysis::Jets jets = NewJets;

    if (jets.size() < JetNumber) return 0;
    analysis::Jets BottomJets;
    analysis::Jets Particles = event.Partons().GenParticles();
    Particles = RemoveIfWrongAbsParticle(Particles, analysis::Id::bottom);
    for (const auto & Particle : Particles) {
        std::sort(jets.begin(), jets.end(), analysis::MinDeltaRTo(Particle));
        if (jets.front().delta_R(Particle) < analysis::DetectorGeometry().JetConeSize())
            BottomJets.emplace_back(jets.front());
    }

    if (Tag == analysis::Tag::signal && BottomJets.size() < SignalBottomNumber)  return 0;
    if (Tag == analysis::Tag::background && BottomJets.size() <= BackgroundBottomNumber)  return 0;

    return 1;
}

int hbottomsumtagger::EventBottomTagger::Multiplets(const analysis::Event &event, analysis::PreCuts &precuts, const TMVA::Reader &) const
{
  Info("event Tags");
  analysis::Jets jets = bottom_reader_.Multiplets(event);
    std::vector<analysis::EventBranch> eventMultiplets;

    analysis::EventBranch eventMultiplet;
//     eventMultiplet.SetJets(jets);
//     eventMultiplet.SetBdt(Bdt(eventMultiplet,reader));
    eventMultiplets.emplace_back(eventMultiplet);
//     return ReduceResult(eventMultiplets);
    return 0;
}
