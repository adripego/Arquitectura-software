//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"
#include <conio.h>

void prototype();

int main(int argc, char* argv[]) {
    Screen::Instance().Open(800, 800, false);
    prototype();
	return 0;
}

void prototype()
{
    int screenWidth = Screen::Instance().GetWidth();
    int screenHeight = Screen::Instance().GetHeight();
    int iPosXChar = screenWidth / 2;
    int iPosYChar = screenHeight - 80;
    float posXfoe1 = screenWidth / 2;
    float posYfoe1 = screenHeight / 2;
    int velY = 10;
    int velX = velY / 2;
    int bounces = 1;
    int sizeChar = 1;

    while (Screen::Instance().IsOpened() && !Screen::Instance().KeyPressed(GLFW_KEY_ESC)) {
        Screen::Instance().Clear();


        if (Screen::Instance().KeyPressed('A'))
        {
            if (iPosXChar > 0)
                iPosXChar -= 5; 
        }
            
        if (Screen::Instance().KeyPressed('D'))
        {
            if (iPosXChar <= screenWidth)
                iPosXChar += 5;
        }


       

            posXfoe1 += velX;
            posYfoe1 += velY;

        if (posYfoe1 < 0.f)
        {
            posYfoe1 = 0.f;
            velY *= -1;
        }
        else if (posYfoe1 > screenHeight)
        {
            posYfoe1 = screenHeight;
            velY *= -1;

        }
        else if (posXfoe1 > screenWidth)
        {
            posXfoe1 = screenWidth;
            velX *= -1;
            bounces++;

        }
        else if (posXfoe1 < 0.f)
        {
            posXfoe1 = 1.f;
            velX *= -1;
        }
 
        Screen::Instance().SetTitle(String::FromFloat(posYfoe1) + "posY | vely" + String::FromFloat(velY));
        
        Renderer::Instance().SetColor(255, 255, 0, 255);
        Renderer::Instance().DrawRect(iPosXChar,iPosYChar,20 * bounces,20);
        Renderer::Instance().SetColor(255,0,0,255);
        Renderer::Instance().DrawEllipse(posXfoe1, posYfoe1,30,30);
        Screen::Instance().Refresh();
    }
    ResourceManager::Instance().FreeResources();
}
