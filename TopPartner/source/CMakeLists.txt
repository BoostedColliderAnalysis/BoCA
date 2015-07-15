HDictionary(BranchTopPartner BranchesTopPartner.cpp ../include/LinkDefTopPartner.hh)

set(AnalysisSources
TopPartnerHadronicTagger.cpp
TopPartnerLeptonicTagger.cpp
HiggsPairTagger.cpp
TopPartnerPairTagger.cpp
TopPartnerHiggsPairTagger.cpp
SignatureTagger.cpp
SignatureSingleTagger.cpp
Septet.cpp
Nonet.cpp
Decuplet.cpp
Quattuordecuplet.cpp
EventTagger.cpp
EventSingleTagger.cpp
)
HLibrary(AnalysisTopPartner AnalysisSources)

HExecutable(TopPartner main.cpp)
