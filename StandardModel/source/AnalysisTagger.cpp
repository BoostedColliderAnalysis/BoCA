#include "../include/AnalysisTagger.hh"
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
    case Process::tt:
        return "tt";
    case Process::tt_lep:
        return "tt_leptonic";
    case Process::tt_had:
        return "tt_hadronic";
    case Process::bb:
        return "bb";
    case Process::cc:
        return "cc";
    case Process::qq:
        return "qq";
    case Process::gg:
        return "gg";
    case Process::hh:
        return "hh";
    case Process::hh_bb:
        return "hh_bb";
    case Process::ww:
        return "ww";
    case Process::zz:
        return "zz";
    case Process::zz_bb:
        return "zz_bb";
    default:
        Error("Process Name", "unhandled case", to_int(process));
        return "";
    }
}

std::string Analysis::ColliderName(const Collider collider) const
{
    switch (collider) {
    case Collider::LHC :
        return "14TeV";
    case Collider::FHC:
        return "100TeV";
    case Collider::LE:
        return "LE";
    default:
        Error("Collider name", "unhandled case", to_int(collider));
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
    case Process::bb:
        return "b";
    case Process::cc:
        return "c";
    case Process::qq:
        return "q";
    case Process::gg:
        return "g";
    case Process::hh:
        return "h";
    case Process::hh_bb:
        return "h|_{b}";
    case Process::ww:
        return "W";
    case Process::zz:
        return "Z";
    case Process::zz_bb:
        return "Z|_{b}";
    case Process::tt_had:
        return "t_{h}";
    case Process::tt_lep:
        return "t_{l}";
    default:
        Error("Nice Name", "unhandled case", ProcessName(process));
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

void Analysis::NewSignalFile(const Process process)
{
    analysis::Analysis::NewSignalFile(FileName(process), NiceName(process));
}

void Analysis::NewBackgroundFile(const Process process)
{
    analysis::Analysis::NewBackgroundFile(FileName(process), NiceName(process));
}

std::string Analysis::FileName(const Process process) const
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


Collider Analysis::collider_type() const
{
    //       return Collider::LHC;
    //       return Collider::FHC;
    return Collider::LE;
}

int Analysis::BackgroundFileNumber() const
{
    return 1;
    //         return 2;
    //       return 4;
    //       return 5;
    //       return 10;
}

File Analysis::BackgroundFile(const Process process) const
{
    return BackgroundFile(process, BackgroundFileNumber());
}

File Analysis::BackgroundFile(const Process process, const int file_sum) const
{
    Strings FileNames;
    for (int file_number = 0; file_number < file_sum; ++file_number) {
        FileNames.emplace_back(FileName(process));
    }
    return File(FileNames);
}

std::string Analysis::BackgroundTree(const Process Process) const
{
    return ProcessName(Process) + "_" + std::to_string(LowerPtCut()) + "GeV" + "-run_01";
}

}

}
