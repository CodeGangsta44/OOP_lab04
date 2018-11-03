#include "invoice.h"

using namespace std;

class Accounting_dep;

template<class type, class sel>
class Client{
  protected:
    char* name;
    int budget;
    Storage<type> stor;
    int count_of_inv;
    int num_of_inv;
    Invoice<type, sel, Client<type, sel>> curr_inv;
    Invoice<type, sel, Client<type, sel>> *arr_of_invs;
  public:
    Client(){
      name = new char();
      strcpy(name, "");
      budget = 0;
      count_of_inv = 0;
      num_of_inv = 10;
      arr_of_invs = new Invoice<type, sel, Client<type, sel>>();
    };
    Client(const char* _name, int _budget){
      name = new char();
      strcpy(name, _name);
      budget = _budget;
      count_of_inv = 0;
      num_of_inv = 10;
      arr_of_invs = new Invoice<type, sel, Client<type, sel>>();
    }
    void set_name(const char* _name){
      name = new char();
      strcpy(name, _name);
    }
    char* get_name(){
      return name;
    }
    void set_budget(int _budget){
      budget = _budget;
    }
    int get_budget(){
      return budget;
    }
    void add_money(int num){
      budget += num;
    }
    bool pay(int num){
      if(budget > num){
        budget -= num;
        return true;
      } else return false;
    }
    type& get_item(const char* item_name){
      return stor.get_item(item_name);
    }
    void create_order(sel* seller, Storage<type>& items){
      curr_inv = seller->get_order(items);
      curr_inv.set_buyer(this);
      curr_inv.calculate();
      curr_inv.pay();
      curr_inv.confirm();
    }
    void add(Storage<type>& positions){
      for(int i = 0; i < positions.get_counter(); i++){
        stor.add(positions[i]);
      }
    }
};

class prov;

class Accounting_dep : public Client<Store_item, prov>{
  public:
    Accounting_dep():Client<Store_item, prov>(){};
    Accounting_dep(const char* _name, int _budget):Client<Store_item, prov>(_name, _budget){};

    Invoice<Client_item, Accounting_dep, Client<Client_item, Accounting_dep>>&
    get_order(Storage<Client_item>& order){
      bool check = true;
      for(int i = 0; i < order.get_counter(); i++){
        Store_item *curr = new Store_item(order[i].get_name(), order[i].get_amount());
        bool result = this->stor.check_avai(*curr);
        check = check && result;
      }
      if(check){
        Invoice<Client_item, Accounting_dep, Client<Client_item, Accounting_dep>> *inv
        = new Invoice<Client_item, Accounting_dep, Client<Client_item, Accounting_dep>>(order, this);
        return *inv;
      }
    }
    void add(Storage<Store_item>& items){
      for(int i = 0; i < items.get_counter(); i++){
        this->stor.add(items[i].get_name(), items[i].get_amount());
      }
    }
    void give_goods(Storage<Client_item>& order){
      for(int i = 0; i < order.get_counter(); i++){
        Store_item *curr = new Store_item(order[i].get_name(), order[i].get_amount());
        this->stor.take(*curr);
      }
    }
    int calculate(Storage<Client_item>& order){
      int total = 0;
      for(int i = 0; i < order.get_counter(); i++){

        int am = order[i].get_amount();
        this->stor.get_counter();
        int price = this->stor.get_item(order[i].get_name()).get_pur_price() + 1;
        total += (am*price);
      }
      return total;
    }
};
