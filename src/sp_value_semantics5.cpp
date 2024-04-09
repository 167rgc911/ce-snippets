/*
 * =====================================================================================
 *
 *       Filename:  sp_value_semantics5.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  04/08/24 21:00:33
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
#include <string>
#include <vector>

void
draw (const int &x, std::ostream &out, std::size_t position)
{
  out << std::string (position, ' ') << x << std::endl;
}

void
draw (const std::string &x, std::ostream &out, std::size_t position)
{
  out << std::string (position, ' ') << x << std::endl;
}

class object_t
{
public:
  object_t (const std::string &x) : object_ (new string_model_t (x))
  {
    std::cout << "string::ctor" << std::endl;
  }

  object_t (const int &x) : object_ (new int_model_t (x))
  {
    std::cout << "int::ctor" << std::endl;
  }

  object_t (const object_t &x) : object_ (x.object_->copy_ ())
  {
    std::cout << "::copy" << std::endl;
  }
  object_t (object_t &&x) = default;
  object_t &
  operator= (object_t x)
  {
    object_ = std::move (x.object_);
    return *this;
  }

  friend void
  draw (const object_t &x, std::ostream &out, std::size_t position)
  {
    x.object_->draw (out, position);
  }

private:
  struct concept_t
  {
    virtual ~concept_t () = default;
    virtual concept_t *copy_ () = 0;
    virtual void draw (std::ostream &, std::size_t) const = 0;
  };
  struct string_model_t : concept_t
  {
    string_model_t (const std::string &x) : data_ (x) {}
    concept_t *
    copy_ ()
    {
      return new string_model_t (*this);
    }
    void
    draw (std::ostream &out, std::size_t position) const
    {
      ::draw (data_, out, position);
    }

    std::string data_;
  };
  struct int_model_t : concept_t
  {
    int_model_t (const int &x) : data_ (x) {}
    concept_t *
    copy_ ()
    {
      return new int_model_t (*this);
    }
    void
    draw (std::ostream &out, std::size_t position) const
    {
      ::draw (data_, out, position);
    }

    int data_;
  };
  std::unique_ptr<concept_t> object_;
};

using document_t = std::vector<object_t>;

void
draw (const document_t &x, std::ostream &out, std::size_t position)
{
  out << std::string (position, ' ') << "document" << std::endl;
  for (auto e : x)
    draw (e, out, position + 2);
  out << std::string (position, ' ') << "/document" << std::endl;
}

int
main ()
{
  document_t document;

  document.reserve (5);

  document.emplace_back (0);
  document.emplace_back (std::string ("Hello"));
  document.emplace_back (2);
  document.emplace_back (3);

  std::reverse (document.begin (), document.end ());

  draw (document, std::cout, 0);
}
