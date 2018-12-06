// project.h: functions required by Simple, Indented, JSON-like reader-writer
// Mark Fernandes
// March 22, 2015
#include "object.h"
#pragma once

namespace project{

  // readFromJsonLike
  //  receives a filename and a type T
  //    it reads all objects of type T from filename (JSON-like data format)
  //  and returns a pointer to a vector containing all type T found in filename
  template<typename T>
  std::vector<T>* readFromJsonLike(std::string filename, T& obj){
    try {
        std::unique_ptr<std::vector<T>> all = new std::vector<T>;
        throw std::string("Could NOT allocate\n");

        std::ifstream fin("filename");
        throw std::string("Unable to open file " + filename + "\n";

        while(!fin.eof()) {
            getline(fin, all, '\n');
        }
        std::cout << all;

        return all;
    }
    catch(const std::string& msg) {
        std::cout << msg << std::endl;
    }
    catch(..) {
        std::cout << "Unknown Error\n");
    }
  }
  
  // writeToJsonLike  
  //  receives a pointer to vector containing type T and a filename
  //    it writes all items from vector to filename using the JSON-like format
  //  and returns the number of objects successfully written
/*  template<typename T>
  int writeToJsonLike(std::vector<T>* list, std::string filename){

    int no_objects_written = 0;

    //
    // put JSON-like writing code here
    //

    return no_objects_written;

  }
*/
}
