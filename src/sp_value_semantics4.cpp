/*
 * =====================================================================================
 *
 *       Filename:  sp_value_semantics4.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/08/24 12:33:08
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
#include <memory>
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
  object_t(const int& x) : object_(new int_model_t(x)) {}
  ~object_t() { delete object_; }
  
  object_t(const object_t& x) : object_(new int_model_t(*x.object_)) {}
  object_t& operator=(const object_t& x)
  { delete object_; object_ = new int_model_t(*x.object_); return *this; }

  friend void draw(const object_t& x, std::ostream& out, std::size_t position)
  { x.object_->draw(out, position); }
private:
  struct int_model_t
  {
    int_model_t(const int& x) : data_(x) {}
    void draw(std::ostream& out, std::size_t position) const
    { ::draw(data_, out, position); }

    int data_;
  };
  int_model_t* object_;
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
