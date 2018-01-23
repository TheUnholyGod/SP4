#ifndef _MESHCOMPONENT_H
#define _MESHCOMPONENT_H

#include "../Component.h"
#include "PassKey.h"
#include "Mesh.h"

class ComponentManager;

class MeshComponent : public BaseComponent
{
private:
    Mesh* m_mesh;
public:
    MeshComponent(unsigned _ID, PassKey<ComponentManager> _passkey) : BaseComponent(_ID, _passkey) {}
    virtual ~MeshComponent() {}

    Mesh* GetMesh() { return m_mesh; }
    void SetMesh(Mesh* _mesh) { m_mesh = _mesh; }
};

#endif