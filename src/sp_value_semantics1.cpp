/*
 * =====================================================================================
 *
 *       Filename:  sp_value_semantics1.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  04/08/24 11:49:13
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

using object_t = int;

void
draw (const object_t &x, std::ostream &out, std::size_t position)
{
  out << std::string (position, ' ') << x << std::endl;
}

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

  document.emplace_back (0);
  document.emplace_back (1);
  document.emplace_back (2);
  document.emplace_back (3);

  draw (document, std::cout, 0);
}
