#include "Register.h"
#include <algorithm>
using namespace std;

Register::~Register()
{
    list<Operation *>::iterator it;
    for (it = components.begin(); it != components.end(); ++it)
    {
        delete (*it);
    }
}

int Register::get_value()
{
    if (components.empty())
        return 0;
    else
    {
        int total_value = 0;
        list<Operation *>::iterator it;
        for (it = components.begin(); it != components.end(); ++it)
        {
            total_value = (*it)->get_value(total_value);
        }
        return total_value;
    }
}

void Register::assign_name(string input_for_name)
{
    transform(input_for_name.begin(), input_for_name.end(), input_for_name.begin(), ::tolower);
    name = input_for_name;
}

void Register::add_component(Operation *new_component)
{
    components.push_back(new_component);
}