#include "mydatastore.h"
#include "util.h"
using namespace std;


MyDataStore::~MyDataStore(){
  for (size_t i = 0; i < products_.size(); i++) {
    delete products_[i];
  }

  for (size_t i = 0; i < users_.size(); i++) {
    delete users_[i];
  }
}

void MyDataStore::addProduct(Product* p){
  products_.push_back(p);
  set<string> keywords = p->keywords();
  for (set<string>::iterator it = keywords.begin(); it !=keywords.end(); ++it){
    keyW_[*it].insert(p);
  }
}

void MyDataStore::addUser(User* u){
  users_.push_back(u);
  string name = convToLower(u->getName());
  user_map_[name] = u;
  carts_[name] = vector<Product*>();//creates an empty list of products for each new user
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
  set<Product*> search_result;
  if (terms.empty()) {
    return vector<Product*>();
  }
  if (type == 0){
    map<string, set<Product*> >::iterator it = keyW_.find(convToLower(terms[0]));
    if (it == keyW_.end()){
      return vector<Product*>();
    }
    search_result = it->second;
    for (size_t i = 1; i < terms.size();i++){
      it = keyW_.find(convToLower(terms[i]));
      if (it == keyW_.end()){//that is if any AND term doesnt exist in keyw, we return empty list
        return vector<Product*>();
      }
      search_result = setIntersection(search_result, it->second);
      if (search_result.empty()){
        break;
      }
    }
  }
  else if (type == 1){
    for (size_t i = 0; i < terms.size(); i++){
      map<string, set<Product*> >::iterator it = keyW_.find(convToLower(terms[i]));
      if (it != keyW_.end()){
        search_result.insert((it->second).begin(), (it->second).end());
      }
    }
  }
  vector<Product*> hits(search_result.begin(),search_result.end());
  return hits;
}

void MyDataStore::dump(std::ostream& ofile){
  ofile << "<products>" << endl;
  for (size_t i = 0; i < products_.size(); i++){
    products_[i]->dump(ofile);
  }
  ofile << "</products>" << endl;
  ofile << "<users>" << endl;
  for (size_t i = 0; i < users_.size(); i++){
    users_[i]->dump(ofile);
  }
  ofile << "</users>";
}
void MyDataStore::addCart(const std::string& username, Product* product){
  string name = convToLower(username);
   map<string, User*>::iterator it = user_map_.find(name);
  if (it == user_map_.end() || product == nullptr){
    cout << "Invalid request" << endl;
    return;
  }
   carts_[name].push_back(product);
}

vector<Product*> MyDataStore::viewCart(const std::string& username) const{
  string name = convToLower(username);
  if (user_map_.find(name) == user_map_.end()){
    cout << "Invalid username" << endl;
    return std::vector<Product*>();
  }
  map<string, vector<Product*>>::const_iterator it = carts_.find(name);
  if (it == carts_.end()){
    return std::vector<Product*>(); //that is cart is empty
  }
   return it->second;
}

void MyDataStore::buyCart(const std::string& username){
  string name = convToLower(username);
  map<string, User*>::iterator it = user_map_.find(name);
  if (it == user_map_.end()){
    cout << "Invalid username" << endl;
    return;
  }
  User* user = it->second;
  map<string, vector<Product*> >::iterator cartIt = carts_.find(name);
  if (cartIt == carts_.end()){
    return;
  }
  vector<Product*>& cart = cartIt->second;
  vector<Product*>::iterator product_it = cart.begin();
  while(product_it !=cart.end()){
    Product* product = *product_it;
    if (product->getQty() > 0 && user->getBalance() >= product->getPrice()){
      product->subtractQty(1);
      user->deductAmount(product->getPrice());
      product_it = cart.erase(product_it);
    }
    else{
      ++product_it;
    }
  }
}
