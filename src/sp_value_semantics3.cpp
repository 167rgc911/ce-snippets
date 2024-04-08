/*
 * =====================================================================================
 *
 *       Filename:  sp_value_semantics3.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/08/24 12:28:14
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  rgc (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

void
draw(const int& x, std::ostream& out, std::size_t position)
{
  out << std::string(position, ' ') << x << std::endl;
}

class
object_t
{
public:
  object_t(const int& x) : object_(x) {}
  friend void draw(const object_t& x, std::ostream& out, std::size_t position)
  { draw(x.object_, out, position); }
private:
  int object_;
};

using document_t = std::vector<object_t>;

void
draw(const document_t& x, std::ostream& out, std::size_t position)
{
  out << std::string(position, ' ') << "document" << std::endl;
  for (auto e: x) draw(e, out, position + 2);
  out << std::string(position, ' ') << "/document" << std::endl;
}


int
main()
{
  document_t document;

  document.emplace_back(0);
  document.emplace_back(1);
  document.emplace_back(2);
  document.emplace_back(3);

  draw(document,std::cout, 0);
}
