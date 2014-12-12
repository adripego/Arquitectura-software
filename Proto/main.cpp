//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"
//#include "include/ecs.h"


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
const int iMaxFoes = 5;

struct Game
{
    String text;
    int iPosXChar;
    int iPosYChar;
    int iCharWidth;
    int iCharHeight;
    int bouncesH;
    int bouncesV;
    int sizeChar;
    int arrayFoeVelX[5];
    int arrayFoeVelY[5];
    int counter;
    float timer;
    FOE arrayFoes[5];
};

// Declaracion de variables globales
int g_gameMode;
uint16 screenWidth;
uint16 screenHeight;
Font* g_font;
int g_mmenu_opt;
int g_igmenu_opt;
int g_optmenu_opt;
Game game;
bool g_exitGame;

// Declaracion de funciones
void EnterState(GameState st);
void mainmenu_init(void);
void mainmenu_run(void);
void printMainMenu(int opt);
void playgame_init(void);
void playgame_run(void);
void igmenu_init(void);
void igmenu_run(void);
void exitGame(void);
void printIGMenu(int opt);
void printOPTMenu(int opt);
void optmenu_init();
void optmenu_run();

// Método encargado de finalizar el estado anterior e iniciar el nuevo estado
void EnterState(GameState st)
{
    // Terminate current state
    switch (g_gameMode)
    {
    case GS_MAIN_MENU:
        Screen::Instance().Clear();
        break;
    case GS_PLAY_GAME:
        //Screen::Instance().Clear();
        break;
    case GS_OPT_MENU:
        //Screen::Instance().Clear();
        break;
    case GS_IG_MENU:
        ResourceManager::Instance().FreeResources();
        //Screen::Instance().Clear();
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
        igmenu_init();
        break;
    default:
        break;
    }
    g_gameMode = st;
}


int main(int argc, char* argv[]) {
    Screen::Instance().Open(800, 800, false);
    EnterState(GS_MAIN_MENU);
    screenWidth =  Screen::Instance().GetWidth();
    screenHeight =  Screen::Instance().GetHeight();
    g_font = new Font("data/monospaced.png");
    g_exitGame = false;

    // Bucle principal
    while (Screen::Instance().IsOpened() && !Screen::Instance().KeyPressed(GLFW_KEY_ESC)) {
        Screen::Instance().Clear();

        while (Screen::Instance().IsOpened() && g_exitGame != true) {
            switch (g_gameMode)
            {
            case GS_MAIN_MENU:
                mainmenu_run();
                break;
            case GS_PLAY_GAME:
                playgame_run();
                break;
            case GS_OPT_MENU:
                optmenu_run();
                break;
            case GS_IG_MENU:
                igmenu_run();
                break;
            default:
                break;
            }
            Screen::Instance().Refresh();
        }
        ResourceManager::Instance().FreeResources();
        return 0;
    }
}

// Inicializacion  del menu principal
void mainmenu_init(void)
{
    g_mmenu_opt = 0;
}

void mainmenu_run()
{
    Screen::Instance().SetTitle(String("menu opt: ") + String::FromInt(g_mmenu_opt));
    Renderer::Instance().SetColor(0,0,0,255);
    Renderer::Instance().DrawRect(0,0,screenWidth, screenHeight);
    Renderer::Instance().SetColor(255, 255, 255, 0);
    switch (g_mmenu_opt)
    {
    case 0:
        printMainMenu(0);
        break;
    case 1:
        printMainMenu(1);
        break;
    case 2:
        printMainMenu(2);
        break;
    case 3:
        printMainMenu(3);
        break;
    default:
        break;
    }

    if (Screen::Instance().KeyOnce(GLFW_KEY_DOWN))
    {
        if (g_mmenu_opt < 3)
        {
            g_mmenu_opt++;
        }
    }
    else if (Screen::Instance().KeyPressedOnce(GLFW_KEY_UP))
    {
        if (g_mmenu_opt > 0)
        {
            g_mmenu_opt--;
        }
    }
    else if (Screen::Instance().KeyPressedOnce(GLFW_KEY_ENTER))
    {
        switch (g_mmenu_opt)
        {
        case 0:
            EnterState(GS_PLAY_GAME);
            break;
        case 1:
            EnterState(GS_OPT_MENU);
            break;
        case 2:
            break;
        case 3:
            exitGame();
            break;
        default:
            break;
        }
    }
}


