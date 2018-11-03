
#include <string.h>

using namespace std;

class Item{
  protected:
    char* name;
    int amount;
  public:
    Item(){};
    Item(const char* _name, int _amount){
      name = new char();
      strcpy(name, _name);
      amount = _amount;
    }
    void set_name(const char* _name){
      name = new char();
      strcpy(name, _name);
    }
    char* get_name(){
      return name;
    }
    void set_amount(int _amount){
      amount = _amount;
    }
    int get_amount(){
      return amount;
    }
    void add(int num){
      amount += num;
    }
    bool subtract(int num){
      if(amount >= num){
        amount -= num;
        return true;
      } else return false;
    }
    ~Item(){
      delete name;
    }
};

class cl_item_abs{
  protected:
    char* date_of_arrival;
    int purchase_price;
  public:
    void set_date(const char* date){
      date_of_arrival = new char();
      strcpy(date_of_arrival, date);
    }
    char* get_date(){
      return date_of_arrival;
    }
    void set_pur_price(int price){
      purchase_price = price;
    }
    int get_pur_price(){
      return purchase_price;
    }
    ~cl_item_abs(){
      delete date_of_arrival;
    }
};

class Client_item : public Item, public cl_item_abs{
  public:
    Client_item():Item(){
      this->set_date("");
      this->set_pur_price(0);
    };
    Client_item(const char* _name, int _amount) : Item(_name, _amount){
      this->set_date("");
      this->set_pur_price(0);
    };
};

class pr_item_abs{
  protected:
    int selling_price;
  public:
    void set_selling_price(int price){
      selling_price = price;
    }
    int get_selling_price(){
      return selling_price;
    }
};

class Prov_item : public Item, public pr_item_abs{
  public:
    Prov_item():Item(){};
    Prov_item(const char* _name, int _amount) : Item(_name, _amount){
      this->set_selling_price(0);
    };
};

class Store_item : public Item, public cl_item_abs, public pr_item_abs{
  public:
    Store_item():Item(){
      this->set_date("");
      this->set_pur_price(0);
      this->set_selling_price(0);
    };
    Store_item(const char* _name, int _amount) : Item(_name, _amount) {
      this->set_date("");
      this->set_pur_price(0);
      this->set_selling_price(0);
    };
    Store_item(Store_item & original):Item(original.get_name(), original.get_amount()){
      this->set_date(original.get_date());
      purchase_price = original.get_pur_price();
      selling_price = original.get_selling_price();
    }
};
