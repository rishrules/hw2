#include "clothing.h"
#include "util.h"

#include <sstream>
#include <iomanip>
using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, 
  string size, string brand) : Product(category, name, price, qty) {
  size_ = size; brand_ = brand;
}

Clothing::~Clothing(){

}

set<std::string> Clothing::keywords() const{
  set<string> k = parseStringToWords(name_);
  set<string> b = parseStringToWords(brand_);
  return setUnion(k, b);
}

std::string Clothing::displayString() const{
  std::ostringstream info;

  info << "Product_category: Book\n" << "Name: " << name_ << '\n' << "Price: " << price_ << '\n'
  << "Quantity: " << qty_ << '\n' << "Size: " << size_ << '\n' << "Brand: " << brand_;
  return info.str();
}

void Clothing::dump(std::ostream& os) const{
  os << size_ << "\n" << brand_ << endl;
}