
#include "Files.hh"
namespace boca
{
Files::Files(boca::Phase& phase, boca::File& file, TFile& export_file)
    : phase_(phase)
    , import_file_(file)
    , export_file_(export_file)
{
}
boca::Phase Files::Phase() const
{
    return phase_;
}
const boca::File& Files::Import() const
{
    return import_file_;
}
TFile& Files::Export()
{
    return export_file_;
}
}
