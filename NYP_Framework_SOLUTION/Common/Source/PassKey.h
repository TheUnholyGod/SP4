#pragma once

template<class Type>
class PassKey
{
    friend Type;
    PassKey() {}
};