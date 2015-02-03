# include "HFileDelphes.hh"

hanalysis::hdelphes::HFile::HFile()
{
    Print(HInformation, "Constructor");
    SetVariables();
    TreeName = "Delphes";
    FileSuffix = "_delphes_events.root";
}

hanalysis::hdelphes::HFile::HFile(const std::string &Process)
{
    Print(HInformation, "Constructor");
    SetVariables();
    ProcessFolder = Process;
    TreeName = "Delphes";
    FileSuffix = "_delphes_events.root";
}

hanalysis::hdelphes::HFile::HFile(const std::string &Process, const std::string &Run)
{
    Print(HInformation, "Constructor");
    SetVariables();
    ProcessFolder = Process;
    RunFolder = Run;
    TreeName = "Delphes";
    FileSuffix = "_delphes_events.root";
}

std::string hanalysis::hdelphes::HFile::GetFilePath() const
{
    Print(HInformation, "FilePath");
    return GetMadGraphFilePath() + TagName +  FileSuffix;
}

std::shared_ptr<hanalysis::HEvent> hanalysis::hdelphes::HFile::GetEvent()
{
    Print(HNotification, "Get Event");
    return std::shared_ptr<hanalysis::HEvent>(new HEvent());
}

std::shared_ptr<hanalysis::HClonesArray> hanalysis::hdelphes::HFile::GetClonesArrays()
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
