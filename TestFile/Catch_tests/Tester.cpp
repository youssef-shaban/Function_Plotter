//
// Created by youss on 5/17/2022.
//
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "functiongenerator.h"

TEST_CASE("CalculatingTest","[FunctionGenerator]"){

    CHECK(FunctionGenerator::FCalc("3*x+2",3)==11);
    CHECK(FunctionGenerator::FCalc("3*(x+2)",3)==15);
    CHECK(FunctionGenerator::FCalc("(3*x/2+1)/(x+2)",2)==1);
}
TEST_CASE("CalculatingTest2","[FunctionGenerator]"){

    CHECK(FunctionGenerator::FCalc("3x",3)==9);

}

TEST_CASE("ErrorTest1","[FunctionGenerator]"){
    try{
        FunctionGenerator::FCalc("3**x",2);
    }catch (const std::runtime_error& re){
        string error= re.what();
        CHECK(error.compare("you can't use ** or // or any two symbols")==0);
    }
}

TEST_CASE("ErrorTest2","[FunctionGenerator]"){
    try{
        FunctionGenerator::FCalc("3*Y",2);
    }catch (const std::runtime_error& re){
        string error= re.what();
        CHECK( error.compare("ONLY USE numbers, x, ^*-+/()")==0);
    }
}
TEST_CASE("ErrorTest3","[FunctionGenerator]"){
    try{
        FunctionGenerator::FCalc("3*2)",2);
    }catch (const std::runtime_error& re){
        string error= re.what();
        CHECK( error.compare("You are closing a bracket without opening it.")==0);
    }
}
TEST_CASE("ErrorTest4","[FunctionGenerator]"){
    try{
        FunctionGenerator::FCalc("((x+2)",2);
    }catch (const std::runtime_error& re){
        string error= re.what();
        CHECK( error.compare("Please close opened brackets.")==0);
    }
}