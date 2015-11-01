/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Trees.hh"
#include "File.hh"
// #define DEBUG
#include "Debug.hh"

namespace boca
{

Files::Files(std::string name, boca::Stage stage, boca::Tag tag): export_file_ {name.c_str(), "Recreate"} {
    Info0;
    stage_ = stage;
    tag_ = tag;
}

TFile& Files::export_file()
{
    return export_file_;
}

File& Files::file() const
{
    return *file_;
}

Stage Files::stage() const
{
    return stage_;
}

Tag Files::tag() const
{
    return tag_;
}

void Files::set_file(File& file)
{
    Info0;
    file_ = &file;
}

Trees::Trees(Files& files):
    tree_writer_(exroot::TreeWriter(&(files.export_file()), files.file().Title().c_str())),
    clones_arrays_(files.file().clones_arrays()),
    event_(files.file().event())
{
    Info0;
}

void Trees::WriteTree()
{
    Info0;
    //         if(event_number_ == tree_reader().GetEntries())
    Error(event_number_, pre_cut_number_, object_sum_);
    if (!analysis_empty_) tree_writer_.Write();
    Info("tree written");
}

void Trees::UseBranches(File& file, std::string const& name)
{
    Info0;
    tree_branch_ = tree_writer_.NewBranch(name.c_str(), InfoBranch::Class());
    tree_reader_ = file.TreeReader();
    clones_arrays_.UseBranches(tree_reader_);
    info_branch_ = FillInfoBranch(file);
}

void Trees::NewEvent(Mass const& mass)
{
    Info0;
    tree_reader_.ReadEntry(entry);
    event_.NewEvent(clones_arrays_);
    event_.SetMass(mass);
}

void Trees::SaveAnalysis(int object_number)
{
    Info0;
    if (object_number == 0) return;
    object_sum_ += object_number;
    info_branch_.EventNumber = event_number_;
//     info_branch_.PreCutNumber = pre_cut_number_;
    analysis_empty_ = false;
    static_cast<InfoBranch&>(*tree_branch_->NewEntry()) = info_branch_;
    tree_writer_.Fill();
    Debug(event_number_, pre_cut_number_, object_sum_);
}

InfoBranch Trees::FillInfoBranch(const File& file)
{
    Info0;
    InfoBranch info_branch;
    info_branch.Crosssection = file.crosssection() / fb;
    info_branch.CrosssectionError = file.crosssection_error() / fb;
    info_branch.Mass = file.mass() / GeV;
    //         info_branch.EventNumber = std::min((long)tree_reader.GetEntries(), event_number_max);
    //         info_branch.EventNumber = event_number_2_;
    info_branch.Name = file.nice_name();
    //         info_branch.NiceName = file.nice_name();
    return info_branch;
}

exroot::TreeReader& Trees::tree_reader()
{
    return tree_reader_;
}

exroot::TreeWriter& Trees::tree_writer()
{
    return tree_writer_;
}

long int& Trees::object_sum()
{
    return object_sum_;
}

Event& Trees::event()
{
    return event_;
}

}

