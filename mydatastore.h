#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <map>
#include <set>
#include <string>
#include <vector>
#include "datastore.h"
#include "product.h"
#include "user.h"
class MyDataStore : public DataStore{
  public:
    ~MyDataStore();
    void addProduct(Product* p);//Adds a product to the data store
    void addUser(User* u);//Adds a user to the data store

    //Performs a search of products whose keywords match the given "terms"
    //type 0 = AND search (intersection of results for each term) while
    //type 1 = OR search (union of results for each term)
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    
    //Reproduce the database file from the current Products and User values
    void dump(std::ostream& ofile);

    void addCart(const std::string& username, Product* product);
    std::vector<Product*> viewCart(const std::string& username) const;
    void buyCart(const std::string& username);
  private:
  std::vector<Product*> products_;
  std::vector<User*> users_;
  std::map<std::string, std::set<Product*>> keyW_;//basically for each keyword->products with that keyword
  std::map<std::string, User*> user_map_;
  std::map<std::string, std::vector<Product*>> carts_;
  
};



#endif
