#include "boca/generic/Types.hh"
#include "boca/multivariant/Stage.hh"
#include "boca/generic/DEBUG.hh"
namespace boca
{
std::string Name(Stage stage)
{
    switch (stage) {
    case Stage::trainer : return "Trainer";
    case Stage::reader : return "Reader";
        DEFAULT(to_int(stage), "");
    }
}
}
