#ifndef _ECS_H
#define _ECS_H

#include "array.h"
class Entity;

struct Message
{
};

class Component
{
    Entity* m_owner;
public:
    virtual void update() = 0;
    void receiveMessage(Message* msg);
};

class Entity
{
    Array<Component> m_arrayComponentes;
public:
    virtual void update();
    void addComponent(Component* comp);
};

class C_Renderable : public Component
{
public:
    C_Renderable();
    virtual void update();
    void receiveMessage(Message* msj);
};

class C_InputControl: public Component
{
public:
    C_InputControl();
    virtual void update();
    void receiveMessage(Message* msj);
};

#endif