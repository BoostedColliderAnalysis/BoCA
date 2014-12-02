# include "HFileDelphes.hh"

hanalysis::hdelphes::HFile::HFile()
{

    Print(HNotification, "Constructor");

    SetVariables();

    TreeName = "Delphes";

    FileSuffix = "_delphes_events.root";

}

hanalysis::hdelphes::HFile::HFile(const std::string &Process)
{

    Print(HNotification, "Constructor");

    SetVariables();

    ProcessFolder = Process;

    TreeName = "Delphes";

    FileSuffix = "_delphes_events.root";

}

hanalysis::hdelphes::HFile::HFile(const std::string &Process, const std::string &Run)
{

    Print(HNotification, "Constructor");

    SetVariables();

    ProcessFolder = Process;

    RunFolder = Run;

    TreeName = "Delphes";

    FileSuffix = "_delphes_events.root";

}

std::string hanalysis::hdelphes::HFile::GetFilePath() const
{

    Print(HInformation, "FilePath");


    return (GetMadGraphFilePath() + TagName +  FileSuffix);

}

hanalysis::HEvent *hanalysis::hdelphes::HFile::GetEvent()
{

    Print(HNotification, "Get Event");

    Event = new HEvent();

    return Event;

}

hanalysis::HClonesArray *hanalysis::hdelphes::HFile::GetClonesArrays()
{

    Print(HNotification, "Get Clones Arrays");

        if (SnowMass) {

            ClonesArrays = new HClonesArraySnowmass();

        } else {

            ClonesArrays = new HClonesArray();

        }

    return ClonesArrays;

}
