#include "../include/image.h"
#include "../include/glinclude.h"
#include "../include/math.h"
#include <math.h>
#include <stdlib.h>
#include "../include/renderer.h"

// TAREA: Declarar funciones de stb_image.c

extern "C"
{
    unsigned char *stbi_load(char const *filename, int *x, int *y, int *comp, int req_comp);
    void stbi_image_free(void *buffer);
}


Image::Image(const String &filename, uint16 hframes, uint16 vframes) {
	this->filename = filename;
	this->hframes = hframes;
	this->vframes = vframes;
	width = 0;
	height = 0;
	handlex = 0;
	handley = 0;
	gltex = 0;
	lastU = 1.0;
	lastV = 1.0;
    unsigned char *buffer;
    int comp;

	// TAREA: Cargar el buffer de la imagen
    buffer = stbi_load(filename.ToCString(), reinterpret_cast<int *>(&width), reinterpret_cast<int *>(&height), &comp, 4);
	// Generamos la textura
   
	if ( buffer ) {
        newWidth = static_cast<uint16>(pow(2, ceil(Log2(width))));
		newHeight = static_cast<uint16>(pow(2, ceil(Log2(height))));

		// TAREA: Generar la textura de OpenGL
        if (newWidth != width || newHeight != height)
        {
            unsigned char *newBuffer = static_cast<unsigned char*>(malloc(newWidth*newHeight*4));     // 65536 
            int fullNewWidth = newWidth * 4;
            int fullOldWidth = width * 4;
            
            for (unsigned int  i = 0; i < height; i++)
            {
                  //  newBuffer[i] = buffer[i];
                memcpy(&newBuffer[fullNewWidth * i], &buffer[fullOldWidth * i], fullOldWidth);
                
            }

			lastU = static_cast<double>(width) / static_cast<double>(newWidth);
			lastV = static_cast<double>(height) / static_cast<double>(newHeight);
            gltex = Renderer::Instance().GenImage(newBuffer, newWidth, newHeight);
        }
        else
        {
            gltex = Renderer::Instance().GenImage(buffer, width, height);
        }
	}
}

Image::~Image() {
	// TAREA: Eliminar la imagen de la memoria de OpenGL    
    Renderer::Instance().DeleteImage(gltex);
}

void Image::Bind() const {
	// TAREA: Establecer la textura actual
    Renderer::Instance().BindImage(gltex);
}