void printMainMenu(int opt)
{
    switch (opt)
    {
    case 0:
        Renderer::Instance().SetColor(255,0,0,255);
        g_font->Render("New Game", 30, screenHeight / 2);
        Renderer::Instance().SetColor(255, 255, 255, 255);
        g_font->Render("Options", 30, screenHeight / 2 + 20);
        g_font->Render("Credits", 30, screenHeight / 2 + 40);
        g_font->Render("Exit Game", 30, screenHeight / 2 + 60);
        break;
    case 1:
        Renderer::Instance().SetColor(255, 255, 255, 255);
        g_font->Render("New Game", 30, screenHeight / 2);
        Renderer::Instance().SetColor(255, 0, 0, 255);
        g_font->Render("Options", 30, screenHeight / 2 + 20);
        Renderer::Instance().SetColor(255, 255, 255, 255);
        g_font->Render("Credits", 30, screenHeight / 2 + 40);
        g_font->Render("Exit Game", 30, screenHeight / 2 + 60);
        break;
    case 2:
        Renderer::Instance().SetColor(255, 255, 255, 255);

        g_font->Render("New Game", 30, screenHeight / 2);
        g_font->Render("Options", 30, screenHeight / 2 + 20);
        Renderer::Instance().SetColor(255, 0, 0, 255);
        g_font->Render("Credits", 30, screenHeight / 2 + 40);
        Renderer::Instance().SetColor(255, 255, 255, 255);
        g_font->Render("Exit Game", 30, screenHeight / 2 + 60);
        break;
    case 3:
        Renderer::Instance().SetColor(255, 255, 255, 255);
        g_font->Render("New Game", 30, screenHeight / 2);
        g_font->Render("Options", 30, screenHeight / 2 + 20);
        g_font->Render("Credits", 30, screenHeight / 2 + 40);
        Renderer::Instance().SetColor(255, 0, 0, 255);
        g_font->Render("Exit Game", 30, screenHeight / 2 + 60);
        break;

    default:
        break;
    }
}

void printIGMenu(int opt)
{
    switch (opt)
    {
    case 0:
        Renderer::Instance().SetColor(255, 0, 0, 255);
        g_font->Render("Resume Game", 30, screenHeight / 2);
        Renderer::Instance().SetColor(255, 255, 255, 255);
        g_font->Render("Restart Game", 30, screenHeight / 2 + 20);
        g_font->Render("Options", 30, screenHeight / 2 + 40);
        g_font->Render("Exit Level", 30, screenHeight / 2 + 60);
        break;
    case 1:
        Renderer::Instance().SetColor(255, 255, 255, 255);
        g_font->Render("Resume Game", 30, screenHeight / 2);
        Renderer::Instance().SetColor(255, 0, 0, 255);
        g_font->Render("Restart Game", 30, screenHeight / 2 + 20);
        Renderer::Instance().SetColor(255, 255, 255, 255);
        g_font->Render("Options", 30, screenHeight / 2 + 40);
        g_font->Render("Exit Level", 30, screenHeight / 2 + 60);
        break;
    case 2:
        Renderer::Instance().SetColor(255, 255, 255, 255);

        g_font->Render("Resume Game", 30, screenHeight / 2);
        g_font->Render("Restart Game", 30, screenHeight / 2 + 20);
        Renderer::Instance().SetColor(255, 0, 0, 255);
        g_font->Render("Options", 30, screenHeight / 2 + 40);
        Renderer::Instance().SetColor(255, 255, 255, 255);
        g_font->Render("Exit Level", 30, screenHeight / 2 + 60);
        break;
    case 3:
        Renderer::Instance().SetColor(255, 255, 255, 255);
        g_font->Render("Resume Game", 30, screenHeight / 2);
        g_font->Render("Restart Game", 30, screenHeight / 2 + 20);
        g_font->Render("Options", 30, screenHeight / 2 + 40);
        Renderer::Instance().SetColor(255, 0, 0, 255);
        g_font->Render("Exit Level", 30, screenHeight / 2 + 60);
        break;

    default:
        break;
    }
}

