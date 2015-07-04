HDictionary(BranchTopPartner BranchesTopPartner.cpp ../include/LinkDefTopPartner.hh)

set(AnalysisSources
TopPartnerHadronicTagger.cpp
TopPartnerSemiTagger.cpp
TopPartnerLeptonicTagger.cpp
HiggsPairTagger.cpp
TopPartnerPairTagger.cpp
TopPartnerLeptonicPairTagger.cpp
TopPartnerHiggsPairTagger.cpp
SignatureTagger.cpp
SignatureSingleTagger.cpp
Septet.cpp
Nonet.cpp
Decuplet.cpp
Quattuordecuplet.cpp
EventTagger.cpp
EventSingleTagger.cpp
AnalysisTopPartner.cpp
)
HLibrary(AnalysisTopPartner AnalysisSources)

HExecutable(TopPartner main.cpp)
