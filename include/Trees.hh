#pragma once

#include "TFile.h"
#include "exroot/ExRootAnalysis.hh"

#include "ClonesArrays.hh"
#include "Event.hh"
#include "AnalysisBase.hh"

namespace analysis
{

class Files
{
public:
    Files(std::string name, Stage stage, Tag tag);
    TFile& export_file();
    File& file() const;
    Stage stage() const;
    Tag tag() const;
    void set_file(File& file);
private:
    TFile export_file_;
    File* file_;
    Stage stage_;
    Tag tag_;
};

class Trees
{
public:
    Trees(Files& files);
    void WriteTree();
    void UseBranches(File& file, const std::string& name);
    void NewEvent(int mass);
    void SaveAnalysis(int object_number);
    InfoBranch FillInfoBranch(const File& file);
    exroot::TreeReader& tree_reader();
    exroot::TreeWriter& tree_writer();
    Event& event();
    long& object_sum();
    long entry = 0;
    long event_number_ = 0;
    long pre_cut_number_ = 0;
private:
    exroot::TreeReader tree_reader_;
    exroot::TreeBranch* tree_branch_;
    exroot::TreeWriter tree_writer_;
    ClonesArrays clones_arrays_;
    Event event_;
    InfoBranch info_branch_;
    long object_sum_ = 0;
    bool analysis_empty_ = true;
};

}
