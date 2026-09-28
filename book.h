#ifndef BOOK_H
#define BOOK_H

#include "product.h"

class Book : public Product {
  public:
    Book(const std::string category, const std::string name, double price, int qty, std::string ISBN, std::string author);
    ~Book(); //maybe need it
    std::set<std::string> keywords() const; //Returns the appropriate keywords that this product should be associated with
    std::string displayString() const; //Returns a string to display the product info for hits of the search
    void dump(std::ostream& os) const; //Outputs the product info in the database format
  private:
    std::string ISBN_, author_;
};

#endif