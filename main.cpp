// main.cpp: main for a Simple, Indented, JSON-like reader-writer
// Mark Fernandes
// March 22, 2015

#include <algorithm>    // for count_if()
#include <fstream>
#include <iostream>
#include <string>
#include <memory>       // for std::shared_ptr<>
#include "cartoon.h"    // cartoon is derived from object (see object.h and ../data/*cartoon*.json)
#include "course.h"     // course is derived from object (see object.h and ../data/*course*.json)
#include "project.h"    // declarations required by project

// number of professional options in courses.json
#define PRO_CPA  14
#define PRO_BSD   9
#define CPA_ONLY  6
#define BSD_ONLY  1

// location of test file dir relative to project executable
const std::string data_dir = std::string("../data/");
void clear_screen();
bool is_jsonlike_valid(std::string expected_filename, std::string got_filename);

template<typename T>
std::string to_string(std::string file, T& t, char c=',');

int main(int argc, char** argv) {

  // minimize noisy effect of having to prefix everything with std::
  using namespace std;
  clear_screen();

  bool ok = false;
  try {
    string out;

// READING JSON-like EMPTY FILES TEST (00-empty_*.json, 01-empty_*.json, 02-empty_*.json)
    cartoon c;
    cout << "============ IMPORTANT  ============\n";
    cout << "All file locations are relative to 'bin' as the compiled executable is run from 'bin' directory.\n\n";

    cout << "============ READ FROM JSON-like FILES ============\n";
    cout << "empty: ../data/0[012]-empty_*.json\n  testing empty files";

      out = to_string("00-empty_object.json", c);
      if (!out.empty()) throw string("FAILED WITH: empty object");

      out = to_string("01-empty_array.json", c);
      if (!out.empty()) throw string("FAILED WITH: empty array");

      out = to_string("02-empty_array_with_empty_object.json", c);
      if (!out.empty()) throw string("FAILED WITH: empty array containing empty object");

    cout << "...OK!\n";

// READING JSON-like CARTOON OBJECTS TEST (03-*_cartoon_*.json, 04-*_cartoon_*.json, 05-*_cartoon_*.json)
    cout << "\ncartoons: ../data/0[345]*_cartoon_*.json\n"
         << "  testing with one cartoon in JSON-like and output delimited by ','";

      out = to_string("03-one_cartoon_object.json", c);
      if ( out != "cat,Tom,mice\n")
        throw string(
    "FAILED: reading one cartoon object from ../data/03-one_cartoon_object.json and output delimited by ,\n") +
              string("EXPECTED: cat,Tom,mice\n") +
              string("GOT: ") + out;

      out = to_string("04-array_with_one_cartoon_object.json", c);
      if ( out != "cat,Tom,mice\n")
        throw string(
    "FAILED: reading one cartoon object from ../data/04-array_with_one_cartoon_object.json and output delimited by ,\n") +
              string("EXPECTED:=>cat,Tom,mice\n") +
              string("GOT:=>") + out;

    cout << "...OK!\n";

    cout << "  testing with many cartoon in JSON-like and output format delimited with ':'";
      out = to_string("05-array_with_few_cartoon_objects.json",c, ':');
      if ( out != "cat:Tom:mice\nmouse:Jerry:cheese\n")
        throw string(
    "FAILED: reading 2 cartoon objects from 05-array_with_few_cartoon_objects.json and output delimited with :\n")  +
              string("EXPECTED:=>cat:Tom:mice\nmouse:Jerry:cheese\n") +
              string("GOT:=>") + out;

    cout << "...OK!\n";

// READING JSON-like COURSE OBJECTS TEST (06-*_course*.json, 07-*_course*.json)
    cout << "\ncourses: ../data/0[67]*_courses_*.json\n"
         << "  testing with many course items in JSON-like and output format delimited with ';'";

      course crs;
      auto expected_courses_dsv=\
            "Game Engine Techniques;GAM532;DPS932\n"\
            "Data Structures And Algorithms In C++;DSA555;\n"\
            "Windows Programming Using C#;;DPS910\n";

      out = to_string("06-array_with_few_course_objects.json", crs, ';');
      if ( out != expected_courses_dsv)
        throw string("FAILED: reading ../data/06-array_with_few_course_objects.json and output delimited with ;\n")  +
              string("EXPECTED:=>") + expected_courses_dsv +
              string("GOT:=>") + out;

    cout << "...OK!\n";

    cout << "\n============ WRITE TO JSON-like FILES ============\n";

// WRITING (got_array_with_no_cartoon_object.json) CARTOON OBJECT TO JSON-like TEST
    cout << "filter from ../data/0*_*.json and write to ../data/got_*.json\n"
         << "  testing no dogs, named Spike, were written from 05-array_with_few_cartoon_objects.json";

      shared_ptr<vector<cartoon>> cartoons(project::readFromJsonLike(data_dir + "05-array_with_few_cartoon_objects.json", c));
      vector<cartoon> dog;

      // using for_each to get cartoon object (dog = Spike)
      for_each(cartoons->begin(), cartoons->end(), [&dog](cartoon& c) {
          if (c.get_type()== "dog" && c.get_name() == "Spike" )
            dog.emplace_back(c);
        });

      int no_dogs = project::writeToJsonLike(&dog, data_dir + "got_array_with_no_cartoon_object.json");
      if (no_dogs != 0)
        throw string(
    "\nFAILED: read 05-array_with_few_cartoon_objects.json, filter, and write\n EXPECTED: empty json-like file");

    cout << "...OK!\n\n";

// WRITING (got_array_with_*_object*.json) COURSE OBJECT TO JSON-like TEST
    cout  << "  testing " << PRO_CPA << " CPA and "
          << PRO_BSD << " BSD were read from 07-array_with_many_course_objects.json";

      shared_ptr<vector<course>> courses(project::readFromJsonLike(data_dir + "07-array_with_many_course_objects.json", crs));

      // using query algorithm with a lambda expression
      auto pro_cpa = count_if(courses->begin(), courses->end(), [](course& c){ return (!c.get_cpa().empty()); });
      auto pro_bsd = count_if(courses->begin(), courses->end(), [](course& c){ return (!c.get_bsd().empty()); });

      if (pro_cpa != PRO_CPA || pro_bsd != PRO_BSD)
        throw string("\nFAILED: 07-array_with_many_course_objects.json\n")  +
              string("EXPECTED:=> ") + to_string(PRO_CPA) + string(" CPA and ") + to_string(PRO_BSD) + string(" BSD options\n")  +
              string("GOT:=> ") + to_string(pro_cpa) + string(" CPA and ")  + to_string(pro_bsd) + " BSD options.";

    cout << "...OK!\n";

    cout << "  testing " << CPA_ONLY  << " CPA-only and "
         << BSD_ONLY << " BSD-only were read from 07-array_with_many_course_objects.json";

      vector<course> cpa, bsd;

      for_each(courses->begin(), courses->end(), [&cpa](course& c) { if (c.get_bsd().empty()) cpa.emplace_back(c); });
      for_each(courses->begin(), courses->end(), [&bsd](course& c) { if (c.get_cpa().empty()) bsd.emplace_back(c); });


      int no_cpa = project::writeToJsonLike(&cpa, data_dir + "got_array_with_many_cpa_objects.json");
      int no_bsd = project::writeToJsonLike(&bsd, data_dir + "got_array_with_one_bsd_object.json");

      if (cpa.size() != CPA_ONLY || bsd.size() != BSD_ONLY)
        throw string("\nFAILED: filter  write 07-array_with_many_course_objects.json\n") +
              string("EXPECTED:=> 6 CPA only courses and 1 BSD only course\n") +
              string("GOT:=> ") + to_string(no_cpa) + string(" CPA and ") + to_string(no_bsd) + string(" BSD.");

    cout << "...OK!\n";

// ARE THE WRITTEN JSON-like FILES VALID?
    cout << "\n============ VERIFY SAVED FILES ARE JSON-like ============\n";
    cout << "comparing ../data/got_*.json with ../data/expected_*.json\n";

      string expected_json[] = {
        "expected_array_with_no_cartoon_object.json",
        "expected_array_with_one_bsd_object.json",
        "expected_array_with_many_cpa_objects.json"
      };

      string got_json[] = {
        "got_array_with_no_cartoon_object.json",
        "got_array_with_one_bsd_object.json",
        "got_array_with_many_cpa_objects.json"
      };

      for(int i=0; i<3; i++){
        cout << "  testing if " << got_json[i] << " written by you was valid";
        ok=is_jsonlike_valid(expected_json[i],got_json[i]);
        if (!ok)
          throw string("\n FAILED: " + got_json[i] +
                       "\nEXPECTED: output should be exactly like " + data_dir + expected_json[i]);
        cout << "...OK!\n";
      }
      cout << "\n";


// ALL OK
      ok = true;

  }
  catch(const string& e){
      cerr << e << "\n";
  }

  if (ok)
    cout << "CONGRATULATIONS! You passed all tests.\n"
         << "You may now hand-in your project according to your professor's instructions.\n";
  return 0;
}

bool is_jsonlike_valid(std::string expected_filename, std::string got_filename){

  bool valid=true;

  std::ifstream expected(data_dir + expected_filename);
  std::ifstream actual(data_dir + got_filename);

  std::string eline, aline;

  while (!expected.eof() && valid){
    getline(expected, eline);
    getline(actual, aline);
    //std::cout << "\neline " << eline << '\n';
    //std::cout << "aline " << aline << '\n';
    if (eline != aline) valid=false;
  }

  return valid;
}

template<typename T>
std::string to_string(std::string file, T& t, char c){

  std::string output;
  try{
    std::shared_ptr<std::vector<T>> l(project::readFromJsonLike(data_dir + file, t));

    for(auto item: *l){
      //  std::cout << item << "\n";
      output += item.to_DSV(c) + "\n";
    }
  }
  catch(const std::string& e){
    std::cerr << e << "\n";
    std::exit(0);
  }

  return output;
}

// clear display - platform dependent
void clear_screen() {
#ifdef _MSC_VER
    system("cls");
#else
    system("clear");
#endif
}
