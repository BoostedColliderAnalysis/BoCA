# include "HAnalysisBTagger.hh"


void hbtagger::HAnalysis::SetFiles(const hanalysis::HObject::Tag tag)
{
    Print(HNotification, "Set File Vector", tag);

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
    Print(HInformation, "Analysis");
    ++event_sum_;
    switch (stage) {
    case hanalysis::Tagger::kTrainer :
        return tagger_.Train(event, tag);
    case hanalysis::Tagger::kReader :
        return reader_.GetBdt(event);
    }
}

