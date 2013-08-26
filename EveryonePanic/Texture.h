#ifndef TEXTURE_FL_GAME_H_INCLUDED
#define TEXTURE_FL_GAME_H_INCLUDED


#include <GL/freeglut.h>
#include <memory>

struct TexRsc
{
    GLuint tex;

    TexRsc():tex(0) {}

    ~TexRsc()
    {
        if(tex)
            glDeleteTextures(1, &tex);
    }
};

struct Texture
{

    int w;
    int h;
    int ch;

    std::shared_ptr<TexRsc> tex;

    Texture(const char* file);


    operator bool()
    {
        return tex->tex;
    }

    Texture()
        :w(0),h(0),ch(0),tex(new TexRsc())
    {

    }

    Texture(int widthIn, int heightIn, int channelsIn);

    bool operator<(const Texture& in)const
    {
        return tex->tex < in.tex->tex;
    }

    void bind();

    void subImage(const unsigned char* data);

};

#endif
