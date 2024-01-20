#include <systemc>
#include "routing_tb.h"
#include "Routing_XY_Moore.h"
#include "Routing_XY_Mealy.h"
#include "Routing.h"

#define WIDTH 8
#define id 17
#define y_id 1
#define x_id 1
#define MODE 0

SC_MODULE(SYSTEM){
    IRouting *routing0;
    routing_tb<WIDTH,x_id,y_id> *tb;

    sc_clock clk_w;
    sc_signal<bool> rst_w;
    sc_signal<bool> frame_w;
    sc_signal<sc_bv<WIDTH>> data_w;
    sc_signal<bool> rok_w;
    sc_signal<bool> rd_w;
    sc_signal<bool> req_l_o;
    sc_signal<bool> req_n_o;
    sc_signal<bool> req_e_o;
    sc_signal<bool> req_s_o;
    sc_signal<bool> req_w_o;

     SC_CTOR(SYSTEM):clk_w("clk_w",10,SC_NS){
         if(MODE == 0)
            routing0 = new  Routing_XY_Moore("routing0",0,id,0);
         else
            routing0 = new  Routing_XY_Mealy("routing0",0,id,0);

            routing0->i_CLK(clk_w);
            routing0->i_RST(rst_w);
            routing0->i_ROK(rok_w);
            routing0->i_RD(rd_w);
            routing0->i_DATA(data_w);
            routing0->i_FRAME(frame_w);
            routing0->o_REQ_E(req_e_o);
            routing0->o_REQ_L(req_l_o);
            routing0->o_REQ_S(req_s_o);
            routing0->o_REQ_W(req_w_o);
            routing0->o_REQ_N(req_n_o);

            tb = new routing_tb<WIDTH,x_id,y_id>("tb");

            tb->clk_i(clk_w);
            tb->rst_i(rst_w);
            tb->rok_i(rok_w);
            tb->rd_i(rd_w);
            tb->data_i(data_w);
            tb->frame_i(frame_w);
            tb->req_e_o(req_e_o);
            tb->req_l_o(req_l_o);
            tb->req_s_o(req_s_o);
            tb->req_w_o(req_w_o);
            tb->req_n_o(req_n_o);

     }

    ~SYSTEM(){
        delete  routing0;
        delete  tb;
    }
};

SYSTEM *top = NULL;

int sc_main(int argc, char* argv[]){

    top = new SYSTEM("top");
    //sc_start(150, SC_NS);]
    sc_start();
    
    return 0;

}
