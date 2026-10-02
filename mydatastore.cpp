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
  string name = convToLower(u->getName();
  user_map_[name] = u;
  carts_[name] = vector<Product*>();//creates an empty list of products for each new user
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
  set<Product*> search_result;
  lastHits_.clear();
  if (type == 0){
    map<string, set<Product*> >::iterator it = keyW_.find(terms[0]);
    if (it == keyW_.end()){
      return vector<Product*>();
    }
    search_result = it->second;
    for (size_t i = 1; i < terms.size();i++){
      it = keyW_.find(terms[i]);
      if (it == keyW_.end()){//that is if any AND term doesnt exist in keyw, we return empty list
        return vector<Product*>();
      }
      search_result = setIntersection(search_result, termIt->second);
      if (search_result.empty()){
        break;
      }
    }
  }
  else if (type == 1){
    for (size_t i = 0; terms.size(); i++){
      map<string, set<Product*> >::iterator it = keyW_.find(terms[i]);
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
    ofile << products_[i]->dump(ofile);
  }
  ofile << "</products>" << endl;
  ofile << "<users>" << endl;
  for (size_t i = 0; i < users_.size(); i++){
    users_[i]->dump(ofile);
  }
  ofile << "</users>";
}
void MyDataStore::addCart(const std::string& username, Product* product){
  username = convToLower(username);
   map<string, User*>::iterator it = user_map_.find(username);
  if (it == user_map_.end() || product == nullptr){
    cout << "Invalid request" << endl;
    return;
  }
   carts_[username].push_back(product);
}

void MyDataStore::viewCart(const std::string& username) const{
  username = convToLower(username);
  if (user_map_.find(username) == user_map_.end()){
    cout << "Invalid username" << endl;
    return std::vector<Product*>();
  }
   map<string, User*>::const_iterator it = carts_.find(username);
  if (it == carts_.end()){
    return std::vector<Product*>(); //that is cart is empty
  }
   return cartIt->second;
}

void MyDataStore::buyCart(const std::string& username){
  username = convToLower(username);
  map<string, User*>::iterator it = user_map_().find(username);
  if (it == user_map_.end()){
    cout << "Invalid username" << endl;
  }
  User* user = it->second;
  if (carts_.find(username) == carts_.end()){
    return;
  }
  vector<Product*>& cart = cartIt->second;
  vector<Product*>::iterator it = cart.begin();
  while(it !=cart.end()){
    Product* product = *it;
    if (product->getQty() > 0 && user->getBalance() >= product->getPrice()){
      product->subtractQty(1);
      user->deductAmount(product->getPrice());
      it = cart.erase(it);
    }
    else{
      ++it;
    }
  }
}