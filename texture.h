#ifndef TEXTURE_H
#define TEXTURE_H

#include <QOpenGLFunctions>

//! \brief Simple class for creating textures from a bitmap file.
//! \author Dag Nylund
//! \date 16/02/05
//!

class Texture : protected QOpenGLFunctions
{
private:
    GLubyte pixels[12];
    GLuint mId;
    unsigned char *mBitmap;
    int mColumns;
    int mRows;
    int mnByte;
    void readBitmap(const std::string& filename);
    void setTexture();
public:
    Texture();
    Texture(const QString& filename);
    GLuint id() const;
};

#endif // TEXTURE_H
