HDictionary(BranchTopPartner BranchesTopPartner.cpp ../include/LinkDefTopPartner.hh)

set(AnalysisSources
TopPartnerHadronicTagger.cpp
TopPartnerSemiTagger.cpp
HiggsPairTagger.cpp
TopPartnerPairTagger.cpp
TopPartnerHiggsPairTagger.cpp
SignatureTagger.cpp
SignatureSingleTagger.cpp
Septet.cpp
Decuplet.cpp
Quattuordecuplet.cpp
EventTagger.cpp
EventSingleTagger.cpp
AnalysisTopPartner.cpp
)
HLibrary(AnalysisTopPartner AnalysisSources)

HExecutable(TopPartner main.cpp)
