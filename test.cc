#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Register.h"
#include "Operation.h"

TEST_CASE("Initilazing registers")
{
    Register myreg;
    myreg.assign_name("MYREG");
    Register myreg2;
    myreg2.assign_name("MYR123EG");
    REQUIRE(myreg.get_value() == 0);
    REQUIRE(myreg2.name == "myr123eg");
}

TEST_CASE("Initilazing simple add/sub operations")
{
    int number = 12;
    Add_Operation myadd(number);
    Sub_Operation mysub(number);
    REQUIRE(myadd.get_value(0) == 12);
    REQUIRE(mysub.get_value(0) == -12);
}

TEST_CASE("Sub/add-operations and registers together")
{
    Register myreg;
    Add_Operation *myadd = new Add_Operation(12);
    myreg.add_component(myadd);
    REQUIRE(myreg.get_value() == 12);
    Sub_Operation *mysub = new Sub_Operation(12);
    myreg.add_component(mysub);
    REQUIRE(myreg.get_value() == 0);
}

TEST_CASE("Sub/add-operations with registers and registers together")
{
    Register *myreg = new Register();
    Register *myreg2 = new Register();
    Add_Operation *myadd2 = new Add_Operation(12);
    myreg2->add_component(myadd2);
    Add_Operation *myadd = new Add_Operation(myreg2);
    myreg->add_component(myadd);
    myreg->add_component(myadd2);
    REQUIRE(myreg->get_value() == 24);
    REQUIRE(myreg2->get_value() == 12);
}

TEST_CASE("Multiplication as well")
{
    Register *myreg = new Register();
    Register *myreg2 = new Register();
    Add_Operation *myadd2 = new Add_Operation(12);

    //add 12 to both registers
    myreg2->add_component(myadd2);
    myreg->add_component(myadd2);

    //Multiply first register with 2
    Mult_Operation *mymult = new Mult_Operation(2);
    myreg->add_component(mymult);

    //Add second register to the first
    Add_Operation *myadd = new Add_Operation(myreg2);
    myreg->add_component(myadd);

    REQUIRE(myreg->get_value() == 36);
    REQUIRE(myreg2->get_value() == 12);

    //Multiply only the second register with 2
    myreg2->add_component(mymult);
    REQUIRE(myreg->get_value() == 48);
    REQUIRE(myreg2->get_value() == 24);

    //Multiply the first register with 2
    myreg->add_component(mymult);
    REQUIRE(myreg->get_value() == 96);
}
