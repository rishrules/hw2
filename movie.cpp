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
  k.insert(convToLower(genre_));
  return k;
}

std::string Movie::displayString() const{
  std::ostringstream info;

  info << name_ << '\n' << "Genre: " << genre_<< " Rating: " << rating_ << '\n' << price_ << " " << qty_ << " left.";
  return info.str();
}

void Movie::dump(std::ostream& os) const{
  Product::dump(os);
  os << genre_ << "\n" << rating_ << endl;
}