void playgame_init(void)
{
    //Entity* Character = new Entity();
    //Character->addComponent(C_Renderable);

    game.text = "Score: ";
    game.iPosXChar = screenWidth / 2;
    game.iPosYChar = screenHeight - 80;
    game.iCharWidth = 20;
    game.iCharHeight = game.iCharWidth;
    game.bouncesH = 1;
    game.bouncesV = 1;
    game.sizeChar = 1;
    //const int iMaxFoes = 5;
    //game.counter;
    game.timer = 0;

    for (unsigned int i = 0; i < 5; i++)
    {
        game.arrayFoes[i].posXfoe = -1;
        game.arrayFoes[i].posYfoe = -1;
        game.arrayFoeVelX[i] = 0;
        game.arrayFoeVelY[i] = 0;
    }

    game.arrayFoes[0].posXfoe = 10;
    game.arrayFoes[0].posYfoe = 10;
    game.arrayFoeVelX[0] = rand() % 100 + 325;
    game.arrayFoeVelY[0] = rand() % 100 + 325;
    game.counter = 0;
}

void playgame_run(void)
{
    Screen::Instance().Clear();
    game.timer += Screen::Instance().ElapsedTime();
    Screen::Instance().SetTitle(String::FromInt(game.bouncesV) + "V H" + String::FromInt(game.bouncesH));
    Renderer::Instance().SetColor(255, 255, 255, 255);

    switch (game.bouncesH + game.bouncesV)
    {
    case 5:
        game.counter = 1;
        game.arrayFoes[game.counter].posXfoe = rand() % 100 + (screenWidth / 2);
        game.arrayFoes[game.counter].posYfoe = +(screenHeight / 2);
        game.arrayFoeVelX[game.counter] = rand() % 100 + 125;
        game.arrayFoeVelY[game.counter] = rand() % 100 + 125;
        break;
    case 8:
        game.counter = 2;
        game.arrayFoes[game.counter].posXfoe = rand() % 100 + (screenWidth / 2);
        game.arrayFoes[game.counter].posYfoe = rand() % 100 + (screenHeight / 2);
        game.arrayFoeVelX[game.counter] = rand() % 100 + 125;
        game.arrayFoeVelY[game.counter] = rand() % 100 + 125;
        break;
    case 10:
        game.counter = 3;
        game.arrayFoes[game.counter].posXfoe = rand() % 100 + (screenWidth / 2);
        game.arrayFoes[game.counter].posYfoe = rand() % 100 + (screenHeight / 2);
        game.arrayFoeVelX[game.counter] = rand() % 100 + 125;
        game.arrayFoeVelY[game.counter] = rand() % 100 + 125;
        break;
    case 12:
        game.counter = 4;
        game.arrayFoes[game.counter].posXfoe = rand() % 100 + (screenWidth / 2);
        game.arrayFoes[game.counter].posYfoe = rand() % 100 + (screenHeight / 2);
        game.arrayFoeVelX[game.counter] = rand() % 100 + 125;
        game.arrayFoeVelY[game.counter] = rand() % 100 + 125;
        break;
    case 15:
        game.counter = 5;
        game.arrayFoes[game.counter].posXfoe = rand() % 100 + (screenWidth / 2);
        game.arrayFoes[game.counter].posYfoe = rand() % 100 + (screenHeight / 2);
        game.arrayFoeVelX[game.counter] = rand() % 100 + 125;
        game.arrayFoeVelY[game.counter] = rand() % 100 + 125;
        break;
    }


    for (unsigned int i = 0; i < 5; i++)
    {
        if (game.arrayFoes[i].posXfoe != -1 && game.arrayFoes[i].posYfoe != -1)
        {
            game.arrayFoes[i].posXfoe += game.arrayFoeVelX[i] * Screen::Instance().ElapsedTime();
            game.arrayFoes[i].posYfoe += game.arrayFoeVelY[i] * Screen::Instance().ElapsedTime();

            if (game.arrayFoes[i].posYfoe < 0.f)
            {
                game.arrayFoes[i].posYfoe = 0.f;
                game.arrayFoeVelY[i] *= -1;
                game.bouncesV++;

            }
            else if (game.arrayFoes[i].posYfoe > screenHeight)
            {
                game.arrayFoes[i].posYfoe = screenHeight;
                game.arrayFoeVelY[i] *= -1;
                game.bouncesV++;


            }
            else if (game.arrayFoes[i].posXfoe > screenWidth)
            {
                game.arrayFoes[i].posXfoe = screenWidth;
                game.arrayFoeVelX[i] *= -1;
                game.bouncesH++;

            }
            else if (game.arrayFoes[i].posXfoe < 0.f)
            {
                game.arrayFoes[i].posXfoe = 1.f;
                game.arrayFoeVelX[i] *= -1;
                game.bouncesH++;
            }
            Renderer::Instance().SetColor(255, 0, 0, 255);
            Renderer::Instance().DrawEllipse(game.arrayFoes[i].posXfoe, game.arrayFoes[i].posYfoe, 30, 30);
        }

    }

    if (Screen::Instance().KeyPressed('A'))
    {
        if (game.iPosXChar > 0)
            game.iPosXChar -= 5;
    }
    else if (Screen::Instance().KeyPressed('D'))
    {
        if ((game.iPosXChar + (game.iCharWidth)) < screenWidth)
            game.iPosXChar += 5;
    }
    else if (Screen::Instance().KeyPressed('W'))
    {
        if (game.iPosYChar > 0 && game.iPosXChar < 100 || game.iPosXChar > 700)
            game.iPosYChar -= 5;
    }
    else if (Screen::Instance().KeyPressed('S'))
    {
        if (game.iPosYChar + game.iCharHeight < screenHeight && game.iPosXChar < 100 || game.iPosXChar > 700)
            game.iPosYChar -= -5;
    }
    else if (Screen::Instance().KeyPressed(GLFW_KEY_ESC))
    {
        EnterState(GS_IG_MENU);
    }

    Renderer::Instance().SetColor(255, 255, 0, 255);
    Renderer::Instance().DrawRect(game.iPosXChar, game.iPosYChar, game.iCharWidth * (game.bouncesH / 2) + 1, game.iCharHeight * (game.bouncesV / 2) + 1);
    Renderer::Instance().SetColor(250, 250, 250, 255);
    g_font->Render(game.text + String::FromInt(game.timer), 600, 10);

}


