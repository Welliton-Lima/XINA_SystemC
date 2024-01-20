#ifndef __FLOW_IN_MEALY__H__
#define __FLOW_IN_MEALY__H__

#include <systemc>
#include "Flow_in.h"


class Flow_in_Mealy: public IFlow_in{
protected:
    enum mealy_in_stage_fsm{// Enumerador para identificação do estado da máquina de estado.
        s0, s1
    };
public:
    sc_signal<mealy_in_stage_fsm> state;
    sc_signal<mealy_in_stage_fsm> next_state;

    void flow_in_mealy_logic();
    void output();

    SC_HAS_PROCESS(Flow_in_Mealy);
    Flow_in_Mealy(sc_module_name mn);

    inline const char* moduleName() const { return "Flow_in_Melay"; }

  ~Flow_in_Mealy();

};

inline Flow_in_Mealy::Flow_in_Mealy(sc_module_name mn)
                                : IFlow_in(mn)
{
           SC_METHOD(flow_in_mealy_logic);
           sensitive <<i_CLK << i_RST;

           SC_METHOD(output);
           sensitive << i_VAL << i_WOK << i_DATA << state;
}


void Flow_in_Mealy::flow_in_mealy_logic(){

        if(i_RST.read() == 1){
           state.write(s0);
        }

        else if(i_CLK.posedge()){
            state.write(next_state.read());
        }
}

void Flow_in_Mealy::output(){

     switch(state.read()){
            case s0:

            if(i_VAL.read() == 1 && i_WOK.read() == 1){
                o_ACK.write(0);
                o_WR.write(0);
                next_state.write(s1);
            }
            else {
                o_ACK.write(0);
                o_WR.write(0);
                next_state.write(s0);
            }
            break;

            case s1:

                if(i_VAL.read() == 1){
                    o_ACK.write(1);
                    o_WR.write(1);
                    next_state.write(s1);
                }
                else {
                    o_ACK.write(1);
                    o_WR.write(0);
                    next_state.write(s0);

                }
            break;

            default:
                o_WR.write(0);
                o_ACK.write(0);
                next_state.write(s0);

            break;
        }

       o_DATA.write(i_DATA.read());
}
inline Flow_in_Mealy::~Flow_in_Mealy(){}



#endif //__FLOW_IN_MEALY__H__
