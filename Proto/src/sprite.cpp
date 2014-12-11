#include "../include/sprite.h"
//#include "../include/rectcollision.h"
#include "../include/image.h"
//#include "../include/map.h"
#include "../include/math.h"
//#include "../include/pixelcollision.h"
#include "../include/renderer.h"
//#include "../include/circlecollision.h"
#include <math.h>



Sprite::Sprite(Image* image) {
	// TAREA: Implementar
    this->image = image;
    x = 0.f;
    y = 0.f;
    angle = 0.f;
    scalex = 1.f;
    scaley = 1.f;
    blendMode = Renderer::BlendMode::ALPHA;
    r = 255;
    g = 255;
    b = 255;
    a = 255;
    userData = NULL;
    currentFrame = 0.f;

    rotating = false;
    toAngle = 0;
    rotatingSpeed = 0;
    anglesToRotate = 0;
    moving = false;
    toX = 0;
    toY = 0;
    movingSpeedX = 0;
    movingSpeedY = 0;
    prevX = 0;
    prevY = 0;
    animFPS = 0;
    firstFrame = 0;
    lastFrame = 0;
}

Sprite::~Sprite() {
    // TAREA: Implementar
}

void Sprite::SetColor(uint8 r, uint8 g, uint8 b, uint8 alpha)
{
    this->r = r; 
    this->g = g; 
    this->b = b; 
    this->a = alpha;
}


//void Sprite::SetCollision(CollisionMode mode) {
//	// TAREA: Implementar
//}
//
//bool Sprite::CheckCollision(Sprite* sprite) {
//	// TAREA: Implementar
//}
//
//bool Sprite::CheckCollision(const Map* map) {
//	// TAREA: Implementar
//}

void Sprite::RotateTo(int32 angle, double speed) {
    // TAREA: Implementar
    //anguloDestino - anguloActual < anguloActual - anguloDestino
    rotating = true;
    toAngle = WrapValue(angle, 360);

    if (WrapValue(angle - this->angle, 360) < WrapValue(this->angle - angle, 360))
    {
        anglesToRotate = abs(angle - this->angle);
        rotatingSpeed = abs(speed);
    }
    else
    {
        anglesToRotate = abs(this->angle - angle);
        rotatingSpeed = -abs(speed);
    }
}

void Sprite::MoveTo(double x, double y, double speedX, double speedY) {
    moving = true;
    toX = x;
    toY = y;
    prevX = abs(x - this->x);
    prevY = abs(y - this->y);

    if (this->x > x) 
        movingSpeedX = -speedX;
    else
        movingSpeedX = speedX;

    if (this->y > y) 
        movingSpeedY = -speedY;
    else 
        movingSpeedY = speedY;
}

void Sprite::Update(double elapsed, const Map* map) {
    // Informacion inicial de colision
    colSprite = NULL;
    collided = false;
    // TAREA: Actualizar animacion

    if (animFPS != 0){
        currentFrame += animFPS * elapsed;
        if (currentFrame <= firstFrame) currentFrame = static_cast<double>(lastFrame) + 0.9999;
        if (currentFrame >= (lastFrame + 1)) currentFrame = static_cast<double>(firstFrame);
    }

    // TAREA: Actualizar rotacion animada 
    if (rotating)
    {
        this->angle = WrapValue(this->angle + rotatingSpeed * elapsed, 360);
        Screen::Instance().SetTitle(String::FromFloat(this->angle));
        anglesToRotate = anglesToRotate - abs(rotatingSpeed * elapsed);

        if (anglesToRotate <= 0)
        {
            this->angle = toAngle;
            rotating = false;
        }
        else
            rotating = true;
    }

    // TAREA: Actualizar movimiento animado
    if (moving)
    {
        this->x = this->x + movingSpeedX * elapsed;
        this->y = this->y + movingSpeedY * elapsed;

        prevX = prevX - movingSpeedX * elapsed;
        if (prevX <= 0)
        {
            this->x = toX;
            moving = false;
        }
        prevY = prevY -  movingSpeedY * elapsed;
        if (prevY <= 0)
        {
            this->y = toY;
            moving = false;
        }
    }

	// Informacion final de colision
	UpdateCollisionBox();
}

void Sprite::Render() const {
    // TAREA: Implementar
    // activar el blender
    Renderer::Instance().SetBlendMode(blendMode);
    // activar color
    Renderer::Instance().SetColor(r, g, b, a);
    // pintar
    Renderer::Instance().DrawImage(image, x, y, currentFrame, image->GetWidth() * scalex, image->GetHeight() * scaley, this->angle);
}

void Sprite::UpdateCollisionBox() {
	// TAREA: Implementar
}

void Sprite::UpdateCollisionBox(double x, double y, double w, double h) {
	// TAREA: Implementar
}
