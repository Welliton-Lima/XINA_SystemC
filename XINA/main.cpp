#include "systemc"

#include "XINA_tb.h"
#include "XINA.h"
#include "NoC.h"

#define cols_c 2
#define rows_c 2

#define buffer_depth_p     8
#define data_width_c       8

SC_MODULE(SYSTEM){

    INoC *xina;
//      XINA *xina;

    XINA_tb<rows_c,cols_c,data_width_c> *tb;

    sc_clock        clk_i;
    sc_signal<bool> rst_i;

    sc_signal<sc_bv<data_width_c+1>> i_IN_DATA_L [cols_c][rows_c];
    sc_signal<bool>                  i_IN_VAL_L  [cols_c][rows_c];
    sc_signal<bool>                  o_IN_ACK_L  [cols_c][rows_c];
    sc_signal<sc_bv<data_width_c+1>> o_OUT_DATA_L[cols_c][rows_c];
    sc_signal<bool>                  o_OUT_VAL_L [cols_c][rows_c];
    sc_signal<bool>                  i_OUT_ACK_L [cols_c][rows_c];

     SC_CTOR(SYSTEM):clk_i("clk_i",10,SC_NS){
        xina = new XINA("XINA");

        tb = new XINA_tb<rows_c,cols_c,data_width_c>("tb");

        xina->i_CLK(clk_i);
        xina->i_RST(rst_i);

        tb->clk_i(clk_i);
        tb->rst_i(rst_i);

        unsigned int k=0;
        for(int i=0; i<cols_c; i++){
            for(int j=0; j<rows_c; j++){
                xina->i_DATA_IN    [k](i_IN_DATA_L [i][j]);
                xina->i_VALID_IN   [k](i_IN_VAL_L  [i][j]);
                xina->o_RETURN_IN  [k](o_IN_ACK_L  [i][j]);
                xina->o_DATA_OUT   [k](o_OUT_DATA_L[i][j]);
                xina->o_VALID_OUT  [k](o_OUT_VAL_L [i][j]);
                xina->i_RETURN_OUT [k](i_OUT_ACK_L [i][j]);


                tb->l_in_data_i[i][j](i_IN_DATA_L [i][j]);
                tb->l_in_val_i[i][j](i_IN_VAL_L  [i][j]);
                tb->l_in_ack_o[i][j](o_IN_ACK_L  [i][j]);
                tb->l_out_data_o[i][j](o_OUT_DATA_L[i][j]);
                tb->l_out_val_o[i][j](o_OUT_VAL_L [i][j]);
                tb->l_out_ack_i[i][j](i_OUT_ACK_L [i][j]);
                k++;
            }
        }
     }
    ~SYSTEM(){
        delete  xina;
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
