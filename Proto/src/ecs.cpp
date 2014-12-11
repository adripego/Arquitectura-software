#include "../include/ecs.h"

void Entity::update()
{
    for (unsigned int i = 0; i < m_arrayComponentes.Size(); i++)
        m_arrayComponentes[i].update();
}

C_Renderable::C_Renderable() : public Component
{

}

