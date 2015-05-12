# include "HAnalysisBTagger.hh"


hbtagger::HAnalysis::HAnalysis(hanalysis::Tagger &tagger) : hanalysis::HAnalysis::HAnalysis(tagger)
{
  Print(kNotification, "Constructor");
  event_sum_ = 0;
  tagger_.set_analysis_name(ProjectName());
}


void hbtagger::HAnalysis::SetFiles(const hanalysis::HObject::Tag tag)
{
    Print(kNotification, "Set File Vector", tag);

    switch (tag) {
    case kSignal :
        NewSignalFile(bb);
//     NewSignalFile(Hbb);
//     NewSignalFile(ttbb);
//     NewSignalFile(ttlep);
//     NewSignalFile(tthad);
//     NewSignalFile(tt);

//     NewBackgroundFile(bb);
        break;
    case kBackground :
        NewBackgroundFile(cc);
//     NewBackgroundFile(jj);
//     NewBackgroundFile(tt);
//         NewBackgroundFile(ttcc);
//         NewBackgroundFile(ttjj);
//     NewBackgroundFile(qq);
//     NewBackgroundFile(gg);
//     NewBackgroundFile(hh);
//     NewBackgroundFile(ww);
    }

}


int hbtagger::HAnalysis::Analysis(hanalysis::HEvent &event, const hanalysis::Tagger::Stage stage, const Tag tag)
{
    Print(kInformation, "Analysis");
    ++event_sum_;
    switch (stage) {
    case hanalysis::Tagger::kTrainer :
        return tagger_.Train(event, tag);
    case hanalysis::Tagger::kReader :
        return reader_.GetBdt(event);
    }
}

