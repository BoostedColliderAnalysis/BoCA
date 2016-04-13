#pragma once

#include <memory>
#include <map>
#include <iostream>

#include "TChain.h"
#include "TTreeReader.h"

#include "io/TreeReaderArray.hh"

namespace boca
{

enum class Branch
{
    particle,
    photon,
    electron,
    muon,
    jet,
    missing_et,
    track,
    tower,
    e_flow_track,
    e_flow_photon,
    e_flow_neutral_hadron,
    e_flow_muon,
    gen_jet,
    scalar_ht,
    tau
};

std::string Name(Branch branch);

enum class Source
{
    delphes,
    pgs,
    parton,
    tagger
};

std::string Name(Source source);

class TreeReader
{

public:

    TreeReader(std::vector<std::string> const& paths, std::string const& tree_name, Source source = Source::delphes);

    TreeReader(std::string const& path, std::string const& tree_name, Source source = Source::delphes);

    TreeReader(TreeReader const& tree_reader);

    long GetEntries() const;

    bool Next(){
      return tree_reader_.Next();
    }

    bool ReadEntry(long number);

    template<typename Object_>
    TTreeReaderArray<Object_>& Array(Branch branch) const {
        if (!Has(branch)) std::cout << Name(branch) << " does not exist " << generator_arrays_.size() << std::endl;
        return const_cast<TTreeReaderArray<Object_> &>(*std::dynamic_pointer_cast<TTreeReaderArray<Object_>>(generator_arrays_.at(branch)).get());
    }

    template<typename Object_>
    TTreeReaderArray<Object_>& Array(std::string const& name) {
      if (!Has(name)) tagger_arrays_.emplace(name, std::make_shared<TTreeReaderArray<Object_>>(tree_reader_, name.c_str()));
      return const_cast<TTreeReaderArray<Object_> &>(*std::dynamic_pointer_cast<TTreeReaderArray<Object_>>(tagger_arrays_.at(name)).get());
    }

    TreeReaderArray& Array(std::string const& name, TClass & cl);

    bool Has(Branch branch) const;

    bool Has(std::string const& name) const;

    TChain & Chain();

private:

    void NewBase(std::string name, TClass & cl);

    TreeReaderArray& Array(std::string const& name) const;

    template<typename Object_>
    void NewElement(std::string const& name) {
      if (Has(name)) std::cout << name << " exists already, will be overwritten" << tagger_arrays_.size() << std::endl;
      tagger_arrays_.emplace(name, std::make_shared<TTreeReaderArray<Object_>>(tree_reader_, name.c_str()));
    }

    void Initialize();

    template<typename Object_>
    void NewElement(Branch branch) {
        if (Has(branch)) std::cout << Name(branch) << " exists already will be overwritten " << generator_arrays_.size() << std::endl;
        generator_arrays_.emplace(branch, std::make_shared<TTreeReaderArray<Object_>>(tree_reader_, Name(branch).c_str()));
    }

    void NewElements();

    std::map<Branch, std::shared_ptr<ROOT::TTreeReaderArrayBase>> generator_arrays_;

    std::map<std::string, std::shared_ptr<ROOT::TTreeReaderArrayBase>> tagger_arrays_;

    TChain chain_;

    TTreeReader tree_reader_;

    Source source_;

    std::string tree_name_;

    std::vector<std::string> paths_;

};

}
