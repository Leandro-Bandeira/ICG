#ifndef STRUCTS_H
#define STRUCTS_H



namespace  ConfigData{
class Structs{
  public:
    Structs();

    void set_points_line(int x, int y, int ord);

    void resetCounterLine(){counter_click_line = 0;};
    void incCounterLine(){counter_click_line+=1;};
    
    
    int xi_line;
    int yi_line;  
    int xf_line;
    int yf_line;

    int counter_click_line;
  private:
    
};
}









#endif 
