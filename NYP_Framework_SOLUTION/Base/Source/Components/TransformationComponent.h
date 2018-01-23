#ifndef _TRANSFORMATIONCOMPONENT_H
#define _TRANSFORMATIONCOMPONENT_H

#include "../Component.h"
#include "PassKey.h"
#include "Mesh.h"
#include "Vector3.h"
#include "Mtx44.h"

class ComponentManager;

class TransformationComponent : public BaseComponent
{
private:
    Vector3 m_translation;
    Vector3 m_rotationaxis;
    Vector3 m_scaling;
    double m_rotationangle;

public:
    TransformationComponent(unsigned _ID, PassKey<ComponentManager> _passkey) : BaseComponent(_ID, _passkey) {}
    virtual ~TransformationComponent() {}

    void Init(Vector3 _translation = Vector3(0, 0, 0), Vector3 _rotation = Vector3(1, 0, 0), Vector3 _scaling = Vector3(1, 1, 1), double _rotationangle = 0)
    {
        m_translation = _translation;
        m_rotationaxis = _rotation;
        m_scaling = _scaling;
        m_rotationangle = _rotationangle;
    }

    MS& LoadTransformationMatrix(MS& _modelStack)
    {
        _modelStack.Translate(m_translation);
        _modelStack.Rotate(m_rotationangle, m_rotationaxis);
        _modelStack.Scale(m_scaling);
        return _modelStack;
    }

};

#endif