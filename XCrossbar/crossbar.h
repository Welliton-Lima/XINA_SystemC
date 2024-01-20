#ifndef __CROSSBAR_H__
#define __CROSSBAR_H__

#include <systemc>

using namespace sc_core;

SC_MODULE(Crossbar){
    //Local channel requests --------------------------
public:
    //inputs
    sc_in<bool>i_L_REQ_N;
    sc_in<bool>i_L_REQ_E;
    sc_in<bool>i_L_REQ_S;
    sc_in<bool>i_L_REQ_W;

    //outputs
    sc_out<bool>o_L_REQ_N;
    sc_out<bool>o_L_REQ_E;
    sc_out<bool>o_L_REQ_S;
    sc_out<bool>o_L_REQ_W;

    //North channel requests --------------------------

    //inputs
    sc_in<bool>i_N_REQ_L;
    sc_in<bool>i_N_REQ_E;
    sc_in<bool>i_N_REQ_S;
    sc_in<bool>i_N_REQ_W;

    //outputs
    sc_out<bool>o_N_REQ_L;
    sc_out<bool>o_N_REQ_E;
    sc_out<bool>o_N_REQ_S;
    sc_out<bool>o_N_REQ_W;


    //East channel requests --------------------------

    //inputs
    sc_in<bool>i_E_REQ_L;
    sc_in<bool>i_E_REQ_N;
    sc_in<bool>i_E_REQ_S;
    sc_in<bool>i_E_REQ_W;

    //outputs
    sc_out<bool>o_E_REQ_L;
    sc_out<bool>o_E_REQ_N;
    sc_out<bool>o_E_REQ_S;
    sc_out<bool>o_E_REQ_W;

    //South channel requests --------------------------

    //inputs
    sc_in<bool>i_S_REQ_L;
    sc_in<bool>i_S_REQ_N;
    sc_in<bool>i_S_REQ_E;
    sc_in<bool>i_S_REQ_W;

    //outputs
    sc_out<bool>o_S_REQ_L;
    sc_out<bool>o_S_REQ_N;
    sc_out<bool>o_S_REQ_E;
    sc_out<bool>o_S_REQ_W;

    //West channel requests --------------------------
    //inputs
    sc_in<bool>i_W_REQ_L;
    sc_in<bool>i_W_REQ_N;
    sc_in<bool>i_W_REQ_E;
    sc_in<bool>i_W_REQ_S;

    //outputs
    sc_out<bool>o_W_REQ_L;
    sc_out<bool>o_W_REQ_N;
    sc_out<bool>o_W_REQ_E;
    sc_out<bool>o_W_REQ_S;

    /// Local chanel grants --------------------------

    //inputs
    sc_in<bool>i_L_GNT_N;
    sc_in<bool>i_L_GNT_E;
    sc_in<bool>i_L_GNT_S;
    sc_in<bool>i_L_GNT_W;

    //outputs
    sc_out<bool>o_L_GNT_N;
    sc_out<bool>o_L_GNT_E;
    sc_out<bool>o_L_GNT_S;
    sc_out<bool>o_L_GNT_W;

     /// North chanel grants --------------------------

    //inputs
    sc_in<bool>i_N_GNT_L;
    sc_in<bool>i_N_GNT_E;
    sc_in<bool>i_N_GNT_S;
    sc_in<bool>i_N_GNT_W;

    //outputs
    sc_out<bool>o_N_GNT_L;
    sc_out<bool>o_N_GNT_E;
    sc_out<bool>o_N_GNT_S;
    sc_out<bool>o_N_GNT_W;

    /// East chanel grants --------------------------

    //inputs
    sc_in<bool>i_E_GNT_L;
    sc_in<bool>i_E_GNT_N;
    sc_in<bool>i_E_GNT_S;
    sc_in<bool>i_E_GNT_W;

    //outputs
    sc_out<bool>o_E_GNT_L;
    sc_out<bool>o_E_GNT_N;
    sc_out<bool>o_E_GNT_S;
    sc_out<bool>o_E_GNT_W;

   /// South chanel grants --------------------------

    //inputs
    sc_in<bool>i_S_GNT_L;
    sc_in<bool>i_S_GNT_N;
    sc_in<bool>i_S_GNT_E;
    sc_in<bool>i_S_GNT_W;

    //outputs
    sc_out<bool>o_S_GNT_L;
    sc_out<bool>o_S_GNT_N;
    sc_out<bool>o_S_GNT_E;
    sc_out<bool>o_S_GNT_W;

   /// West chanel grants --------------------------

    //inputs
    sc_in<bool>i_W_GNT_L;
    sc_in<bool>i_W_GNT_N;
    sc_in<bool>i_W_GNT_E;
    sc_in<bool>i_W_GNT_S;

    //outputs
    sc_out<bool>o_W_GNT_L;
    sc_out<bool>o_W_GNT_N;
    sc_out<bool>o_W_GNT_E;
    sc_out<bool>o_W_GNT_S;

    void Xcrossbar(){
            //Requests --------------------------------

        //Local chanel connections
        o_L_REQ_N.write(i_L_REQ_N.read());
        o_L_REQ_E.write(i_L_REQ_E.read());
        o_L_REQ_S.write(i_L_REQ_S.read());
        o_L_REQ_W.write(i_L_REQ_W.read());

        //North chanel connections
        o_N_REQ_L.write(i_N_REQ_L.read());
        o_N_REQ_E.write(0);
        o_N_REQ_S.write(i_N_REQ_S.read());
        o_N_REQ_W.write(0);

        //East chanel connections
        o_E_REQ_L.write(i_E_REQ_L.read());
        o_E_REQ_N.write(i_E_REQ_N.read());
        o_E_REQ_S.write(i_E_REQ_S.read());
        o_E_REQ_W.write(i_E_REQ_W.read());

        //South chanel connections
        o_S_REQ_L.write(i_S_REQ_L.read());
        o_S_REQ_N.write(i_S_REQ_N.read());
        o_S_REQ_E.write(0);
        o_S_REQ_W.write(0);

        //West chanel connections
        o_W_REQ_L.write(i_W_REQ_L.read());
        o_W_REQ_N.write(i_W_REQ_N.read());
        o_W_REQ_E.write(i_W_REQ_E.read());
        o_W_REQ_S.write(i_W_REQ_S.read());

        //Grants ---------------------------------

        // Local channel connections
        o_L_GNT_N.write(i_L_GNT_N.read());
        o_L_GNT_E.write(i_L_GNT_E.read());
        o_L_GNT_S.write(i_L_GNT_S.read());
        o_L_GNT_W.write(i_L_GNT_W.read());

        //North channel connections
        o_N_GNT_L.write(i_N_GNT_L.read());
        o_N_GNT_E.write(i_N_GNT_E.read());
        o_N_GNT_S.write(i_N_GNT_S.read());
        o_N_GNT_W.write(i_N_GNT_W.read());

        //East channel connections
        o_E_GNT_L.write(i_E_GNT_L.read());
        o_E_GNT_N.write(0);
        o_E_GNT_S.write(0);
        o_E_GNT_W.write(i_E_GNT_W.read());

        //South channel connections
        o_S_GNT_L.write(i_S_GNT_L.read());
        o_S_GNT_N.write(i_S_GNT_N.read());
        o_S_GNT_E.write(i_S_GNT_E.read());
        o_S_GNT_W.write(i_S_GNT_W.read());

        //West channel connections
        o_W_GNT_L.write(i_W_GNT_L.read());
        o_W_GNT_N.write(0);
        o_W_GNT_E.write(i_W_GNT_E.read());
        o_W_GNT_S.write(0);
    }

//     SC_HAS_PROCESS(Crossbar);
        SC_CTOR(Crossbar){
        SC_METHOD(Xcrossbar);
        sensitive << i_L_REQ_N << i_L_REQ_E<< i_L_REQ_S << i_L_REQ_W
        << i_N_REQ_L << i_N_REQ_S
        << i_E_REQ_L << i_E_REQ_N << i_E_REQ_S << i_E_REQ_W
        << i_S_REQ_L << i_S_REQ_N
        << i_W_REQ_L << i_W_REQ_N << i_W_REQ_E << i_W_REQ_S

        << i_L_GNT_N << i_L_GNT_E << i_L_GNT_S << i_L_GNT_W
        << i_N_GNT_L << i_N_GNT_E << i_N_GNT_S << i_N_GNT_W
        << i_E_GNT_L << i_E_GNT_W
        << i_S_GNT_L << i_S_GNT_N << i_S_GNT_E << i_S_GNT_W
        << i_W_GNT_L << i_W_GNT_E;
    }

    ~Crossbar(){};
};

#endif //__CROSSBAR_H__
