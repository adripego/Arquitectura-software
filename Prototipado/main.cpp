//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"


void basica();
void avanzada();

int main(int argc, char* argv[]) {
    Screen::Instance().Open(800, 800, false);
    //basica();
    avanzada();
	return 0;
}

void basica()
{
    int screenWidth = Screen::Instance().GetWidth();
    int screenHeight = Screen::Instance().GetHeight();
    Font *font = new Font("data/monospaced.png");
    String *text = new String("Hola, mundo");
    double posX, posY, velX, velY;
    velX = rand() % 127 + 128;
    velY = rand() % 127 + 128;
    //velX = 128 + (rand() % static_cast<int>(255 - 128 + 1));
    //velY = 128 + (rand() % static_cast<int>(255 - 128 + 1));
    
    posX = Screen::Instance().GetWidth() / 2;
    posY = Screen::Instance().GetHeight() / 2;
    while (Screen::Instance().IsOpened() && !Screen::Instance().KeyPressed(GLFW_KEY_ESC)) {
        Screen::Instance().Clear();
        posX += velX * Screen::Instance().ElapsedTime();
        posY += velY * Screen::Instance().ElapsedTime();

        if ((posX + font->GetTextWidth(*text))  > Screen::Instance().GetWidth())
        {
           posX = Screen::Instance().GetWidth() - font->GetTextWidth(*text);
            velX *= -1;
            Renderer::Instance().SetColor(255 + rand() % (255 + 1), 255 + rand() % (255 + 1), 255 + rand() % (255 + 1), 255);
        }

        if (posX < 0)
        {
            posX = 0;
            velX *= -1;
            Renderer::Instance().SetColor(255 + rand() % (255 + 1), 255 + rand() % (255 + 1), 255 + rand() % (255 + 1), 255);
        }

        if ((posY + font->GetTextHeight(*text)) > Screen::Instance().GetHeight())
        {
            posY = Screen::Instance().GetHeight() - font->GetTextHeight(*text);
            velY *= -1;
            Renderer::Instance().SetColor(255 + rand() % (255 + 1), 255 + rand() % (255 + 1), 255 + rand() % (255 + 1), 255);
        }

        if (posY < 0)
        {
            posY = 0;
            velY *= -1;
            Renderer::Instance().SetColor(255 + rand() % (255 + 1), 255 + rand() % (255 + 1), 255 + rand() % (255 + 1), 255);
        }
        font->Render(*text, posX, posY);
        // Refrescamos la pantalla
        Screen::Instance().Refresh();
    }
    delete text;
    ResourceManager::Instance().FreeResources();
}

void avanzada()
{
    Font * font = new Font("data/arial16.png");
    String *text = new String("Hola, mundo");
    while (Screen::Instance().IsOpened() && !Screen::Instance().KeyPressed(GLFW_KEY_ESC)) {
        Screen::Instance().Clear();

        font->Render(*text,0,0);
        
        Screen::Instance().Refresh();
    }
    ResourceManager::Instance().FreeResources();
}
