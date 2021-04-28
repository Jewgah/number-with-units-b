#include "doctest.h"
#include "NumberWithUnits.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace ariel;
using namespace std;

ifstream units_file{"units.txt"};

NumberWithUnits km(7, "km");
NumberWithUnits cm(18, "cm");
NumberWithUnits hour(12, "hour");
NumberWithUnits minutes(30, "min");
NumberWithUnits ton(10, "ton");
NumberWithUnits kg(28, "kg");
NumberWithUnits USD(3, "USD");

TEST_CASE("+ / -")
{
    km=km+cm;
    CHECK(km == NumberWithUnits (7.018, "km"));
    km=km-cm;
    CHECK(km == NumberWithUnits (7, "km"));
    hour=hour+minutes;
    CHECK(hour == NumberWithUnits (12.5, "hour"));
    hour=hour-minutes;
    CHECK(hour == NumberWithUnits (12, "hour"));
    ton=ton+kg;
    CHECK(ton == NumberWithUnits (10.028, "ton"));
    ton=ton-kg;
    CHECK(ton == NumberWithUnits (3, "ton"));
}

TEST_CASE("+= / -=")
{
    km+=cm;
    CHECK(km == NumberWithUnits (7.018, "km"));
    km-=cm;
    CHECK(km == NumberWithUnits (7, "km"));
    hour+=minutes;
    CHECK(hour == NumberWithUnits (12.5, "hour"));
    hour-=minutes;
    CHECK(hour == NumberWithUnits (12, "hour"));
    ton+=kg;
    CHECK(ton == NumberWithUnits (10.028, "ton"));
    ton-=kg;
    CHECK(km == NumberWithUnits (3, "km"));
}

TEST_CASE("> / >= / < / <= / == / !=")
{
    CHECK_GT(km,cm);
    CHECK_LT(cm,km);
    CHECK_GT(hour,minutes);
    CHECK_LT(minutes,hour);
    CHECK_GT(ton,kg);
    CHECK_LT(kg,ton);

    CHECK_GE(km,km);
    CHECK_LE(km,km);
    CHECK_EQ(ton, NumberWithUnits(10000, "kg"));
    CHECK_EQ(hour, NumberWithUnits(720, "min"));
    CHECK_EQ(USD, NumberWithUnits(9.99, "ILS"));

}

TEST_CASE("++ / --")
{
    km++;
    CHECK(km ==  NumberWithUnits (8, "km"));
    km--;
    CHECK(km ==  NumberWithUnits (7, "km"));
    hour++;
    CHECK(hour ==  NumberWithUnits (13, "hour"));
    hour--;
    CHECK(hour ==  NumberWithUnits (12, "hour"));
    ton++;
    CHECK(ton ==  NumberWithUnits (11, "ton"));
    ton--;
    CHECK(ton ==  NumberWithUnits (10, "ton"));
}
TEST_CASE("* / *=")
{
    km=km*2;
    CHECK(km ==  NumberWithUnits (14, "km"));
    km*=0.5;
    CHECK(km ==  NumberWithUnits (7, "km"));
    hour=hour*2;
    CHECK(hour ==  NumberWithUnits (24, "hour"));
    hour*=0.5;
    CHECK(hour ==  NumberWithUnits (12, "hour"));
    ton=ton*2;
    CHECK(ton ==  NumberWithUnits (20, "ton"));
    ton*=0.5;
    CHECK(ton ==  NumberWithUnits (10, "ton"));
}