#ifndef UGINE_SPRITE_H
#define UGINE_SPRITE_H

#include "renderer.h"
#include "types.h"
#include "screen.h"

class Collision;
class CollisionPixelData;
class Image;
class Map;

class Sprite {
public:
	enum CollisionMode {
		COLLISION_NONE,
		COLLISION_CIRCLE,
		COLLISION_PIXEL,
		COLLISION_RECT
	};

	Sprite(Image* image);
	virtual ~Sprite();

    virtual void SetImage(Image* image) { this->image = image; }
    virtual const Image* GetImage() const { return this->image; }

    virtual void SetPosition(double x, double y) { this->x = x; this->y = y; }
    virtual void SetX(double x) { this->x = x; }
    virtual void SetY(double y) { this->y = y; }
    virtual double GetX() const { return x; }
    virtual double GetY() const { return y; }
    virtual double GetScreenX() const { return Screen::Instance().GetWidth(); }
    virtual double GetScreenY() const { return Screen::Instance().GetHeight(); }

    virtual void SetAngle(double angle) { this->angle = angle; }
    virtual double GetAngle() const { return angle; }

    virtual void SetScale(double sx, double sy) { this->scalex = sx; this->scaley = sy; }
    virtual void SetScaleX(double sx) { this->scalex = sx; }
    virtual void SetScaleY(double sy) { this->scaley = sy; }
    virtual double GetScaleX() const { return scalex; }
    virtual double GetScaleY() const { return scaley; }
    
    virtual void SetFPS(int16 fps) { animFPS = fps; }
    virtual int16 GetFPS() const { return animFPS; }
    virtual void SetFrameRange(uint16 firstFrame, uint16 lastFrame) { this->firstFrame = firstFrame; this->lastFrame = lastFrame; }
    virtual uint16 GetFirstFrame() const { return firstFrame; }
    virtual uint16 GetLastFrame() { return lastFrame; }
    virtual void SetCurrentFrame(uint16 frame) { currentFrame = frame; }
    virtual uint16 GetCurrentFrame() const { return currentFrame; }

    virtual void SetBlendMode(Renderer::BlendMode blend) { this->blendMode = blend; }
    virtual Renderer::BlendMode GetBlendMode() const { return this->blendMode; }
    virtual void SetColor(uint8 r, uint8 g, uint8 b, uint8 alpha = 255);
    virtual uint8 GetRed() const { return this->r; }
    virtual uint8 GetGreen() const { return this->g; }
    virtual uint8 GetBlue() const { return this->b; }
    virtual uint8 GetAlpha() const { return this->a; }

//  virtual void SetRadius(double radius) { /* TAREA: Implementar */ }
//  virtual double GetRadius() const { /* TAREA: Implementar */ }

//  virtual void SetCollision(CollisionMode mode);
//  virtual void SetCollisionPixelData(const CollisionPixelData* colPixelData) { /* TAREA: Implementar */ }
//  virtual const Collision* GetCollision() const { /* TAREA: Implementar */ }
//  virtual bool CheckCollision(Sprite* sprite);
//  virtual bool CheckCollision(const Map* map);
//  virtual const Sprite* CollisionSprite() const { /* TAREA: Implementar */ }
//  virtual bool DidCollide() const { /* TAREA: Implementar */ }

    virtual void RotateTo(int32 angle, double speed);
    virtual void MoveTo(double x, double y, double speedX, double speedY = 0.0);
//  virtual bool IsRotating() const { /* TAREA: Implementar */ }
//  virtual bool IsMoving() const { /* TAREA: Implementar */ }
    

    virtual void Update(double elapsed, const Map* map = NULL);
    virtual void Render() const;
	
	virtual void SetUserData(void* data) { userData = data; }
	virtual void* GetUserData() { return userData; }
	virtual const void* GetUserData() const { return userData; }
protected:
    virtual void UpdateCollisionBox();
    virtual void UpdateCollisionBox(double x, double y, double w, double h);
private:
    // Practica 4 Parte 1
	Image* image;
    double x, y;
    double angle;
    double scalex, scaley;
    Renderer::BlendMode blendMode;
    uint8 r, g, b, a;
	void* userData;
	
	// Practica 4 Parte 2
    bool rotating;
    uint16 toAngle;
    double rotatingSpeed;
    double anglesToRotate;
    bool moving;
    double toX, toY;
    double movingSpeedX, movingSpeedY;
    double prevX, prevY;
	
	// Info animacion
    int16 animFPS;
    uint16 firstFrame, lastFrame;
    double currentFrame;

    // Info colision
	double colx, coly, colwidth, colheight;
    double radius;
    Collision* collision;
    const CollisionPixelData* colPixelData;
    Sprite* colSprite;
    bool collided;
};

#endif
