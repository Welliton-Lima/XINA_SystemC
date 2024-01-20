#include <systemc.h>
#include "Flow_in.h"
#include "Flow_in_Moore.h"
#include "Flow_in_Mealy.h"
#include "flow_in_tb.h"

#define WIDTH 9
#define MODE 0

SC_MODULE(SYSTEM){
    IFlow_in *flow_i;
    flow_in_tb<WIDTH> *tb;

    sc_clock w_clk;
    sc_signal<bool> w_rst;
    sc_signal<sc_bv<WIDTH>> w_data_i;
    sc_signal<sc_bv<WIDTH>> w_data_o;
    sc_signal<bool> w_val;
    sc_signal<bool> w_wok;
    sc_signal<bool> w_ack;
    sc_signal<bool> w_wr;

     SC_CTOR(SYSTEM): w_clk("clk",10,SC_NS){
         if( MODE == 0)
            flow_i = new Flow_in_Moore("flow_i");
         else
            flow_i = new Flow_in_Mealy("flow_i");

            flow_i->i_CLK(w_clk);
            flow_i->i_RST(w_rst);
            flow_i->i_DATA(w_data_i);
            flow_i->i_VAL(w_val);
            flow_i->i_WOK(w_wok);
            flow_i->o_ACK(w_ack);
            flow_i->o_WR(w_wr);
            flow_i->o_DATA(w_data_o);

            tb = new flow_in_tb<WIDTH>("tb");

            tb->clk_i(w_clk);
            tb->rst_i(w_rst);
            tb->data_i(w_data_i);
            tb->val_i(w_val);
            tb->wok_i(w_wok);
            tb->ack_o(w_ack);
            tb->wr_o(w_wr);
            tb->data_o(w_data_o);
     }
    ~SYSTEM(){
        delete  flow_i;
        delete  tb;
    }
};

SYSTEM *top = NULL;

int sc_main(int argc, char* argv[]){

    top = new SYSTEM("top");

    sc_start();
    
    return 0;

}
