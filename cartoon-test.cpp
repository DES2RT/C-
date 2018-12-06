// cartoon-test.cpp
// Greg Blair
// April 1, 2015

#include <iostream>
#include <vector>
#include <iomanip>      // setw + friends
#include <utility>      // pair, make_pair
using namespace std;

#include "cartoon.h"

#if 0
// how to use pair<-,-> x, x = make_pair(-,-), x.first, x.second
// http://www.cplusplus.com/reference/utility/make_pair/

// make_pair example
#include <utility>      // pair
#include <iostream>     // cout

int main () {
  pair <int,int> foo;
  pair <int,int> bar;

  foo = make_pair (10,20);
  bar = make_pair (10.5,'A'); // ok: implicit conversion from pair<double,char>

  cout << "foo: " << foo.first << ", " << foo.second << '\n';
  cout << "bar: " << bar.first << ", " << bar.second << '\n';

  return 0;
}
#endif

int main(int argc, char** argv)
{
     // {
         // "type": "cat",
         // "name": "Tom",
         // "likes": "mice"
     // },
     // {
         // "type": "mouse",
         // "name": "Jerry",
         // "likes": "cheese"
     // }

  vector< pair<string,string> > v1;

  v1.push_back( make_pair( string("type") , string("cat") ) );
  v1.push_back( make_pair( string("name") , string("Tom") ) );
  v1.push_back( make_pair( string("likes"), string("mice") ) );
  cout<<"v1->"; for(auto e : v1) cout << "{\"" << e.first << "\":\"" << e.second << "\"}"; cout << "\n";

  cout << "cartoon1:\n";
  cartoon cartoon1;
  cartoon1.set(v1);
  cout << "to_DSV returned=" << cartoon1.to_DSV();
  cout << "to_json returned=\n" << cartoon1.to_json(4);
  cout << "\n";

  vector<pair<string,string>> v2;

  v2.push_back( make_pair( string("type") , string("mouse") ) );
  v2.push_back( make_pair( string("name") , string("Jerry") ) );
  v2.push_back( make_pair( string("likes"), string("cheese") ) );
  cout<<"v2->"; for(auto e : v2) cout << "{\"" << e.first << "\":\"" << e.second << "\"}"; cout << "\n";

  cout << "cartoon2:\n";
  cartoon cartoon2;
  cartoon2.set(v2);
  cout << "\nto_DSV returned=" << cartoon2.to_DSV();
  cout << "\nto_json returned=\n" << cartoon2.to_json(4);
  cout << "\n";

  std::vector<cartoon>* all = new std::vector<cartoon>;

  all->push_back(cartoon1);
  all->push_back(cartoon2);

  int count = 0;
  for( auto e : *all) {
     cerr << "NODE all[" << setw(2) << count << "] to_dsv() returned '" << e.to_DSV() << "'\n";
     cerr << "NODE all[" << setw(2) << count << "] to_json(4) returned \n'" << e.to_json() << "'\n";
     count++;
  }

}
