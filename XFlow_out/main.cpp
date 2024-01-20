#include <systemc.h>
#include "Flow_out.h"
#include "Flow_out_Moore.h"
#include "Flow_out_Mealy.h"
#include "flow_out_tb.h"

#define WIDTH 9
#define MODE 1

SC_MODULE(SYSTEM){
    IFlow_out *flow_o;
    flow_out_tb<WIDTH> *tb;

    sc_clock w_clk_i;
    sc_signal<bool> w_rst_i;

    sc_signal<sc_bv<WIDTH>> w_data_i, w_data_o;
    sc_signal<bool> w_val_o, w_rok_i, w_ack_i, w_rd_o;


     SC_CTOR(SYSTEM): w_clk_i("clk_i",10,SC_NS){
         if(MODE==0)
            flow_o = new Flow_out_Moore("flow_o");
         else
            flow_o = new Flow_out_Mealy("flow_o");

            flow_o->i_CLK(w_clk_i);
            flow_o->i_RST(w_rst_i);
            flow_o->i_ROK(w_rok_i);
            flow_o->i_ACK(w_ack_i);
            flow_o->i_DATA(w_data_i);
            flow_o->o_VAL(w_val_o);
            flow_o->o_RD(w_rd_o);
            flow_o->o_DATA(w_data_o);

            tb = new flow_out_tb<WIDTH>("tb");

            tb->clk_i(w_clk_i);
            tb->rst_i(w_rst_i);
            tb->rok_i(w_rok_i);
            tb->ack_i(w_ack_i);
            tb->data_i(w_data_i);
            tb->rd_o(w_rd_o);
            tb->val_o(w_val_o);
            tb->data_o(w_data_o);
     }
    ~SYSTEM(){
        delete  flow_o;
        delete  tb;
    }
};

SYSTEM *top = NULL;

int sc_main(int argc, char* argv[]){

    top = new SYSTEM("top");

    sc_start();
    
    return 0;

}
