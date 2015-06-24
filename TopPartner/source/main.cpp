# include "AnalysisTopPartner.hh"

# include "TSystem.h"
# include "Factory.hh"
# include "EventTagger.hh"
# include "EventSingleTagger.hh"

void RunTagger(analysis::Tagger &tagger, analysis::Tagger::Stage stage)
{
    analysis::toppartner::Analysis analysis(tagger);
    const std::string name = tagger.name(stage);
    analysis.Print(analysis.kError, "Tagger", name);

    std::string file_name = analysis.ProjectName() + "/" + name + ".root";
    if (gSystem->AccessPathName(file_name.c_str())) analysis.AnalysisLoop(stage);
}

void RunFactory(analysis::Tagger &tagger)
{
    analysis::toppartner::Analysis analysis(tagger);
    const std::string name = tagger.name(analysis::Tagger::kTrainer);
    analysis.Print(analysis.kError, "Tagger", name);
    std::string file_name = analysis.ProjectName() + "/Mva" + name + ".root";
    if (gSystem->AccessPathName(file_name.c_str())) analysis::Factory factory(tagger);
}

void RunReader(analysis::Tagger &tagger)
{
    analysis::toppartner::Analysis analysis(tagger);
    const std::string file_name = analysis.ProjectName() + "/" + tagger.tagger_name() + "Bdt.root";
    if (gSystem->AccessPathName(file_name.c_str())) {
        analysis::Reader reader(tagger);
        reader.OptimalSignificance();
    }
}

void RunFast(analysis::Tagger &tagger)
{
    RunTagger(tagger, analysis::Tagger::kTrainer);
    RunFactory(tagger);
    RunTagger(tagger, analysis::Tagger::kReader);
}

int main()
{

    bool single = true;

    analysis::BottomTagger bottom_tagger;
    RunFast(bottom_tagger);

    analysis::HiggsTagger higgs_tagger;
    RunFast(higgs_tagger);

    analysis::WHadronicTagger w_hadronic_tagger;
    RunFast(w_hadronic_tagger);

    analysis::WSemiTagger w_semi_tagger;
    RunFast(w_semi_tagger);

    analysis::TopHadronicTagger top_hadronic_tagger;
    RunFast(top_hadronic_tagger);

    analysis::TopSemiTagger top_semi_tagger;
    RunFast(top_semi_tagger);

    analysis::ZHadronicTagger z_hadronic_tagger;
    RunFast(z_hadronic_tagger);

    analysis::toppartner::TopPartnerSemiTagger top_partner_semi_tagger;
    RunFast(top_partner_semi_tagger);

    if (single) {

        analysis::toppartner::TopPartnerHiggsPairTagger top_partner_higgs_pair_tagger;
        RunFast(top_partner_higgs_pair_tagger);

        analysis::toppartner::SignatureSingleTagger signature_tagger;
        RunFast(signature_tagger);

        analysis::toppartner::EventSingleTagger event_tagger;
        RunFast(event_tagger);
        RunReader(event_tagger);

    } else {

//         analysis::toppartner::TopPartnerHadronicTagger top_partner_hadronic_tagger;
//         Run(top_partner_hadronic_tagger);
//
//         analysis::toppartner::HiggsPairTagger higgs_pair_tagger;
//         Run(higgs_pair_tagger);
//
//         analysis::toppartner::TopPartnerPairTagger top_partner_pair_tagger;
//         Run(top_partner_pair_tagger);
//
//         analysis::toppartner::SignatureTagger signature_tagger;
//         Run(signature_tagger);
//
//         analysis::toppartner::EventTagger event_tagger;
//         Run(event_tagger);
//         RunReader(event_tagger);

    }

}

