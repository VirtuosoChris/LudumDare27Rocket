#include "Texture.h"
#include "stb_image.h"
#include <iostream>

#include <stdexcept>

void Texture::bind()
{

    glBindTexture(GL_TEXTURE_2D, tex->tex);

}



void Texture::subImage(const unsigned char* data)
{

    GLenum formats[4]= {GL_LUMINANCE, GL_LUMINANCE_ALPHA, GL_RGB, GL_RGBA};

    glTexSubImage2D(GL_TEXTURE_2D,  0,  0, 0,w, h,  formats[ch-1],  GL_UNSIGNED_BYTE,data);

}

Texture::Texture(int widthIn, int heightIn, int channelsIn)
:tex(new TexRsc()),
w(widthIn),h(heightIn), ch(channelsIn)
{

        glGenTextures(1,&(tex->tex) );

         std::cout<<"tex genned"<<std::endl;

        glBindTexture(GL_TEXTURE_2D, tex->tex);

         std::cout<<"tex bound"<<std::endl;

        GLenum formats[4]= {GL_LUMINANCE, GL_LUMINANCE_ALPHA, GL_RGB, GL_RGBA};

        std::cout<<"formats built"<<std::endl;

        std::cout<<"chs "<<ch<<std::endl;


        glTexImage2D(GL_TEXTURE_2D, 0, formats[ch-1], w, h, 0, formats[ch-1], GL_UNSIGNED_BYTE, 0);


        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);



    }



Texture::Texture(const char* texture)
    :tex(new TexRsc())
{

    unsigned char* data = stbi_load(texture, &w, &h, &ch, 0);
    if(data)
    {

        std::cout<<"Loaded texture "<<texture<<" with dimensions "<<w<<","<<h<<'\n';

        glGenTextures(1,&(tex->tex) );

         std::cout<<"tex genned"<<std::endl;

        glBindTexture(GL_TEXTURE_2D, tex->tex);

         std::cout<<"tex bound"<<std::endl;

        GLenum formats[4]= {GL_LUMINANCE, GL_LUMINANCE_ALPHA, GL_RGB, GL_RGBA};

       if(gluBuild2DMipmaps(GL_TEXTURE_2D, formats[ch-1],w,h,formats[ch-1],GL_UNSIGNED_BYTE,data)){
        throw std::runtime_error("Failed to generate mipmaps");
       }

        std::cout<<"mips built"<<std::endl;

        stbi_image_free(data);

         std::cout<<"data freed"<<std::endl;

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

             std::cout<<"tex params set"<<std::endl;


    std::cout<<"Left texture ctor"<<std::endl;

}
else{

std::cout<<"Unable to load "<<texture<<std::endl;
}
}
