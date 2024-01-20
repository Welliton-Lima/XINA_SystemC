#include <systemc>
#include "Channel_in.h"
#include "xin_tb.h"

#define flow_mode_p     0
#define routing_mode_p  0
#define buffer_mode_p   0
#define buffer_depth_p  8
#define data_width_p    8
#define c_ena 1
#define x_id 1
#define y_id 1

SC_MODULE(SYSTEM){
    Channel_in *channel_in0;
    xin_tb<data_width_p,routing_mode_p> *tb;

    sc_clock clk_i;
    sc_signal<bool> rst_i;
    sc_signal<sc_bv<data_width_p+1>> data_i;
    sc_signal<bool> val_i;
    sc_signal<bool> ack_o;

    sc_signal<bool> req_l_o, req_n_o, req_e_o, req_s_o, req_w_o;
    sc_signal<sc_bv<4>> gnt_i;

    sc_signal<bool> rok_o;
    sc_signal<sc_bv<4>> rd_i;
    sc_signal<sc_bv<data_width_p+1>> data_o;

//      sc_signal<bool> c_ena;
//      sc_signal<unsigned int> x_id,y_id;


     SC_CTOR(SYSTEM): clk_i("clk_i",10,SC_NS){

        channel_in0 = new Channel_in ("channel_in0",c_ena,flow_mode_p,routing_mode_p,buffer_depth_p,x_id,y_id);

        channel_in0->i_RST(rst_i);
        channel_in0->i_CLK(clk_i);
        channel_in0->i_DATA(data_i);
        channel_in0->i_VAL(val_i);
        channel_in0->o_ACK(ack_o);
        channel_in0->o_L_REQ(req_l_o);
        channel_in0->o_N_REQ(req_n_o);
        channel_in0->o_E_REQ(req_e_o);
        channel_in0->o_S_REQ(req_s_o);
        channel_in0->o_W_REQ(req_w_o);
        channel_in0->i_GNT(gnt_i);
        channel_in0->o_ROK(rok_o);
        channel_in0->i_RD(rd_i);
        channel_in0->o_DATA(data_o);

        tb = new xin_tb<data_width_p,routing_mode_p>("tb");

        tb->rst_i(rst_i);
        tb->clk_i(clk_i);
        tb->data_i(data_i);
        tb->val_i(val_i);
        tb->ack_o(ack_o);
        tb->req_l_o(req_l_o);
        tb->req_n_o(req_n_o);
        tb->req_e_o(req_e_o);
        tb->req_s_o(req_s_o);
        tb->req_w_o(req_w_o);
        tb->gnt_i(gnt_i);
        tb->rok_o(rok_o);
        tb->rd_i(rd_i);
        tb->data_o(data_o);
    }
    ~SYSTEM(){
        delete  channel_in0;
        delete  tb;
    }
};

SYSTEM *top = NULL;

int sc_main(int argc, char* argv[]) {

    top = new SYSTEM("top");

    sc_start();

    return 0;
}
