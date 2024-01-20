#include <systemc.h>
#include "Router.h"
#include "XINA_Router.h"
#include "router_tb.h"

#define flow_mode_p        0
#define routing_mode_p     1
#define arbitration_mode_p 0
#define buffer_mode_p      0

#define buffer_depth_p     16
#define data_width_p       8

#define x_id_p             1
#define y_id_p             1
#define l_ena_p            1
#define n_ena_p            1
#define e_ena_p            1
#define s_ena_p            1
#define w_ena_p            1

SC_MODULE(SYSTEM){

    IRouter *router0;
    router_tb<data_width_p> *tb;

    sc_clock        clk_i;
    sc_signal<bool> rst_i;

    sc_signal<sc_bv<data_width_p+1>> l_in_data_i;
    sc_signal<bool>              l_in_val_i;
    sc_signal<bool>              l_in_ack_o;
    sc_signal<sc_bv<data_width_p+1>> l_out_data_o;
    sc_signal<bool>              l_out_val_o;
    sc_signal<bool>              l_out_ack_i;

    sc_signal<sc_bv<data_width_p+1>> n_in_data_i;
    sc_signal<bool>              n_in_val_i;
    sc_signal<bool>              n_in_ack_o;
    sc_signal<sc_bv<data_width_p+1>> n_out_data_o;
    sc_signal<bool>              n_out_val_o;
    sc_signal<bool>              n_out_ack_i;

    sc_signal<sc_bv<data_width_p+1>> e_in_data_i;
    sc_signal<bool>              e_in_val_i;
    sc_signal<bool>              e_in_ack_o;
    sc_signal<sc_bv<data_width_p+1>> e_out_data_o;
    sc_signal<bool>              e_out_val_o;
    sc_signal<bool>              e_out_ack_i;

    sc_signal<sc_bv<data_width_p+1>> s_in_data_i;
    sc_signal<bool>              s_in_val_i;
    sc_signal<bool>              s_in_ack_o;
    sc_signal<sc_bv<data_width_p+1>> s_out_data_o;
    sc_signal<bool>              s_out_val_o;
    sc_signal<bool>              s_out_ack_i;

    sc_signal<sc_bv<data_width_p+1>> w_in_data_i;
    sc_signal<bool>              w_in_val_i;
    sc_signal<bool>              w_in_ack_o;
    sc_signal<sc_bv<data_width_p+1>> w_out_data_o;
    sc_signal<bool>              w_out_val_o;
    sc_signal<bool>              w_out_ack_i;

    SC_CTOR(SYSTEM):clk_i("clk_i",10,SC_NS){

        router0 = new XINA_Router("router0",x_id_p,y_id_p,l_ena_p,n_ena_p,e_ena_p,s_ena_p,w_ena_p,flow_mode_p,routing_mode_p,arbitration_mode_p,buffer_mode_p);

        router0->i_CLK(clk_i);
        router0->i_RST(rst_i);
        router0->i_IN_DATA_L(l_in_data_i);
        router0->i_IN_VAL_L(l_in_val_i);
        router0->o_IN_ACK_L(l_in_ack_o);
        router0->o_OUT_DATA_L(l_out_data_o);
        router0->o_OUT_VAL_L(l_out_val_o);
        router0->i_OUT_ACK_L(l_out_ack_i);

        router0->i_IN_DATA_N(n_in_data_i);
        router0->i_IN_VAL_N(n_in_val_i);
        router0->o_IN_ACK_N(n_in_ack_o);
        router0->o_OUT_DATA_N(n_out_data_o);
        router0->o_OUT_VAL_N(n_out_val_o);
        router0->i_OUT_ACK_N(n_out_ack_i);

        router0->i_IN_DATA_E(e_in_data_i);
        router0->i_IN_VAL_E(e_in_val_i);
        router0->o_IN_ACK_E(e_in_ack_o);
        router0->o_OUT_DATA_E(e_out_data_o);
        router0->o_OUT_VAL_E(e_out_val_o);
        router0->i_OUT_ACK_E(e_out_ack_i);

        router0->i_IN_DATA_S(s_in_data_i);
        router0->i_IN_VAL_S(s_in_val_i);
        router0->o_IN_ACK_S(s_in_ack_o);
        router0->o_OUT_DATA_S(s_out_data_o);
        router0->o_OUT_VAL_S(s_out_val_o);
        router0->i_OUT_ACK_S(s_out_ack_i);

        router0->i_IN_DATA_W(w_in_data_i);
        router0->i_IN_VAL_W(w_in_val_i);
        router0->o_IN_ACK_W(w_in_ack_o);
        router0->o_OUT_DATA_W(w_out_data_o);
        router0->o_OUT_VAL_W(w_out_val_o);
        router0->i_OUT_ACK_W(w_out_ack_i);

        tb = new router_tb<data_width_p>("tb");

        tb->clk_i(clk_i);
        tb->rst_i(rst_i);

        tb->l_in_data_i(l_in_data_i);
        tb->l_in_val_i(l_in_val_i);
        tb->l_in_ack_o(l_in_ack_o);
        tb->l_out_data_o(l_out_data_o);
        tb->l_out_val_o(l_out_val_o);
        tb->l_out_ack_i(l_out_ack_i);

        tb->n_in_data_i(n_in_data_i);
        tb->n_in_val_i(n_in_val_i);
        tb->n_in_ack_o(n_in_ack_o);
        tb->n_out_data_o(n_out_data_o);
        tb->n_out_val_o(n_out_val_o);
        tb->n_out_ack_i(n_out_ack_i);

        tb->e_in_data_i(e_in_data_i);
        tb->e_in_val_i(e_in_val_i);
        tb->e_in_ack_o(e_in_ack_o);
        tb->e_out_data_o(e_out_data_o);
        tb->e_out_val_o(e_out_val_o);
        tb->e_out_ack_i(e_out_ack_i);

        tb->s_in_data_i(s_in_data_i);
        tb->s_in_val_i(s_in_val_i);
        tb->s_in_ack_o(s_in_ack_o);
        tb->s_out_data_o(s_out_data_o);
        tb->s_out_val_o(s_out_val_o);
        tb->s_out_ack_i(s_out_ack_i);

        tb->w_in_data_i(w_in_data_i);
        tb->w_in_val_i(w_in_val_i);
        tb->w_in_ack_o(w_in_ack_o);
        tb->w_out_data_o(w_out_data_o);
        tb->w_out_val_o(w_out_val_o);
        tb->w_out_ack_i(w_out_ack_i);

     }
    ~SYSTEM(){
        delete  router0;
        delete  tb;
    }
};

SYSTEM *top = NULL;

int sc_main(int argc, char* argv[]){

    top = new SYSTEM("top");
    ///sc_start(1500, SC_NS);
    sc_start();

    return 0;

}
