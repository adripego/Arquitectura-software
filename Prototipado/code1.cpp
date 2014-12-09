#include "stdafx.h"
#include "code1.h"
#include "sys.h"
#include "core.h"

#define SCR_WIDTH  640
#define SCR_HEIGHT 480
#define SCR_FULLSCREEN 0


//=============================================================================
// Sprites engine
enum TexId
{
  T_FONT
};

struct Sprite
{
  char   name[100];
  bool   wrap;
  GLuint tex;
};

Sprite sprites[] =
{
  { "data/kromasky.32.bmp" , false, 0 },
};

void LoadSprites()
{
  for (int i = 0; i < SIZE_ARRAY(sprites); i++)
    sprites[i].tex = CORE_LoadBmp(sprites[i].name, true);
}

void UnloadSprites()
{
  for (int i = 0; i < SIZE_ARRAY(sprites); i++)
    CORE_UnloadBmp(sprites[i].tex);
}

GLuint Tex(TexId id)
{
  return sprites[id].tex;
}

//=============================================================================
// Font support
#define FONT_ROWS 8
#define FONT_COLS 8
#define MAX_FONT_CHARDEFS 256
#define FONT_CHAR_WIDTH (16.f/128.f)
#define FONT_CHAR_HEIGHT (16.f/128.f)

char fontdef[FONT_ROWS][FONT_COLS+1] =
{
  { " !\"~*%-'" },
  { "   +, ./" },
  { "01234567" },
  { "89:;aib?" },
  { "*ABCDEFG" },
  { "HIJKLMNO" },
  { "PQRSTUVW" },
  { "XYZ     " },
};

struct FontCharDef
{
  char ch;
  vec2 p0;
};

FontCharDef fontchardefs[MAX_FONT_CHARDEFS] = { 0 };

//-----------------------------------------------------------------------------
void PrepareFont()
{
  for (int i = 0; i < FONT_ROWS; i++) // One iteration per row
  {
    for (int j = 0; j < FONT_COLS; j++) // Inside row
    {
      unsigned char ch = fontdef[i][j];
      fontchardefs[ch].ch = ch;
      fontchardefs[ch].p0 = vmake(j * FONT_CHAR_WIDTH, (FONT_ROWS - i - 1) * FONT_CHAR_HEIGHT);
    }
  }
}

//-----------------------------------------------------------------------------
void DrawChar(vec2 p0, vec2 p1, unsigned char ch)
{
  if (ch < MAX_FONT_CHARDEFS && fontchardefs[ch].ch == ch)
  {
    glBindTexture( GL_TEXTURE_2D, Tex(T_FONT) );
    glBegin( GL_QUADS );
    glTexCoord2d(fontchardefs[ch].p0.x                  , fontchardefs[ch].p0.y                   ); glVertex2f(p0.x, p0.y);
    glTexCoord2d(fontchardefs[ch].p0.x + FONT_CHAR_WIDTH, fontchardefs[ch].p0.y                   ); glVertex2f(p1.x, p0.y);
    glTexCoord2d(fontchardefs[ch].p0.x + FONT_CHAR_WIDTH, fontchardefs[ch].p0.y + FONT_CHAR_HEIGHT); glVertex2f(p1.x, p1.y);
    glTexCoord2d(fontchardefs[ch].p0.x                  , fontchardefs[ch].p0.y + FONT_CHAR_HEIGHT); glVertex2f(p0.x, p1.y);
    glEnd();
  }
}

//-----------------------------------------------------------------------------
void DrawString(vec2 p0, const char string[])
{
  int n = (int)strlen(string);
  for (int i = 0; i < n; i++)
  {
    DrawChar(p0, vadd(p0, vmake(16.f, 16.f)), string[i]);
    p0 = vadd(p0, vmake(16.f, 0.f));
  }
}


//-----------------------------------------------------------------------------
int Main(void)
{
  // Start things up & load resources ---------------------------------------------------
  LoadSprites();
  PrepareFont();

  // Set up rendering ---------------------------------------------------------------------
  glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
  glClearColor( 0.0f, 0.1f, 0.3f, 0.0f );
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho( 0.0, SCR_WIDTH, 0.0, SCR_HEIGHT, 0.0, 1.0);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Start main loop ---------------------------------------------------------------------
  float t = 0;
  while (!SYS_GottaQuit())
  {
    glClear( GL_COLOR_BUFFER_BIT );
   
    glDisable(GL_TEXTURE_2D);
    glBegin( GL_TRIANGLES );
    //glColor3f( 1.0f, 0.0f, 0.0f ); glVertex2f(  .5f * cos(2.f * 3.14f * t/120.f),  0.5f );
    glColor4f( 1.0f, 0.0f, 0.0f, 1.0f ); glVertex2f(  0.0f,  (float)SCR_HEIGHT );
    glColor4f( 0.0f, 1.0f, 0.0f, 1.0f ); glVertex2f(  (float)SCR_WIDTH, 0 );
    glColor4f( 0.0f, 0.0f, 1.0f, 1.0f ); glVertex2f( -(float)SCR_WIDTH, 0 );
    glEnd();

    glEnable(GL_TEXTURE_2D);
    glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
    DrawString(vmake(SCR_WIDTH/2.5f, SCR_HEIGHT/2.5f), "HELLO WORLD!");

    SYS_Show();
   
    // Keep system running
    SYS_Pump();

    t = t + 1.f;
  }

  // Free resources & terminate things ----------------------------------------------------
  UnloadSprites();


  return 0;
}