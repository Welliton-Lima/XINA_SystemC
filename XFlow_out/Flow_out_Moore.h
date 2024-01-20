#ifndef __FLOW_OUT_MOORE__H__
#define __FLOW_OUT_MOORE__H__

#include <systemc>
#include "Flow_out.h"

//network data width
class Flow_out_Moore : public IFlow_out{
protected:
    enum moore_stage_fsm{// Enumerador para identificação do estado da máquina de estado.
      s0, s1, s2
    };
public:
    sc_signal<moore_stage_fsm> state;
    sc_signal<moore_stage_fsm> next_state;

    void flow_out_moore_logic();
    void state_logic();
    void update_logic();

    SC_HAS_PROCESS(Flow_out_Moore);
    Flow_out_Moore(sc_module_name mn);

    inline const char* moduleName() const { return "Flow_out_Moore"; }

  ~Flow_out_Moore();

};

inline Flow_out_Moore::Flow_out_Moore(sc_module_name mn)
                                :IFlow_out(mn)
{
        SC_METHOD(flow_out_moore_logic);
        sensitive <<i_CLK << i_RST << next_state;

        SC_METHOD(state_logic);
        sensitive << i_ACK << i_ROK << state;

        SC_METHOD(update_logic);
        sensitive << state << i_DATA;
}

void Flow_out_Moore::flow_out_moore_logic(){

        if(i_RST.read() == 1){
            state.write(s0);
        }

        else if(i_CLK.posedge()){
            state.write(next_state.read());
        }

}

void Flow_out_Moore::state_logic(){
    switch(state.read()){
            case s0:
                if (i_ACK.read() ==0 && i_ROK.read() == 1){
                    next_state.write(s1);
                }
                else{
                    next_state.write(s0);
                }
            break;

            case s1:
                if (i_ACK.read() ==1){
                    next_state.write(s2);
                }
                else{
                    next_state.write(s1);
                }
            break;

            case s2:
                if (i_ACK.read() ==0 && i_ROK.read() == 1){
                    next_state.write(s1);
                }
                    else{
                    next_state.write(s0);
                }
            break;

            default:
                next_state.write(s0);
            break;
        }
}


void Flow_out_Moore::update_logic(){
        if(state.read() == s1){
            o_VAL.write(1);
        }
        else {
            o_VAL.write(0);
        }
        if(state.read() == s2){
            o_RD.write(1);
        }
        else {
            o_RD.write(0);
        }
        o_DATA.write(i_DATA.read());
}
inline Flow_out_Moore::~Flow_out_Moore(){}




#endif //__FLOW_OUT_MOORE__H__
