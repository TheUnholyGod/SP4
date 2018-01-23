#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "Source\PassKey.h"

class Entity;
class ComponentManager;

class BaseComponent
{
private:
    unsigned m_ID;
    Entity* m_parent;
public:
    BaseComponent(unsigned _ID, PassKey<ComponentManager> _passkey) : m_ID(_ID) {}
    virtual ~BaseComponent() {}
    void SetParent(Entity* _parent) { m_parent = _parent; }
};

#endif