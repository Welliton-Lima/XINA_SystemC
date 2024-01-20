#include <systemc.h>
#include "Ring_Buffering.h"
#include "Shift_Buffering.h"
#include "fifo_tb.h"
#include "Memory.h"

#define WIDTH 9
#define DEPTH 8
#define MODE 1

SC_MODULE(SYSTEM){
    //Ring_buffering<WIDTH,DEPTH> *fifo;
    IMemory *fifo;
    fifo_tb<WIDTH, DEPTH> *tb;

    sc_clock clk;
    sc_signal<bool>w_rst;

    sc_signal<sc_bv<WIDTH>> w_data_i;
    sc_signal<sc_bv<WIDTH>> w_data_o;

    sc_signal<bool>w_rd_i;
    sc_signal<bool> w_wr_i;
    sc_signal<bool> w_rok_o;
    sc_signal<bool> w_wok_o;


     SC_CTOR(SYSTEM): clk("clk",10,SC_NS){
         if(MODE == 0)
            fifo = new Ring_Buffering("fifo");
         else
            fifo = new Shift_Buffering("fifo");

            fifo->i_RST(w_rst);
            fifo->i_CLK(clk);
            fifo->i_DATA(w_data_i);
            fifo->o_DATA(w_data_o);

            fifo->i_RD(w_rd_i);
            fifo->i_WR(w_wr_i);
            fifo->o_ROK(w_rok_o);
            fifo->o_WOK(w_wok_o);

            tb = new fifo_tb<WIDTH, DEPTH>("tb");
            tb->data_i(w_data_i);
            tb->data_o(w_data_o);
            tb->rst_i(w_rst);
            tb->rd_i(w_rd_i);
            tb->wr_i(w_wr_i);
            tb->rok_o(w_rok_o);
            tb->wok_o(w_wok_o);
            tb->clk_i(clk);
    }
    ~SYSTEM(){
        delete  fifo;
        delete  tb;
    }
};

SYSTEM *top = NULL;

int sc_main(int argc, char* argv[]) {

    top = new SYSTEM("top");

    sc_start();

    return 0;
}
