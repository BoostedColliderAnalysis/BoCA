HDictionary(BranchTopPartner BranchesTopPartner.cpp ../include/LinkDefTopPartner.hh)

set(AnalysisSources
TopPartnerHadronicTagger.cpp
TopPartnerSemiTagger.cpp
HiggsPairTagger.cpp
TopPartnerPairTagger.cpp
SignatureTagger.cpp
Decuplet.cpp
Quattuordecuplet.cpp
EventTagger.cpp
AnalysisTopPartner.cpp
)
HLibrary(AnalysisTopPartner "${AnalysisSources}")

HExecutable(TopPartner main.cpp)
