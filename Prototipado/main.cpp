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
    struct FOE
    {
        float posXfoe;
        float posYfoe;
    };

    Font *font = new Font("data/monospaced.png");
    String text = "Score: ";
    int screenWidth = Screen::Instance().GetWidth();
    int screenHeight = Screen::Instance().GetHeight();
    int iPosXChar = screenWidth / 2;
    int iPosYChar = screenHeight - 80;
    int iCharWidth = 20;
    int iCharHeight = iCharWidth;
    //float posXfoe1 = screenWidth / 2;
    //float posYfoe1 = screenHeight / 2;
    int bounces = 1;
    int sizeChar = 1;
    const int iMaxFoes = 5;
    int arrayFoeVelX[iMaxFoes];
    int arrayFoeVelY[iMaxFoes];
    int counter;
    float timer = 0;

    FOE arrayFoes[iMaxFoes];

    for (unsigned int i = 0; i < iMaxFoes; i++)
    {
        arrayFoes[i].posXfoe = -1;
        arrayFoes[i].posYfoe = -1;
        arrayFoeVelX[i] = 0;
        arrayFoeVelY[i] = 0;
    }

    arrayFoes[0].posXfoe = 10;
    arrayFoes[0].posYfoe = 10;
    arrayFoeVelX[0] = rand() % 100 + 325;
    arrayFoeVelY[0] = rand() % 100 + 325;
    counter = 0;

    while (Screen::Instance().IsOpened() && !Screen::Instance().KeyPressed(GLFW_KEY_ESC)) {
        Screen::Instance().Clear();
        timer += Screen::Instance().ElapsedTime();
        Screen::Instance().SetTitle(String::FromFloat(timer));
        Renderer::Instance().SetColor(255,255,255,255);
        font->Render(text + String::FromInt(timer), 650, 5);

        switch (bounces)
        {
        case 5:
            counter = 1;
            arrayFoes[counter].posXfoe = 50;
            arrayFoes[counter].posYfoe = 50;
            arrayFoeVelX[counter] = rand() % 100 + 125;
            arrayFoeVelY[counter] = rand() % 100 + 125;
            break;
        case 8:
            counter = 2;
            arrayFoes[counter].posXfoe = 50;
            arrayFoes[counter].posYfoe = 50;
            arrayFoeVelX[counter] = rand() % 100 + 125;
            arrayFoeVelY[counter] = rand() % 100 + 125;
            break;
        case 10:
            counter = 3;
            arrayFoes[counter].posXfoe = 50;
            arrayFoes[counter].posYfoe = 50;
            arrayFoeVelX[counter] = rand() % 100 + 125;
            arrayFoeVelY[counter] = rand() % 100 + 125;
            break;
        case 12:
            counter = 4;
            arrayFoes[counter].posXfoe = 50;
            arrayFoes[counter].posYfoe = 50;
            arrayFoeVelX[counter] = rand() % 100 + 125;
            arrayFoeVelY[counter] = rand() % 100 + 125;
            break;
        case 15:
            counter = 5;
            arrayFoes[counter].posXfoe = 50;
            arrayFoes[counter].posYfoe = 50;
            arrayFoeVelX[counter] = rand() % 100 + 125;
            arrayFoeVelY[counter] = rand() % 100 + 125;
            break;
        default:
            break;
        }


        for (unsigned int i = 0; i < iMaxFoes; i++)
        {
            if (arrayFoes[i].posXfoe != -1 && arrayFoes[i].posYfoe != -1)
            {
                arrayFoes[i].posXfoe += arrayFoeVelX[i] * Screen::Instance().ElapsedTime();
                arrayFoes[i].posYfoe += arrayFoeVelY[i] * Screen::Instance().ElapsedTime();

                if (arrayFoes[i].posYfoe < 0.f)
                {
                    arrayFoes[i].posYfoe = 0.f;
                    arrayFoeVelY[i] *= -1;
                }
                else if (arrayFoes[i].posYfoe > screenHeight)
                {
                    arrayFoes[i].posYfoe = screenHeight;
                    arrayFoeVelY[i] *= -1;

                }
                else if (arrayFoes[i].posXfoe > screenWidth)
                {
                    arrayFoes[i].posXfoe = screenWidth;
                    arrayFoeVelX[i] *= -1;
                    bounces++;

                }
                else if (arrayFoes[i].posXfoe < 0.f)
                {
                    arrayFoes[i].posXfoe = 1.f;
                    arrayFoeVelX[i] *= -1;
                }
                Renderer::Instance().SetColor(255, 0, 0, 255);
                Renderer::Instance().DrawEllipse(arrayFoes[i].posXfoe, arrayFoes[i].posYfoe, 30, 30);
            }
        }

        if (Screen::Instance().KeyPressed('A'))
        {
            if (iPosXChar > 0)
                iPosXChar -= 5; 
        }
            
        if (Screen::Instance().KeyPressed('D'))
        {
            if ((iPosXChar + (iCharWidth)) < screenWidth)
                iPosXChar += 5;
        }

        if (Screen::Instance().KeyPressed('W'))
        {
            if (iPosYChar > 0 && iPosXChar < 100 || iPosXChar > 700)
                iPosYChar -= 5;
        }

        if (Screen::Instance().KeyPressed('S'))
        {
            if (iPosYChar + iCharHeight < screenHeight && iPosXChar < 100 || iPosXChar > 700)
                iPosYChar -= -5;
        }

        Renderer::Instance().SetColor(255, 255, 0, 255);
        Renderer::Instance().DrawRect(iPosXChar,iPosYChar,iCharWidth * bounces,iCharHeight);
       
        Screen::Instance().Refresh();
    }
    ResourceManager::Instance().FreeResources();
}
