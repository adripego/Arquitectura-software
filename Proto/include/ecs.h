//#ifndef _ECS_H
//#define _ECS_H
//
//#include "array.h"
//class Entity;
//
//struct Message
//{
//	Message();
//	virtual ~Message();
//};
//
//
//struct MoveMessage : public Message
//{
//	MoveMessage(int incX, int incY);
//	~MoveMessage();
//	int m_deltaX;
//	int m_deltaY;
//};
//
//class Component
//{
//    Entity* m_owner;
//public:
//	virtual ~Component();
//    virtual void update();
//    void receiveMessage(Message msg);
//};
//
//
//class Entity
//{
//    Array<Component> m_arrayComponentes;
//public:
//	Entity();
//	virtual ~Entity();
//    virtual void update();
//    void addComponent(Component* comp);
//	void receiveMessage(Message msj);
//};
//
//
//class C_Position : public Component
//{
//	int m_posX;
//	int m_posY;
//public:
//	C_Position(); 
//	virtual ~C_Position();
//	virtual void update();
//	void receiveMessage(Message* msj);
//};
//
//
////class C_Renderable : public Component
////{
////public:
////    C_Renderable();
////    virtual void update();
////    void receiveMessage(Message msj);
////};
////
////class C_InputControl: public Component
////{
////public:
////    C_InputControl();
////    virtual void update();
////    void receiveMessage(Message msj);
////};
//
//
//#endif