#ifndef _COMPONENT_MANAGER_H
#define _COMPONENT_MANAGER_H

#include "Source\SingletonTemplate.h"
#include "Component.h"
#include "Source\PassKey.h"

#include <bitset>
#include <memory>

#include <iostream>

class ComponentManager:public Singleton<ComponentManager>
{
    friend Singleton<ComponentManager>;
private:

public:

    inline std::size_t ComponentManager::GetComponentTypeID()
    {
        static std::size_t lastID = 0;
        return ++lastID;
    }
    template <typename ComponentType>
    inline std::size_t GetComponentTypeID() noexcept
    {
        static std::size_t typeID = GetComponentTypeID();
        return typeID;
    }

    template <typename ComponentType>
    inline BaseComponent* CreateComponent()
    {
        std::cout << "A new Component is being created" << std::endl;
        BaseComponent* newComponent = new ComponentType(GetComponentTypeID<ComponentType>(), PassKey<ComponentManager>());
        return newComponent;
    }

};

#endif
