#include "systemc.h"

template<int data_width_p, int buffer_depth_p>

SC_MODULE(fifo_tb){
    sc_in_clk clk_i;
    sc_out<bool>rst_i;
    sc_out<bool> rd_i, wr_i;

    sc_in<bool> rok_o, wok_o;

    sc_out<sc_bv<data_width_p>> data_i;
    sc_in<sc_bv<data_width_p>> data_o;

    void logic(){
        data_i.write("00000000");
        rst_i = 1;
        wait(10, SC_NS);
        rst_i = 0;
        wait(10, SC_NS);

        sc_bv<data_width_p> words[10] = {"00000001", "00000011", "00000111", "00001111", "00011111", "00111111", "01111111", "11111111", "11111110", "11111100"};

        data_i.write(0);
        for(int i=0; i<10; i++){
            if(wok_o == 1){
                data_i.write(words[i]);
                wait(10, SC_NS);
            }
            wait(10, SC_NS);
        }
        wait(100, SC_NS);
        sc_stop();
    }
    void wr(){
        while(true){
            while(wok_o == 1){
                wr_i.write(1);
                wait(10, SC_NS);
            }
            while(wok_o == 0) {
                wr_i.write(0);
                wait(10, SC_NS);
            }
        }

    }

    void rd(){
        while(true){
            while(rok_o == 1){
                rd_i.write(1);
                wait(10, SC_NS);
            }
            while(rok_o == 0) {
                rd_i.write(0);
                wait(10, SC_NS);
            }
        }
    }

    SC_CTOR(fifo_tb){
        sensitive << clk_i.pos();
        SC_THREAD(logic);
        SC_THREAD(wr);
        SC_THREAD(rd);

        sc_trace_file *wf = sc_create_vcd_trace_file("fifo_shift");
//         sc_trace_file *wf = sc_create_vcd_trace_file("fifo_ring");

        sc_trace(wf, data_i, "input");
        sc_trace(wf, data_o, "output");
        sc_trace(wf, rst_i, "rst_i");
        sc_trace(wf, rd_i, "rd_i");
        sc_trace(wf, wr_i, "wr_i");
        sc_trace(wf, rok_o, "rok_o");
        sc_trace(wf, wok_o, "wok_o");
        sc_trace(wf, clk_i, "clk_i");
    }
};
