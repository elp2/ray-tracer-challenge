#include "primitives/matrix.h"
#include "primitives/transformation.h"

Matrix Translation(float x, float y, float z) {
    Matrix translation = IdentityMatrix(4);
    translation.Set(x, 0, 3);
    translation.Set(y, 1, 3);
    translation.Set(z, 2, 3);

    return translation;
}
