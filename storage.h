#include "item.h"
#include <string.h>

using namespace std;

template<class type>
class Storage{
  protected:
    int count;
    int number_of_items;
    type *available_goods;
  public:
    Storage(int num = 10){
      available_goods = new type[num];
      number_of_items = num;
      count = 0;
    }
    Storage(Storage & original){
      available_goods = new type[original.get_counter()];
      count = original.get_counter();
      number_of_items = original.get_num();
    }
    int get_counter(){
      return count;
    }
    int get_num(){
      return number_of_items;
    }
    void resize(){
      type *new_arr = new type[(number_of_items + 10)];
      for(int i = 0; i < number_of_items; i++){
        new_arr[i] = available_goods[i];
      }
      available_goods = new_arr;
      number_of_items += 10;
    }

    type& operator[](const char* name){
      for(int i = 0; i < count; i++){
        if(!strcmp(name, available_goods[i].get_name())){
          return available_goods[i];
        }
      }
      type* result = new type(name, 0);
      available_goods[count] = *result;
      if(count == number_of_items - 1) resize();
      return available_goods[count++];
    }
    type& operator[](int num){
      if(num < count){
        return available_goods[num];
      }
      type* result = new type();
      available_goods[count] = *result;
      return available_goods[count++];
    }

    int is_in_stor(const char* name){
      for(int i = 0; i < count; i++){
        if(!strcmp(name, available_goods[i].get_name())){
          return i;
        }
      }
      return -1;
    }

    void add(const char* name, int amount){
      (*this)[name].add(amount);
    }
    void add(type& item){
      (*this)[item.get_name()].add(item.get_amount());
    }
    template<class... args>
    void add(type& first, args&... rest){
      (*this)[first.get_name()].add(first.get_amount());
      add(rest...);
    }

    type& get_item(const char* name){
      return (*this)[name];
    }

    bool check_avai(type& item){
      return ((*this)[item.get_name()].get_amount() >= item.get_amount());
    }
    template<class... args>
    bool check_avai(type& first, args&... rest){
      return (((*this)[first.get_name()].get_amount() >= first.get_amount()) && check_avai(rest...));
    }

    void take(type& item){
      (*this)[item.get_name()].subtract(item.get_amount());
    }
    template<class... args>
    void take(type& first, args&... rest){
      (*this)[first.get_name()].subtract(first.get_amount());
      take(rest...);
    }
};
