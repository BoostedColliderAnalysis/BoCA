#include  "LatexFile.hh"
#include  "Debug.hh"

namespace boca
{
LatexFile::LatexFile(const std::string& name)
{
    latex_file_.open(name + ".tex");
    latex_file_ << "\\documentclass[a4paper,11pt]{article}\n\n"
                << "\\usepackage{booktabs}\n"
                << "\\usepackage{graphicx}\n"
                // << "\\usepackage[landscape]{geometry}\n"
                << "\\usepackage[cm]{fullpage}\n"
                << "\\usepackage{units}\n"
                // << "\\usepackage{siunitx}\n\n"
                // << "\\newcolumntype{R}{S[table-number-alignment = right, table-parse-only]}\n"
                // << "\\newcolumntype{L}{S[table-number-alignment = left,table-parse-only]}\n"
                // << "\\newcolumntype{E}{R@{$\\pm$}L}\n"
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
void LatexFile::operator<<(const std::string& string)
{
    latex_file_ << string;
}
void LatexFile::IncludeGraphic(std::string file_name, std::string caption)
{
    latex_file_ << "\n\\begin{figure}\n\\centering\n\\includegraphics[width=0.5\\textwidth]{../" + file_name + "}\n\\caption{" + caption + ".}\n\\end{figure}\n";
//         return "\n\\begin{figure}\n\\centering\n\\scalebox{0.6}{\\input{" + file_name + "}}\n\\caption{" + caption + ".}\n\\end{figure}\n";
}
void LatexFile::Table(const std::string& header, const std::string& content, std::string caption)
{
    latex_file_ << "\n\\begin{table}\n\\centering\n\\begin{tabular}{" << header << "}\n    \\toprule\n";
    latex_file_ << content;
    latex_file_ << " \\bottomrule\n\\end{tabular}\n\\caption{" << caption << ".}\n\\end{table}\n";
}
std::string LatexFile::Mass(boca::Mass mass) const
{
    Info();
    std::stringstream mass_string;
    if (mass > massless) {
        mass_string << boost::units::engineering_prefix << "\\section*{Mass = " << mass << "}\n";
    }
    return mass_string.str();
}
}

