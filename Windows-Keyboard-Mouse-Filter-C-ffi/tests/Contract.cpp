#include "InterceptorBridge.h"
#include <windows.h>
#include <stdexcept>
#include <cstring>
#include <thread>
#include <iostream>
extern "C" __declspec(dllimport) void windows_keyboard_mouse_filter_test_mode(unsigned);
extern "C" __declspec(dllimport) long long windows_keyboard_mouse_filter_test_seen(unsigned,unsigned);
void Check(bool value) {if(!value)throw std::runtime_error("Product C ABI contract failed");}
bool Allowed(unsigned kind) {return kind<=2 ? (TEST_INPUT_MASK&(1u<<(kind-1)))!=0 : (TEST_CONTROLLER_MASK&(1u<<(kind-3)))!=0;}
int main() {
 try {
  Check(!std::strcmp(windows_keyboard_mouse_filter_product_name(),TEST_PRODUCT));
  Check(windows_keyboard_mouse_filter_input_mask()==TEST_INPUT_MASK && windows_keyboard_mouse_filter_controller_mask()==TEST_CONTROLLER_MASK);
  Check(windows_keyboard_mouse_filter_version()==1 && windows_keyboard_mouse_filter_sizeof(1)==sizeof(windows_keyboard_mouse_filter_field) && windows_keyboard_mouse_filter_sizeof(6)==sizeof(windows_keyboard_mouse_filter_info));
  unsigned expected=0;for(unsigned k=1;k<=6;++k)if(Allowed(k))++expected;
  windows_keyboard_mouse_filter_error error{};uint64_t session=0,other=0;
  Check(!windows_keyboard_mouse_filter_open(&session,&error));Check(windows_keyboard_mouse_filter_open(&other,&error)==ERROR_BUSY && !other);
  windows_keyboard_mouse_filter_init init{};Check(!windows_keyboard_mouse_filter_initialize(session,&init,&error)&&init.ready);
  windows_keyboard_mouse_filter_info info{};Check(!windows_keyboard_mouse_filter_info_get(session,&info,&error));
  Check(info.input_mask==TEST_INPUT_MASK && info.controller_mask==TEST_CONTROLLER_MASK);
  const windows_keyboard_mouse_filter_devices* devices=nullptr;Check(!windows_keyboard_mouse_filter_devices_get(session,&devices,&error)&&devices->count==expected);
  for(unsigned n=0;n<devices->count;++n)Check(Allowed(devices->items[n].kind));
  const windows_keyboard_mouse_filter_batch* batch=nullptr;Check(!windows_keyboard_mouse_filter_receive(session,0,&batch,&error)&&batch->count==expected);
  auto ticket=batch->id;const windows_keyboard_mouse_filter_batch* unused=nullptr;
  Check(windows_keyboard_mouse_filter_receive(session,0,&unused,&error)==ERROR_BUSY && !unused);
  for(unsigned n=0;n<batch->count;++n) {
   auto& event=batch->events[n];Check(Allowed(event.kind));Check(event.sequence>0x7fffffffffffffffull);
   for(unsigned f=0;f<event.field_count;++f) {
    auto& field=event.fields[f];
    if(event.kind==1 && !std::strcmp(field.name,"scan_code"))field.value=0x30;
    if(event.kind==2 && !std::strcmp(field.name,"y"))field.value=-7;
    if((event.kind==3 || event.kind==5) && field.group==WINDOWS_KEYBOARD_MOUSE_FILTER_AXIS && field.index==0){field.value=50;field.normalized=.5;}
    if(event.kind==4 && !std::strcmp(field.name,"left_x"))field.value=-100;
   }
  }
  Check(!windows_keyboard_mouse_filter_send(session,ticket,&error)&&error.accepted==expected);
  if(Allowed(1))Check(windows_keyboard_mouse_filter_test_seen(1,1)==0x30);
  if(Allowed(2))Check(windows_keyboard_mouse_filter_test_seen(2,1)==-7);
  if(Allowed(3))Check(windows_keyboard_mouse_filter_test_seen(3,1)==50 && windows_keyboard_mouse_filter_test_seen(3,2)==500);
  Check(!windows_keyboard_mouse_filter_send(session,ticket,&error)&&!error.accepted);
  Check(!windows_keyboard_mouse_filter_receive(session,0,&batch,&error));Check(windows_keyboard_mouse_filter_send(session,ticket,&error)==ERROR_INVALID_HANDLE);
  batch->events[0].blocked=1;Check(!windows_keyboard_mouse_filter_send(session,batch->id,&error)&&error.accepted==expected-1);
  Check(!windows_keyboard_mouse_filter_receive(session,0,&batch,&error));windows_keyboard_mouse_filter_test_mode(2);
  Check(windows_keyboard_mouse_filter_send(session,batch->id,&error)==ERROR_BUSY && error.accepted==1);
  Check(!windows_keyboard_mouse_filter_send(session,batch->id,&error)&&error.accepted==expected-1);windows_keyboard_mouse_filter_test_mode(0);
  Check(!windows_keyboard_mouse_filter_receive(session,0,&batch,&error));Check(!windows_keyboard_mouse_filter_discard(session,batch->id,&error));
  for(unsigned kind=1;kind<=6;++kind)if(!Allowed(kind)) {
   windows_keyboard_mouse_filter_event input{};input.kind=kind;Check(windows_keyboard_mouse_filter_inject(session,&input,1,&error)==ERROR_NOT_SUPPORTED);
  }
  if(Allowed(2)) {
   windows_keyboard_mouse_filter_field x{};x.name="x";x.value=123;windows_keyboard_mouse_filter_event input{};input.kind=2;input.fields=&x;input.field_count=1;
   Check(!windows_keyboard_mouse_filter_inject(session,&input,1,&error)&&error.accepted==1);
  }
  windows_keyboard_mouse_filter_blob blob{};Check(!windows_keyboard_mouse_filter_descriptor(session,devices->items[0].token,1,&blob,&error));
  windows_keyboard_mouse_filter_test_mode(1);uint32_t result=999;
  std::thread reader([&]{windows_keyboard_mouse_filter_error e{};const windows_keyboard_mouse_filter_batch* empty=nullptr;result=windows_keyboard_mouse_filter_receive(session,5000,&empty,&e);});
  Sleep(30);Check(!windows_keyboard_mouse_filter_cancel(session,&error));reader.join();Check(!result);
  Check(!windows_keyboard_mouse_filter_close(session,&error));Check(windows_keyboard_mouse_filter_close(session,&error)==ERROR_INVALID_HANDLE);
  windows_keyboard_mouse_filter_test_mode(0);Check(!windows_keyboard_mouse_filter_open(&session,&error));Check(!windows_keyboard_mouse_filter_close(session,&error));
  std::cout<<TEST_PRODUCT<<": C ABI, product masks, edits, blocking, retries, uint64, injection and cancellation passed\n";
 }catch(const std::exception& e){std::cerr<<e.what()<<"\n";return 1;}
}
