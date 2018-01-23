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

    /*
    Adds a component to the coresponding entity based on the type passed through the template.
    Example:
        entity->AddComponent<MeshComponent>();

    @usage      AddComponent<ComponentType>();
    @return     BaseComponent
    @params     void
    */
    template <typename ComponentType>
    BaseComponent& AddComponent()
    {
        ComponentManager* cm = ComponentManager::GetInstance();
        BaseComponent* c = dynamic_cast<BaseComponent*>(cm->CreateComponent<ComponentType>());
        std::unique_ptr<BaseComponent> uPtr(c);
        uPtr->SetParent(this);
        this->m_components.emplace_back(std::move(uPtr));

        this->m_component_array[cm->GetComponentTypeID<ComponentType>()] = c;
        this->m_component_bitset[cm->GetComponentTypeID<ComponentType>()] = true;
        return *c;
    }

    //template <typename... ComponentType>
    //ComponentType& AddComponent()
    //{
    //    ComponentManager* cm = ComponentManager::GetInstance();
    //    ComponentType* c = cm->CreateComponent<ComponentType>();
    //    std::unique_ptr<BaseComponent> uPtr(c);
    //    uPtr->SetParent(this);
    //    this->m_components.emplace_back(std::move(uPtr));

    //    this->m_component_array[cm->GetComponentTypeID<ComponentType>()] = uPtr.get();
    //    this->m_component_bitset[cm->GetComponentTypeID<ComponentType>()] = true;
    //    //c->Init();
    //    return *c;
    //}

    template <typename ComponentType>
    ComponentType* GetComponent() const
    {
        BaseComponent* ptr = this->m_component_array[ComponentManager::GetInstance()->GetComponentTypeID<ComponentType>()];
        return static_cast<ComponentType*>(ptr);
    }
};

#endif