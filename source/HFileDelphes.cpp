# include "HFileDelphes.hh"

hanalysis::hdelphes::HFile::HFile()
{

    Print(1, "Constructor");

    SetVariables();

    TreeName = "Delphes";

    FileSuffix = "_delphes_events.root";

}

hanalysis::hdelphes::HFile::HFile(const string &Process)
{

    Print(1, "Constructor");

    SetVariables();

    ProcessFolder = Process;

    TreeName = "Delphes";

    FileSuffix = "_delphes_events.root";

}

hanalysis::hdelphes::HFile::HFile(const string &Process, const string &Run)
{

    Print(1, "Constructor");

    SetVariables();

    ProcessFolder = Process;

    RunFolder = Run;

    TreeName = "Delphes";

    FileSuffix = "_delphes_events.root";

}

string hanalysis::hdelphes::HFile::GetFilePath() const
{

    Print(2, "FilePath");


    return (GetMadGraphFilePath() + TagString +  FileSuffix);

}

hanalysis::HEvent *hanalysis::hdelphes::HFile::GetEvent()
{

    Print(1, "Get Event");

    Event = new HEvent();

    return Event;

}

hanalysis::HClonesArray *hanalysis::hdelphes::HFile::GetClonesArrays()
{

    Print(1, "Get Clones Arrays");

        if (SnowMass) {

            ClonesArrays = new HClonesArraySnowmass();

        } else {

            ClonesArrays = new HClonesArray();

        }

    return ClonesArrays;

}
