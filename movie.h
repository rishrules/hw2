#ifndef MOVIE_H
#define MOVIE_H

#include "product.h"

class Movie : public Product {
  public:
    Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating);
    ~Movie(); //maybe need it
    std::set<std::string> keywords() const; //Returns the appropriate keywords that this product should be associated with
    std::string displayString() const; //Returns a string to display the product info for hits of the search
    void dump(std::ostream& os) const; //Outputs the product info in the database format
  private:
    std::string genre_, rating_;
};



#endif