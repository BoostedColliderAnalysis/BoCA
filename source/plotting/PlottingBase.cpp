/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include <boost/range/numeric.hpp>
#include <boost/range/join.hpp>

#include "boca/generic/Vector.hh"
#include "boca/generic/Types.hh"

#include "boca/io/FileWriter.hh"
#include "boca/io/TreeReader.hh"

#include "boca/latex/File.hh"

#include "boca/branch/Bdt.hh"
#include "boca/branch/Cut.hh"
#include "boca/branch/Info.hh"
#include "boca/branch/Result.hh"

#include "boca/plotting/PlottingBase.hh"
#include "boca/plotting/Graphs.hh"
#include "boca/plotting/Results.hh"
#include "boca/plotting/Histograms.hh"
#include "boca/plotting/Histogram2Dim.hh"
#include "boca/plotting/Profile.hh"
#include "boca/plotting/Plots.hh"
#include "boca/plotting/Font.hh"

#include "boca/tagger/Base.hh"

// #define INFORMATION
#include "boca/generic/DEBUG.hh"

namespace boca
{

namespace
{

auto Ratio(int min = 0)
{
    return LatexName(Significance::experimental) + (min > 0 ? "\\geq \\unit[" + std::to_string(min / cU) + "]{\\%}" : "");
}

}

void PlottingBase::TaggingEfficiency() const
{
    INFO0;
    auto results = ReadBdtFiles(Stage::reader);
    results.CutEfficiencies();
    latex::File latex_file(Tagger().ExportFolderName());
    latex_file.AddGraphic(PlotHistograms(results));
    latex_file.AddGraphic(PlotAcceptanceGraph(results));
    latex_file.AddGraphic(PlotEfficiencyGraph(results));
    latex_file.AddTable(CutEfficiencyTable(results));
    latex_file.AddTable(TruthLevelCutTable(results));
}

void PlottingBase::OptimalCuts() const
{
    INFO0;
    auto results = ReadBdtFiles(Stage::reader);
    results.CalculateSignificances();
    latex::File latex_file(Tagger().ExportFolderName());
    latex_file.AddTitle(results.Signals().front().Info().Mass());
    if (Tagger().Mva() == TMVA::Types::EMVA::kBDT) latex_file.AddGraphic(PlotHistograms(results));
    latex_file.AddGraphic(PlotEfficiencyGraph(results));
    latex_file.AddGraphic(PlotCrosssectionsGraph(results));
    latex_file.AddGraphic(PlotMDGraph(results));
    latex_file.AddGraphic(PlotMDExperimentalGraph(results));
    latex_file.AddGraphic(PlotMISignificanceExclusion(results));
    latex_file.AddGraphic(PlotMISignificanceDiscovery(results));
    latex_file.AddGraphic(PlotMIExperimentalGraph(results));
    latex_file.AddGraphic(PlotMIExclusion(results));
    latex_file.AddGraphic(PlotMIDiscovery(results));
    latex_file.AddGraphic(PlotExperimentalVsSignificance(results));
    latex_file.AddTable(EfficienciesTableMI(results, Significance::sum | Significance::experimental | Significance::exclusion));
    latex_file.AddTable(EfficienciesTableMI(results, Significance::background | Significance::exclusion));
    latex_file.AddTable(EfficienciesTableMI(results, Significance::experimental));
    for (const auto & signal : results.Signals()) {
        latex_file.AddTable(EfficienciesTable(results, signal.BestMDBin(Significance::sum)));
        latex_file.AddTable(BestValueTable(signal, results.XValues()));
    }
}

Results PlottingBase::ReadBdtFiles(Stage stage) const
{
    INFO0;
    FileWriter file_writer(Tagger().ExportFileName());
    return Results(ReadBdtFile(file_writer, {stage, Tag::signal}), ReadBdtFile(file_writer, {stage, Tag::background}));
}

std::vector<Result> PlottingBase::ReadBdtFile(FileWriter& file_writer, Phase const& phase) const
{
    INFO0;
    return Transform(Tagger().TreeNames(phase), [&](std::string const & tree_name) {
        switch (Tagger().Mva()) {
        case TMVA::Types::EMVA::kBDT : return BdtDistribution(file_writer, phase, tree_name);
        case TMVA::Types::EMVA::kCuts : return CutDistribution(file_writer, phase, tree_name);
            DEFAULT(Tagger().MvaName(), Result());
        }
    });
}

Result PlottingBase::BdtDistribution(FileWriter& file_writer, Phase const& phase, std::string const& tree_name) const
{
    INFO0;
    TreeReader tree_reader(Tagger().FileName(phase), tree_name, Source::tagger);
    auto& array = tree_reader.Array(Tagger().BranchName(phase), Tagger().Class());
    auto& tree_writer = file_writer.NewTree(tree_name);
    auto& branch = tree_writer.NewBranch<branch::Bdt>(Tagger().BranchName(phase));
    std::vector<double> bdts;
    while (tree_reader.Next()) {
        for (auto const & entry : array) {
            double bdt = static_cast<branch::Bdt const&>(entry).bdt;
            branch.AddEntry<branch::Bdt>().bdt = bdt;
            bdts.emplace_back(bdt);
        }
        tree_writer.Fill();
    }
    tree_writer.Write();
    return Result(Info(Phase(Stage::reader, phase.Tag()), tree_name).first, Info(Phase(Stage::trainer, phase.Tag()), tree_name), bdts, Tagger().Mva());
}

Result PlottingBase::CutDistribution(FileWriter& file_writer, Phase const& phase, std::string const& tree_name) const
{
    INFO0;
    TreeReader tree_reader(Tagger().FileName(phase), tree_name, Source::tagger);
    auto& array = tree_reader.Array(Tagger().BranchName(phase), Tagger().Class());
    auto& tree_writer = file_writer.NewTree(tree_name);
    auto& branch = tree_writer.NewBranch<branch::Cut>(Tagger().BranchName(phase));
    std::vector<std::vector<bool>> passed_matrix;
    while (tree_reader.Next()) {
        for (auto const & entry : array) {
            auto passed_vector = static_cast<branch::Cut const&>(entry).passed;
            branch.AddEntry<branch::Cut>().passed = passed_vector;
            passed_matrix.emplace_back(passed_vector);
        }
        tree_writer.Fill();
    }
    tree_writer.Write();
    return Result(Info(Phase(Stage::reader, phase.Tag()), tree_name).first, Info(Phase(Stage::trainer, phase.Tag()), tree_name), passed_matrix, Tagger().Mva());
}

std::pair<branch::Info, int> PlottingBase::Info(Phase const& phase, std::string const& tree_name) const
{
    INFO(Name(phase.Tag()));
    TreeReader tree_reader(Tagger().FileName(phase), tree_name, Source::tagger);
    INFO(Tagger().WeightBranchName());
    if (tree_reader.GetEntries() == 0) {
        ERROR("tree reader empty, no object for casting");
        return std::make_pair(boca::branch::Info(), 0);
    }
    auto& array = tree_reader.Array<boca::branch::Info>(Tagger().WeightBranchName());
    tree_reader.ReadEntry(tree_reader.GetEntries() - 1);
    if (array.GetSize() == 0) {
        ERROR("array empty, no object for casting");
        return std::make_pair(boca::branch::Info(), 0);
    }
    return std::make_pair(array.At(array.GetSize() - 1), tree_reader.GetEntries());
}

latex::Graphic PlottingBase::PlotHistograms(Results const& results) const
{
    INFO0;
    Histograms histograms(Tagger().ExportFolderName(), "Bdt");
    for (auto const & signal : results.Signals()) {
        histograms.AddHistogram(signal.Bdts(), signal.Info().Names(), results.Range());
        histograms.AddLine(signal.BestMIValue(Significance::sum | Significance::experimental));
        histograms.AddLine(signal.BestMDValue(Significance::sum));
    }
    for (auto const & background : results.Backgrounds()) histograms.AddHistogram(background.Bdts(), background.Info().Names(), results.Range());
    histograms.SetLegend(Orientation::top);
    histograms.SetXAxis("BDT");
    histograms.SetYAxis(latex::String("N", true));
    return {histograms.FileBaseName(), "BDT Distribution"};
}

latex::Graphic PlottingBase::PlotEfficiencyGraph(Results const& results) const
{
    INFO0;
    Graphs graphs(Tagger().ExportFolderName(), "Efficiency");
    for (auto const & signal : results.Signals()) {
        graphs.AddGraph(results.XValues(), signal.PreCutEfficiencies(), signal.Info().LatexName());
        graphs.AddLine(signal.BestMDValue(Significance::sum));
        graphs.AddLine(signal.BestMIValue(Significance::sum | Significance::experimental));
    }
    for (auto const & background : results.Backgrounds()) graphs.AddGraph(results.XValues(), background.PreCutEfficiencies(), background.Info().LatexName());
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
    return {graphs.FileBaseName(), "Efficiency"};
}

latex::Graphic PlottingBase::PlotAcceptanceGraph(Results const& results) const
{
    INFO0;
    std::vector<std::string> names;
    for (auto const & signal : results.Signals()) {
        Graphs graphs(Tagger().ExportFolderName(), "Acceptance" + std::to_string(Position(results.Signals(), signal)));
        graphs.AddGraph(signal.PureEfficiencies(), signal.PureEfficiencies(), signal.Info().LatexName());
        for (auto const & background : results.Backgrounds()) graphs.AddGraph(signal.PureEfficiencies(), background.PureEfficiencies(), background.Info().LatexName());
        graphs.SetLegend(Orientation::right | Orientation::bottom/*, signal.Info().LatexName()*/);
        graphs.SetXAxis("Signal acceptance", {0.2, 0.9});
        graphs.SetYAxis("Background acceptance", {1e-3, 1});
        names.emplace_back(graphs.FileBaseName());
    }
    return {names, "Acceptance"};
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

latex::Graphic PlottingBase::PlotCrosssectionsGraph(Results const& results) const
{
    INFO0;
    Graphs graphs(Tagger().ExportFolderName(), "Crosssection");
    for (auto const & signal : results.Signals()) {
        graphs.AddGraph(results.XValues(), FloatVector(signal.Crosssections()), signal.Info().LatexName());
        graphs.AddLine(signal.BestMDValue(Significance::sum));
        graphs.AddLine(signal.BestMIValue(Significance::sum | Significance::experimental));
    }
    for (auto const & background : results.Backgrounds()) graphs.AddGraph(results.XValues(), FloatVector(background.Crosssections()), background.Info().LatexName());
    graphs.SetLegend(Orientation::bottom | Orientation::left);
    SetDefaultXAxis(graphs, results);
    graphs.SetYAxis("Crosssection [fb]");
    return {graphs.FileBaseName(), "Crosssection in fb"};
}

latex::Graphic PlottingBase::PlotMDGraph(Results const& results) const
{
    INFO0;
    Graphs graphs(Tagger().ExportFolderName(), "MDSignificance");
    for (auto const & signal : results.Signals()) for (auto const & significance : SignificancesMD()) {
            graphs.AddGraph(results.XValues(), signal.MD(significance), LatexName(significance));
            graphs.AddLine(signal.BestMDValue(significance));
        }
    graphs.SetLegend(Orientation::top | Orientation::left);
    SetDefaultXAxis(graphs, results);
    graphs.SetYAxis("Significance");
    return {graphs.FileBaseName(), "Maximization of significance"};
}

latex::Graphic PlottingBase::PlotMDExperimentalGraph(Results const& results) const
{
    INFO0;
    Graphs graphs(Tagger().ExportFolderName(), "MDExperimental");
    for (auto const & signal : results.Signals()) {
        graphs.AddGraph(results.XValues(), signal.MD(Significance::experimental));
        graphs.AddLine(signal.BestMDValue(Significance::experimental));
    }
    SetDefaultXAxis(graphs, results);
    graphs.SetYAxis( {"S/B", true});
    return {graphs.FileBaseName(), "Maximization of " + Ratio()};
}

latex::Graphic PlottingBase::PlotExperimentalVsSignificance(Results const& results) const
{
    INFO0;
    Graphs graphs(Tagger().ExportFolderName(), "SBvsSsqrtB");
    for (auto const & signal : results.Signals()) for (auto const & significance : SignificancesMD()) graphs.AddGraph(signal.MD(Significance::experimental), signal.MD(significance), LatexName(significance));
    graphs.SetXAxis(latex::String("S/B", true));
    graphs.SetYAxis("Significance");
    return {graphs.FileBaseName(), Ratio() + "versus significance"};
}

latex::Graphic PlottingBase::PlotMISignificanceExclusion(Results const& results) const
{
    INFO0;
    Graphs graphs(Tagger().ExportFolderName(), "MISignificanceExclusion");
    for (auto const & signal : results.Signals()) for (auto const & significance : Exclusion(SignificancesBase())) {
            graphs.AddGraph(results.XValues(), FloatVector(signal.MI(significance)), LatexName(significance));
            graphs.AddLine(signal.BestMIValue(significance));
        }
    graphs.SetLegend(Orientation::left);
    graphs.SetYAxis("Exclusion crosssection [fb]");
    SetDefaultXAxis(graphs, results);
    return {graphs.FileBaseName(), "Minimization of the model independent crosssection for significance"};
}

latex::Graphic PlottingBase::PlotMISignificanceDiscovery(Results const& results) const
{
    INFO0;
    Graphs graphs(Tagger().ExportFolderName(), "MISignificanceDiscovery");
    for (auto const & signal : results.Signals()) for (auto const & significance : Discovery(SignificancesBase())) {
            graphs.AddGraph(results.XValues(), FloatVector(signal.MI(significance)), LatexName(significance));
            graphs.AddLine(signal.BestMIValue(significance));
        }
    graphs.SetLegend(Orientation::left);
    graphs.SetYAxis("Discovery crosssection [fb]");
    SetDefaultXAxis(graphs, results);
    return {graphs.FileBaseName(), "Minimization of the model independent crosssection for significance"};
}

latex::Graphic PlottingBase::PlotMIExperimentalGraph(Results const& results) const
{
    INFO0;
    Graphs graphs(Tagger().ExportFolderName(), "MIExperimental");
    for (auto const & signal : results.Signals()) {
        graphs.AddGraph(results.XValues(), FloatVector(signal.MI(Significance::experimental)), signal.Info().LatexName());
        graphs.AddLine(signal.BestMIValue(Significance::experimental), LatexName(Significance::experimental));
    }
    graphs.SetLegend(Orientation::left);
    graphs.SetYAxis("Crosssection [fb]");
    SetDefaultXAxis(graphs, results);
    return {graphs.FileBaseName(), "Minimization of model independent cross section for " + Ratio(Settings::Experimental())};
}

latex::Graphic PlottingBase::PlotMIDiscovery(Results const& results) const
{
    INFO0;
    Graphs graphs(Tagger().ExportFolderName(), "MIConstrainedDiscovery");
    for (auto const & signal : results.Signals()) for (auto const & significance : Constrained(Discovery(SignificancesBase()))) {
            graphs.AddGraph(results.XValues(), FloatVector(signal.MI(significance)), LatexName(significance &~ Significance::experimental));
            graphs.AddLine(signal.BestMIValue(significance));
        }
    graphs.SetLegend(Orientation::left);
    graphs.SetYAxis("Discovery crosssection [fb]");
    SetDefaultXAxis(graphs, results);
    return {graphs.FileBaseName(), "Minimization of model independent crosssection for significance and " + Ratio(Settings::Experimental())};
}

latex::Graphic PlottingBase::PlotMIExclusion(Results const& results) const
{
    INFO0;
    Graphs graphs(Tagger().ExportFolderName(), "MIConstrainedExclusion");
    for (auto const & signal : results.Signals()) for (auto const & significance : Constrained(Exclusion(SignificancesBase()))) {
            graphs.AddGraph(results.XValues(), FloatVector(signal.MI(significance)), LatexName(significance &~ Significance::experimental));
            graphs.AddLine(signal.BestMIValue(significance));
        }
    graphs.SetLegend(Orientation::left);
    graphs.SetYAxis("Exclusion crosssection [fb]");
    SetDefaultXAxis(graphs, results);
    return {graphs.FileBaseName(), "Minimization of model independent crosssection for significance and " + Ratio(Settings::Experimental())};
}

latex::Table PlottingBase::BestValueTable(Result const& signal, std::vector<double> const& x_values) const
{
    INFO0;
    latex::Table table("rllllll");
    table.AddRow("Model optimization", "Cut", "Significance", "Ratio [\\%]", "Crosssection [fb]");
    table.AddLine();
    for (const auto & significance : SignificancesMD()) table.AddRow(BestValueRow(signal, x_values, significance, "dependent ", signal.BestMDBin(significance)));
    table.AddLine();
    for (const auto & significance : SignificancesMI()) table.AddRow(BestValueRow(signal, x_values, significance, "independent ", signal.BestMIBin(significance)));
    table.AddLine();
    for (const auto & significance : Constrained(SignificancesMI())) table.AddRow(BestValueRow(signal, x_values, significance, "independent ", signal.BestMIBin(significance)));
    table.AddCaption("Results for the optimal model-(in)dependent cuts");
    return table;
}

latex::Row PlottingBase::BestValueRow(Result const& signal, std::vector<double> const& x_values, Significance significance, std::string const& model, int bin) const
{
    INFO0;
    latex::Row row(model + LatexName(significance).str(latex::Medium::latex));
    row.AddCell(RoundToDigits(x_values.at(bin)));
    row.AddCell(RoundToDigits(signal.MD(significance &~Significance::experimental).at(bin)));
    row.AddCell(RoundToDigits(signal.MD(Significance::experimental).at(bin) / cU));
    row.AddCell(RoundToDigits(signal.MI(significance).at(bin) / fb));
    return row;
}

latex::Table PlottingBase::EfficienciesTable(Results const& results, int bin) const
{
    INFO0;
    latex::Table table("rllllll");
    table.AddRow("Sample", "before", "pre-cut", "cut", "Efficiency", "$\\sigma$  [fb]", latex::Formula("N_{", latex::Command("mathcal", "L"), " = ", latex::Unit("fb^{-1}", static_cast<int>(Settings::Luminosity() * fb)), "}").str());
    table.AddLine();
    for (auto const & result : results.Signals()) table.AddRow(EfficienciesRow(result, Position(results.Signals(), result), Tag::signal, bin));
    for (auto const & result : results.Backgrounds()) table.AddRow(EfficienciesRow(result, Position(results.Backgrounds(), result), Tag::background, bin));
    table.AddCaption("Model dependent efficiencies calculated by maximizing the Significance");
    return table;
}

namespace
{
std::string Red(int value)
{
    return value == 1 ? latex::Command("textcolor", "red", value).str() : std::to_string(value);
}

}

latex::Row PlottingBase::EfficienciesRow(Result const& result, int, Tag tag, int bin) const
{
    INFO0;
    latex::Row row(result.Info().Names().Latex().str(latex::Medium::latex));
    row.AddCell(result.Info().EventNumber());
    row.AddCell(result.PartialSum().front());
    row.AddCell(Red(result.PartialSum().at(bin)));
    row.AddCell(RoundToDigits(result.PreCutEfficiencies().at(bin)));
    row.AddCell(RoundToDigits(result.Info().Crosssection() / fb * Results::ScalingFactor(tag)));
    row.AddCell(RoundToDigits(result.Info().Crosssection() * Settings::Luminosity() * result.PreCutEfficiencies().at(bin) * Results::ScalingFactor(tag)));
    return row;
}

latex::Table PlottingBase::EfficienciesTableMI(Results const& results, Significance significance) const
{
    INFO0;
    latex::Table table("rlllll");
    table.AddRow("Sample", "before", "pre-cut", "cut", "Efficiency", "$\\sigma$  [fb]\n");
    table.AddLine();
    for (auto const & signal : results.Signals()) {
        auto bin = signal.BestMIBin(significance);
        CHECK(bin > 0, bin, Name(significance));
        table.AddRow(EfficienciesRowMI(signal, bin));
        for (auto const & background : results.Backgrounds()) table.AddRow(EfficienciesRowMI(background, bin));
    }
    table.AddCaption("Model independent efficiencies calculated by minimizing the exclusion cross section" + LatexName(significance).str(latex::Medium::latex));
    return table;
}

latex::Row PlottingBase::EfficienciesRowMI(Result const& result, int bin) const
{
    INFO0;
    latex::Row row(result.Info().LatexName().str(latex::Medium::latex));
    row.AddCell(result.Info().EventNumber());
    row.AddCell(result.PartialSum().front());
    row.AddCell(Red(result.PartialSum().at(bin)));
    row.AddCell(RoundToDigits(result.PreCutEfficiencies().at(bin)));
    row.AddCell(RoundToDigits(result.Crosssections().at(bin) / fb));
    return row;
}

latex::Table PlottingBase::CutEfficiencyTable(Results const& results) const
{
    INFO0;
    latex::Table table("rllllllllll");
    table.AddRow("", latex::MultiColumn("Pure Efficiencies [\\%]", 9));
    latex::Row row("BDT value");
    for (auto const & eff : results.SelectedEfficiencies()) row.AddCell(RoundToDigits(eff));
    table.AddRow(row);
    table.AddLine();
    for (auto const & result : results.Signals()) table.AddRow(CutEfficiencyRow(result, Position(results.Signals(), result), Tag::signal));
    for (auto const & result : results.Backgrounds()) table.AddRow(CutEfficiencyRow(result, Position(results.Backgrounds(), result), Tag::background));
    table.AddCaption("Tagging rates and fake rates");
    return table;
}

latex::Row PlottingBase::CutEfficiencyRow(Result const& result, int , Tag) const
{
    INFO0;
    latex::Row row(result.Info().LatexName().str(latex::Medium::latex));
    for (auto const & eff : result.SelectedEfficiencies()) row.AddCell(RoundToDigits(eff * 100));
    return row;
}

latex::Table PlottingBase::TruthLevelCutTable(Results const& results) const
{
    INFO0;
    latex::Table table("rll");
    table.AddRow("Sample", "Efficiency");
    table.AddLine();
    for (auto const & result : results.Signals()) table.AddRow(TruthLevelCutRow(result, Tag::signal));
    for (auto const & result : results.Backgrounds()) table.AddRow(TruthLevelCutRow(result, Tag::background));
    table.AddCaption("Truth level cut efficiency");
    return table;
}

latex::Row PlottingBase::TruthLevelCutRow(Result const& result, Tag) const
{
    INFO0;
    latex::Row row(result.Info().LatexName().str(latex::Medium::latex));
    row.AddCell(RoundToDigits(static_cast<double>(result.TrainerSize()) / result.TrainerInfo().EventNumber()));
    return row;
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
    auto signal_x = signal.CoreData([](Vector3<double> const & vector_1, Vector3<double> const & vector_2) {
        return vector_1.X() < vector_2.X();
    });
    auto signal_y = signal.CoreData([](Vector3<double> const & vector_1, Vector3<double> const & vector_2) {
        return vector_1.Y() < vector_2.Y();
    });
    auto background_x = background.CoreData([](Vector3<double> const & vector_1, Vector3<double> const & vector_2) {
        return vector_1.X() < vector_2.X();
    });
    auto background_y = background.CoreData([](Vector3<double> const & vector_1, Vector3<double> const & vector_2) {
        return vector_1.Y() < vector_2.Y();
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
    profile.SetZAxis(latex::String("BDT_{") + signal.Title().LatexName() + "}", 30);
}

std::vector<Plots> PlottingBase::Import(Phase const& phase) const
{
    INFO(Tagger().FileName(phase), Tagger().TreeNames(phase).size());
    TFile file(Tagger().FileName(phase).c_str(), "Read");
    std::vector<Plots> results;
    for (auto const & tree_name : Tagger().TreeNames(phase)) results.emplace_back(PlotResult(file, tree_name, phase));
    return results;
}

Plots PlottingBase::PlotResult(TFile& file, std::string const& tree_name, Phase const& phase) const
{
    INFO0;
    Plots plots(Info(phase, tree_name).first);
    TTree& tree = static_cast<TTree&>(*file.Get(tree_name.c_str()));
    tree.SetMakeClass(true);
    plots.PlotVector() = UnorderedPairs(ConstCast(Tagger().Branch()).Variables().Vector(), [&](Observable const & variable_1, Observable const & variable_2) {
        auto plot = ReadTree(tree, variable_1.Name(), variable_2.Name(), phase.Stage());
        plot.x_is_int = variable_1.IsInt();
        plot.y_is_int = variable_2.IsInt();
        return plot;
    });
    plots.Names().SetName(tree_name);
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
    for (auto entry : IntegerRange(tree.GetEntries())) {
        DETAIL(tree.GetEntries(), entry);
        tree.GetEntry(entry);
        DETAIL(branch_size, leaf_values_1.size(), leaf_values_2.size());
        for (auto element : IntegerRange(branch_size)) plot.Add(Vector3<double>(leaf_values_1.at(element), leaf_values_2.at(element), bdt_values.at(element)));
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
    std::vector<boca::branch::Info> branches;
    for (auto const & tree_name : Tagger().TreeNames(phase)) {
        if (branches.size() < Tagger().TreeNames(phase).size()) branches.emplace_back(Info(phase, tree_name).first);
        auto& tree = static_cast<TTree&>(*file.Get(tree_name.c_str()));
        tree.SetMakeClass(true);
        auto plot = ReadTree2(tree, variable.Name());
        plot.x_is_int = variable.IsInt();
        plot.Title() = branches.at(Position(Tagger().TreeNames(phase), tree_name)).Names();
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
    for (auto entry : IntegerRange(tree.GetEntries())) {
        DETAIL(tree.GetEntries(), entry);
        tree.GetEntry(entry);
        for (auto element : IntegerRange(branch_size)) plot.Add(Vector3<double>(leaf_values.at(element), 0, 0));
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
    for (auto const & plot : plots.PlotVector()) histograms.AddHistogram(plot.XData(), plot.Title(), plots.XRange(), plot.x_is_int);
    histograms.SetLog();
    histograms.SetLegend(Orientation::outside | Orientation::right);
    histograms.SetYAxis(latex::String("N", true));
    histograms.SetXAxis(plots.Names().LatexName());
}

}
