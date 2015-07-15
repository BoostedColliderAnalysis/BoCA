# include "EflowAnalysis.hh"

# include <sys/stat.h>

# include "TTree.h"

# include "exroot/ExRootAnalysis.hh"

# include "Branches.hh"
# include "Event.hh"

# include "TClonesArray.h"
# include "TPad.h"
# include "TDirectoryFile.h"
# include "TTree.h"
# include "TCanvas.h"
# include "TMultiGraph.h"
# include "TLine.h"
# include "TStyle.h"
# include "TH1F.h"



namespace analysis {

namespace eflow
{

EflowAnalysis::EflowAnalysis(Tagger &tagger) : analysis::standardmodel::Analysis::Analysis(tagger)
{
   Print(Severity::notification, "Constructor");
}

void EflowAnalysis::SetFiles(const Tag tag)
{
     Print(Severity::notification, "Set File Vector", Name(tag));
    switch (tag) {
    case Tag::signal :
        NewSignalFile(tthad);
	break;
    case Tag::background :
        NewBackgroundFile(tthad);
        break;
    }
}

void EflowAnalysis::AnalysisMain()
{
    TCanvas canvas;
    TLegend legend = Legend(0.15, 0.85, 0.2, 0.4);
    std::vector<TH1F> histograms;
    int file_index=1;
    for (const auto & tag : std::vector<Tag> {Tag::background, Tag::signal}) {
        Print(Severity::notification, "Analysing Mva Sample", Name(tag));
        ClearFiles();
	SetFiles(tag);
        for (auto & file : Files(tag)) {
            ClonesArrays clones_arrays = file.clones_arrays();
            Event event = file.event();
            exroot::TreeReader tree_reader = file.TreeReader();
            clones_arrays.UseBranches(tree_reader);
	    int initial_number = 0;
	    TH1F histogram("JetNum", "", 50, 0.0, 6000.0);
            for (int event_number = initial_number; event_number< tree_reader.GetEntries()/10.0;++event_number) {
                tree_reader.ReadEntry(event_number);
                event.NewEvent(clones_arrays);
		int num_jet=0;
		Jets jets =  fastjet::sorted_by_pt(SetJetType(tag, event));
		for(auto &jet: jets){
		  if(jet.pt()>40)num_jet++;
//                   histogram.Fill(jet.pt());		  
		}
// 		histogram.Fill(num_jet);
 		histogram.Fill(jets.at(0).pt());
            }
            histogram.SetLineColor(file_index);
            histogram.SetLineStyle(file_index+2);
	    JetTypeName(tag);
	    Print(Severity::notification, "higogram filled", file_index);
	    file_index++;
            histograms.emplace_back(histogram);
        }
    }
    for (auto & histogram : histograms) {
        histogram.GetXaxis()->SetTitle("ttlep_jetNum");
        histogram.GetYaxis()->SetTitle("N");
	std::string name = nice_names_.at(&histogram - &histograms[0]);
        legend.AddEntry(&histogram,name.c_str(),"l");
        histogram.Draw("same");
    }
    legend.Draw();
    canvas.Print("LeadingJetPt_tthad.pdf");
  
}


TLegend EflowAnalysis::Legend(float x_min, float y_max, float width, float height, const std::string &name)
{
    TLegend legend(x_min, y_max - height, x_min + width, y_max);
    if(name != "") legend.SetHeader(name.c_str());
    legend.SetBorderSize(0);
    legend.SetFillStyle(0);
    return legend;
}


Jets EflowAnalysis::SetJetType(const Tag tag, Event &event)
{
    switch(tag){
    case Tag::signal :
      return static_cast<delphes::Hadrons &>(event.Hadrons()).ClusteredJets();
    case Tag::background :
      return static_cast<delphes::Hadrons &>(event.Hadrons()).DelphesJets(FourVector::kStructure);
  }
}

void EflowAnalysis::JetTypeName(const Tag tag)
{
  switch(tag){
    case Tag::signal :
      nice_names_.emplace_back("EFLow");
      break;
    case Tag::background:
      nice_names_.emplace_back("delphes");
      break;
  }
  
}

}

}
