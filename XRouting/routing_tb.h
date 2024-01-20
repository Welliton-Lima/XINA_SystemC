#include <systemc.h>

// #define X 1
// #define Y 1

template<unsigned int width_p,unsigned int x_id_p,unsigned int y_id_p>
SC_MODULE(routing_tb){

    sc_in<bool>  clk_i;
    sc_out<bool> rst_i;
    sc_out<bool> frame_i;
    sc_out<sc_bv<width_p>> data_i;
    sc_out<bool> rok_i;
    sc_out<bool> rd_i;
    sc_in<bool>  req_l_o;
    sc_in<bool>  req_n_o;
    sc_in<bool>  req_e_o;
    sc_in<bool>  req_s_o;
    sc_in<bool>  req_w_o;

    void logic(){

        sc_bv<width_p> count[4][4] = {{"00010010", "00000010", "00000101", "00000111"},
                                      {"00100001", "00000010", "00000101", "00000111"},
                                      {"00010000", "00000010", "00000101", "00000111"},
                                      {"00000001", "00000010", "00000101", "00000111"}};
        bool frame0[4][4] = {{1,0,0,1},{1,0,0,1},{1,0,0,1},{1,0,0,1}};

        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                frame_i.write(frame0[i][j]);

                data_i.write(count[i][j]);

                rok_i.write(1);
                rd_i.write(0);

                wait(10,SC_NS);

                rok_i.write(1);
                rd_i.write(1);

                wait(10, SC_NS);
            }
        }
        frame_i.write(0);
        wait(50,SC_NS);
        sc_stop();
    }

    void reset(){
        rst_i = 1;
        wait(10, SC_NS);
        rst_i = 0;
        wait(10, SC_NS);
    }

    SC_CTOR(routing_tb){

        sensitive << clk_i.pos() << rst_i << rok_i << rd_i << data_i;
        SC_THREAD(logic);
        SC_THREAD(reset);

        sc_trace_file *wf = sc_create_vcd_trace_file("routing_xy_tb");

        sc_trace(wf, req_w_o, "req_w_o");
        sc_trace(wf, req_s_o, "req_s_o");
        sc_trace(wf, req_e_o, "req_e_o");
        sc_trace(wf, req_n_o, "req_n_o");
        sc_trace(wf, req_l_o, "req_l_o");
        sc_trace(wf, data_i, "data_i");
        sc_trace(wf, rok_i, "rok_i");
        sc_trace(wf, rd_i, "rd_i");
        sc_trace(wf, rst_i, "rst_i");
        sc_trace(wf, clk_i, "clk_i");
        sc_trace(wf, frame_i, "frame_i");
    }
};
