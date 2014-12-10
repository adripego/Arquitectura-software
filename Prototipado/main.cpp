//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"
#include <conio.h>


void mainmenu_init(void);
void mainmenu_run(void);
void playgame_init(void);
void playgame_run(void);
void igmenu_init(void);
void optmenu_run(void);

enum GameState
{
    GS_NULL,
    GS_MAIN_MENU,
    GS_PLAY_GAME,
    GS_OPT_MENU,
    GS_IG_MENU
};

struct FOE
{
    float posXfoe;
    float posYfoe;
};

int g_gameMode;

void EnterState(GameState st)
{
    // Terminate current state
    switch (g_gameMode)
    {
    case GS_MAIN_MENU:
        break;
    case GS_PLAY_GAME:
        break;
    case GS_OPT_MENU:
        break;
    case GS_IG_MENU:
        break;
    default:
        break;
    }

    // Init new state
    g_gameMode = GS_NULL;
    switch (st)
    {
    case GS_MAIN_MENU:
        mainmenu_init();
        break;
    case GS_PLAY_GAME:
        playgame_init();
        break;
    case GS_OPT_MENU:
        break;
    case GS_IG_MENU:
        break;
    default:
        break;
    }
    g_gameMode = st;
}


Font* g_font = new Font("data/monospaced.png");
int g_menu_opt;

int main(int argc, char* argv[]) {
    Screen::Instance().Open(800, 800, false);
    bool exit_game = false;
    EnterState(GS_MAIN_MENU);

    // && !Screen::Instance().KeyPressed(GLFW_KEY_ESC)
    while (Screen::Instance().IsOpened() && exit_game == false) {
        switch (g_gameMode)
        {
        case GS_MAIN_MENU:
            mainmenu_run();
            break;
        case GS_PLAY_GAME:
            playgame_run();
            break;
        case GS_IG_MENU:
            //igmenu_run();
            break;
        case GS_OPT_MENU:
           // optmenu_run();
            break;
        default:
            break;
        }
    }
    ResourceManager::Instance().FreeResources();
	return 0;
}

//-------------------------------------------------------------------
void mainmenu_init(void)
{
    g_menu_opt = 0;
}

void mainmenu_run()
{
    // procesar tecla
    //if (Screen::Instance().KeyPress(GLFW_KEY_UP))
    //{

    //}

    // pintar
    String mmenuText = "New Game\nOptions\nCredits\nExit Game";
    g_font->Render(mmenuText, Screen::Instance().GetWidth() / 2, Screen::Instance().GetHeight() / 2);
 
}

//-------------------------------------------------------------------


void playgame_init(void)
{
    Font *font = new Font("data/monospaced.png");
    String text = "Score: ";
    int screenWidth = Screen::Instance().GetWidth();
    int screenHeight = Screen::Instance().GetHeight();
    int iPosXChar = screenWidth / 2;
    int iPosYChar = screenHeight - 80;
    int iCharWidth = 20;
    int iCharHeight = iCharWidth;
    int bouncesH = 1;
    int bouncesV = 1;
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
}


void playgame_run(void)
{
  /*  g_gameMode = GS_PLAY_GAME;
    initGame();
    Screen::Instance().Clear();
    timer += Screen::Instance().ElapsedTime();
    Screen::Instance().SetTitle(String::FromFloat(timer));
    Renderer::Instance().SetColor(255, 255, 255, 255);
    font->Render(text + String::FromInt(timer), 650, 5);

    switch (bouncesH + bouncesV)
    {
    case 5:
        counter = 1;
        arrayFoes[counter].posXfoe = rand() % 100 + (screenWidth / 2);
        arrayFoes[counter].posYfoe = +(screenHeight / 2);
        arrayFoeVelX[counter] = rand() % 100 + 125;
        arrayFoeVelY[counter] = rand() % 100 + 125;
        break;
    case 8:
        counter = 2;
        arrayFoes[counter].posXfoe = rand() % 100 + (screenWidth / 2);
        arrayFoes[counter].posYfoe = rand() % 100 + (screenHeight / 2);
        arrayFoeVelX[counter] = rand() % 100 + 125;
        arrayFoeVelY[counter] = rand() % 100 + 125;
        break;
    case 10:
        counter = 3;
        arrayFoes[counter].posXfoe = rand() % 100 + (screenWidth / 2);
        arrayFoes[counter].posYfoe = rand() % 100 + (screenHeight / 2);
        arrayFoeVelX[counter] = rand() % 100 + 125;
        arrayFoeVelY[counter] = rand() % 100 + 125;
        break;
    case 12:
        counter = 4;
        arrayFoes[counter].posXfoe = rand() % 100 + (screenWidth / 2);
        arrayFoes[counter].posYfoe = rand() % 100 + (screenHeight / 2);
        arrayFoeVelX[counter] = rand() % 100 + 125;
        arrayFoeVelY[counter] = rand() % 100 + 125;
        break;
    case 15:
        counter = 5;
        arrayFoes[counter].posXfoe = rand() % 100 + (screenWidth / 2);
        arrayFoes[counter].posYfoe = rand() % 100 + (screenHeight / 2);
        arrayFoeVelX[counter] = rand() % 100 + 125;
        arrayFoeVelY[counter] = rand() % 100 + 125;
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
                bouncesV++;

            }
            else if (arrayFoes[i].posYfoe > screenHeight)
            {
                arrayFoes[i].posYfoe = screenHeight;
                arrayFoeVelY[i] *= -1;
                bouncesV++;


            }
            else if (arrayFoes[i].posXfoe > screenWidth)
            {
                arrayFoes[i].posXfoe = screenWidth;
                arrayFoeVelX[i] *= -1;
                bouncesH++;

            }
            else if (arrayFoes[i].posXfoe < 0.f)
            {
                arrayFoes[i].posXfoe = 1.f;
                arrayFoeVelX[i] *= -1;
                bouncesH++;
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
    Renderer::Instance().DrawRect(iPosXChar, iPosYChar, iCharWidth * bouncesH, iCharHeight + bouncesV);

    Screen::Instance().Refresh();*/
}
