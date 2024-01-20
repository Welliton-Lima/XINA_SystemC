#include <systemc.h>

template<unsigned int data_width_p>
SC_MODULE(router_tb){

    sc_in<bool>  clk_i;
    sc_out<bool> rst_i;

    // local channel interface
    sc_out<sc_bv<data_width_p+1>>l_in_data_i;
    sc_out<bool>             l_in_val_i;
    sc_in<bool>              l_in_ack_o;
    sc_in<sc_bv<data_width_p+1>> l_out_data_o;
    sc_in<bool>              l_out_val_o;
    sc_out<bool>             l_out_ack_i;

    // north channel interface
    sc_out<sc_bv<data_width_p+1>> n_in_data_i;
    sc_out<bool>              n_in_val_i;
    sc_in<bool>               n_in_ack_o;
    sc_in<sc_bv<data_width_p+1>>  n_out_data_o;
    sc_in<bool>               n_out_val_o;
    sc_out<bool>              n_out_ack_i;

    // east channel interface
    sc_out<sc_bv<data_width_p+1>> e_in_data_i;
    sc_out<bool>              e_in_val_i;
    sc_in<bool>               e_in_ack_o;
    sc_in<sc_bv<data_width_p+1>>  e_out_data_o;
    sc_in<bool>               e_out_val_o;
    sc_out<bool>              e_out_ack_i;

    // south channel interface
    sc_out<sc_bv<data_width_p+1>> s_in_data_i;
    sc_out<bool>              s_in_val_i;
    sc_in<bool>               s_in_ack_o;
    sc_in<sc_bv<data_width_p+1>>  s_out_data_o;
    sc_in<bool>               s_out_val_o;
    sc_out<bool>              s_out_ack_i;

    // west port interface
    sc_out<sc_bv<data_width_p+1>>w_in_data_i;
    sc_out<bool>             w_in_val_i;
    sc_in<bool>              w_in_ack_o;
    sc_in<sc_bv<data_width_p+1>> w_out_data_o;
    sc_in<bool>              w_out_val_o;
    sc_out<bool>             w_out_ack_i;

    void rst(){
        rst_i.write(1);
        wait(10, SC_NS);
        rst_i.write(0);
        wait(10, SC_NS);

    }

    void in(){

        sc_bv<data_width_p+1> pack_n[4][4]  = { {"100010010", "000000001", "000000010", "100000011"},
                                                {"100110001", "000000100", "000000101", "100000110"},
                                                {"100010000", "000000111", "000001000", "100001001"},
                                                {"100001010", "000001011", "000001100", "100001101"} };

        l_in_data_i.write("000000000");
        l_in_val_i.write(0);
         wait(10, SC_NS);
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                l_in_val_i.write(0);
                l_in_data_i.write(pack_n[i][j]);
                wait(10, SC_NS);

                l_in_val_i.write(1);
                while(l_in_ack_o != 1){
                    wait(10, SC_NS);
                }
                l_in_val_i.write(0);
                while(l_in_ack_o!= 0){
                    wait(10, SC_NS);
                }
            }
        }
        l_in_data_i.write("00000000");
        l_in_val_i.write(0);

        wait(600, SC_NS);
        sc_stop();

     }

    void e_o(){
        while(true){
//             wait(10, SC_NS);
            e_out_ack_i.write(0);
            while (e_out_val_o != 1)
            {
                wait(10, SC_NS);
            }
            wait(10, SC_NS);
            e_out_ack_i.write(1);
            while (e_out_val_o!= 0)
            {
                wait(10, SC_NS);
           }
        }
    }

    void s_o(){
        while(true){
//             wait(10, SC_NS);
            s_out_ack_i.write(0);
            while (s_out_val_o != 1)
            {
                wait(10, SC_NS);

            }
             wait(10, SC_NS);
            s_out_ack_i.write(1);
            while (s_out_val_o!= 0)
            {
                wait(10, SC_NS);
            }
        }
    }

    void n_o(){
        while(true){
//             wait(10, SC_NS);
            n_out_ack_i.write(0);
            while (n_out_val_o != 1)
            {
                wait(10, SC_NS);
            }
            wait(10, SC_NS);
            n_out_ack_i.write(1);
            while (n_out_val_o != 0)
            {
                wait(10, SC_NS);
            }
        }
    }

    void w_o(){
        while(true){
            wait(10, SC_NS);
            w_out_ack_i.write(0);
            while (w_out_val_o != 1)
            {
                wait(10, SC_NS);
            }
            wait(10, SC_NS);
            w_out_ack_i.write(1);
            while (w_out_val_o!= 0)
            {
                wait(10, SC_NS);
            }
        }
    }

    void l_o(){
        while(true){
//             wait(10, SC_NS);
            l_out_ack_i.write(0);
            while (l_out_val_o != 1)
            {
                wait(10, SC_NS);
            }
            wait(10, SC_NS);
            l_out_ack_i.write(1);
            while (l_out_val_o != 0)
            {
                wait(10, SC_NS);
            }
        }
    }

    SC_CTOR(router_tb){

        SC_THREAD(n_o);
        SC_THREAD(e_o);
        SC_THREAD(s_o);
        SC_THREAD(w_o);
        SC_THREAD(l_o);
        SC_THREAD(in);
        SC_THREAD(rst);

        sensitive << clk_i.pos()<<rst_i;

        sc_trace_file *wf = sc_create_vcd_trace_file("router_tb_mode_1");

        sc_trace(wf, clk_i, "clk");
        sc_trace(wf, rst_i, "rst");

        sc_trace(wf, l_in_data_i, "l_in_data_i");
        sc_trace(wf, l_in_val_i,  "l_in_val_i");
        sc_trace(wf, l_in_ack_o,  "l_in_ack_o");
        sc_trace(wf, l_out_data_o,"l_out_data_o");
        sc_trace(wf, l_out_val_o, "l_out_val_o");
        sc_trace(wf, l_out_ack_i, "l_out_ack_i");

        sc_trace(wf, n_in_data_i, "n_in_data_i");
        sc_trace(wf, n_in_val_i,  "n_in_val_i");
        sc_trace(wf, n_in_ack_o,  "n_in_ack_o");
        sc_trace(wf, n_out_data_o,"n_out_data_o");
        sc_trace(wf, n_out_val_o, "n_out_val_o");
        sc_trace(wf, n_out_ack_i, "n_out_ack_i");

        sc_trace(wf, e_in_data_i, "e_in_data_i");
        sc_trace(wf, e_in_val_i,  "e_in_val_i");
        sc_trace(wf, e_in_ack_o,  "e_in_ack_o");
        sc_trace(wf, e_out_data_o,"e_out_data_o");
        sc_trace(wf, e_out_val_o, "e_out_val_o");
        sc_trace(wf, e_out_ack_i, "e_out_ack_i");

        sc_trace(wf, s_in_data_i, "s_in_data_i");
        sc_trace(wf, s_in_val_i,  "s_in_val_i");
        sc_trace(wf, s_in_ack_o,  "s_in_ack_o");
        sc_trace(wf, s_out_data_o,"s_out_data_o");
        sc_trace(wf, s_out_val_o, "s_out_val_o");
        sc_trace(wf, s_out_ack_i, "s_out_ack_i");

        sc_trace(wf, w_in_data_i, "w_in_data_i");
        sc_trace(wf, w_in_val_i,  "w_in_val_i");
        sc_trace(wf, w_in_ack_o,  "w_in_ack_o");
        sc_trace(wf, w_out_data_o,"w_out_data_o");
        sc_trace(wf, w_out_val_o, "w_out_val_o");
        sc_trace(wf, w_out_ack_i, "w_out_ack_i");
     }
};
