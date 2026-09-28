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

  info << "Product_category: Book\n" << "Name: " << name_ << '\n' << "Price: " << price_ << '\n'
  << "Quantity: " << qty_ << '\n' << "ISBN: " << ISBN_ << '\n' << "Author: " << author_;
  return info.str();
}

void Book::dump(std::ostream& os) const{
  os << ISBN_ << "\n" << author_ << endl;
}