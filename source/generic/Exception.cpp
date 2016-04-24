#include "boca/generic/Exception.hh"

namespace boca
{

char const* Problematic::what() const throw ()
{
    return ("Problematic Multiplet: " + arg_).c_str();
}

char const* Overlap::what() const throw ()
{
    return "Overlaping Multiplet";
}

char const* Empty::what() const throw ()
{
    return "Empty or too small container";
}

char const* Isolated::what() const throw ()
{
    return "not isolated";
}

}

