#ifndef CLOTHING_H
#define CLOTHING_H

#include "product.h"


class Clothing : public Product {
  public:
    Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand);
    ~Clothing(); //maybe need it
    std::set<std::string> keywords() const; //Returns the appropriate keywords that this product should be associated with
    std::string displayString() const; //Returns a string to display the product info for hits of the search
    void dump(std::ostream& os) const; //Outputs the product info in the database format
  private:
    std::string size_, brand_;
};


#endif