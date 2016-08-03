#pragma once

#include "boca/analysis/Analysis.hh"

template<typename Tagger_>
class Analysis : public boca::Analysis<Tagger_> {

public:

    void SetFiles(boca::Tag tag, boca::Stage) {
        switch(tag) {
        case boca::Tag::signal :
            boca::AnalysisBase::NewFile(tag, "Signal.root", "h");
            break;
        case boca::Tag::background :
            boca::AnalysisBase::NewFile(tag, "Background.root", "bb");
            break;
        }
    }

    std::string AnalysisName() const {
        return "SimpleAnalysis";
    }

};
