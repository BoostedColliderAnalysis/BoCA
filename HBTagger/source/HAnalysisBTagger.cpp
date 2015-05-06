# include "HAnalysisBTagger.hh"


void hbtagger::HAnalysis::SetFiles(const hanalysis::HObject::Tag tag)
{
    Print(HNotification, "Set File Vector", tag);

    if(tag == kSignal)NewSignalFile(bb);
//     NewSignalFile(Hbb);
//     NewSignalFile(ttbb);
//     NewSignalFile(ttlep);
//     NewSignalFile(tthad);
//     NewSignalFile(tt);

//     NewBackgroundFile(bb);
    if(tag == kBackground)NewBackgroundFile(cc);
//     NewBackgroundFile(jj);
//     NewBackgroundFile(tt);
//         NewBackgroundFile(ttcc);
//         NewBackgroundFile(ttjj);
//     NewBackgroundFile(qq);
//     NewBackgroundFile(gg);
//     NewBackgroundFile(hh);
//     NewBackgroundFile(ww);

//     NewFiles.front().SetBasePath("~/Projects/BTagging/"); // FIXME implement this info
//     NewFiles.front().SetFileSuffix(".root"); // FIXME implement this info

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

