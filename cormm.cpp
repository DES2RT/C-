#include <iostream>
#include <fstream>
#include <vector>
#include <new>
#include <memory>
#include <algorithm>
#include "object.h"
#include "cartoon.h"

int main(int argc, char** argv) {

    Cartoon::cartoon* car;
    std::string carString;;
    std::vector<std::pair<std::string, std::string>> carVector;
    size_t count=0;
    bool array = false;
    // open file and read contents to determine size of memory needed
    std::ifstream fin("05-array_with_few_cartoon_objects.json", std::ifstream::binary);
    //std::ifstream fin("03-one_cartoon_object.json", std::ifstream::binary);
    if(fin) {
        // get size (in bytes) of the file
        fin.seekg(0, fin.end);
        int size = fin.tellg();
        //std::cout << "sizeis: " << size << "\n";
        fin.seekg(0, fin.beg);
        char* buffer = new char[size];
        fin.read(buffer,size);
        int x=0;
        while(x<size) {
            carString += buffer[x];
            if(buffer[x] == '[')
                array = true;
            if(buffer[x] == '}') {
                count++;
            }
            x++;
        }
        fin.seekg(0, fin.beg);
        if(count>0) {
            std::string dsv, json;
            // allocate memory
            car = new Cartoon::cartoon[count];
            size_t end = carString.find('}');
            size_t end2 = carString.find('}', end+1);
            if(end2!=-1) size_t end3 = carString.find('}', end2+1);
            //std::cout << b << std::endl;
            
            for(int i=0; i<count; i++) {  
                car[i].setString(carString, array);
                int x=0;
                while(!fin.eof()) {
                    // read line by line executing each statement for every line
                    getline(fin, carString, '\n');
                    //std::cout << carString;   
                
                    // parse the string to find the variables 
                    int s1 = carString.find('\"');
                    int s2 = carString.find('\"', s1+1);
                    int s3 = carString.find("\"", s2+1);
                    int s4 = carString.find("\"", s3+1);
                    int s5 = carString.find('}');
                    
                    // get vars, create pair add to vector
                    std::string p1, p2;
                    std::pair<std::string, std::string>  prVar;
                    if(s1 != -1 && s2 != -1) {
                        p1 = carString.substr(s1,s2-s1+1);
                        p2 = carString.substr(s3,s4-s3+1);
                        prVar.first=p1;
                        prVar.second=p2;
                        carVector.push_back(prVar);
                    }
                    if(s5!=-1) {
                        //std::cout << carVector.size() << ' ';
                        // call the set function 
                        car[i].count();
                        car[i].set(carVector);
                        dsv = car[i].to_DSV();
                        if(array)
                            json = car[i].to_json(8);
                        else
                            json = car[i].to_json(4);
                        std::cout << dsv;    
                        std::cout << json;    
                        carVector.clear();
                    }
                    s5=0;
                }
            }
        }
    }
        //std::cout << "vCar: " << carVector.front() << std::endl;
        std::cout << "isall\n";
                std::cin.get();
}
