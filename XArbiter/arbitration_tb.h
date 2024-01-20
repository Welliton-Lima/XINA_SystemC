#include <systemc.h>

SC_MODULE(arbitration_tb){

    sc_in_clk clk_w;
    sc_out<bool> rst_w;
    sc_out<sc_bv<4>> req_w;
    sc_in<sc_bv<4>> gnt_w;

    void logic(){

        sc_bv<4> count[8] = {"0000", "0001", "0010", "0100", "1000", "0100", "0001", "0010"};
        req_w.write("0000");
        wait(10,SC_NS);
        for(int i=0; i<8; i++){
            req_w.write(count[i]);
            wait(10,SC_NS);
        }
        wait(10,SC_NS);
        sc_stop();
    }
    void reset(){
        rst_w = 1;
        wait(10, SC_NS);
        rst_w = 0;
        wait(10, SC_NS);
    }


    SC_CTOR(arbitration_tb){
        sensitive<< clk_w;
        SC_THREAD(logic);
        SC_THREAD(reset);


        sc_trace_file *wf = sc_create_vcd_trace_file("arbitration_tb");

        sc_trace(wf, clk_w, "clk");
        sc_trace(wf, rst_w, "rst");
        sc_trace(wf, req_w, "req_w");
        sc_trace(wf, gnt_w, "gnt_w");


    }
};
