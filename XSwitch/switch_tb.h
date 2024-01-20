#include <systemc.h>
#include "Switch.h"


#define WIDTH 9

SC_MODULE(switch_tb) {
    sc_out<sc_bv<4>> sel_i;
    sc_out<sc_bv<WIDTH>> data3_i, data2_i, data1_i, data0_i;
    sc_in<sc_bv<WIDTH>> data_o;
//     sc_out<bool> data3_i, data2_i, data1_i, data0_i;
//     sc_in<bool> data_o;

    void logic(){
        sel_i.write("1000");
        data0_i.write("100000000");
        data1_i.write("000000001");
        data2_i.write("000000011");
        data3_i.write("000000111");
        wait(10, SC_NS);

        sel_i.write("0000");
        wait(10, SC_NS);

        sel_i.write("0100");
        wait(10, SC_NS);

        sel_i.write("0000");
        wait(10, SC_NS);

        sel_i.write("0001");
        wait(10, SC_NS);

        sel_i.write("0000");
        wait(10, SC_NS);

        sel_i.write("0010");
        wait(10, SC_NS);

        sel_i.write("0000");
        wait(10, SC_NS);

        sel_i.write("0000");
/*
         sel_i.write("1000");
        data0_i.write(1);
        data1_i.write(1);
        data2_i.write(1);
        data3_i.write(1);
        wait(10, SC_NS);

        sel_i.write("0000");
        wait(10, SC_NS);

        sel_i.write("0100");
        wait(10, SC_NS);

        sel_i.write("0000");
        wait(10, SC_NS);

        sel_i.write("0001");
        wait(10, SC_NS);

        sel_i.write("0000");
        wait(10, SC_NS);

        sel_i.write("0010");
        wait(10, SC_NS);

        sel_i.write("0000");
        wait(10, SC_NS);

        sel_i.write(0);*/
        wait(100, SC_NS);
        sc_stop();
    }

    SC_CTOR(switch_tb){
        SC_THREAD(logic);
        sensitive << sel_i, data3_i, data2_i, data1_i, data0_i;

        sc_trace_file *wf = sc_create_vcd_trace_file("switch_tb");

        sc_trace(wf, data0_i, "data0");
        sc_trace(wf, data1_i, "data1");
        sc_trace(wf, data2_i, "data2");
        sc_trace(wf, data3_i, "data3");
        sc_trace(wf, data_o, "data_o");
        sc_trace(wf, sel_i, "sel");
    }
};
