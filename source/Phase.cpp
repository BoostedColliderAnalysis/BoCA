#include "Phase.hh"
namespace boca
{
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
