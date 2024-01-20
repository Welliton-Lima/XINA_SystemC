#include <systemc>

template<unsigned int data_width_p>
SC_MODULE(flow_in_tb){

    sc_in_clk clk_i;
    sc_out<bool> rst_i;
    sc_out<bool> val_i;
    sc_out<bool> wok_i;
    sc_in<bool>  ack_o;
    sc_in<bool>  wr_o;
    sc_out<sc_bv<data_width_p>> data_i;
    sc_in<sc_bv<data_width_p>> data_o;

    void logic(){
        data_i.write("00000000");
        rst_i =1;
        wait(10, SC_NS);
        rst_i = 0;
        wait(10, SC_NS);

        sc_bv<data_width_p> words[8] = {"100000001","000000011","000000111","000001111","000011111","000111111","001111111","111111111"};
        for(int i=0; i<8; i++){
            wait(10, SC_NS);
            data_i.write(words[i]);
            while(wr_o.read()==1){
                wait(10, SC_NS);
            }
            while(wr_o.read()==0){
                wait(10, SC_NS);
            }
        }
        wait(100, SC_NS);
        sc_stop();
    }

    void wr(){
        while(true){
            if(wr_o.read() ==1){
                wok_i.write(0);
                wait(10, SC_NS);
            }
            else {
                wok_i.write(1);
                wait(10,SC_NS);
            }
            //cout<<"Data: "<<data_o.read()<<endl;
        }
    }

    void ack(){
        while(true){
            if(ack_o.read()==1){
                val_i.write(0);
                wait(10, SC_NS);
            }
            else {
                val_i.write(1);
                wait(10,SC_NS);
            }
            //cout<<"Data: "<<data_o.read()<<endl;
        }
    }

    SC_CTOR(flow_in_tb){
        sensitive << clk_i;
        SC_THREAD(logic);
        SC_THREAD(wr);
        SC_THREAD(ack);

        sc_trace_file *wf = sc_create_vcd_trace_file("flow_in");

        sc_trace(wf, data_i, "data_i");
        sc_trace(wf, data_o, "data_o");
        sc_trace(wf, clk_i, "clk_i");
        sc_trace(wf, rst_i, "rst_i");
        sc_trace(wf, val_i, "val_i");
        sc_trace(wf, wok_i, "wok_i");
        sc_trace(wf, ack_o, "ack_o");
        sc_trace(wf, wr_o, "wr_o");
    }
};
