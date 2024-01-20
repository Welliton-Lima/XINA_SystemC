#include <systemc>
#include "arbitration_tb.h"
#include "Arbiter.h"
#include "Arbitration_RR_Moore.h"
#include "Arbitration_RR_Mealy.h"

#define MODE 0

SC_MODULE(SYSTEM){
    IArbiter *rr;
    arbitration_tb *tb;

    sc_clock w_clk_i;
    sc_signal<bool> rst_w;
    sc_signal<sc_bv<4>> req_w;
    sc_signal<sc_bv<4>> gnt_w;


     SC_CTOR(SYSTEM): w_clk_i("w_clk_i",10,SC_NS){
         if(MODE == 0)
            rr = new Arbitration_RR_Moore("rr",0,0,0);
         else
            rr = new Arbitration_RR_Mealy("rr",0,0,0);

            rr->i_CLK(w_clk_i);
            rr->i_RST(rst_w);
            rr->i_REQ(req_w);
            rr->o_GNT(gnt_w);

            tb = new arbitration_tb("tb");
            tb->clk_w(w_clk_i);
            tb->rst_w(rst_w);
            tb->req_w(req_w);
            tb->gnt_w(gnt_w);

     }
    ~SYSTEM(){
        delete  rr;
        delete  tb;
    }
};

SYSTEM *top = NULL;

int sc_main(int argc, char* argv[]){

    top = new SYSTEM("top");

    sc_start();
    
    return 0;

}
