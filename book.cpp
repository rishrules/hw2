#include "book.h"
#include "util.h"

#include <sstream>
#include <iomanip>
using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, 
  string ISBN, string author) : Product(category, name, price, qty) {
  ISBN_ = ISBN; author_ = author;
}

Book::~Book(){

}

set<std::string> Book::keywords() const{
  set<string> k = parseStringToWords(name_);
  k.insert(ISBN_);
  return k;
}

std::string Book::displayString() const{
  std::ostringstream info;

  info << name_ << '\n' << "Author: " << author_<< " ISBN: " << ISBN_ << '\n' << price_ <<  " " << qty_ << " left.";
  return info.str();
}

void Book::dump(std::ostream& os) const{
  os << ISBN_ << "\n" << author_ << endl;
}