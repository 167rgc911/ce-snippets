/*
 * =====================================================================================
 *
 *       Filename:  sp_value_semantics9.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/09/24 10:16:41
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  rgc (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// forward decls
class object_t;
using document_t = std::vector<object_t>;
void draw(const document_t& x, std::ostream& out, std::size_t position);

class my_class_t;
void draw(const my_class_t& x, std::ostream& out, std::size_t position);

template <typename T>
void
draw(const T& x, std::ostream& out, std::size_t position)
{
  out << std::string(position, ' ') << x << std::endl;
}

class
object_t
{
public:
  template <typename T>
  object_t(const T& x) : object_(new model<T>(x)) { } 
  
  object_t(const object_t& x) : object_(x.object_->copy_()) { } 
  object_t(object_t&& x) = default;
  object_t& operator=(object_t x)
  { object_ = std::move(x.object_); return *this; }

  friend void draw(const object_t& x, std::ostream& out, std::size_t position)
  { x.object_->draw(out, position); }
private:
  struct concept_t
  {
    virtual ~concept_t() = default;
    virtual concept_t* copy_() = 0;
    virtual void draw(std::ostream&, std::size_t) const = 0;
  };
  template <typename T>
  struct model : concept_t
  {
    model(const T& x) : data_(x) {}
    concept_t* copy_() { return new model<T>(*this); }
    void draw(std::ostream& out, std::size_t position) const
    { ::draw(data_, out, position); }

    T data_;
  };
  std::unique_ptr<concept_t> object_;
};

using document_t = std::vector<object_t>;

void
draw(const document_t& x, std::ostream& out, std::size_t position)
{
  out << std::string(position, ' ') << "document" << std::endl;
  for (auto e: x) draw(e, out, position + 2);
  out << std::string(position, ' ') << "/document" << std::endl;
}

class my_class_t
{ };

void
draw(const my_class_t& x, std::ostream& out, std::size_t position)
{
  out << std::string(position, ' ') << "my_class_t" << std::endl;
}

using history_t = std::vector<document_t>;
void commit(history_t& x) { assert(x.size()); x.push_back(x.back()); }
void undo(history_t& x) { assert(x.size()); x.pop_back(); }
document_t& current(history_t& x) { assert(x.size()); return x.back(); }

int
main()
{
  history_t h(1);
  current(h).emplace_back(0);
  current(h).emplace_back(std::string("Hello"));
  draw(current(h), std::cout, 0);
  std::cout << "<----------------------------------------<" << std::endl;
  commit(h);

  current(h).emplace_back(current(h));
  current(h).emplace_back(my_class_t());
  current(h)[1] = std::string("World");
  draw(current(h), std::cout, 0);
  std::cout << "<----------------------------------------<" << std::endl;

  undo(h);
  draw(current(h), std::cout, 0);

  return 0;
}
