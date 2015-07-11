#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <TApplication.h>
#include <TBox.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
#include <TLatex.h>
#include <TPaveStats.h>


// ****** Compilation command *************************************************
// g++ -o RootBdt2Dat `root-config --cflags` RootBdt2Dat.cpp `root-config --glibs`
// ****************************************************************************

// Usage  : ./convertTH1 rootFile.root histName

// Output : ASCII file with header and data.  Header contains ROOT
// file, histogram name, number of bins
// Following the header is the data in two columns for bin center and
// bin content.  All bins are included (including bins with zero
// counts).  Overflow and underflow bins are not included.

// If histogram is in directory, include the entire directory tree in
// the hist name.  For example "QDC/QDC_LowerPMT"

using namespace std;

void Help()
{
    cout << " ***** convertTH1 *****" << endl;
    cout << " You must provide two input parameters: " << endl;
    cout << "     1) Name of file containing histogram to convert" << endl;
    cout << "     2) Name of histogram to convert" << endl;
    cout << "  Output is a text file containing two columns: " << endl;
    cout << "     1) Center of X-bin" << endl;
    cout << "     2) Value of bin" << endl;
    cout << " **********************" << endl;

    exit(0); // normal
}

int main(int ArgumentNumber, char *ArgumentVector[])
{
    if (ArgumentNumber < 2) Help();

    string Name = ArgumentVector[1];
    string FileName = "Mva" + Name + ".root";
    string Name2 = ArgumentVector[2];
    if (Name2 == "") Name2 = Name;

    string BranchName = Name + "." + Name2 + "Tag";

    TApplication app("App", &ArgumentNumber, ArgumentVector);

    // cout << file_name << endl;
    // cout << hist_name << endl;

    TFile File(FileName.c_str(), "READ");
    if (File.IsZombie()) {
        cout << "Error opening file.  " << FileName << cout;
        cout << "Perhaps file not there or not closed correctly" << endl;
        return (1);
    }
    TTree *Tree = (TTree *)File.Get("TestTree");

    float Bdt, Tag;
    Tree->SetBranchAddress("Bdt", &Bdt);
    Tree->SetBranchAddress(BranchName.c_str(), &Tag);

    TH1F *Signal = new TH1F("Signal", "", 100, -1, 1);
    TH1F *Background = new TH1F("Background", "", 100, -1, 1);

    int Entries = Tree->GetEntries();
    for (int Entry = 0; Entry < Entries; ++Entry) {
        Tree->GetEntry(Entry);
        if (Tag)Signal->Fill(Bdt);
        else Background->Fill(Bdt);
    }


//     File.GetObject(BranchName, Signal);
    if (!Signal) {
        cout << "Sorry, histogram " << BranchName << " not found in file" << endl;
        return (1);
    }

//     char OutputFileName[500];
    string OutputFileName = Name + ".dat";
//     snprintf(OutputFileName.c_str(), sizeof(OutputFileName), "%s.hist", Signal->GetName());
    FILE *OutputFile;
    OutputFile = fopen(OutputFileName.c_str(), "w");
    cout << "Making output file: " << OutputFileName << endl;
    fprintf(OutputFile, "%s\t%s\t%d\n", FileName.c_str(), BranchName.c_str(), Signal->GetNbinsX());
    for (int Bin = 1; Bin <= Signal->GetNbinsX(); ++Bin) {
        fprintf(OutputFile, "%g\t%g\t%g\n",
                Signal -> GetBinCenter(Bin),
                Signal -> GetBinContent(Bin),
                Background -> GetBinContent(Bin)
               );
    }
    fclose(OutputFile);
    cout << "Output complete" << endl;
    return 0;
}




// void BdtData(std::string Name,std::string Name2)
// {
//
//   std::string file_name = "Mva" + Name + ".root";
//   if (Name2 == "") Name2 = Name;
//
//   std::string branch_name = Name + "." + Name2 + "Tag";
//
//   TFile file(file_name.c_str(), "READ");
//   if (file.IsZombie()) {
//     std::cout << "Error opening file.  " << file_name << std::cout;
//     std::cout << "Perhaps file not there or not closed correctly" << std::endl;
//     return;
//   }
//   TTree &tree = static_cast<TTree &>(*file.Get("TestTree"));
//
//   float bdt, tag;
//   tree.SetBranchAddress("Bdt", &bdt);
//   tree.SetBranchAddress(branch_name.c_str(), &tag);
//
//   TH1F signal("Signal", "", 100, -1, 1);
//   TH1F background("Background", "", 100, -1, 1);
//
//   for (int entry = 0; entry < tree.GetEntries(); ++entry) {
//     tree.GetEntry(entry);
//     if (tag)signal->Fill(bdt);
//     else background->Fill(bdt);
//   }
//
//   //     File.GetObject(BranchName, Signal);
//   if (!signal) {
//     std::cout << "Sorry, histogram " << branch_name << " not found in file" << std::endl;
//     return (1);
//   }
//
//   //     char OutputFileName[500];
//   std::string output_file_name = Name + ".dat";
//   //     snprintf(OutputFileName.c_str(), sizeof(OutputFileName), "%s.hist", Signal->GetName());
//   FILE *output_file;
//   output_file = fopen(output_file_name.c_str(), "w");
//   std::cout << "Making output file: " << output_file_name << std::endl;
//   fprintf(output_file, "%s\t%s\t%d\n", file_name.c_str(), branch_name.c_str(), signal->GetNbinsX());
//   for (int bin = 1; bin <= signal->GetNbinsX(); ++bin) {
//     fprintf(output_file, "%g\t%g\t%g\n",
//             signal -> GetBinCenter(Bin),
//             signal -> GetBinContent(Bin),
//             background -> GetBinContent(Bin)
//     );
//   }
//   fclose(output_file);
//   std::cout << "Output complete" << std::endl;
//   return ;
// }

