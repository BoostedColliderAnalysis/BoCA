/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "TFile.h"
#include "TClonesArray.h"
#include "TTree.h"

#include "exroot/ExRootAnalysis.hh"

#include "plotting/Plotting.hh"
#include "plotting/LatexFile.hh"
#include "plotting/Graphs.hh"
#include "plotting/Results.hh"
#include "plotting/Histograms.hh"
#include "plotting/Histogram2Dim.hh"
#include "plotting/Profile.hh"
#include "plotting/Plots.hh"
#include "plotting/Font.hh"
#include "Branches.hh"

// #define INFORMATION
#include "Debug.hh"

namespace boca
{

Plotting::Plotting(boca::Tagger& tagger) :
    tagger_(tagger)
{
    Info0;
}

void Plotting::TaggingEfficiency() const
{
    Info0;
    Results results = ReadBdtFiles();
    PlotHistograms(results);
    PlotEfficiencyGraph(results);
    PlotAcceptanceGraph(results);
}

void Plotting::OptimalCuts() const
{
    Info0;
    Results results = ReadBdtFiles();
    results.CalculateSignificances();
    LatexFile latex_file(Tagger().ExportFolderName());
    latex_file.Mass(results.Signals().front().InfoBranch().Mass());
    if (Tagger().Mva() == TMVA::Types::EMVA::kBDT) latex_file.IncludeGraphic(PlotHistograms(results), "BDT Distribution");
    latex_file.IncludeGraphic(PlotEfficiencyGraph(results), "Efficiency");
    latex_file.IncludeGraphic(PlotCrosssectionsGraph(results), "Crosssection in fb");
    latex_file.IncludeGraphic(PlotModelIndependentGraph(results), "Minimization of the crosssection for the model-independent result");
    latex_file.IncludeGraphic(PlotModelDependentGraph(results), "Maximization of the significance for the model-dependent result");
    latex_file.IncludeGraphic(PlotCrosssectionGraph(results), "Maximization of $S/\\sqrt B$");
    latex_file.Table("rlllll", EfficienciesTable(results, results.BestModelInDependentBin()), "Model independent efficiencies");
    latex_file.Table("rlllll", EfficienciesTable(results, results.BestModelDependentBin()), "Model dependent efficiencies");
    latex_file.Table("rlll", BestValueTable(results), "Results for the optimal model-(in)dependent cuts");
}

Results Plotting::ReadBdtFiles() const
{
    Info0;
    TFile file(Tagger().ExportFileName().c_str(), "Recreate");
    return Results(ReadBdtFile(file, Tag::signal), ReadBdtFile(file, Tag::background));
}

std::vector<Result> Plotting::ReadBdtFile(TFile& export_file, Tag tag) const
{
    Info0;
    std::string file_name = Tagger().FileName(Stage::reader, tag);
    Debug(file_name);
    if (!Exists(file_name)) Error("non existent", file_name);
    TFile file(file_name.c_str(), "Read");
    std::vector<Result> results;
    switch (Tagger().Mva()) {
    case TMVA::Types::EMVA::kBDT : for (auto const & tree_name : Tagger().TreeNames(tag)) results.emplace_back(BdtDistribution(file, tree_name, export_file));
        return results;
    case TMVA::Types::EMVA::kCuts: for (auto const & tree_name : Tagger().TreeNames(tag)) results.emplace_back(CutDistribution(file, tree_name, export_file));
        return results;
        Default(Tagger().Mva(), results);
    }
}

Result Plotting::BdtDistribution(TFile& file, std::string const& tree_name, TFile& export_file) const
{
    Info0;
    std::string branch_name = Tagger().BranchName(Stage::reader);
    Debug(branch_name);
    exroot::TreeReader tree_reader(static_cast<TTree*>(file.Get(tree_name.c_str())));
    TClonesArray& clones_array = *tree_reader.UseBranch(branch_name.c_str());
    exroot::TreeWriter tree_writer(&export_file, tree_name.c_str());
    exroot::TreeBranch& branch = *tree_writer.NewBranch(branch_name.c_str(), BdtBranch::Class());
    std::vector<float> bdts;
    for (auto const & event_number : Range(tree_reader.GetEntries())) {
        tree_reader.ReadEntry(event_number);
        for (auto const & entry : Range(clones_array.GetEntriesFast())) {
            float bdt =  static_cast<BdtBranch&>(*clones_array.At(entry)).Bdt;
            static_cast<BdtBranch&>(*branch.NewEntry()).Bdt = bdt;
            bdts.emplace_back(bdt);
        }
        tree_writer.Fill();
        tree_writer.Clear();
    }
    tree_writer.Write();
    return Result(InfoBranch(file, tree_name), bdts, Tagger().Mva());
}

Result Plotting::CutDistribution(TFile& file, std::string const& tree_name, TFile& export_file) const
{
    INFO(tree_name);
    std::string branch_name = Tagger().BranchName(Stage::reader);
    exroot::TreeReader tree_reader(static_cast<TTree*>(file.Get(tree_name.c_str())));
    TClonesArray& clones_array = *tree_reader.UseBranch(branch_name.c_str());
    exroot::TreeWriter tree_writer(&export_file, tree_name.c_str());
    exroot::TreeBranch& branch = *tree_writer.NewBranch(branch_name.c_str(), CutBranch::Class());
    std::vector<std::vector<bool>> passed_matrix;
    for (auto const & event_number : Range(tree_reader.GetEntries())) {
        tree_reader.ReadEntry(event_number);
        for (auto const & entry : Range(clones_array.GetEntriesFast())) {
            std::vector<bool> passed_vector = dynamic_cast<CutBranch&>(*clones_array.At(entry)).passed_;
            static_cast<CutBranch&>(*branch.NewEntry()).passed_ = passed_vector;
            passed_matrix.emplace_back(passed_vector);
        }
        tree_writer.Fill();
        tree_writer.Clear();
    }
    tree_writer.Write();
    return Result(InfoBranch(file, tree_name), passed_matrix, Tagger().Mva());
}

InfoBranch Plotting::InfoBranch(TFile& file, std::string const& tree_name) const
{
    INFO(tree_name);
    exroot::TreeReader tree_reader(static_cast<TTree*>(file.Get(tree_name.c_str())));
    Error(tree_name, Tagger().WeightBranchName());
    TClonesArray* clones_array = tree_reader.UseBranch(Tagger().WeightBranchName().c_str());
    tree_reader.ReadEntry(tree_reader.GetEntries() - 1);
    return static_cast<boca::InfoBranch&>(*clones_array->Last());
}

std::string Plotting::PlotHistograms(Results const& results) const
{
    Info0;
    Histograms histograms(Tagger().ExportFolderName(), "Bdt");
    for (auto const & result : results.Signals()) histograms.AddHistogram(result.Bdts(), result.InfoBranch().LatexName(), results.Bounds());
    for (auto const & result : results.Backgrounds()) histograms.AddHistogram(result.Bdts(), result.InfoBranch().LatexName(), results.Bounds());
    histograms.SetLegend(Orientation::top);
    histograms.SetXAxis("BDT");
    histograms.SetYAxis("N");
    histograms.AddLine(results.BestModelDependentValue());
    histograms.AddLine(results.BestModelInDependentValue());
    return histograms.FileBaseName();
}

std::string Plotting::PlotEfficiencyGraph(Results const& results) const
{
    Info0;
    Graphs graphs(Tagger().ExportFolderName(), "Efficiency");
    for (auto const & result : results.Signals()) graphs.AddGraph(results.XValues(), result.Efficiencies(), result.InfoBranch().LatexName());
    for (auto const & result : results.Backgrounds()) graphs.AddGraph(results.XValues(), result.Efficiencies(), result.InfoBranch().LatexName());
    graphs.SetLegend(Orientation::bottom | Orientation::left);
    switch (Tagger().Mva()) {
    case TMVA::Types::EMVA::kBDT :
        graphs.SetXAxis("BDT", results.Bounds().Horizontal());
        graphs.SetYAxis("Efficiency");
        break;
    case TMVA::Types::EMVA::kCuts :
        graphs.SetXAxis("Calculated", results.Bounds().Horizontal());
        graphs.SetYAxis("Measured");
        break;
    default : Error(Tagger().Mva(), "case not handled");
    }
    graphs.AddLine(results.BestModelDependentValue());
    graphs.AddLine(results.BestModelInDependentValue());
    return graphs.FileBaseName();
}

void Plotting::PlotAcceptanceGraph(Results const& results) const
{
    Info0;
    for (auto const & signal : results.Signals()) {
        Graphs graphs(Tagger().ExportFolderName(), "Acceptance" + std::to_string(&signal - &results.Signals().front()));
        for (auto const & background : results.Backgrounds()) graphs.AddGraph(signal.PureEfficiencies(), background.PureEfficiencies(), background.InfoBranch().LatexName());
        graphs.SetLegend(Orientation::right | Orientation::bottom, signal.InfoBranch().LatexName());
        graphs.SetXAxis("Signal acceptance", {0.2, 0.9});
        graphs.SetYAxis("Background acceptance");
    }
}

std::string Plotting::PlotCrosssectionsGraph(Results const& results) const
{
    Info0;
    Graphs graphs(Tagger().ExportFolderName(), "Crosssection");
    for (auto const & result : results.Signals()) graphs.AddGraph(results.XValues(), FloatVector(result.Crosssections()), result.InfoBranch().LatexName());
    for (auto const & result : results.Backgrounds()) graphs.AddGraph(results.XValues(), FloatVector(result.Crosssections()), result.InfoBranch().LatexName());
    graphs.SetLegend(Orientation::bottom | Orientation::left);
    switch (Tagger().Mva()) {
    case TMVA::Types::EMVA::kBDT :
        graphs.SetXAxis("BDT", results.Bounds().Horizontal());
        break;
    case TMVA::Types::EMVA::kCuts :
        graphs.SetXAxis("MVA", results.Bounds().Horizontal());
        break;
    default : Error(Tagger().Mva(), "case not handled");
    }
    graphs.SetYAxis("Crosssection [fb]");
    graphs.AddLine(results.BestModelDependentValue());
    graphs.AddLine(results.BestModelInDependentValue());
    return graphs.FileBaseName();
}

std::string Plotting::PlotModelDependentGraph(Results const& results) const
{
    Info0;
    Graphs graphs(Tagger().ExportFolderName(), "Significance");
    graphs.AddGraph(results.XValues(), results.Significances());
    switch (Tagger().Mva()) {
    case TMVA::Types::EMVA::kBDT :
        graphs.SetXAxis("BDT", results.Bounds().Horizontal());
        break;
    case TMVA::Types::EMVA::kCuts :
        graphs.SetXAxis("MVA", results.Bounds().Horizontal());
        break;
    default : Error(Tagger().Mva(), "case not handled");
    }
    graphs.SetYAxis("Significance");
    graphs.AddLine(results.BestModelDependentValue());
    return graphs.FileBaseName();
}

std::string Plotting::PlotCrosssectionGraph(Results const& results) const
{
    Info0;
    Graphs graphs(Tagger().ExportFolderName(), "SB");
    graphs.AddGraph(results.XValues(), results.Acceptances());
    switch (Tagger().Mva()) {
    case TMVA::Types::EMVA::kBDT :
        graphs.SetXAxis("BDT", results.Bounds().Horizontal());
        break;
    case TMVA::Types::EMVA::kCuts :
        graphs.SetXAxis("MVA", results.Bounds().Horizontal());
        break;
    default : Error(Tagger().Mva(), "case not handled");
    }
    graphs.SetYAxis(Formula("S/#sqrt{B}"));
    graphs.AddLine(results.BestAcceptanceValue());
    return graphs.FileBaseName();
}

std::string Plotting::PlotModelIndependentGraph(Results const& results) const
{
    Info0;
    Graphs graphs(Tagger().ExportFolderName(), "Exclusion");
    graphs.AddGraph(results.XValues(), FloatVector(results.ModelIndependentCrosssection()));
    switch (Tagger().Mva()) {
    case TMVA::Types::EMVA::kBDT :
        graphs.SetXAxis("BDT", results.Bounds().Horizontal());
        break;
    case TMVA::Types::EMVA::kCuts :
        graphs.SetXAxis("MVA", results.Bounds().Horizontal());
        break;
    default : Error(Tagger().Mva(), "case not handled");
    }
    graphs.SetYAxis("Crosssection");
    graphs.AddLine(results.BestModelInDependentValue());
    return graphs.FileBaseName();
}

std::string Plotting::BestValueTable(Results const& results) const
{
    Info0;
    std::stringstream table;
    table << "    Model\n  & Cut\n  & $p$-value\n  & Crosssection [fb]";
    table << "\n \\\\ \\midrule\n   ";
    table << BestValueRow(results, results.BestModelDependentBin(), "Dependet");
    table << BestValueRow(results, results.BestModelInDependentBin(), "Independet");
    table << BestValueRow(results, results.BestAcceptanceBin(), "$S/\\sqrt B$");
    return table.str();
}

std::string Plotting::BestValueRow(Results const& results, int bin, std::string const& name) const
{
    Info0;
    std::stringstream row;
    row << " " << name;
    row << "\n  & " << RoundToDigits(results.XValue(bin));
    row << "\n  & " << RoundToDigits(results.Significances().at(bin));
    row << "\n  & " << RoundToDigits(results.ModelIndependentCrosssection().at(bin) / fb);
    row << "\n \\\\";
    return row.str();
}

std::string Plotting::EfficienciesTable(Results const& results, int bin) const
{
    Info0;
    std::stringstream table;
    table << "    Sample\n  & before\n  & after\n  & Efficiency\n  & $\\sigma$  [fb]\n  & $N_{\\mathcal L = \\unit[" << RoundToDigits(DetectorGeometry::Luminosity() * fb) << "]{fb^{-1}}}$";
    table << "\n \\\\ \\midrule\n   ";
    for (auto const & result : results.Signals()) table << EfficienciesRow(result, &result - &results.Signals().front(), Tag::signal, bin);
    for (auto const & result : results.Backgrounds()) table << EfficienciesRow(result, &result - &results.Backgrounds().front(), Tag::background, bin);
    return table.str();
}

std::string Plotting::EfficienciesRow(Result const& result, int index, Tag tag, int bin) const
{
    Info0;
    std::stringstream row;
    row << " \\verb|" << Tagger().TreeNames(tag).at(index) << "|";
    row << "\n  & " << result.InfoBranch().EventNumber();
    row << "\n  & " << result.EventSums().at(bin);
    row << "\n  & " << RoundToDigits(result.Efficiencies().at(bin));
    row << "\n  & " << RoundToDigits(result.InfoBranch().Crosssection() / fb);
    row << "\n  & " << RoundToDigits(result.InfoBranch().Crosssection() * DetectorGeometry::Luminosity() * result.Efficiencies().at(bin));
    row << "\n \\\\";
    return row.str();
}

void Plotting::RunPlots(Stage stage) const
{
    Info0;
    Debug(Tagger().FileName(stage, Tag::signal), Tagger().TreeNames(Tag::signal).size());
    std::vector<Plots> signals = Import(stage, Tag::signal);
    Debug(Tagger().FileName(stage, Tag::background), Tagger().TreeNames(Tag::background).size());
    std::vector<Plots> backgrounds = Import(stage, Tag::background);
    Plots background = backgrounds.front();
    if (backgrounds.size() > 1) {
        background = std::accumulate(backgrounds.begin() + 1, backgrounds.end(), background, [](Plots & sum, Plots const & plots) {
            for (auto & plot : sum.plots()) plot.Join(plots.plots().at(&plot - &sum.plots().front()).Data());
            return sum;
        });
        background.SetName("background");
    }
    for (auto & signal : signals) DoPlot(signal, background, stage);

}

void Plotting::DoPlot(Plots& signals, Plots& backgrounds, Stage stage) const
{
    Info0;
    NamePairs names = unordered_pairs(tagger_.Branch().Variables().Vector(), [&](Observable const & variable_1, Observable const & variable_2) {
        return std::make_pair(variable_1.Names(), variable_2.Names());
    });
    signals.SetNames(names);
    backgrounds.SetNames(names);
    for (auto & signal : signals.plots()) PlotDetails(signal, backgrounds.plots().at(&signal - &signals.plots().front()), stage);
}

void Plotting::PlotDetails(Plot& signal, Plot& background, Stage stage) const
{
    INFO(signal.Data().size(), background.Data().size());
    std::vector<Vector3<float>> signal_x = signal.CoreData([](Vector3<float> const & a, Vector3<float> const & b) {
        return a.X() < b.X();
    });
    std::vector<Vector3<float>> signal_y = signal.CoreData([](Vector3<float> const & a, Vector3<float> const & b) {
        return a.Y() < b.Y();
    });
    std::vector<Vector3<float>> background_x = background.CoreData([](Vector3<float> const & a, Vector3<float> const & b) {
        return a.X() < b.X();
    });
    std::vector<Vector3<float>> background_y = background.CoreData([](Vector3<float> const & a, Vector3<float> const & b) {
        return a.Y() < b.Y();
    });
    Rectangle<float> bounds;
    bounds.SetXMin(std::min(signal_x.front().X(), background_x.front().X()));
    bounds.SetXMax(std::max(signal_x.back().X(), background_x.back().X()));
    bounds.SetYMin(std::min(signal_y.front().Y(), background_y.front().Y()));
    bounds.SetYMax(std::max(signal_y.back().Y(), background_y.back().Y()));
    switch (stage) {
    case Stage::trainer : return PlotHistogram(signal, background, bounds);
    case Stage::reader : return PlotProfile(signal, background, bounds);
    }
}

void Plotting::PlotHistogram(Plot const& signal, Plot const& background, Rectangle<float> const& bounds) const
{
    INFO(signal.Data().size(), background.Data().size());
    Histogram2Dim histogram(Tagger().ExportFolderName(), signal.XAxis().Name() + "-" + signal.YAxis().Name());
    int bin_number = 20;
    histogram.AddHistogram("Background", bin_number, bounds, background, kBlue);
    histogram.AddHistogram("Signal", bin_number, bounds, signal, kRed);
    histogram.SetLegend(Orientation::top | Orientation::outside);
    histogram.SetXAxis(signal.XAxis().LatexName());
    histogram.SetYAxis(signal.YAxis().LatexName());
}

void Plotting::PlotProfile(Plot const& signal, Plot const& background, Rectangle<float> const& bounds) const
{
    Info0;
    Profile profile(Tagger().ExportFolderName(), signal.Title().Name(), signal.XAxis().Name() + "-" + signal.YAxis().Name());
    profile.SetDimensions(Tagger().LatexName(), 30, bounds);
    profile.SetProfile(signal, background);
    profile.SetXAxis(signal.XAxis().LatexName());
    profile.SetYAxis(signal.YAxis().LatexName());
    profile.SetZAxis("BDT_{" + signal.Title().LatexName() + "}", 30);
}

std::vector<Plots> Plotting::Import(Stage stage, Tag tag) const
{
    INFO(Tagger().FileName(stage, tag), Tagger().TreeNames(tag).size());
    TFile file(Tagger().FileName(stage, tag).c_str(), "Read");
    std::vector<Plots> results;
    for (auto const & tree_name : Tagger().TreeNames(tag)) results.emplace_back(PlotResult(file, tree_name, stage));
    return results;
}

Plots Plotting::PlotResult(TFile& file, std::string const& tree_name, Stage stage) const
{
    INFO(tree_name);
    Plots plots(InfoBranch(file, tree_name));
    TTree& tree = static_cast<TTree&>(*file.Get(tree_name.c_str()));
    tree.SetMakeClass(1);
    plots.plots() = unordered_pairs(tagger_.Branch().Variables().Vector(), [&](Observable const & variable_1, Observable const & variable_2) {
        Plot plot = ReadTree(tree, variable_1.Name(), variable_2.Name(), stage);
        plot.x_is_int = variable_1.IsInt();
        plot.y_is_int = variable_2.IsInt();
        return plot;
    });
    plots.SetName(tree_name);
    Debug(plots.plots().size(), tagger_.Branch().Variables().Vector().size());
    return plots;
}

Plot Plotting::ReadTree(TTree& tree, std::string const& leaf_1_name, std::string const& leaf_2_name, Stage stage) const
{
    Info0;
    tree.SetBranchStatus("*", false);
    std::string branch_name = Tagger().BranchName(stage);
    Debug(branch_name);

    int branch_value = 0;
    SetBranch(tree, branch_value, branch_name);

    int branch_size = 0;
    SetBranch(tree, branch_size, branch_name + "_size");

    //FIXME remove this magic number
    size_t max_value = 200;
    std::vector<float> leaf_values_1(max_value);
    SetBranch(tree, leaf_values_1, branch_name + "." + leaf_1_name);

    std::vector<float> leaf_values_2(max_value);
    SetBranch(tree, leaf_values_2, branch_name + "." + leaf_2_name);

    std::vector<float> bdt_values(max_value);
    SetBranch(tree, bdt_values, branch_name + ".Bdt");

    Plot plot;
    for (auto const & entry : Range(tree.GetEntries())) {
        Detail(tree.GetEntries(), entry);
        tree.GetEntry(entry);
        Detail(branch_size, leaf_values_1.size(), leaf_values_2.size());
        for (auto const & element : Range(branch_size)) plot.Add(Vector3<float>(leaf_values_1.at(element), leaf_values_2.at(element), bdt_values.at(element)));
    }
    return plot;
}

void Plotting::SetBranch(TTree& tree, std::vector< float >& values, std::string const& name) const
{
    tree.SetBranchStatus(name.c_str(), true);
    tree.SetBranchAddress(name.c_str(), &values.front());
}

void Plotting::SetBranch(TTree& tree, int& value, std::string const& name) const
{
    tree.SetBranchStatus(name.c_str(), true);
    tree.SetBranchAddress(name.c_str(), &value);
}

Tagger const& Plotting::Tagger() const
{
    return tagger_;
}

}
