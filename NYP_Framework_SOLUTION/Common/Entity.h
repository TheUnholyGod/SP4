#ifndef _ENTITY_H
#define _ENTITY_H

#include "Component.h"
#include "ComponentManager.h"

#include <memory>
#include <vector>
#include <array>

constexpr std::size_t MaxComponents = 32;
using ComponentBitSet = std::bitset<MaxComponents>;
using ComponentArray = std::array<BaseComponent*, MaxComponents>;

class Entity
{
private:
    bool m_active;
    std::vector<std::unique_ptr<BaseComponent>> m_components;

    ComponentArray m_component_array;
    ComponentBitSet m_component_bitset;
public:
    template <typename ComponentType> bool HasComponent() const
    {
        return this->m_component_bitset[GetComponentTypeID<ComponentType>()];
    }

    template <typename ComponentType, typename... ComponentArgs>
    ComponentType& AddComponent()
    {
        ComponentManager* cm = ComponentManager::GetInstance();
        BaseComponent* c = cm->CreateComponent<ComponentType>();
        std::unique_ptr<BaseComponent> uPtr(c);
        uPtr->SetParent(this);
        this->m_components.emplace_back(std::move(uPtr));

        this->m_component_array[cm->GetComponentTypeID<ComponentType>()] = uPtr.get();
        this->m_component_bitset[cm->GetComponentTypeID<ComponentType>()] = true;
        //c->Init();
        return *dynamic_cast<ComponentType*>(c);
    }

    template <typename ComponentType>
    ComponentType& GetComponent() const
    {
        Component* ptr = this->m_component_array[GetComponentTypeID<ComponentType>()];
        return static_cast<ComponentType*>(ptr);
    }
};

#endif