void igmenu_init(void)
{

}

void igmenu_run(void)
{
    //Renderer::Instance().SetColor(255, 255, 255, 0);
    switch (g_igmenu_opt)
    {
    case 0:
        printIGMenu(0);
        break;
    case 1:
        printIGMenu(1);
        break;
    case 2:
        printIGMenu(2);
        break;
    case 3:
        printIGMenu(3);
        break;
    default:
        break;
    }

    if (Screen::Instance().KeyOnce(GLFW_KEY_DOWN))
    {
        if (g_igmenu_opt < 3)
        {
            g_igmenu_opt++;
        }
    }
    else if (Screen::Instance().KeyPressedOnce(GLFW_KEY_UP))
    {
        if (g_igmenu_opt > 0)
        {
            g_igmenu_opt--;
        }
    }
    else if (Screen::Instance().KeyPressedOnce(GLFW_KEY_ENTER))
    {
        switch (g_igmenu_opt)
        {
        case 0:
            break;
        case 1:
            EnterState(GS_PLAY_GAME);
            break;
        case 2:
            break;
        case 3:
            EnterState(GS_MAIN_MENU);
            break;
        default:
            break;
        }
    }
}


void printOPTMenu(int opt)
{
    switch (opt)
    {
    case 0:
        Renderer::Instance().SetColor(255, 0, 0, 255);
        g_font->Render("Music", 30, screenHeight / 2);
        Renderer::Instance().SetColor(255, 255, 255, 255);
        g_font->Render("SFX", 30, screenHeight / 2 + 20);
        g_font->Render("Game Speed", 30, screenHeight / 2 + 40);
        g_font->Render("Exit Options", 30, screenHeight / 2 + 60);
        break;
    case 1:
        Renderer::Instance().SetColor(255, 255, 255, 255);
        g_font->Render("Music", 30, screenHeight / 2);
        Renderer::Instance().SetColor(255, 0, 0, 255);
        g_font->Render("SFX", 30, screenHeight / 2 + 20);
        Renderer::Instance().SetColor(255, 255, 255, 255);
        g_font->Render("Game Speed", 30, screenHeight / 2 + 40);
        g_font->Render("Exit Options", 30, screenHeight / 2 + 60);
        break;
    case 2:
        Renderer::Instance().SetColor(255, 255, 255, 255);

        g_font->Render("Music", 30, screenHeight / 2);
        g_font->Render("SFX", 30, screenHeight / 2 + 20);
        Renderer::Instance().SetColor(255, 0, 0, 255);
        g_font->Render("Game Speed", 30, screenHeight / 2 + 40);
        Renderer::Instance().SetColor(255, 255, 255, 255);
        g_font->Render("Exit Options", 30, screenHeight / 2 + 60);
        break;
    case 3:
        Renderer::Instance().SetColor(255, 255, 255, 255);
        g_font->Render("Music", 30, screenHeight / 2);
        g_font->Render("SFX", 30, screenHeight / 2 + 20);
        g_font->Render("Game Speed", 30, screenHeight / 2 + 40);
        Renderer::Instance().SetColor(255, 0, 0, 255);
        g_font->Render("Exit Options", 30, screenHeight / 2 + 60);
        break;

    default:
        break;
    }
}

