/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include <boost/range/numeric.hpp>
#include <boost/range/join.hpp>

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
#include "Vector.hh"

// #define INFORMATION
#include "Debug.hh"

namespace boca
{

Plotting::Plotting(boca::Tagger& tagger) :
    tagger_(tagger)
{
    INFO0;
}

void Plotting::TaggingEfficiency() const
{
    INFO0;
    Results results = ReadBdtFiles();
    results.Efficiencies();
    LatexFile latex_file(Tagger().ExportFolderName());
    latex_file.IncludeGraphic(PlotHistograms(results), "BDT Distribution");
    latex_file.IncludeGraphic(PlotAcceptanceGraph(results), "Acceptance");
    latex_file.IncludeGraphic(PlotEfficiencyGraph(results), "Efficiency");
    latex_file.Table("rllllllllll", CutEfficiencyTable(results), "Tagging rates and fake rates");
}

namespace
{

std::string Significance(int min = 0)
{
    return " $\\frac{S}{\\sqrt{S + B}}" + (min > 0 ? "\\geq" + std::to_string(min) + "$ " : "$ ");
}

std::string Ratio(int min = 0)
{
    return " $\\frac{S}{B}" + (min > 0 ? "\\geq \\unit[" + std::to_string(min) + "]{\\%}$ " : "$ ");

}

}

void Plotting::OptimalCuts() const
{
    INFO0;
    Results results = ReadBdtFiles();
    results.CalculateSignificances();
    LatexFile latex_file(Tagger().ExportFolderName());
    latex_file.Mass(results.Signals().front().InfoBranch().Mass());
    if (Tagger().Mva() == TMVA::Types::EMVA::kBDT) latex_file.IncludeGraphic(PlotHistograms(results), "BDT Distribution");
    latex_file.IncludeGraphic(PlotEfficiencyGraph(results), "Efficiency");
    latex_file.IncludeGraphic(PlotCrosssectionsGraph(results), "Crosssection in fb");
    latex_file.IncludeGraphic(PlotModelDependentGraph(results), "Maximization of" + Significance());
    latex_file.IncludeGraphic(PlotSBGraph(results), "Maximization of" + Ratio());
    latex_file.IncludeGraphic(PlotCrosssectionGraph(results), "Maximization of $\\frac{S}{\\sqrt B}$");
    latex_file.IncludeGraphic(PlotModelIndependentGraph(results), "Minimization of model independent crosssection for" + Significance(2) + "and" + Ratio(1));
    latex_file.IncludeGraphic(PlotModelIndependentGraphSig(results), "Minimization of the model independent crosssection for" + Significance(2));
    latex_file.IncludeGraphic(PlotModelIndependentGraphSB(results), "Minimization of model independent cross section for" + Ratio(1));
    latex_file.IncludeGraphic(PlotSBvsSsqrtBGraph(results), Ratio() + "versus" + Significance());
    latex_file.Table("rlllll", EfficienciesTable(results, results.BestModelDependentBin()), "Model dependent efficiencies calculated by maximizing the Significance");
    latex_file.Table("rlllll", EfficienciesTableMI(results, results.BestModelInDependentBin(), [](Result const & result) {
        return result.ModelIndependent();
    }), "Model independent efficiencies calculated bu minimizing the exclusion cross section for" + Significance(2) + "and" + Ratio(1));
    latex_file.Table("rlllll", EfficienciesTableMI(results, results.BestAcceptanceBin(), [](Result const & result) {
        return result.ModelIndependentSig();
    }), "Model independent efficiencies calculated bu minimizing the exclusion cross section for" + Significance(2));
    latex_file.Table("rlllll", EfficienciesTableMI(results, results.BestSOverBBin(), [](Result const & result) {
        return result.ModelIndependentSB();
    }), "Model independent efficiencies calculated bu minimizing the exclusion cross section for" + Ratio(1));
    latex_file.Table("rllllll", BestValueTable(results), "Results for the optimal model-(in)dependent cuts");
    latex_file.Table("rllllll", BestValueTableDoubleCheck(results), "Model independent cross section for the model dependent cut");
}

Results Plotting::ReadBdtFiles() const
{
    INFO0;
    TFile file(Tagger().ExportFileName().c_str(), "Recreate");
    return Results(ReadBdtFile(file, Tag::signal), ReadBdtFile(file, Tag::background));
}

std::vector<Result> Plotting::ReadBdtFile(TFile& export_file, Tag tag) const
{
    INFO0;
    std::string file_name = Tagger().FileName(Stage::reader, tag);
    DEBUG(file_name);
    if (!Exists(file_name)) ERROR("non existent", file_name);
    TFile file(file_name.c_str(), "Read");
    std::vector<Result> results;
    switch (Tagger().Mva()) {
    case TMVA::Types::EMVA::kBDT : for (auto const & tree_name : Tagger().TreeNames(tag)) results.emplace_back(BdtDistribution(file, tree_name, export_file));
        return results;
    case TMVA::Types::EMVA::kCuts: for (auto const & tree_name : Tagger().TreeNames(tag)) results.emplace_back(CutDistribution(file, tree_name, export_file));
        return results;
        DEFAULT(Tagger().Mva(), results);
    }
}

Result Plotting::BdtDistribution(TFile& file, std::string const& tree_name, TFile& export_file) const
{
    INFO0;
    std::string branch_name = Tagger().BranchName(Stage::reader);
    DEBUG(branch_name);
    exroot::TreeReader tree_reader(static_cast<TTree*>(file.Get(tree_name.c_str())));
    TClonesArray& clones_array = *tree_reader.UseBranch(branch_name.c_str());
    exroot::TreeWriter tree_writer(&export_file, tree_name.c_str());
    exroot::TreeBranch& branch = *tree_writer.NewBranch(branch_name.c_str(), BdtBranch::Class());
    std::vector<float> bdts;
    for (auto const & event_number : IntegerRange(tree_reader.GetEntries())) {
        tree_reader.ReadEntry(event_number);
        for (auto const & entry : IntegerRange(clones_array.GetEntriesFast())) {
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
    for (auto const & event_number : IntegerRange(tree_reader.GetEntries())) {
        tree_reader.ReadEntry(event_number);
        for (auto const & entry : IntegerRange(clones_array.GetEntriesFast())) {
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
    INFO(file.GetName() , tree_name);
    auto* tree = static_cast<TTree*>(file.Get(tree_name.c_str()));
    INFO(tree->GetName());
    exroot::TreeReader tree_reader(tree);
    INFO(Tagger().WeightBranchName());
    TClonesArray* clones_array = tree_reader.UseBranch(Tagger().WeightBranchName().c_str());
    if (!clones_array) ERROR("empty clones array");
    INFO(tree_reader.GetEntries());
    tree_reader.ReadEntry(tree_reader.GetEntries() - 1);
    TObject* object = clones_array->Last();
    if (!object) {
        ERROR("no object for casting");
        return boca::InfoBranch();
    }
    return static_cast<boca::InfoBranch&>(*object);
}

std::string Plotting::PlotHistograms(Results const& results) const
{
    INFO0;
    Histograms histograms(Tagger().ExportFolderName(), "Bdt");
    for (auto const & result : results.Signals()) histograms.AddHistogram(result.Bdts(), result.InfoBranch().LatexName(), results.Range());
    for (auto const & result : results.Backgrounds()) histograms.AddHistogram(result.Bdts(), result.InfoBranch().LatexName(), results.Range());
    histograms.SetLegend(Orientation::top);
    histograms.SetXAxis("BDT");
    histograms.SetYAxis(Formula("N"));
    histograms.AddLine(results.BestModelInDependentValue());
    histograms.AddLine(results.BestModelDependentValue());
    return histograms.FileBaseName();
}

std::string Plotting::PlotEfficiencyGraph(Results const& results) const
{
    INFO0;
    Graphs graphs(Tagger().ExportFolderName(), "Efficiency");
    for (auto const & result : results.Signals()) graphs.AddGraph(results.XValues(), result.Efficiencies(), result.InfoBranch().LatexName());
    for (auto const & result : results.Backgrounds()) graphs.AddGraph(results.XValues(), result.Efficiencies(), result.InfoBranch().LatexName());
    graphs.SetLegend(Orientation::bottom | Orientation::left);
    switch (Tagger().Mva()) {
    case TMVA::Types::EMVA::kBDT :
        graphs.SetXAxis("BDT", results.Range().Horizontal());
        graphs.SetYAxis("Efficiency");
        break;
    case TMVA::Types::EMVA::kCuts :
        graphs.SetXAxis("Calculated", results.Range().Horizontal());
        graphs.SetYAxis("Measured");
        break;
        DEFAULT(Tagger().Mva());
    }
    graphs.AddLine(results.BestModelDependentValue());
    graphs.AddLine(results.BestModelInDependentValue());
    return graphs.FileBaseName();
}

std::vector<std::string> Plotting::PlotAcceptanceGraph(Results const& results) const
{
    INFO0;
    std::vector<std::string> names;
    for (auto const & signal : results.Signals()) {
        Graphs graphs(Tagger().ExportFolderName(), "Acceptance" + std::to_string(Position(results.Signals(), signal)));
        for (auto const & background : results.Backgrounds()) graphs.AddGraph(signal.PureEfficiencies(), background.PureEfficiencies(), background.InfoBranch().LatexName());
        graphs.SetLegend(Orientation::right | Orientation::bottom, signal.InfoBranch().LatexName());
        graphs.SetXAxis("Signal acceptance", {0.2, 0.9});
        graphs.SetYAxis("Background acceptance");
        names.emplace_back(graphs.FileBaseName());
    }
    return names;
}

void Plotting::SetDefaultXAxis(Graphs& graphs, Results const& results) const
{
    switch (Tagger().Mva()) {
    case TMVA::Types::EMVA::kBDT :
        graphs.SetXAxis("BDT", results.Range().Horizontal());
        break;
    case TMVA::Types::EMVA::kCuts :
        graphs.SetXAxis("MVA", results.Range().Horizontal());
        break;
        DEFAULT(Tagger().Mva());
    }
}

std::string Plotting::PlotCrosssectionsGraph(Results const& results) const
{
    INFO0;
    Graphs graphs(Tagger().ExportFolderName(), "Crosssection");
    for (auto const & result : results.Signals()) graphs.AddGraph(results.XValues(), FloatVector(result.Crosssections()), result.InfoBranch().LatexName());
    for (auto const & result : results.Backgrounds()) graphs.AddGraph(results.XValues(), FloatVector(result.Crosssections()), result.InfoBranch().LatexName());
    graphs.AddLine(results.BestModelDependentValue());
    graphs.AddLine(results.BestModelInDependentValue());
    graphs.SetLegend(Orientation::bottom | Orientation::left);
    SetDefaultXAxis(graphs, results);
    graphs.SetYAxis("Crosssection [fb]");
    return graphs.FileBaseName();
}

std::string Plotting::PlotModelDependentGraph(Results const& results) const
{
    INFO0;
    Graphs graphs(Tagger().ExportFolderName(), "Significance");
    graphs.AddGraph(results.XValues(), results.Significances());
    graphs.AddLine(results.BestModelDependentValue(), "Significance");
    SetDefaultXAxis(graphs, results);
    graphs.SetYAxis("Significance");
    return graphs.FileBaseName();
}

std::string Plotting::PlotCrosssectionGraph(Results const& results) const
{
    INFO0;
    Graphs graphs(Tagger().ExportFolderName(), "SsqrtB");
    graphs.AddGraph(results.XValues(), results.Acceptances());
    graphs.AddLine(results.BestAcceptanceValue());
    SetDefaultXAxis(graphs, results);
    graphs.SetYAxis(Formula("S/#sqrt{B}"));
    return graphs.FileBaseName();
}

std::string Plotting::PlotSBGraph(Results const& results) const
{
    INFO0;
    Graphs graphs(Tagger().ExportFolderName(), "SB");
    graphs.AddGraph(results.XValues(), results.SOverB());
    graphs.AddLine(results.BestSOverBValue());
    SetDefaultXAxis(graphs, results);
    graphs.SetYAxis(Formula("S/B"));
    return graphs.FileBaseName();
}

std::string Plotting::PlotSBvsSsqrtBGraph(Results const& results) const
{
    INFO0;
    Graphs graphs(Tagger().ExportFolderName(), "SBvsSsqrtB");
    graphs.AddGraph(results.SOverB(), results.Significances());
    graphs.SetXAxis(Formula("S/B"));
    graphs.SetYAxis(Formula("S/#sqrt{S+B}"));
    return graphs.FileBaseName();
}

std::string Plotting::PlotModelIndependentGraph(Results const& results) const
{
    INFO0;
    Graphs graphs(Tagger().ExportFolderName(), "Exclusion");
    for (auto const & signal : results.Signals()) graphs.AddGraph(results.XValues(), FloatVector(signal.ModelIndependent()), signal.InfoBranch().LatexName());
    graphs.AddLine(results.BestModelInDependentValue(), "Crosssection");
    graphs.AddLine(results.BestAcceptanceValue(), "Crosssection (" + Formula("S/#sqrt{S+B}") + ")");
    graphs.AddLine(results.BestSOverBValue(), "Crosssection (" + Formula("S/B") + ")");
    graphs.SetLegend(Orientation::top | Orientation::right, "Minimization");
    graphs.SetYAxis("Exclusion crosssection [fb]");
    SetDefaultXAxis(graphs, results);
    return graphs.FileBaseName();
}

std::string Plotting::PlotModelIndependentGraphSB(Results const& results) const
{
    INFO0;
    Graphs graphs(Tagger().ExportFolderName(), "ExclusionSB");
    for (auto const & signal : results.Signals()) graphs.AddGraph(results.XValues(), FloatVector(signal.ModelIndependentSB()), signal.InfoBranch().LatexName());
    graphs.AddLine(results.BestModelInDependentValue(), "Crosssection");
    graphs.AddLine(results.BestAcceptanceValue(), "Crosssection (" + Formula("S/#sqrt{S+B}") + ")");
    graphs.AddLine(results.BestSOverBValue(), "Crosssection (" + Formula("S/B") + ")");
    graphs.SetLegend(Orientation::top | Orientation::right, "Minimization");
    graphs.SetYAxis("Exclusion crosssection [fb]");
    SetDefaultXAxis(graphs, results);
    return graphs.FileBaseName();
}

std::string Plotting::PlotModelIndependentGraphSig(Results const& results) const
{
    INFO0;
    Graphs graphs(Tagger().ExportFolderName(), "ExclusionSig");
    for (auto const & signal : results.Signals()) graphs.AddGraph(results.XValues(), FloatVector(signal.ModelIndependentSig()), signal.InfoBranch().LatexName());
    graphs.AddLine(results.BestModelInDependentValue(), "Crosssection");
    graphs.AddLine(results.BestAcceptanceValue(), "Crosssection (" + Formula("S/#sqrt{S+B}") + ")");
    graphs.AddLine(results.BestSOverBValue(), "Crosssection (" + Formula("S/B") + ")");
    graphs.SetLegend(Orientation::top | Orientation::right, "Minimization");
    graphs.SetYAxis("Exclusion crosssection [fb]");
    SetDefaultXAxis(graphs, results);
    return graphs.FileBaseName();
}

std::string Plotting::BestValueTable(Results const& results) const
{
    INFO0;
    std::stringstream table;
    table << "    Model\n  & Cut\n  & $p$-value\n";
    for (auto const & signal : results.Signals()) table << " & $\\sigma$(" << signal.InfoBranch().Name() << ") [fb]";
    table << "\n \\\\ \\midrule\n   ";
    table << BestValueRow(results, results.BestModelDependentBin(), "Significance", [](Result const & result) {
        return result.ModelIndependentSig();
    });
    table << BestValueRow(results, results.BestModelInDependentBin(), "Crosssection (" + Significance() + "+" + Ratio() + ")", [](Result const & result) {
        return result.ModelIndependent();
    });
    table << BestValueRow(results, results.BestAcceptanceBin(), "Crosssection (" + Significance() + ")", [](Result const & result) {
        return result.ModelIndependentSig();
    });
    table << BestValueRow(results, results.BestSOverBBin(), "Crosssection (" + Ratio() + ")", [](Result const & result) {
        return result.ModelIndependentSB();
    });
    return table.str();
}

std::string Plotting::BestValueTableDoubleCheck(Results const& results) const
{
    INFO0;
    std::stringstream table;
    table << "    Model\n  & Cut\n  & $p$-value\n";
    for (auto const & signal : results.Signals()) table << " & $\\sigma$(" << signal.InfoBranch().Name() << ") [fb]";
    table << "\n \\\\ \\midrule\n   ";
    table << BestValueRow(results, results.BestModelDependentBin(), "Significance", [](Result const & result) {
        return result.ModelIndependentSig();
    });
    table << BestValueRow(results, results.BestModelDependentBin(), "Crosssection (" + Significance() + "+" + Ratio() + ")", [](Result const & result) {
        return result.ModelIndependent();
    });
    table << BestValueRow(results, results.BestModelDependentBin(), "Crosssection (" + Significance() + ")", [](Result const & result) {
        return result.ModelIndependentSig();
    });
    table << BestValueRow(results, results.BestModelDependentBin(), "Crosssection (" + Ratio() + ")", [](Result const & result) {
        return result.ModelIndependentSB();
    });
    return table.str();
}

std::string Plotting::BestValueRow(Results const& results, int bin, std::string const& name, std::function<std::vector<Crosssection>(Result const&)> const& function) const
{
    INFO0;
    std::stringstream row;
    row << " " << name;
    row << "\n  & " << RoundToDigits(results.XValue(bin));
    row << "\n  & " << RoundToDigits(results.Significances().at(bin));
    for (auto const & signal : results.Signals()) row << "\n  & " << RoundToDigits(function(signal).at(bin) / fb);
    row << "\n \\\\";
    return row.str();
}

std::string Plotting::EfficienciesTable(Results const& results, int bin) const
{
    INFO0;
    std::stringstream table;
    table << "    Sample\n  & before\n  & after\n  & Efficiency\n  & $\\sigma$  [fb]\n  & $N_{\\mathcal L = \\unit[" << RoundToDigits(DetectorGeometry::Luminosity() * fb) << "]{fb^{-1}}}$";
    table << "\n \\\\ \\midrule\n   ";
    for (auto const & result : results.Signals()) table << EfficienciesRow(result, Position(results.Signals(), result), Tag::signal, bin);
    for (auto const & result : results.Backgrounds()) table << EfficienciesRow(result, Position(results.Backgrounds(), result), Tag::background, bin);
    return table.str();
}

std::string Plotting::EfficienciesRow(Result const& result, int index, Tag tag, int bin) const
{
    INFO0;
    std::stringstream row;
//     row << " \\verb|" << Tagger().TreeNames(tag).at(index) << "|";
    row << " \\verb|" << result.InfoBranch().LatexName() << "|";
    row << "\n  & " << result.InfoBranch().EventNumber();
    row << "\n  & " << result.EventSums().at(bin);
    row << "\n  & " << RoundToDigits(result.Efficiencies().at(bin));
    row << "\n  & " << RoundToDigits(result.InfoBranch().Crosssection() / fb * Results::ScalingFactor());
    row << "\n  & " << RoundToDigits(result.InfoBranch().Crosssection() * DetectorGeometry::Luminosity() * result.Efficiencies().at(bin) * Results::ScalingFactor());
    row << "\n \\\\";
    return row.str();
}

std::string Plotting::EfficienciesTableMI(Results const& results, int bin, std::function<std::vector<Crosssection>(Result const&)> const& function) const
{
    INFO0;
    std::stringstream table;
    table << "    Sample\n  & before\n  & after\n  & Efficiency\n  & $\\sigma$  [fb]\n";
    table << "\n \\\\ \\midrule\n   ";
    for (auto const & result : results.Signals()) table << EfficienciesRowMI(result, Position(results.Signals(), result), Tag::signal, bin, function);
    for (auto const & result : results.Backgrounds()) table << EfficienciesRowMI(result, Position(results.Backgrounds(), result), Tag::background, bin);
    return table.str();
}

std::string Plotting::EfficienciesRowMI(Result const& result, int index, Tag tag, int bin, std::function<std::vector<Crosssection>(Result const&)> const& function) const
{
    INFO0;
    std::stringstream row;
    row << " \\verb|" << result.InfoBranch().LatexName() << "|";
    row << "\n  & " << result.InfoBranch().EventNumber();
    row << "\n  & " << result.EventSums().at(bin);
    row << "\n  & " << RoundToDigits(result.Efficiencies().at(bin));
    row << "\n  & " << RoundToDigits(function(result).at(bin) / fb);
    row << "\n \\\\";
    return row.str();
}

std::string Plotting::EfficienciesRowMI(Result const& result, int index, Tag tag, int bin) const
{
    INFO0;
    return EfficienciesRowMI(result, index, tag, bin, [](Result const & result) {
        return std::vector<Crosssection>(result.Steps(), result.InfoBranch().Crosssection() * Results::ScalingFactor());
    });
}

std::string Plotting::CutEfficiencyTable(Results const& results) const
{
    INFO0;
    std::stringstream table;
    table << "  & \\multicolumn{9}{c}{Pure Efficiencies [\\%]}\n \\\\\n    BDT value";
    for (auto const & eff : results.SelectedEfficiencies()) table << "\n  & " << RoundToDigits(eff);
    table << "\n \\\\ \\midrule\n   ";
    for (auto const & result : results.Signals()) table << CutEfficiencyRow(result, Position(results.Signals(), result), Tag::signal);
    for (auto const & result : results.Backgrounds()) table << CutEfficiencyRow(result, Position(results.Backgrounds(), result), Tag::background);
    return table.str();
}

std::string Plotting::CutEfficiencyRow(Result const& result, int index, Tag tag) const
{
    INFO0;
    std::stringstream row;
    //   row << " \\verb|" << Tagger().TreeNames(tag).at(index) << "|";
    row << " \\verb|" << result.InfoBranch().LatexName() << "|";
    for (auto const & eff : result.SelectedEfficiencies()) row << "\n  & " << RoundToDigits(eff * 100);
    row << "\n \\\\";
    return row.str();
}

void Plotting::RunPlots(Stage stage) const
{
    INFO0;
    DEBUG(Tagger().FileName(stage, Tag::signal), Tagger().TreeNames(Tag::signal).size());
    std::vector<Plots> signals = Import(stage, Tag::signal);
    DEBUG(Tagger().FileName(stage, Tag::background), Tagger().TreeNames(Tag::background).size());
    std::vector<Plots> backgrounds = Import(stage, Tag::background);
    Plots background = backgrounds.front();
    background = std::accumulate(backgrounds.begin() + 1, backgrounds.end(), background, [](Plots & sum, Plots const & plots) {
        for (auto & plot : sum.PlotVector()) plot.Join(plots.PlotVector().at(Position(sum.PlotVector(), plot)).Data());
        return sum;
    });
    background.Names().SetName("background");
    for (auto & signal : signals) DoPlot(signal, background, stage);
}

void Plotting::DoPlot(Plots& signals, Plots& backgrounds, Stage stage) const
{
    INFO0;
    NamePairs names = UnorderedPairs(tagger_.Branch().Variables().Vector(), [&](Observable const & variable_1, Observable const & variable_2) {
        return std::make_pair(variable_1.Names(), variable_2.Names());
    });
    signals.SetNames(names);
    backgrounds.SetNames(names);
    for (auto & signal : signals.PlotVector()) PlotDetails(signal, backgrounds.PlotVector().at(Position(signals.PlotVector(), signal)), stage);
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
    Rectangle<float> range;
    range.SetXMin(std::min(signal_x.front().X(), background_x.front().X()));
    range.SetXMax(std::max(signal_x.back().X(), background_x.back().X()));
    range.SetYMin(std::min(signal_y.front().Y(), background_y.front().Y()));
    range.SetYMax(std::max(signal_y.back().Y(), background_y.back().Y()));
    switch (stage) {
    case Stage::trainer : return PlotHistogram(signal, background, range);
    case Stage::reader : return PlotProfile(signal, background, range);
    }
}

void Plotting::PlotHistogram(Plot const& signal, Plot const& background, Rectangle<float> const& range) const
{
    INFO(signal.Data().size(), background.Data().size());
    Histogram2Dim histogram(Tagger().ExportFolderName(), signal.XAxis().Name() + "-" + signal.YAxis().Name());
    int bin_number = 20;
    histogram.AddHistogram("Background", bin_number, range, background, kBlue);
    histogram.AddHistogram("Signal", bin_number, range, signal, kRed);
    histogram.SetLegend(Orientation::top | Orientation::outside);
    histogram.SetXAxis(signal.XAxis().LatexName());
    histogram.SetYAxis(signal.YAxis().LatexName());
}

void Plotting::PlotProfile(Plot const& signal, Plot const& background, Rectangle<float> const& range) const
{
    INFO0;
    Profile profile(Tagger().ExportFolderName(), signal.Title().Name(), signal.XAxis().Name() + "-" + signal.YAxis().Name());
    profile.SetDimensions(Tagger().LatexName(), 30, range);
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
    tree.SetMakeClass(true);
    plots.PlotVector() = UnorderedPairs(tagger_.Branch().Variables().Vector(), [&](Observable const & variable_1, Observable const & variable_2) {
        Plot plot = ReadTree(tree, variable_1.Name(), variable_2.Name(), stage);
        plot.x_is_int = variable_1.IsInt();
        plot.y_is_int = variable_2.IsInt();
        return plot;
    });
    plots.Names().SetName(tree_name);
    DEBUG(plots.PlotVector().size(), tagger_.Branch().Variables().Vector().size());
    return plots;
}

namespace
{

void SetBranch(TTree& tree, std::vector< float >& values, std::string const& name)
{
    tree.SetBranchStatus(name.c_str(), true);
    tree.SetBranchAddress(name.c_str(), &values.front());
}

void SetBranch(TTree& tree, int& value, std::string const& name)
{
    tree.SetBranchStatus(name.c_str(), true);
    tree.SetBranchAddress(name.c_str(), &value);
}

}

Plot Plotting::ReadTree(TTree& tree, std::string const& leaf_1_name, std::string const& leaf_2_name, Stage stage) const
{
    INFO0;
    tree.SetBranchStatus("*", false);
    std::string branch_name = Tagger().BranchName(stage);
    DEBUG(branch_name);

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
    for (auto const & entry : IntegerRange(tree.GetEntries())) {
        DETAIL(tree.GetEntries(), entry);
        tree.GetEntry(entry);
        DETAIL(branch_size, leaf_values_1.size(), leaf_values_2.size());
        for (auto const & element : IntegerRange(branch_size)) plot.Add(Vector3<float>(leaf_values_1.at(element), leaf_values_2.at(element), bdt_values.at(element)));
    }
    return plot;
}


















std::vector<Plots> Plotting::Import2() const
{
    std::vector<Plots> results;
    for (auto const & variable : tagger_.Branch().Variables().Vector()) results.emplace_back(PlotResult3(variable));
    return results;
}

Plots Plotting::PlotResult3(Observable const& variable) const
{
    ERROR0;
    Plots plots;
    plots.Names() = variable.Names();
    for (auto const & tag : std::vector<Tag>( {Tag::signal, Tag::background})) PlotResult2(variable, tag, plots);
    return plots;
}


Plots Plotting::PlotResult2(Observable const& variable, Tag tag, Plots& plots) const
{
    ERROR(Name(tag));
    TFile file(Tagger().FileName(Stage::trainer, tag).c_str(), "Read");
    std::vector<boca::InfoBranch> branches;
    std::vector<std::string>  names = Tagger().TreeNames(tag);
    for (auto const & tree_name : names) {
        if (branches.size() < names.size()) branches.emplace_back(InfoBranch(file, tree_name));
        TTree& tree = static_cast<TTree&>(*file.Get(tree_name.c_str()));
        tree.SetMakeClass(true);
        Plot plot = ReadTree2(tree, variable.Name());
        plot.x_is_int = variable.IsInt();
        plot.Title() = branches.at(Position(names, tree_name)).Names();
        plots.PlotVector().emplace_back(plot);
    }
    return plots;
}

Plot Plotting::ReadTree2(TTree& tree, std::string const& leaf_name) const
{
    INFO0;
    tree.SetBranchStatus("*", false);
    std::string branch_name = Tagger().BranchName(Stage::trainer);
    DEBUG(branch_name);

    int branch_value = 0;
    SetBranch(tree, branch_value, branch_name);

    int branch_size = 0;
    SetBranch(tree, branch_size, branch_name + "_size");

    //FIXME remove this magic number
    size_t max_value = 200;
    std::vector<float> leaf_values(max_value);
    SetBranch(tree, leaf_values, branch_name + "." + leaf_name);


    Plot plot;
    for (auto const & entry : IntegerRange(tree.GetEntries())) {
        DETAIL(tree.GetEntries(), entry);
        tree.GetEntry(entry);
        for (auto const & element : IntegerRange(branch_size)) plot.Add(Vector3<float>(leaf_values.at(element), 0, 0));
    }
    return plot;
}


void Plotting::RunPlotHist() const
{
    INFO0;
    for (auto const & plots : Import2()) PlotVariables(plots);
}

void Plotting::PlotVariables(Plots const& plots) const
{

    Histograms histograms(Tagger().ExportFolderName(), plots.Names().Name());
    for (auto const & plot : plots.PlotVector()) histograms.AddHistogram(plot.XData(), plot.Title().LatexName(), plots.XRange(), plot.x_is_int);
    histograms.SetLog();
    histograms.SetLegend(Orientation::outside | Orientation::right);
    histograms.SetYAxis(Formula("N"));
    histograms.SetXAxis(plots.Names().LatexName());
}

Tagger const& Plotting::Tagger() const
{
    return tagger_;
}

}


