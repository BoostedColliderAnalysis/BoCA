#include "Phase.hh"
#include "DEBUG.hh"
#include "Types.hh"
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
Phase::Phase(boca::Stage stage, boca::Tag tag)
{
    stage_ = stage;
    tag_ = tag;
}
boca::Stage Phase::Stage() const
{
    return stage_;
}
boca::Tag Phase::Tag() const
{
    return tag_;
}
}
