#include "storage.h"

using namespace std;

template<class type, class sel, class buy>
class Invoice{
  protected:
    sel *seller;
    buy *buyer;
    int total;
    bool payment_status;
    Storage<type> positions;
  public:
    Invoice(){
      total = 0;
      payment_status = false;
    }
    Invoice(sel* _seller){
      seller = _seller;
      total = 0;
      payment_status = false;
    }
    Invoice(Storage<type>& goods_list, sel* _seller){
      seller = _seller;
      total = 0;
      payment_status = false;
      positions = goods_list;
    }

    void set_seller(sel* _seller){
      seller = _seller;
    }
    void set_buyer(buy* _buyer){
      buyer = _buyer;
    }
    void calculate(){
      total = seller->calculate(positions);
    }
    void pay(){
      payment_status = buyer->pay(total);
    }
    void confirm(){
      if(payment_status){
        buyer->add(positions);
        seller->give_goods(positions);
        seller->add_money(total);
        cout << "Товари передаються покупцю" << endl;
      } else {
        cout << "Товари не передалися покупцеві(оплата не проведена)" << endl;
      }
    }
};
