#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

namespace gsl //Game school lib
{

    const std::string assetFilePath = "../3D-programming/assets/";
    const std::string shaderFilePath = "../3D-programming/";

    enum ShaderTypes
    {
      COLOR,
      TEXTURE,
      COLORLIGHT,
      TEXTURELIGHT
    };

}

#endif // CONSTANTS_H