void optmenu_init(void)
{
    g_optmenu_opt = 0;
}

void optmenu_run(void)
{
    Renderer::Instance().SetColor(0, 0, 0, 255);
    Renderer::Instance().DrawRect(0, 0, screenWidth, screenHeight);
    switch (g_optmenu_opt)
    {
    case 0:
        printOPTMenu(0);
        break;
    case 1:
        printOPTMenu(1);
        break;
    case 2:
        printOPTMenu(2);
        break;
    case 3:
        printOPTMenu(3);
        break;
    default:
        break;
    }

    if (Screen::Instance().KeyOnce(GLFW_KEY_DOWN))
    {
        if (g_optmenu_opt < 3)
        {
            g_optmenu_opt++;
        }
    }
    else if (Screen::Instance().KeyPressedOnce(GLFW_KEY_UP))
    {
        if (g_optmenu_opt > 0)
        {
            g_optmenu_opt--;
        }
    }
    else if (Screen::Instance().KeyPressedOnce(GLFW_KEY_ENTER))
    {
        if (g_optmenu_opt == 3)        EnterState(GS_MAIN_MENU);
    }
    else if (Screen::Instance().KeyPressedOnce(GLFW_KEY_RIGHT))
    {

    }
}


void exitGame(void)
{
    g_exitGame = true;
}