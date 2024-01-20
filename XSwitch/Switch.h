#ifndef __SWITCH__H_
#define __SWITCH__H_

#include <systemc>

// data width
SC_MODULE(Switch_module){
public:

    //Sel
    sc_in<sc_bv<4>> i_SEL;

    // Switch
    sc_in<bool>  i_DATA3;
    sc_in<bool>  i_DATA2;
    sc_in<bool>  i_DATA1;
    sc_in<bool>  i_DATA0;
    sc_out<bool> o_DATA;

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
//          o_DATA.write((i_DATA3.read() & i_SEL.read().get_bit(3)) or (i_DATA2.read() & i_SEL.read().get_bit(2)) or (i_DATA1.read() & i_SEL.read().get_bit(1)) or (i_DATA0.read() & i_SEL.read().get_bit(0)) );
    }
     SC_CTOR(Switch_module){
        SC_METHOD(logic);
        sensitive << i_SEL << i_DATA3 << i_DATA2 << i_DATA1 << i_DATA0;
    }
};
#endif //__SWITCH__H_
