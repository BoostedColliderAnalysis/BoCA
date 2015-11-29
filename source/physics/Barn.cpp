#include "physics/Barn.hh"


namespace boca
{

float to_float(Crosssection crosssection)
{
  return crosssection / fb;
}

Crosssection to_crosssection(float crosssection)
{
  return double(crosssection) * fb;
}

float to_float(Luminosity luminosity)
{
  return (luminosity * fb);
}

Luminosity to_luminosity(float luminosity)
{
  return double(luminosity) / fb;
}

}
