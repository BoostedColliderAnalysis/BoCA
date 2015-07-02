#include "AnalysisTagger.hh"
#include "Factory.hh"
#include <sys/stat.h>
#include "Debug.hh"

namespace analysis
{

namespace standardmodel
{

Analysis::Analysis(Tagger &tagger) : analysis::Analysis::Analysis(tagger)
{
    Note();
    this->tagger().set_analysis_name(ProjectName());
}

std::string Analysis::ProcessName(const Process process) const
{
    switch (process) {
    case tt:
        return "tt";
    case tt_lep:
        return "tt_leptonic";
    case tt_had:
        return "tt_hadronic";
    case bb:
        return "bb";
    case cc:
        return "cc";
    case qq:
        return "qq";
    case gg:
        return "gg";
    case hh:
        return "hh";
    case hh_bb:
        return "hh_bb";
    case ww:
        return "ww";
    case zz:
        return "zz";
    case zz_bb:
        return "zz_bb";
    default:
        Error("Process Name", "unhandled case", process);
        return "";
    }
}

std::string Analysis::ColliderName(const Collider collider) const
{
    switch (collider) {
    case LHC :
        return "14TeV";
    case FHC:
        return "100TeV";
    case LE:
        return "LE";
    default:
        Error("Collider name", "unhandled case", collider);
        return "";
    }
}

void Analysis::SetFiles(const Tag tag)
{
    Note(Name(tag));
}

std::string Analysis::NiceName(const Process process) const
{
    switch (process) {
    case bb:
        return "b";
    case cc:
        return "c";
    case qq:
        return "q";
    case gg:
        return "g";
    case hh:
        return "h";
    case hh_bb:
        return "h|_{b}";
    case ww:
        return "W";
    case zz:
        return "Z";
    case zz_bb:
        return "Z|_{b}";
    case tt_had:
        return "t_{h}";
    case tt_lep:
        return "t_{l}";
    default:
        Error("Nice Name", "unhandled case", process);
        return "";
    }
}

std::string Analysis::ProjectName() const
{
    return ColliderName(collider_type()) + "-" + std::to_string(LowerPtCut()) + "GeV";
}

std::string Analysis::FilePath() const
{
    return "~/Projects/Tagger/";
}

void Analysis::NewSignalFile(const standardmodel::Analysis::Process process)
{
    analysis::Analysis::NewSignalFile(FileName(process), NiceName(process));
}

void Analysis::NewBackgroundFile(const standardmodel::Analysis::Process process)
{
    analysis::Analysis::NewBackgroundFile(FileName(process), NiceName(process));
}

std::string Analysis::FileName(const standardmodel::Analysis::Process process) const
{
    return ProcessName(process) + "_" + std::to_string(MadGraphCut()) + "GeV";
}

int Analysis::LowerPtCut() const
{
//         return 350;
//         return 700;
//         return 800;
//     return 500;
    return 1000;
//     return 1200;
}

int standardmodel::Analysis::EventNumberMax() const
{
//     return 1000;
    return 5000;
}


int Analysis::UpperPtCut() const
{
    switch (LowerPtCut()) {
    case 700 :
        return 1000;
    case 1000 :
        return 1500;
    case 1200 :
        return 1500;
    case 500:
        return 1000;
    }
}

int Analysis::MadGraphCut() const
{
    switch (LowerPtCut()) {
    case 500:
        return 500;
    case 700 :
        return 500;
    case 1000 :
        return 1000;
    case 1200 :
        return 1000;
    }
}

int Analysis::LowerQuarkCut() const
{
    return LowerPtCut() * 0.9;
}

int Analysis::UpperQuarkCut() const
{
    return UpperPtCut() * 1.1;
}


standardmodel::Analysis::Collider Analysis::collider_type() const
{
    //       return LHC;
    //       return FHC;
    return LE;
}

int Analysis::BackgroundFileNumber() const
{
    return 1;
    //         return 2;
    //       return 4;
    //       return 5;
    //       return 10;
}

File Analysis::BackgroundFile(const standardmodel::Analysis::Process process) const
{
    return BackgroundFile(process, BackgroundFileNumber());
}

File Analysis::BackgroundFile(const standardmodel::Analysis::Process process, const int file_sum) const
{
    Strings FileNames;
    for (int file_number = 0; file_number < file_sum; ++file_number) {
        FileNames.emplace_back(FileName(process));
    }
    return File(FileNames);
}

std::string Analysis::BackgroundTree(const standardmodel::Analysis::Process Process) const
{
    return ProcessName(Process) + "_" + std::to_string(LowerPtCut()) + "GeV" + "-run_01";
}

void Analysis::RunFast()
{
    RunTagger(analysis::Stage::trainer);
    RunFactory();
}

void Analysis::RunNormal()
{
    RunFast();
    RunTagger(analysis::Stage::reader);
}

void Analysis::RunFull()
{
    RunNormal();
    RunReader();
}

void Analysis::RunTagger(Stage stage)
{
    if (Missing(PathName(tagger().name(stage)))) AnalysisLoop(stage);
}

void Analysis::RunFactory()
{
    PrepareFiles();
    if (Missing(PathName(tagger().factory_name()))) analysis::Factory factory(tagger());
}

void Analysis::RunReader()
{
    PrepareFiles();
    if (Missing(PathName(tagger().bdt_weight_name()))) {
        analysis::Reader reader(tagger());
        reader.TaggingEfficiency();
    }
}

std::string Analysis::PathName(const std::string &file_name) const
{
    Error(file_name);
    return ProjectName() + "/" + file_name + ".root";
}

bool Analysis::Missing(const std::string &name) const
{
    Error(name);
    struct stat buffer;
    return (stat(name.c_str(), &buffer) != 0);
}


}

}
