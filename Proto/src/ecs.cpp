//#include "../include/ecs.h"
//#include "../include/renderer.h"
//
//Entity::Entity()
//{
//
//}
//
//Entity::~Entity()
//{
//	//for (unsigned int i = 0; i < m_arrayComponentes.Size(); i++)
//	//	delete m_arrayComponentes[];
//}
//
//
//void Entity::update()
//{
//    for (unsigned int i = 0; i < m_arrayComponentes.Size(); i++)
//        m_arrayComponentes[i].update();
//}
//
//
//
//void Entity::addComponent(Component* comp)
//{
//	m_arrayComponentes.Add(*comp);
//}
//
//
//void Entity::receiveMessage(Message msj)
//{
//	for (unsigned int i = 0; i < m_arrayComponentes.Size(); i++)
//		m_arrayComponentes[i].receiveMessage(msj);
//}
//
//
//
//MoveMessage::MoveMessage(int incX, int incY)
//{
//	m_deltaX = incX;
//	m_deltaY = incY;
//};
//
//
//void C_Position::receiveMessage(Message* msj)
//{
//	MoveMessage* mvmsg = dynamic_cast<MoveMessage* >(msj);
//	if (mvmsg)
//	{
//		this->m_posX += mvmsg->m_deltaX;
//		this->m_posY += mvmsg->m_deltaY;
//	}
//}