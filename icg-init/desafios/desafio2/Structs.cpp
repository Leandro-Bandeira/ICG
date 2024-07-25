#include "Structs.h"



ConfigData::Structs::Structs(){
  counter_click_line = 0;
}


void ConfigData::Structs::set_points_line(int x, int y, int ord){
  
  if(ord == 0){
    xi_line = x;
    yi_line = y;
  }else{
    xf_line = x;
    yf_line = y;
  }

}
