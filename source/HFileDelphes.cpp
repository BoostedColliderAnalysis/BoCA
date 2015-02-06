# include "HFileDelphes.hh"

hanalysis::hdelphes::HFile::HFile()
{
    Print(HInformation, "Constructor");
//     SetVariables();
    TreeNameM = "Delphes";
    FileSuffix = "_delphes_events.root";
}

hanalysis::hdelphes::HFile::HFile(const std::string &Process)
{
    Print(HInformation, "Constructor");
//     SetVariables();
//     ProcessFolder = Process;
    TreeNameM = "Delphes";
    FileSuffix = "_delphes_events.root";
}

hanalysis::hdelphes::HFile::HFile(const std::string &Process, const std::string &Run)
{
    Print(HInformation, "Constructor");
//     SetVariables();
//     ProcessFolder = Process;
//     RunFolder = Run;
    TreeNameM = "Delphes";
    FileSuffix = "_delphes_events.root";
}

HStrings hanalysis::hdelphes::HFile::Paths() const
{
    Print(HInformation, "FilePath");
    HStrings FilePahts;
    FilePahts.push_back(GetMadGraphFilePath() + TagName +  FileSuffix);
    return FilePahts;
}

std::shared_ptr<hanalysis::HEvent> hanalysis::hdelphes::HFile::Event()
{
    Print(HNotification, "Get Event");
    return std::shared_ptr<hanalysis::HEvent>(new HEvent());
}

std::shared_ptr<hanalysis::HClonesArray> hanalysis::hdelphes::HFile::ClonesArrays()
{
    Print(HNotification, "Get Clones Arrays");
    if (SnowMass) {
//       ClonesArrays = new HClonesArraySnowmass();
      return std::shared_ptr<hanalysis::HClonesArray>(new HClonesArraySnowmass());
//       /*ClonesArrays*/ = std::move(ClonesArrays2);
    } else {
//       ClonesArrays = new HClonesArray();
      return std::shared_ptr<hanalysis::HClonesArray>(new HClonesArray());
//         ClonesArrays = std::move(ClonesArrays2);
    }
//     return ClonesArrays;

}
