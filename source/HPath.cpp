# include "HPath.hh"

HPathBase::HPathBase()
{

    Print(0, "Constructor");

    SetVariables();

}

HPathBase::HPathBase(TString Process)
{

    Print(0, "Constructor");

    SetVariables();

    ProcessFolder = Process;
    
    Title = Process;

}

HPathBase::HPathBase(TString Process, TString Run)
{

    Print(0, "Constructor");

    SetVariables();

    ProcessFolder = Process;

    RunFolder = Run;
    
    Title = Process;


}

void HPathBase::SetVariables()
{

    Print(1, "Set Variables");

    //     MadGraphPath = "/data/hajer/MadGraph/";
    //     MadGraphPath = "$HOME/Development/MadGraph/";
    MadGraphPath = "$HOME/Development/madgraph/";

    RunFolder = "run_01";

    TagString = "tag_1";

    TreeString = "Delphes";
    
    Crosssection = 0;

    Error = 0;

}

HPathBase::~HPathBase()
{


    Print(0, "Destructor");

}

TString HPathParton::GetTreeString()
{
    
    Print(1, "Set Tree String");
    
    TreeString = "LHEF";
    
    return TreeString;
    
}

TString HPathParton::FilePath()
{
    
    Print(1, "FilePath");
    
    TString PartonFilePath = MadGraphFilePath() + TagString +  "_pgs_events.root";
    
    return (PartonFilePath);
    
}

TString HPathPgs::GetTreeString()
{
    
    Print(1, "Set Tree String");
    
    TreeString = "LHCO";
    
    return TreeString;
    
}

TString HPathPgs::FilePath()
{
    
    Print(1, "FilePath");
    
    TString PgsFilePath = MadGraphFilePath() + TagString +  "_pgs_events.root";
        
    return (PgsFilePath);
    
}

TString HPathDelphes::GetTreeString()
{
    
    Print(1, "Set Tree String");
    
    TreeString = "Delphes";
    
    return TreeString;
    
}

TString HPathDelphes::FilePath()
{

    Print(1, "FilePath");
    
    TString DelphesFilePath = MadGraphFilePath() + TagString +  "_delphes_events.root";
            
    return (DelphesFilePath);
    
}

TString HPathFlat::GetTreeString()
{
    
    Print(1, "Set Tree String");
    
    TreeString = "Delphes";
    
    return TreeString;
    
}

TString HPathFlat::FilePath()
{
    
    Print(1, "FilePath");
    
    TString BasePath = "~/Projects/HeavyHiggs/Mass/";
    
    TString FlatFilePath = BasePath + ProcessFolder +  "_delphes_events.root";
    
    Title = ProcessFolder;
    
    return (FlatFilePath);
    
}
