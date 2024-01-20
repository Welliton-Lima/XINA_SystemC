#ifndef __FLOW_OUT_MEALY__H__
#define __FLOW_OUT_MEALY__H__

#include <systemc>
#include "Flow_out.h"

//network data width
class Flow_out_Mealy : public IFlow_out{
protected:
    enum mealy_stage_fsm{s0, s1};// Enumerador para iodentificar o estado da máquina de estado.

public:
    sc_signal<mealy_stage_fsm> r_STATE;
    sc_signal<mealy_stage_fsm> r_NEXT;

    void flow_out_mealy_logic();
    void output();

    SC_HAS_PROCESS(Flow_out_Mealy);
    Flow_out_Mealy(sc_module_name mn);

    inline const char* moduleName() const { return "Flow_out_Melay"; }

  ~Flow_out_Mealy();

};

inline Flow_out_Mealy::Flow_out_Mealy(sc_module_name mn)
                                :IFlow_out(mn)
{
        SC_METHOD(flow_out_mealy_logic);
        sensitive << i_CLK << i_RST;

        SC_METHOD(output);
        sensitive <<  i_ACK << i_ROK << i_DATA<<r_STATE;
}

void Flow_out_Mealy::flow_out_mealy_logic(){

        if(i_RST.read() == 1){
            r_STATE.write(s0);
        }

        else if(i_CLK.posedge()){
            r_STATE.write(r_NEXT.read());
        }
}

void Flow_out_Mealy::output(){
        switch(r_STATE.read()){
            case s0:
                if (i_ACK.read()==0 && i_ROK.read() == 1){
                    o_VAL.write(1);
                    o_RD.write(0);
                    r_NEXT.write(s1);
                }
                else{
                    o_VAL.write(0);
                    o_RD.write(0);
                    r_NEXT.write(s0);
                }
            break;

            case s1:
                if (i_ACK.read()==1){
                    o_VAL.write(1);
                    o_RD.write(1);
                    r_NEXT.write(s0);
                }
                else{
                    o_VAL.write(1);
                    o_RD.write(0);
                    r_NEXT.write(s1);
                }
            break;

            default:
                o_VAL.write(0);
                o_RD.write(0);
                r_NEXT.write(s0);
            break;
        }
        o_DATA.write(i_DATA.read());
}
inline Flow_out_Mealy::~Flow_out_Mealy(){}

#endif //__FLOW_OUT_MEALY__H__
