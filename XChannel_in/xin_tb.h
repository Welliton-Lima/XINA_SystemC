#include <systemc>

template<unsigned int data_width_p,unsigned int MODE_ROUTING>
SC_MODULE(xin_tb){

    sc_in<bool> clk_i;

    sc_out<bool> rst_i;
    sc_out<bool> val_i;

    sc_in<bool> ack_o;
    sc_in<bool> rok_o;
    sc_in<bool> req_l_o, req_n_o, req_e_o, req_s_o, req_w_o;

    sc_out<sc_bv<4>> gnt_i;
    sc_out<sc_bv<4>> rd_i;

    sc_out<sc_bv<data_width_p+1>> data_i;
    sc_in<sc_bv<data_width_p+1>> data_o;
    sc_bv<4> rd0;

    sc_bv<4> gnt0[4][4] = {{"1000", "1000", "1000", "1000"},{"0100", "0100", "0100", "0100"},{"0010", "0010", "0010", "0010"},{"0001", "0001", "0001", "0001"}};

void test(){
    data_i.write("000000000");
    sc_bv<data_width_p+1> pack_n[4][4] = {{"100010010", "000000010", "000000001", "100000111"},
                                            {"100100001", "000000010", "000000001", "100000111"},
                                            {"100010000", "000000010", "000000001", "100000111"},
                                            {"100000001", "000000010", "000000001", "100000111"}};

    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            while(ack_o.read() !=1){
                wait(10, SC_NS);
            }

            data_i.write(pack_n[i][j]);
            wait(10, SC_NS);

            gnt_i.write(gnt0[i][j]);
            rd0 = gnt0[i][j];
            wait(10, SC_NS);

            while(ack_o.read()!=0){
                wait(10, SC_NS);
            }

        }
    }
    wait(100, SC_NS);
    data_i.write("000000000");
    gnt_i.write("0000");
    wait(10,SC_NS);
    sc_stop();
}

void reset(){
    //data_i.write("00000000");
    rst_i.write(1);
    wait(10, SC_NS);
    rst_i.write(0);
    wait(10, SC_NS);
}

void ack(){
    while(true){
        val_i.write(0);
        while(ack_o.read()==1){
            wait(10, SC_NS);

        }
        val_i.write(1);
        while(ack_o.read()==0){
            wait(10,SC_NS);

        }
    }
}
void rd(){
    while(true){
        //wait(10, SC_NS);
        while(rok_o.read() == 1){
            wait(10, SC_NS);
            rd_i.write(rd0);
        }
        //wait(10, SC_NS);
        rd_i.write(0);
        while(rok_o.read()== 0){
            wait(10, SC_NS);
        }
    }
}


    SC_CTOR(xin_tb){
        SC_THREAD(ack);
        SC_THREAD(reset);
        SC_THREAD(test);
        SC_THREAD(rd);

        sensitive << clk_i.pos() << rst_i<< ack_o<<req_l_o<<req_n_o<<req_e_o<<req_s_o<<req_w_o<<rok_o<<data_o;

        sc_trace_file *wf = sc_create_vcd_trace_file("channel_in_mode1");

        sc_trace(wf, clk_i, "clk");
        sc_trace(wf, rst_i, "rst");
        sc_trace(wf, data_i, "data_i");
        sc_trace(wf, val_i, "val_i");
        sc_trace(wf, ack_o, "ack_o");
        sc_trace(wf, req_l_o, "req_l_o");
        sc_trace(wf, req_n_o, "req_n_o");
        sc_trace(wf, req_e_o, "req_e_o");
        sc_trace(wf, req_s_o, "req_s_o");
        sc_trace(wf, req_w_o, "req_w_o");
        sc_trace(wf, gnt_i, "gnt_i");
        sc_trace(wf, rok_o, "rok_o");
        sc_trace(wf, rd_i, "rd_i");
        sc_trace(wf, data_o, "data_o");
    }
};
