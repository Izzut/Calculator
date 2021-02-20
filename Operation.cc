#include "Operation.h"
#include "Register.h"

int Add_Operation::get_value(int old_value) const
{
    if (reg == nullptr)
        return value + old_value;
    else
        return reg->get_value() + old_value;
}

int Sub_Operation::get_value(int old_value) const
{
    if (reg == nullptr)
        return old_value - value;
    else
        return old_value - reg->get_value();
}

int Mult_Operation::get_value(int old_value) const
{
    if (reg == nullptr)
        return old_value * value;
    else
        return reg->get_value() * old_value;
}