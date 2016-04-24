/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include <boost/range/numeric.hpp>
#include <boost/range/join.hpp>

#include "TFile.h"
#include "TTree.h"

#include "generic/Vector.hh"
#include "generic/Types.hh"

#include "io/TreeWriter.hh"
#include "io/TreeReader.hh"

#include "plotting/PlottingBase.hh"
#include "plotting/LatexFile.hh"
#include "plotting/Graphs.hh"
#include "plotting/Results.hh"
#include "plotting/Histograms.hh"
#include "plotting/Histogram2Dim.hh"
#include "plotting/Profile.hh"
#include "plotting/Plots.hh"
#include "plotting/Font.hh"

// #define INFORMATION
#include "generic/DEBUG.hh"

namespace boca
{

namespace
{

auto SignificanceString(int min = 0)
{
    return "$\\frac{S}{\\sqrt{S + B}}" + (min > 0 ? "\\geq" + std::to_string(min) + "$" : "$");
}

auto Ratio(int min = 0)
{
    return "$\\frac{S}{B}" + (min > 0 ? "\\geq \\unit[" + std::to_string(min * 100) + "]{\\%}$" : "$");

}

}

void PlottingBase::TaggingEfficiency() const
{
    INFO0;
    auto results = ReadBdtFiles(Stage::reader);
    results.CutEfficiencies();
    LatexFile latex_file(Tagger().ExportFolderName());
    latex_file.IncludeGraphic(PlotHistograms(results), "BDT Distribution");
    latex_file.IncludeGraphic(PlotAcceptanceGraph(results), "Acceptance");
    latex_file.IncludeGraphic(PlotEfficiencyGraph(results), "Efficiency");
    latex_file.Table("rllllllllll", CutEfficiencyTable(results), "Tagging rates and fake rates");
    latex_file.Table("rll", TruthLevelCutTable(results), "Truth level cut efficiency");
}

void PlottingBase::OptimalCuts() const
{
    INFO0;
    auto results = ReadBdtFiles(Stage::reader);
    results.CalculateSignificances();
    LatexFile latex_file(Tagger().ExportFolderName());
    latex_file.Mass(results.Signals().front().InfoBranch().Mass());
    if (Tagger().Mva() == TMVA::Types::EMVA::kBDT) latex_file.IncludeGraphic(PlotHistograms(results), "BDT Distribution");
    latex_file.IncludeGraphic(PlotEfficiencyGraph(results), "Efficiency");
    latex_file.IncludeGraphic(PlotCrosssectionsGraph(results), "Crosssection in fb");
    latex_file.IncludeGraphic(PlotMDGraph(results), "Maximization of significance");
    latex_file.IncludeGraphic(PlotMDExperimentalGraph(results), "Maximization of " + Ratio());
    latex_file.IncludeGraphic(PlotMISignificanceGraph(results), "Minimization of the model independent crosssection for significance $\\geq " + std::to_string(int(DetectorGeometry::Exclusion())) + "$");
    latex_file.IncludeGraphic(PlotMIExperimentalGraph(results), "Minimization of model independent cross section for " + Ratio(DetectorGeometry::Experimental()));
    latex_file.IncludeGraphic(PlotMIGraph(results), "Minimization of model independent crosssection for significance $\\geq " + std::to_string(int(DetectorGeometry::Exclusion())) + "$ and " + Ratio(DetectorGeometry::Experimental()));
    latex_file.IncludeGraphic(PlotExperimentalVsSignificance(results), Ratio() + "versus significance");
    for (const auto signal : results.Signals()) {
        latex_file.Table("rlllll", EfficienciesTable(results, signal.BestMDBin(Significance::sum)), "Model dependent efficiencies calculated by maximizing the Significance");
        latex_file.Table("rlllll", EfficienciesTableMI(results, signal.BestMDBin(Significance::sum | Significance::experimental), [](Result const & result) {
            return result.MI(Significance::sum);
        }), "Model independent efficiencies calculated by minimizing the exclusion cross section for " + SignificanceString(DetectorGeometry::Exclusion()) + " and " + Ratio(DetectorGeometry::Experimental()));
        latex_file.Table("rlllll", EfficienciesTableMI(results, signal.BestMDBin(Significance::background), [](Result const & result) {
            return result.MI(Significance::sum);
        }), "Model independent efficiencies calculated by minimizing the exclusion cross section for " + SignificanceString(DetectorGeometry::Exclusion()));
        latex_file.Table("rlllll", EfficienciesTableMI(results, signal.BestMDBin(Significance::experimental), [](Result const & result) {
            return result.MI(Significance::experimental);
        }), "Model independent efficiencies calculated by minimizing the exclusion cross section for " + Ratio(DetectorGeometry::Experimental()));
        latex_file.Table("rllllll", BestValueTable(signal, results.XValues()), "Results for the optimal model-(in)dependent cuts");
    }
//     latex_file.Table("rccc", ScalingTable(results), "Significances as function of signal crosssection");
}

Results PlottingBase::ReadBdtFiles(Stage stage) const
{
    INFO0;
    TFile file(Tagger().ExportFileName().c_str(), "Recreate");
    return Results(ReadBdtFile(file, Phase(stage, Tag::signal)), ReadBdtFile(file, Phase(stage, Tag::background)));
}

std::vector<Result> PlottingBase::ReadBdtFile(TFile& export_file, Phase const& phase) const
{
    INFO0;
    return Transform(IntegerRange(Tagger().TreeNames(phase).size()), [&](int tree_number) {
        switch (Tagger().Mva()) {
        case TMVA::Types::EMVA::kBDT : return BdtDistribution(phase, tree_number, export_file);
        case TMVA::Types::EMVA::kCuts : return CutDistribution(phase, tree_number, export_file);
            DEFAULT(Tagger().MvaName(), Result());
        }
    });
}

Result PlottingBase::BdtDistribution(Phase const& phase, int tree_number, TFile& export_file) const
{
    INFO0;
    TreeReader tree_reader(Tagger().FileName(phase), Tagger().TreeNames(phase).at(tree_number), Source::tagger);
    auto branch_name = Tagger().BranchName(phase.Stage());
    auto& array = tree_reader.Array(branch_name, Tagger().Class());
    TreeWriter tree_writer(export_file, Tagger().TreeNames(phase).at(tree_number));
    auto& branch = tree_writer.NewBranch<BdtBranch>(branch_name);
    std::vector<double> bdts;
    while (tree_reader.Next()) {
        for (auto const & entry : array) {
            double bdt = static_cast<BdtBranch const&>(entry).Bdt;
            branch.AddEntry<BdtBranch>().Bdt = bdt;
            bdts.emplace_back(bdt);
        }
        tree_writer.Fill();
    }
    tree_writer.Write();
    return Result(InfoBranch(Phase(Stage::reader, phase.Tag()), tree_number).first, InfoBranch(Phase(Stage::trainer, phase.Tag()), tree_number), bdts, Tagger().Mva());
}

Result PlottingBase::CutDistribution(Phase const& phase, int tree_number, TFile& export_file) const
{
    INFO(tree_number);
    TreeReader tree_reader(Tagger().FileName(phase), Tagger().TreeNames(phase).at(tree_number), Source::tagger);
    auto branch_name = Tagger().BranchName(phase.Stage());
    auto& array = tree_reader.Array(branch_name, Tagger().Class());
    TreeWriter tree_writer(export_file, Tagger().TreeNames(phase).at(tree_number));
    auto& branch = tree_writer.NewBranch<CutBranch>(branch_name);
    std::vector<std::vector<bool>> passed_matrix;
    while (tree_reader.Next()) {
        for (auto const & entry : array) {
            auto passed_vector = static_cast<CutBranch const&>(entry).passed_;
            branch.AddEntry<CutBranch>().passed_ = passed_vector;
            passed_matrix.emplace_back(passed_vector);
        }
        tree_writer.Fill();
    }
    tree_writer.Write();
    return Result(InfoBranch(Phase(Stage::reader, phase.Tag()), tree_number).first, InfoBranch(Phase(Stage::trainer, phase.Tag()), tree_number), passed_matrix, Tagger().Mva());
}

std::pair<InfoBranch, int> PlottingBase::InfoBranch(Phase const& phase, int tree_number) const
{
    INFO(Name(phase.Tag()), tree_number);
    TreeReader tree_reader(Tagger().FileName(phase), Tagger().TreeNames(phase).at(tree_number), Source::tagger);
    INFO(Tagger().WeightBranchName());
    if (tree_reader.GetEntries() == 0) {
        ERROR("tree reader empty, no object for casting");
        return std::make_pair(boca::InfoBranch(), 0);
    }
    auto& array = tree_reader.Array<boca::InfoBranch>(Tagger().WeightBranchName());
    tree_reader.ReadEntry(tree_reader.GetEntries() - 1);
    if (array.GetSize() == 0) {
        ERROR("array empty, no object for casting");
        return std::make_pair(boca::InfoBranch(), 0);
    }
    return std::make_pair(array.At(array.GetSize() - 1), tree_reader.GetEntries());
}

std::string PlottingBase::PlotHistograms(Results const& results) const
{
    INFO0;
    Histograms histograms(Tagger().ExportFolderName(), "Bdt");
    for (auto const & signal : results.Signals()) {
        histograms.AddHistogram(signal.Bdts(), signal.InfoBranch().LatexName(), results.Range());
        histograms.AddLine(signal.BestMIValue(Significance::sum | Significance::experimental));
        histograms.AddLine(signal.BestMDValue(Significance::sum));
    }
    for (auto const & background : results.Backgrounds()) histograms.AddHistogram(background.Bdts(), background.InfoBranch().LatexName(), results.Range());
    histograms.SetLegend(Orientation::top);
    histograms.SetXAxis("BDT");
    histograms.SetYAxis(Formula("N"));
    return histograms.FileBaseName();
}

std::string PlottingBase::PlotEfficiencyGraph(Results const& results) const
{
    INFO0;
    Graphs graphs(Tagger().ExportFolderName(), "Efficiency");
    for (auto const & signal : results.Signals()) {
        graphs.AddGraph(results.XValues(), signal.PreCutEfficiencies(), signal.InfoBranch().LatexName());
        graphs.AddLine(signal.BestMDValue(Significance::sum));
        graphs.AddLine(signal.BestMIValue(Significance::sum | Significance::experimental));
    }
    for (auto const & background : results.Backgrounds()) graphs.AddGraph(results.XValues(), background.PreCutEfficiencies(), background.InfoBranch().LatexName());
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
    return graphs.FileBaseName();
}

std::vector<std::string> PlottingBase::PlotAcceptanceGraph(Results const& results) const
{
    INFO0;
    std::vector<std::string> names;
    for (auto const & signal : results.Signals()) {
        Graphs graphs(Tagger().ExportFolderName(), "Acceptance" + std::to_string(Position(results.Signals(), signal)));
        for (auto const & background : results.Backgrounds()) graphs.AddGraph(signal.PureEfficiencies(), background.PureEfficiencies(), background.InfoBranch().LatexName());
        graphs.SetLegend(Orientation::right | Orientation::bottom, signal.InfoBranch().LatexName());
        graphs.SetXAxis("Signal acceptance", {0.2, 0.9});
        graphs.SetYAxis("Background acceptance", {1e-3, 1});
        names.emplace_back(graphs.FileBaseName());
    }
    return names;
}

void PlottingBase::SetDefaultXAxis(Graphs& graphs, Results const& results) const
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

std::string PlottingBase::PlotCrosssectionsGraph(Results const& results) const
{
    INFO0;
    Graphs graphs(Tagger().ExportFolderName(), "Crosssection");
    for (auto const & signal : results.Signals()) {
        graphs.AddGraph(results.XValues(), FloatVector(signal.Crosssections()), signal.InfoBranch().LatexName());
        graphs.AddLine(signal.BestMDValue(Significance::sum));
        graphs.AddLine(signal.BestMIValue(Significance::sum | Significance::experimental));
    }
    for (auto const & background : results.Backgrounds()) graphs.AddGraph(results.XValues(), FloatVector(background.Crosssections()), background.InfoBranch().LatexName());
    graphs.SetLegend(Orientation::bottom | Orientation::left);
    SetDefaultXAxis(graphs, results);
    graphs.SetYAxis("Crosssection [fb]");
    return graphs.FileBaseName();
}

std::string PlottingBase::PlotMDGraph(Results const& results) const
{
    INFO0;
    Graphs graphs(Tagger().ExportFolderName(), "MDSignificance");
    for (auto const & signal : results.Signals()) {
        graphs.AddGraph(results.XValues(), signal.MD(Significance::poisson), "Poisson");
        graphs.AddGraph(results.XValues(), signal.MD(Significance::sum), "#frac{S}{#sqrt{S + B}}");
        graphs.AddGraph(results.XValues(), signal.MD(Significance::background), "#frac{S}{#sqrt{B}}");
        graphs.AddLine(signal.BestMDValue(Significance::poisson));
        graphs.AddLine(signal.BestMDValue(Significance::sum));
        graphs.AddLine(signal.BestMDValue(Significance::background));
    }
    graphs.SetLegend(Orientation::top | Orientation::left);
    SetDefaultXAxis(graphs, results);
    graphs.SetYAxis("Significance");
    return graphs.FileBaseName();
}

std::string PlottingBase::PlotMDExperimentalGraph(Results const& results) const
{
    INFO0;
    Graphs graphs(Tagger().ExportFolderName(), "MDExperimental");
    for (auto const & signal : results.Signals()) {
        graphs.AddGraph(results.XValues(), signal.MD(Significance::experimental));
        graphs.AddLine(signal.BestMDValue(Significance::experimental));
    }
    SetDefaultXAxis(graphs, results);
    graphs.SetYAxis(Formula("S/B"));
    return graphs.FileBaseName();
}

std::string PlottingBase::PlotExperimentalVsSignificance(Results const& results) const
{
    INFO0;
    Graphs graphs(Tagger().ExportFolderName(), "SBvsSsqrtB");
    for (auto const & signal : results.Signals()) {
      graphs.AddGraph(signal.MD(Significance::experimental), signal.MD(Significance::poisson), "Poisson");
      graphs.AddGraph(signal.MD(Significance::experimental), signal.MD(Significance::sum), "#frac{S}{#sqrt{S+B}}");
      graphs.AddGraph(signal.MD(Significance::experimental), signal.MD(Significance::background), "#frac{S}{#sqrt B}");
    }
    graphs.SetXAxis(Formula("S/B"));
    graphs.SetYAxis("Significance");
    return graphs.FileBaseName();
}

std::string PlottingBase::PlotMIGraph(Results const& results) const
{
    INFO0;
    Graphs graphs(Tagger().ExportFolderName(), "MIConstrained");
    for (auto const & signal : results.Signals()) {
        graphs.AddGraph(results.XValues(), FloatVector(signal.MI(Significance::poisson | Significance::experimental)), "Poisson");
        graphs.AddGraph(results.XValues(), FloatVector(signal.MI(Significance::sum | Significance::experimental)), "#frac{S}{#sqrt{S+B}}");
        graphs.AddGraph(results.XValues(), FloatVector(signal.MI(Significance::background | Significance::experimental)), "#frac{S}{#sqrt{B}}");
        graphs.AddLine(signal.BestMIValue(Significance::poisson | Significance::experimental));
        graphs.AddLine(signal.BestMIValue(Significance::sum | Significance::experimental));
        graphs.AddLine(signal.BestMIValue(Significance::background | Significance::experimental));
    }
    graphs.SetLegend(Orientation::left);
    graphs.SetYAxis("Exclusion crosssection [fb]");
    SetDefaultXAxis(graphs, results);
    return graphs.FileBaseName();
}

std::string PlottingBase::PlotMIExperimentalGraph(Results const& results) const
{
    INFO0;
    Graphs graphs(Tagger().ExportFolderName(), "MIExperimental");
    for (auto const & signal : results.Signals()) {
        graphs.AddGraph(results.XValues(), FloatVector(signal.MI(Significance::experimental)), signal.InfoBranch().LatexName());
        graphs.AddLine(signal.BestMIValue(Significance::experimental), "#frac{S}{B}");
    }
    graphs.SetLegend(Orientation::left);
    graphs.SetYAxis("Exclusion crosssection [fb]");
    SetDefaultXAxis(graphs, results);
    return graphs.FileBaseName();
}

std::string PlottingBase::PlotMISignificanceGraph(Results const& results) const
{
    INFO0;
    Graphs graphs(Tagger().ExportFolderName(), "MISignificance");
    for (auto const & signal : results.Signals()) {
        graphs.AddGraph(results.XValues(), FloatVector(signal.MI(Significance::poisson)), "Poisson");
        graphs.AddGraph(results.XValues(), FloatVector(signal.MI(Significance::sum)), "#frac{S}{#sqrt{S+B}}");
        graphs.AddGraph(results.XValues(), FloatVector(signal.MI(Significance::background)), "#frac{S}{#sqrt{B}}");
        graphs.AddLine(signal.BestMIValue(Significance::poisson));
        graphs.AddLine(signal.BestMIValue(Significance::sum));
        graphs.AddLine(signal.BestMIValue(Significance::background));
    }
    graphs.SetLegend(Orientation::left);
    graphs.SetYAxis("Exclusion crosssection [fb]");
    SetDefaultXAxis(graphs, results);
    return graphs.FileBaseName();
}

std::string PlottingBase::BestValueTable(Result const& signal, std::vector<double> const& x_values) const
{
    INFO0;
    std::stringstream table;
    table << "    Model optimization\n  & Cut\n  & Significance\n  & Ratio [\\%]\n  & Crosssection [fb]";
    table << "\n \\\\ \\midrule\n   ";
    for (const auto & significance : SignificancesUnConstrained()) {
        table << " dependent" << BestValueRow(signal, x_values, significance, signal.BestMDBin(significance));
        table << " independent" << BestValueRow(signal, x_values, significance, signal.BestMIBin(significance));
    }
    table << " \\midrule\n";
    for (const auto & significance : SignificancesConstrained()) table << " independent" << BestValueRow(signal, x_values, significance, signal.BestMIBin(significance));
    return table.str();
}

std::string PlottingBase::BestValueRow(Result const& signal, std::vector<double> const& x_values, Significance significance, int bin) const
{
    INFO0;
    std::stringstream row;
    row << boost::units::engineering_prefix << " " << LatexName(significance);
    row << "\n  & " << RoundToDigits(x_values.at(bin));
    row << "\n  & " << RoundToDigits(signal.MD(significance &~Significance::experimental).at(bin));
    row << "\n  & " << RoundToDigits(signal.MD(Significance::experimental).at(bin) * 100);
    row << "\n  & " << RoundToDigits(signal.MI(significance).at(bin) / fb);
//     row << "\n  & " << RoundToDigits(signal.Crosssections().at(bin) / fb);
    row << "\n \\\\";
    return row.str();
}

// std::string PlottingBase::ScalingTable(Results& results)const
// {
//     INFO0;
//     std::stringstream table;
//     table << "    $\\sigma$ [fb]\n  & " + SignificanceString() + " and " + Ratio() + "\n  &" + SignificanceString() + "\n  &" + Ratio() + "\n";
//     table << "\n \\\\ \\midrule\n   ";
//     for (auto const & exponent : IntegerRange(-3, 4)) {
//         auto factor = std::pow(2., exponent);
//         INFO(exponent, factor);
//         results.CalculateSignificances(factor);
//         if(factor == 1) table << "  \\midrule";
//         table << ScalingRow(results, factor);
//         if(factor == 1) table << "  \\midrule";
//     }
//     return table.str();
// }

// namespace
// {
// std::string BoldFace(std::string const& string, bool do_it)
// {
//     return do_it ? "\\textbf{" + string + "}" : string;
// }
//
// }

// std::string PlottingBase::ScalingRow(Results const& results, double factor) const
// {
//     INFO0;
//     std::stringstream row;
//     row << " " << RoundToDigits(factor * results.Signals().front().InfoBranch().Crosssection() / fb);
//     for(auto const signal : results.Signals()){
//       row << "\n  & " << RoundToDigits(signal.MD(Significance::sum).at(signal.BestMIValue(Significance::sum)));
//       row << "\n  & " << RoundToDigits(signal.MD(Significance::background).at(signal.BestMDValue(Significance::background)));
//       row << "\n  & " << RoundToDigits(signal.MD(Significance::experimental).at(signal.BestMDValue(Significance::experimental)));
//     }
//     row << "\n \\\\";
//     return row.str();
// }

std::string PlottingBase::EfficienciesTable(Results const& results, int bin) const
{
    INFO0;
    std::stringstream table;
    table << "    Sample\n  & before\n  & after\n  & Efficiency\n  & $\\sigma$  [fb]\n  & $N_{\\mathcal L = \\unit[" << RoundToDigits(DetectorGeometry::Luminosity() * fb) << "]{fb^{-1}}}$";
    table << "\n \\\\ \\midrule\n   ";
    for (auto const & result : results.Signals()) table << EfficienciesRow(result, Position(results.Signals(), result), Tag::signal, bin);
    for (auto const & result : results.Backgrounds()) table << EfficienciesRow(result, Position(results.Backgrounds(), result), Tag::background, bin);
    return table.str();
}

std::string PlottingBase::EfficienciesRow(Result const& result, int, Tag , int bin) const
{
    INFO0;
    std::stringstream row;
//     row << " \\verb|" << Tagger().TreeNames(tag).at(index) << "|";
//     row << " \\verb|" << result.InfoBranch().LatexName() << "|";
    row << "$" << result.InfoBranch().Name() << "$";
    row << "\n  & " << result.InfoBranch().EventNumber();
    row << "\n  & " << result.PartialSum().at(bin);
    row << "\n  & " << RoundToDigits(result.PreCutEfficiencies().at(bin));
    row << "\n  & " << RoundToDigits(result.InfoBranch().Crosssection() / fb * Results::ScalingFactor());
    row << "\n  & " << RoundToDigits(result.InfoBranch().Crosssection() * DetectorGeometry::Luminosity() * result.PreCutEfficiencies().at(bin) * Results::ScalingFactor());
    row << "\n \\\\";
    return row.str();
}

std::string PlottingBase::EfficienciesTableMI(Results const& results, int bin, std::function<std::vector<Crosssection>(Result const&)> const& function) const
{
    INFO0;
    std::stringstream table;
    table << "    Sample\n  & before\n  & after\n  & Efficiency\n  & $\\sigma$  [fb]\n";
    table << "\n \\\\ \\midrule\n   ";
    for (auto const & result : results.Signals()) table << EfficienciesRowMI(result, Position(results.Signals(), result), Tag::signal, bin, function);
    for (auto const & result : results.Backgrounds()) table << EfficienciesRowMI(result, Position(results.Backgrounds(), result), Tag::background, bin);
    return table.str();
}

std::string PlottingBase::EfficienciesRowMI(Result const& result, int , Tag , int bin, std::function<std::vector<Crosssection>(Result const&)> const& function) const
{
    INFO0;
    std::stringstream row;
//     row << " \\verb|" << result.InfoBranch().LatexName() << "|";
    row << " $" << result.InfoBranch().Name() << "$";
    row << "\n  & " << result.InfoBranch().EventNumber();
    row << "\n  & " << result.PartialSum().at(bin);
    row << "\n  & " << RoundToDigits(result.PreCutEfficiencies().at(bin));
    row << "\n  & " << RoundToDigits(function(result).at(bin) / fb);
    row << "\n \\\\";
    return row.str();
}

std::string PlottingBase::EfficienciesRowMI(Result const& result, int index, Tag tag, int bin) const
{
    INFO0;
    return EfficienciesRowMI(result, index, tag, bin, [](Result const & result) {
        return std::vector<Crosssection>(result.Steps(), result.InfoBranch().Crosssection() * Results::ScalingFactor());
    });
}

std::string PlottingBase::CutEfficiencyTable(Results const& results) const
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

std::string PlottingBase::CutEfficiencyRow(Result const& result, int , Tag) const
{
    INFO0;
    std::stringstream row;
    //   row << " \\verb|" << Tagger().TreeNames(tag).at(index) << "|";
//     row << " \\verb|" << result.InfoBranch().LatexName() << "|";
    row << "$" << result.InfoBranch().Name() << "$";
    for (auto const & eff : result.SelectedEfficiencies()) row << "\n  & " << RoundToDigits(eff * 100);
    row << "\n \\\\";
    return row.str();
}

std::string PlottingBase::TruthLevelCutTable(Results const& results) const
{
    INFO0;
    std::stringstream table;
    table << "    Sample\n  & Efficiency\n";
    table << "\n \\\\ \\midrule\n   ";
    for (auto const & result : results.Signals()) table << TruthLevelCutRow(result, Tag::signal);
    for (auto const & result : results.Backgrounds()) table << TruthLevelCutRow(result, Tag::background);
    return table.str();
}

std::string PlottingBase::TruthLevelCutRow(Result const& result, Tag) const
{
    INFO0;
    std::stringstream row;
    row << "$" << result.InfoBranch().Name() << "$";
    row << "\n  & " << RoundToDigits(double(result.TrainerSize()) / result.TrainerInfoBranch().EventNumber());
    row << "\n \\\\";
    return row.str();
}

void PlottingBase::RunPlots(Stage stage) const
{
    INFO0;
    DEBUG(Tagger().FileName(stage, Tag::signal), Tagger().TreeNames(Tag::signal).size());
    auto signals = Import(Phase(stage, Tag::signal));
    DEBUG(Tagger().FileName(stage, Tag::background), Tagger().TreeNames(Tag::background).size());
    auto backgrounds = Import(Phase(stage, Tag::background));
    auto background = backgrounds.front();
    background = std::accumulate(backgrounds.begin() + 1, backgrounds.end(), background, [](Plots & sum, Plots const & plots) {
        for (auto & plot : sum.PlotVector()) plot.Insert(plots.PlotVector().at(Position(sum.PlotVector(), plot)).Data());
        return sum;
    });
    background.Names().SetName("background");
    for (auto & signal : signals) DoPlot(signal, background, stage);
}

void PlottingBase::DoPlot(Plots& signals, Plots& backgrounds, Stage stage) const
{
    INFO0;
    auto names = UnorderedPairs(ConstCast(Tagger().Branch()).Variables().Vector(), [&](Observable const & variable_1, Observable const & variable_2) {
        return std::make_pair(variable_1.Names(), variable_2.Names());
    });
    signals.SetNames(names);
    backgrounds.SetNames(names);
    for (auto & signal : signals.PlotVector()) PlotDetails(signal, backgrounds.PlotVector().at(Position(signals.PlotVector(), signal)), stage);
}

void PlottingBase::PlotDetails(Plot& signal, Plot& background, Stage stage) const
{
    INFO(signal.Data().size(), background.Data().size());
    auto signal_x = signal.CoreData([](Vector3<double> const & a, Vector3<double> const & b) {
        return a.X() < b.X();
    });
    auto signal_y = signal.CoreData([](Vector3<double> const & a, Vector3<double> const & b) {
        return a.Y() < b.Y();
    });
    auto background_x = background.CoreData([](Vector3<double> const & a, Vector3<double> const & b) {
        return a.X() < b.X();
    });
    auto background_y = background.CoreData([](Vector3<double> const & a, Vector3<double> const & b) {
        return a.Y() < b.Y();
    });
    Rectangle<double> range;
    range.SetXMin(std::min(signal_x.front().X(), background_x.front().X()));
    range.SetXMax(std::max(signal_x.back().X(), background_x.back().X()));
    range.SetYMin(std::min(signal_y.front().Y(), background_y.front().Y()));
    range.SetYMax(std::max(signal_y.back().Y(), background_y.back().Y()));
    switch (stage) {
    case Stage::trainer : return PlotHistogram(signal, background, range);
    case Stage::reader : return PlotProfile(signal, background, range);
    }
}

void PlottingBase::PlotHistogram(Plot const& signal, Plot const& background, Rectangle<double> const& range) const
{
    INFO(signal.Data().size(), background.Data().size());
    Histogram2Dim histogram(Tagger().ExportFolderName(), signal.XAxis().Name() + "-" + signal.YAxis().Name());
    auto bin_number = 20;
    histogram.AddHistogram("Background", bin_number, range, background, kBlue);
    histogram.AddHistogram("Signal", bin_number, range, signal, kRed);
    histogram.SetLegend(Orientation::top | Orientation::outside);
    histogram.SetXAxis(signal.XAxis().LatexName());
    histogram.SetYAxis(signal.YAxis().LatexName());
}

void PlottingBase::PlotProfile(Plot const& signal, Plot const& background, Rectangle<double> const& range) const
{
    INFO0;
    Profile profile(Tagger().ExportFolderName(), signal.Title().Name(), signal.XAxis().Name() + "-" + signal.YAxis().Name());
    profile.SetDimensions(Tagger().LatexName(), 30, range);
    profile.SetProfile(signal, background);
    profile.SetXAxis(signal.XAxis().LatexName());
    profile.SetYAxis(signal.YAxis().LatexName());
    profile.SetZAxis("BDT_{" + signal.Title().LatexName() + "}", 30);
}

std::vector<Plots> PlottingBase::Import(Phase const& phase) const
{
    INFO(Tagger().FileName(phase), Tagger().TreeNames(phase).size());
    TFile file(Tagger().FileName(phase).c_str(), "Read");
    std::vector<Plots> results;
    for (auto const & tree_number : IntegerRange(Tagger().TreeNames(phase).size())) results.emplace_back(PlotResult(file, tree_number, phase));
    return results;
}

Plots PlottingBase::PlotResult(TFile& file, int tree_number, Phase const& phase) const
{
    INFO(tree_number);
    Plots plots(InfoBranch(phase, tree_number).first);
    TTree& tree = static_cast<TTree&>(*file.Get(Tagger().TreeNames(phase).at(tree_number).c_str()));
    tree.SetMakeClass(true);
    plots.PlotVector() = UnorderedPairs(ConstCast(Tagger().Branch()).Variables().Vector(), [&](Observable const & variable_1, Observable const & variable_2) {
        auto plot = ReadTree(tree, variable_1.Name(), variable_2.Name(), phase.Stage());
        plot.x_is_int = variable_1.IsInt();
        plot.y_is_int = variable_2.IsInt();
        return plot;
    });
    plots.Names().SetName(Tagger().TreeNames(phase).at(tree_number));
    DEBUG(plots.PlotVector().size(), ConstCast(Tagger().Branch()).Variables().Vector().size());
    return plots;
}

namespace
{

void SetBranch(TTree& tree, std::vector< double >& values, std::string const& name)
{
    tree.SetBranchStatus(name.c_str(), true);
    tree.SetBranchAddress(name.c_str(), values.data());
}

void SetBranch(TTree& tree, int& value, std::string const& name)
{
    tree.SetBranchStatus(name.c_str(), true);
    tree.SetBranchAddress(name.c_str(), &value);
}

}

Plot PlottingBase::ReadTree(TTree& tree, std::string const& leaf_1_name, std::string const& leaf_2_name, Stage stage) const
{
    INFO0;
    tree.SetBranchStatus("*", false);
    auto branch_name = Tagger().BranchName(stage);
    DEBUG(branch_name);

    auto branch_value = 0;
    SetBranch(tree, branch_value, branch_name);

    auto branch_size = 0;
    SetBranch(tree, branch_size, branch_name + "_size");

    //FIXME remove this magic number
    std::size_t max_value = 10;
    std::vector<double> leaf_values_1(max_value);
    SetBranch(tree, leaf_values_1, branch_name + "." + leaf_1_name);

    std::vector<double> leaf_values_2(max_value);
    SetBranch(tree, leaf_values_2, branch_name + "." + leaf_2_name);

    std::vector<double> bdt_values(max_value);
    SetBranch(tree, bdt_values, branch_name + ".Bdt");

    Plot plot;
    for (auto const & entry : IntegerRange(tree.GetEntries())) {
        DETAIL(tree.GetEntries(), entry);
        tree.GetEntry(entry);
        DETAIL(branch_size, leaf_values_1.size(), leaf_values_2.size());
        for (auto const & element : IntegerRange(branch_size)) plot.Add(Vector3<double>(leaf_values_1.at(element), leaf_values_2.at(element), bdt_values.at(element)));
    }
    return plot;
}



std::vector<Plots> PlottingBase::Import2() const
{
    return Transform(ConstCast(Tagger().Branch()).Variables().Vector(), [this](Observable const & variable) {
        return PlotResult3(variable);
    });
}

Plots PlottingBase::PlotResult3(Observable const& variable) const
{
    ERROR0;
    Plots plots;
    plots.Names() = variable.Names();
    for (auto const & tag : std::vector<Tag>( {Tag::signal, Tag::background})) PlotResult2(variable, tag, plots);
    return plots;
}


Plots PlottingBase::PlotResult2(Observable const& variable, Tag tag, Plots& plots) const
{
    ERROR(Name(tag));
    Phase phase(Stage::trainer, tag);
    TFile file(Tagger().FileName(phase).c_str(), "Read");
    std::vector<boca::InfoBranch> branches;
    auto names = Tagger().TreeNames(phase);
    for (auto const & tree_number : IntegerRange(names.size())) {
        if (branches.size() < names.size()) branches.emplace_back(InfoBranch(phase, tree_number).first);
        auto& tree = static_cast<TTree&>(*file.Get(Tagger().TreeNames(phase).at(tree_number).c_str()));
        tree.SetMakeClass(true);
        auto plot = ReadTree2(tree, variable.Name());
        plot.x_is_int = variable.IsInt();
        plot.Title() = branches.at(tree_number).Names();
        plots.PlotVector().emplace_back(plot);
    }
    return plots;
}

Plot PlottingBase::ReadTree2(TTree& tree, std::string const& leaf_name) const
{
    INFO0;
    tree.SetBranchStatus("*", false);
    auto branch_name = Tagger().BranchName(Stage::trainer);
    DEBUG(branch_name);

    auto branch_value = 0;
    SetBranch(tree, branch_value, branch_name);

    auto branch_size = 0;
    SetBranch(tree, branch_size, branch_name + "_size");

    //FIXME remove this magic number
    std::size_t max_value = 200;
    std::vector<double> leaf_values(max_value);
    SetBranch(tree, leaf_values, branch_name + "." + leaf_name);


    Plot plot;
    for (auto const & entry : IntegerRange(tree.GetEntries())) {
        DETAIL(tree.GetEntries(), entry);
        tree.GetEntry(entry);
        for (auto const & element : IntegerRange(branch_size)) plot.Add(Vector3<double>(leaf_values.at(element), 0, 0));
    }
    return plot;
}

void PlottingBase::RunPlotHist() const
{
    INFO0;
    for (auto const & plots : Import2()) PlotVariables(plots);
}

void PlottingBase::PlotVariables(Plots const& plots) const
{
    Histograms histograms(Tagger().ExportFolderName(), plots.Names().Name());
    for (auto const & plot : plots.PlotVector()) histograms.AddHistogram(plot.XData(), plot.Title().LatexName(), plots.XRange(), plot.x_is_int);
    histograms.SetLog();
    histograms.SetLegend(Orientation::outside | Orientation::right);
    histograms.SetYAxis(Formula("N"));
    histograms.SetXAxis(plots.Names().LatexName());
}

}
