#include "boca/math/Matrix2.hh"
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

std::string Name(boca::Matrix matrix)
{
    switch (matrix) {
    case Matrix::diagonal : return "diagonal";
    case Matrix::symmetric : return "symmetric";
    case Matrix::antisymmetric : return "antisymmetric";
    case Matrix::row : return "row";
    case Matrix::column : return "column";
    case Matrix::uniform : return "uniform";
        DEFAULT(to_int(matrix), "");
    }
}

}
