#include "systemc.h"
#include <string>
#include <iostream>

using namespace std;

template<unsigned int rows_c,unsigned int cols_c,unsigned int data_width_c>
SC_MODULE(XINA_tb){

    sc_in<bool> clk_i;
    sc_out<bool> rst_i;

    sc_in<sc_bv<data_width_c+1>>   l_out_data_o[cols_c][rows_c];

    sc_in <bool>                   l_in_ack_o[cols_c][rows_c];
    sc_in<bool>                    l_out_val_o[cols_c][rows_c];

    sc_out<bool>                   l_in_val_i[cols_c][rows_c];
    sc_out<bool>                   l_out_ack_i[cols_c][rows_c];
    sc_out<sc_bv<data_width_c+1> > l_in_data_i[cols_c][rows_c];



    void rst(){
        rst_i.write(1);
        wait(10, SC_NS);
        rst_i.write(0);
        wait(10, SC_NS);
    }

     void test(){

        sc_bv<data_width_c+1> pack_n[3][4]  = {{"100010001", "000000001", "000000010", "100000011"},
                                               {"100010001", "000000101", "000000110", "100000111"},
                                               {"100010001", "000001001", "000001010", "100001011"}};

        sc_bv<data_width_c+1> pack_n2[3][4]  = {{"100010000", "000000001", "000000010", "100000011"},
                                                {"100010000", "000000101", "000000110", "100000111"},
                                                {"100010000", "000001001", "000001010", "100001011"}};

        sc_bv<data_width_c+1> pack_n3[3][4]  = {{"100000001", "000000001", "000000010", "100000011"},
                                                {"100000001", "000000101", "000000110", "100000111"},
                                                {"100000001", "000001001", "000001010", "100001011"}};



        sc_bv<data_width_c+1> pack_n4[3][4]  = {{"100000000", "000000001", "000000010", "100000011"},
                                                {"100000000", "000000101", "000000110", "100000111"},
                                                {"100000000", "000001001", "000001010", "100001011"}};


        l_in_val_i[0][0].write(0);
        //wait(10, SC_NS);

    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){

            l_in_data_i[0][0].write(pack_n[i][j]);

            l_in_val_i[0][0].write(1);
            wait(l_in_ack_o[0][0].posedge_event());
            wait(10, SC_NS);
            l_in_val_i[0][0].write(0);
            wait(l_in_ack_o[0][0].negedge_event());
        }
        l_in_val_i[0][0].write(0);
    }
        l_in_val_i[0][0].write(0);
        l_in_data_i[0][0].write(0);

    for(int i=0; i<3; i++){
        for(int j=0; j<4; j++){
            l_in_data_i[0][1].write(pack_n2[i][j]);

            l_in_val_i[0][1].write(1);
            wait(l_in_ack_o[0][1].posedge_event());
            wait(10, SC_NS);
            l_in_val_i[0][1].write(0);
            wait(l_in_ack_o[0][1].negedge_event());
        }
        l_in_val_i[0][1].write(0);
       //// wait(10, SC_NS);
    }
        l_in_val_i[0][1].write(0);
        l_in_data_i[0][1].write(0);


        for(int i=0; i<3; i++){
        for(int j=0; j<4; j++){
            l_in_data_i[1][0].write(pack_n3[i][j]);

            l_in_val_i[1][0].write(1);
            wait(l_in_ack_o[1][0].posedge_event());
            wait(10, SC_NS);
            l_in_val_i[1][0].write(0);
            wait(l_in_ack_o[1][0].negedge_event());
        }
        l_in_val_i[1][0].write(0);
        ///wait(10, SC_NS);
    }
        l_in_val_i[1][0].write(0);
        l_in_data_i[1][0].write(0);

    for(int i=0; i<3; i++){
        for(int j=0; j<4; j++){
            l_in_data_i[1][1].write(pack_n4[i][j]);

            l_in_val_i[1][1].write(1);
            wait(l_in_ack_o[1][1].posedge_event());
            wait(10, SC_NS);
            l_in_val_i[1][1].write(0);
            wait(l_in_ack_o[1][1].negedge_event());
        }
    }
        l_in_val_i[1][1].write(0);
        l_in_data_i[1][1].write(0);

        wait(500, SC_NS);
        sc_stop();
    }

    void o_00(){
        while(true){
            l_out_ack_i[0][0].write(0);
            wait(l_out_val_o[0][0].posedge_event());
            wait(10, SC_NS);
            l_out_ack_i[0][0].write(1);
            wait(l_out_val_o[0][0].negedge_event());
            wait(10, SC_NS);
        }
    }

    void o_01(){
        while(true){
            l_out_ack_i[0][1].write(0);
            wait(l_out_val_o[0][1].posedge_event());
            wait(10, SC_NS);
            l_out_ack_i[0][1].write(1);
            wait(l_out_val_o[0][1].negedge_event());
            wait(10, SC_NS);
        }
    }

    void o_10(){
        while(true){
            l_out_ack_i[1][0].write(0);
            wait(l_out_val_o[1][0].posedge_event());
            wait(10, SC_NS);
            l_out_ack_i[1][0].write(1);
            wait(l_out_val_o[1][0].negedge_event());
            wait(10, SC_NS);
        }
    }

    void o_11(){

        while(true){
            l_out_ack_i[1][1].write(0);
            wait(l_out_val_o[1][1].posedge_event());
            wait(10, SC_NS);
            l_out_ack_i[1][1].write(1);
            wait(l_out_val_o[1][1].negedge_event());
            wait(10, SC_NS);
        }
    }

    SC_CTOR(XINA_tb){
        SC_THREAD(test);
        SC_THREAD(o_00);
        SC_THREAD(o_01);
        SC_THREAD(o_10);
        SC_THREAD(o_11);
        SC_THREAD(rst);

        sensitive << clk_i << rst_i;

        sc_trace_file *wf = sc_create_vcd_trace_file("XINA_tb");

        sc_trace(wf, clk_i, "clk");
        sc_trace(wf, rst_i, "rst");

        int each = 0;
        for(int i=0; i<cols_c; i++){
            for(int j=0; j<rows_c; j++){
                sc_trace(wf, clk_i, "CLK");
                sc_trace(wf, l_in_data_i [i][j], "l_in_data_i" +to_string(each));
                sc_trace(wf, l_in_val_i  [i][j], "l_in_val_i"  +to_string(each));
                sc_trace(wf, l_in_ack_o  [i][j], "l_in_ack_o"  +to_string(each));
                sc_trace(wf, l_out_data_o[i][j], "l_out_data_o"+to_string(each));
                sc_trace(wf, l_out_val_o [i][j], "l_out_val_o" +to_string(each));
                sc_trace(wf, l_out_ack_i [i][j], "l_out_ack_i" +to_string(each));

                each++;
            }
        }
    }
};
