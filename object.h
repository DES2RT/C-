// object.h
// Mark Fernandes
// March 22, 2015
#pragma once

#include <string>
#include <vector>

class object{
  public:
    // when derived objects may contain pointers, virtual destructors are necessary
    virtual ~object(){}

    // (optional) use set to assign values to their respective data members of the derived object
    virtual void set(std::vector<std::pair<std::string,std::string>>) {}

    // (required) returns member data as Delimited Separated Values (default separator is comma)
    virtual const std::string to_DSV(const char c=',')=0;

    // (required) returns member data as simple indented json; item is indented by number of leading spaces 
    virtual const std::string to_json(int leading_spaces=0)=0;
};
