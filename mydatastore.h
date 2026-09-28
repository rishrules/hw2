#ifndef MYDATASTORE_H
#define MYDATASTORE_H_H
#include "datastore.h"

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

  private:


};



#endif