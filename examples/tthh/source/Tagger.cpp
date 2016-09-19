#include "tthh/Tagger.hh"

//#define INFORMATION
#include "boca/generic/DEBUG_MACROS.hh"

namespace tthh {

using namespace boca::units;
    
int Tagger::Train(boca::Event const &event, boca::PreCuts const &, boca::Tag tag)
{
    Observables observables(event);
    observables.SetTag(tag);
    auto mass = observables.PhotonPM();
    auto masswindow = 20_GeV;
    INFO(mass);
    if(tag == boca::Tag::signal){
        if (mass == boca::massless) return 0;
        if(mass > MassOf(boca::Id::higgs) + masswindow) return 0;
        if(mass < MassOf(boca::Id::higgs) - masswindow) return 0;
    }
//    else {
//        if(mass < MassOf(boca::Id::higgs) + masswindow && mass > MassOf(boca::Id::higgs) - masswindow) return 0;
//    }
    return SaveEntries({observables});
}

std::vector<Observables> Tagger::Multiplets(boca::Event const &event, boca::PreCuts const &, TMVA::Reader const &reader)
{
    Observables observables(event);
    observables.SetBdt(Bdt(observables, reader));
    return {observables};
}

std::string Tagger::Name() const
{
    return "tthh";
}

}
