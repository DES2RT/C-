// FINAL PROJECT
// OOP345 SECTION B
// DALE STEWART
// 023567902
// 17/04.2015

// COURSE.H
// THE COURSE.H FILE CONTAINS THE CLASS DEFINITION OF COURSE. DEFINING ITS MEMBER
// INSTANCES AND FUNCTIONS. THE COURSE CLASS IS DERIVED FROM OBJECT CLASS
// 'OBJECT.H' AND TWO PURE VIRTUAL FUNCTIONS ARE MANDATED FROM THAT CLASS

#ifndef _COURSE_H_
#define _COURSE_H_

#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <utility>
#include "object.h"

namespace Course {
    
    class course: public object {
        //std::vector<std::pair<std::string, std::string>> carVector;
        std::pair<std::string, std::string> prType;
        std::pair<std::string, std::string> prName;
        std::pair<std::string, std::string> prLikes;
        std::string fString;
        int numCars;                   // holds number of valid json objects in file;
        bool array;
      public:
        course() : numCars(0) { }
        void setString(std::string s, bool b) { fString = s; array = b; }
        void set(std::vector<std::pair<std::string, std::string>> src) {
            typedef std::vector<std::pair<std::string, std::string>> myV;
            for(myV::const_iterator i=src.begin(); i!= src.end(); ++i) {
                prLikes = src.back();
                src.pop_back();
                prName= src.back();
                src.pop_back();
                prType = src.back();
                //std::cout << "\n in set: " << prType.first << ' ' << prType.second;
                //std::cout << "\n in set: " << prName.first << ' ' << prName.second;
                //std::cout << "\n in set: " << prLikes.first << ' ' << prLikes.second;
                //std::cout << std::endl;
            }
        }// end set function
        

        const std::string to_DSV(const char c=',') {
            std::string dsv;
            dsv += "\ndsv ";
            dsv += prType.first + ':' + prType.second + c;
            dsv += prName.first + ':' + prName.second + c;
            dsv += prLikes.first + ':' + prLikes.second;
            dsv += '\n';
            
            return dsv;
        }
        
        const std::string to_json(int leading_spaces=0) {
            std::string json;
            int ls = leading_spaces;
            if(array) {
                std::cout << '[' << '\n'<<"     {" << '\n';
                json += '[';
                json += "\n";
                json += "     {";
                json += "\n";
            } 
            else {
                std::cout << '{' << '\n'; 
                json += '{';
                json += '\n';
            }
            
            std::cout << '\t' << std::right << prType.first << ": " << prType.second << ',' << '\n';
            std::cout << '\t' << prName.first << ": " << prName.second << ',' << '\n';
            std::cout << '\t' << prLikes.first << ": " << prLikes.second << ',';
            json.clear();

            if(array) {
                std::cout << '\n' << "     }" << '\n' << ']';
            }
            else {
                std::cout << '\n' << '}';
            }
            return json;
        }
        
        void count() { numCars++; }
        void countDisplay() { std::cout << numCars << std::endl; }
        size_t size() const { return numCars; }

        const std::string getType() const { 
            std::string type;
            type += prType.first + ':';
            type += prType.second;
            return type; 
        }
        const std::string getName() const { 
            std::string name;
            name += prName.first + ' ';
            name += prName.second;
            return name; 
        }
        const std::string getLikes() const { 
            std::string likes;
            likes += prLikes.first + ' ';
            likes += prLikes.second;
            return likes; 
        }

        ~course() { }
    };

}

#endif
