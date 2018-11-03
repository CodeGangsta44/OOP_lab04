#include <iostream>
#include "organization.h"

using namespace std;

int main(){
  Client_item *it1 = new Client_item("Turbo", 500);
  Client_item *it2 = new Client_item("Block", 20);
  Client_item *it3 = new Client_item("Piston", 51);
  Store_item *check1 = new Store_item("Turbo", 500);
  Store_item *check2 = new Store_item("Block", 200);
  Store_item *check3 = new Store_item("Piston", 69);

  Storage<Store_item> store(4);
  Storage<Client_item> order(3);
  store.add(*check1, *check2, *check3);
  order.add(*it1, *it2, *it3);

  Client<Client_item, Accounting_dep> *cl = new Client<Client_item, Accounting_dep>("Roma", 4444);
  Accounting_dep *firma = new Accounting_dep();

  firma->add(store);
  cl->create_order(firma, order);
  cout << cl->get_name() << " Money:" << cl->get_budget() << endl;
  Store_item *result = &firma->get_item("Turbo");
  cout << firma->get_budget() << endl;
  return 0;
}
