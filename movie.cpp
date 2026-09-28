#include "movie.h"
#include "util.h"

#include <sstream>
#include <iomanip>
using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, 
  string genre, string rating) : Product(category, name, price, qty) {
  genre_ = genre; rating_ = rating;
}

Movie::~Movie(){

}

set<std::string> Movie::keywords() const{
  set<string> k = parseStringToWords(name_);
  k.insert(genre_);
  return k;
}

std::string Movie::displayString() const{
  std::ostringstream info;

  info << "Product_category: Book\n" << "Name: " << name_ << '\n' << "Price: " << price_ << '\n'
  << "Quantity: " << qty_ << '\n' << "Genre: " << genre_ << '\n' << "Rating: " << rating_;
  return info.str();
}

void Movie::dump(std::ostream& os) const{
  os << genre_ << "\n" << rating_ << endl;
}