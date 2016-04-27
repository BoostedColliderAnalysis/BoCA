/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/plotting/LatexFile.hh"
#include "boca/generic/DEBUG.hh"

namespace boca
{
LatexFile::LatexFile(std::string const& name)
{
    latex_file_.open(name + ".tex");
    latex_file_ << "\\documentclass[a4paper,11pt]{article}\n\n"
                << "\\usepackage{booktabs}\n"
                << "\\usepackage{graphicx}\n"
                << "\\usepackage{amsmath}\n"
                // << "\\usepackage[landscape]{geometry}\n"
                << "\\usepackage[cm]{fullpage}\n"
                << "\\usepackage{units}\n"
                // << "\\usepackage{siunitx}\n\n"
                // << "\\newcolumntype{R}{S[table-number-alignment = right, table-parse-only]}\n"
                // << "\\newcolumntype{L}{S[table-number-alignment = left,table-parse-only]}\n"
                // << "\\newcolumntype{E}{R@{$#pm$}L}\n"
//                     << "\\usepackage{tikz}\n"
//                     << "\\usetikzlibrary{patterns}\n"
//                     << "\\usetikzlibrary{plotmarks}\n"
                << "\\setcounter{topnumber}{0}\n"
                << "\\setcounter{bottomnumber}{6}\n"
                << "\\setcounter{totalnumber}{6}\n"
                << "\\renewcommand{\\bottomfraction}{1}\n"
                << "\\renewcommand{\\textfraction}{0}\n"
                << "\n\\begin{document}\n";
}

LatexFile::~LatexFile()
{
    latex_file_ << "\n\\end{document}\n";
    latex_file_.close();
}

void LatexFile::operator<<(std::string const& string)
{
    latex_file_ << string;
}

void LatexFile::IncludeGraphic(std::string const& file_name, std::string const& caption)
{
    latex_file_ << "\n\\begin{figure}\n\\centering\n\\includegraphics[width=0.5\\textwidth]{{{../" + file_name + "}}}\n\\caption{" + caption + ".}\n\\end{figure}\n";
//         return "\n\\begin{figure}\n\\centering\n\\scalebox{0.6}{\\input{" + file_name + "}}\n\\caption{" + caption + ".}\n\\end{figure}\n";
}

void LatexFile::IncludeGraphic(std::vector< std::string > const& file_names, std::string const& caption)
{
    for (auto const & name : file_names) IncludeGraphic(name, caption);
}

void LatexFile::Table(std::string const& header, std::string const& content, std::string const& caption)
{
    latex_file_ << "\n\\begin{table}\n\\centering\n\\begin{tabular}{" << header << "}\n    \\toprule\n";
    latex_file_ << content;
    latex_file_ << " \\bottomrule\n\\end{tabular}\n\\caption{" << caption << ".}\n\\end{table}\n";
}

void LatexFile::AddTable(LatexTable const& table)
{
  latex_file_ << table.Table();
}

void LatexFile::Mass(boca::Mass const& mass)
{
    INFO0;
    if (mass > massless) {
        std::stringstream mass_string;
        mass_string << boost::units::engineering_prefix << "\\section*{Mass = " << mass << "}\n";
        latex_file_ << mass_string.str();
    }
}

}

