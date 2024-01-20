#ifndef __SWITCH_DATA_H_
#define __SWITCH_DATA_H_

#include <systemc>
#include "../Parameters/Parameters.h"

// data width

///class Switch_module: public SC_MODULE{
SC_MODULE(Switch_Data){
public:

    //Sel
    sc_in<sc_bv<4>> i_SEL;

    // Switch
//     sc_in<Flit> i_DATA3;
//     sc_in<Flit> i_DATA2;
//     sc_in<Flit> i_DATA1;
//     sc_in<Flit> i_DATA0;
//     sc_out<Flit> o_DATA;
//
    sc_in <sc_bv<9>> i_DATA3;
    sc_in <sc_bv<9>> i_DATA2;
    sc_in <sc_bv<9>> i_DATA1;
    sc_in <sc_bv<9>> i_DATA0;
    sc_out<sc_bv<9>> o_DATA;

    void logic(){
        switch(i_SEL.read().to_uint()){
            case 8:
                 o_DATA.write(i_DATA3.read());
            break;

            case 4:
                 o_DATA.write(i_DATA2.read());
            break;

            case 2:
                 o_DATA.write(i_DATA1.read());
            break;

            case 1:
                 o_DATA.write(i_DATA0.read());
            break;

            default:
                 o_DATA.write(0);
            break;
        }

    }
     SC_CTOR(Switch_Data){
        SC_METHOD(logic);
        sensitive << i_SEL << i_DATA3 << i_DATA2 << i_DATA1 << i_DATA0;
    }
};
#endif //__SWITCH_DATA_H_
