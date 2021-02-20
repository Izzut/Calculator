#ifndef OPERATION_H
#define OPERATION_H

class Register; //Forward decleration

class Operation
{
public:
    Operation(int in_value) : value{in_value} {};
    Operation(Register *in_reg) : reg{in_reg} {};
    virtual ~Operation() {};
    int value;
    Register *reg = nullptr;
    virtual int get_value(int old_value) const = 0;
};

class Add_Operation
    : public Operation
{
public:
    Add_Operation(int in_value) : Operation(in_value){};
    Add_Operation(Register *in_reg) : Operation(in_reg){};
    ~Add_Operation() {};
    int get_value(int old_value) const override;
};

class Sub_Operation
    : public Operation
{
public:
    Sub_Operation(int in_value) : Operation(in_value){};
    Sub_Operation(Register *in_reg) : Operation(in_reg){};
    ~Sub_Operation() {};
    int get_value(int old_value) const override;
};

class Mult_Operation
    : public Operation
{
public:
    Mult_Operation(int in_value) : Operation(in_value){};
    Mult_Operation(Register *in_reg) : Operation(in_reg){};
    ~Mult_Operation() {};
    int get_value(int old_value) const override;
};
#endif
