#include <systemc>
#include "switch_tb.h"
#include "Switch.h"
#include "Switch_Data.h"

#define WIDTH 9

SC_MODULE(SYSTEM){
//     Switch_module *sw;
    Switch_Data *sw;

    switch_tb *tb;

    sc_signal<sc_bv<4>> w_sel_i;

//     sc_signal<bool> w_data3_i;
//     sc_signal<bool> w_data2_i;
//     sc_signal<bool> w_data1_i;
//     sc_signal<bool> w_data0_i;
//     sc_signal<bool> w_data_o;

    sc_signal<sc_bv<WIDTH>> w_data3_i;
    sc_signal<sc_bv<WIDTH>> w_data2_i;
    sc_signal<sc_bv<WIDTH>> w_data1_i;
    sc_signal<sc_bv<WIDTH>> w_data0_i;
    sc_signal<sc_bv<WIDTH>> w_data_o;

     SC_CTOR(SYSTEM){
//             sw = new Switch_module("sw");
            sw = new Switch_Data("sw");
            sw->i_DATA0(w_data0_i);
            sw->i_DATA1(w_data1_i);
            sw->i_DATA2(w_data2_i);
            sw->i_DATA3(w_data3_i);
            sw->i_SEL(w_sel_i);
            sw->o_DATA(w_data_o);


            tb = new switch_tb("tb");
            tb->data0_i(w_data0_i);
            tb->data1_i(w_data1_i);
            tb->data2_i(w_data2_i);
            tb->data3_i(w_data3_i);
            tb->sel_i(w_sel_i);
            tb->data_o(w_data_o);

     }
    ~SYSTEM(){
        delete  sw;
        delete  tb;
    }
};

SYSTEM *top = NULL;

int sc_main(int argc, char* argv[]){

    top = new SYSTEM("top");
    sc_start(150, SC_NS);
    
    return 0;

}
