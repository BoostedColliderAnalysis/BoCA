HDictionary(BranchTopPartner ./Branches.cpp ../include/LinkDefTopPartner.hh)

set(AnalysisSources
TopPartnerTagger.cpp
SignatureTagger.cpp
Quattuordecuplet.cpp
)
HLibrary(AnalysisTopPartner "${AnalysisSources}")

# HExecutable(TopPartner Main.cpp)
