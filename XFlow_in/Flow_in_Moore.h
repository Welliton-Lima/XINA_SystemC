#ifndef __FLOW_IN_MOORE__H__
#define __FLOW_IN_MOORE__H__

#include <systemc>

#include "Flow_in.h"

class Flow_in_Moore: public IFlow_in{
protected:
    enum moore_in_stage_fsm{// Enumerador para o estado da máquina de estado.
        s0, s1,s2
    };
public:
    sc_signal<moore_in_stage_fsm> state;
    sc_signal<moore_in_stage_fsm> next_state;

    void flow_in_moore_logic();
    void clock_logic();
    void update_logic();

    SC_HAS_PROCESS(Flow_in_Moore);
    Flow_in_Moore(sc_module_name mn);

    inline const char* moduleName() const { return "Flow_in_Moore"; }

  ~Flow_in_Moore();

};

inline Flow_in_Moore::Flow_in_Moore(sc_module_name mn)
             : IFlow_in(mn)
{
        SC_METHOD(clock_logic);
        sensitive << i_RST<<  i_CLK << next_state;

        SC_METHOD(flow_in_moore_logic);
        sensitive  << i_VAL << i_WOK << state;

        SC_METHOD(update_logic);
        sensitive  <<state << i_DATA;
}

void Flow_in_Moore::clock_logic()
{
    if(i_RST.read() == 1){
        state.write(s0);
    }
    else if(i_CLK.posedge()){
        state.write(next_state.read());
    }
}

void Flow_in_Moore::flow_in_moore_logic(){
    switch(state.read()){
        case s0:

            if(i_VAL.read() == 1 && i_WOK.read()== 1){
                next_state.write(s1);
            } else {
                next_state.write(s0);
            }
        break;

        case s1:

            if(i_VAL.read() == 0){
                next_state.write(s0);
            } else {
                next_state.write(s2);
            }
        break;

        case s2:

            if(i_VAL.read()== 0){
                next_state.write(s0);
            } else {
                next_state.write(s2);
            }
            break;

        default:
            next_state.write(s0);
        break;
    }
}

void Flow_in_Moore::update_logic(){
       if(state.read() == s1 or state.read() == s2){
            o_ACK.write(1);
        }
        else{
            o_ACK.write(0);
        }
        if(state.read() == s1){
            o_WR.write(1);
        }
        else{
            o_WR.write(0);
        }

        o_DATA.write(i_DATA.read());
}

inline Flow_in_Moore::~Flow_in_Moore(){}


#endif //__FLOW_IN_MOORE__H__
