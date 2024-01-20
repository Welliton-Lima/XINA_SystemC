#ifndef __ARBITRATION_RR_H__
#define __ARBITRATION_RR_H__

#include <systemc>
#include <bitset>
#include <string>
#include <stdlib.h>
#include "Arbiter.h"

/////////////////////////////////////////////////////////////
/// Arbitration Round Robin Class
/////////////////////////////////////////////////////////////

class Arbitration_RR_Moore : public IArbiter{
protected:
    enum fsm_state{// Enumerador para identificar o estado da máquina de estado.
            stage0,stage1,stage2,stage3,stage4,stage5,stage6,stage7
        };
public:
    sc_signal<fsm_state> state;
    sc_signal<fsm_state> next_state;
    sc_signal<sc_bv<4>>w_GNT;

    void Arbitration_Moore();
    void clock_logic();
    void update_logic();

    SC_HAS_PROCESS(Arbitration_RR_Moore);
    Arbitration_RR_Moore(sc_module_name mn,
             unsigned short nPorts,
             unsigned short ROUTER_ID,
             unsigned short PORT_ID);

    const char* moduleName() const { return "Arbiter_RR_Moore"; }

    ~Arbitration_RR_Moore();
};

/////////////////////////////////////////////////////////////
/// End of Arbitration Round Robin Class
/////////////////////////////////////////////////////////////

inline Arbitration_RR_Moore::Arbitration_RR_Moore(sc_module_name mn,
                                                  unsigned short nPorts,
                                                  unsigned short ROUTER_ID,
                                                  unsigned short PORT_ID)
                                                  :IArbiter(mn,nPorts,ROUTER_ID,PORT_ID)
{
        SC_METHOD(clock_logic);
        sensitive << i_CLK << i_RST;

        SC_METHOD(Arbitration_Moore);
        sensitive << i_REQ << state;

        SC_METHOD(update_logic);
        sensitive << state << w_GNT << i_REQ;

}

/////////////////////////////////////////////////////////////
/// Arbitration Round Robin FSM MOORE XINA
/////////////////////////////////////////////////////////////
void Arbitration_RR_Moore::clock_logic(){

        if(i_RST.read() == 1){
            state.write(stage0);
        }
        else if(i_CLK.posedge()){
            state.write(next_state.read());
        }
}

void Arbitration_RR_Moore::Arbitration_Moore(){
        switch(state.read()){
            case stage0:
                if(i_REQ.read()[3]== "1"){
                    next_state.write(stage1);
                }
                else if(i_REQ.read()[2] == "1"){
                    next_state.write(stage3);
                }
                else if(i_REQ.read()[1]== "1"){
                    next_state.write(stage5);
                }
                else if(i_REQ.read()[0]== "1"){
                    next_state.write(stage7);
                }
                else{
                    next_state.write(stage0);
                }
            break;

            case stage1:
                if(i_REQ.read()[3]== "1"){
                    next_state.write(stage1);
                }
                else if(i_REQ.read()[2] == "1"){
                    next_state.write(stage3);
                }
                else if(i_REQ.read()[1]== "1"){
                    next_state.write(stage5);
                }
                else if(i_REQ.read()[0]== "1"){
                    next_state.write(stage7);
                }
                else{
                    next_state.write(stage2);
                }
            break;

            case stage2:
                if(i_REQ.read()[2]== "1"){
                    next_state.write(stage3);
                }
                else if(i_REQ.read()[1] == "1"){
                    next_state.write(stage5);
                }
                else if(i_REQ.read()[0]== "1"){
                    next_state.write(stage7);
                }
                else if(i_REQ.read()[3]== "1"){
                    next_state.write(stage1);
                }
                else{
                    next_state.write(stage2);
                }
            break;

            case stage3:
                if(i_REQ.read()[2] == "1"){
                    next_state.write(stage3);
                }
                else if(i_REQ.read()[1]== "1"){
                    next_state.write(stage5);
                }
                else if(i_REQ.read()[0]== "1"){
                    next_state.write(stage7);
                }
                else if(i_REQ.read()[3]== "1"){
                    next_state.write(stage1);
                }
                else{
                    next_state.write(stage4);
                }
            break;

            case stage4:

                if(i_REQ.read()[1]== "1"){
                    next_state.write(stage5);
                }
                else if(i_REQ.read()[0]== "1"){
                    next_state.write(stage7);
                }
                else if(i_REQ.read()[3]== "1"){
                    next_state.write(stage1);
                }
                else if(i_REQ.read()[2] == "1"){
                    next_state.write(stage3);
                }
                else{
                    next_state.write(stage4);
                }
            break;

            case stage5:
                if(i_REQ.read()[1]== "1"){
                    next_state.write(stage5);
                }
                else if(i_REQ.read()[0]== "1"){
                    next_state.write(stage7);
                }
                else if(i_REQ.read()[3]== "1"){
                    next_state.write(stage1);
                }
                else if(i_REQ.read()[2] == "1"){
                    next_state.write(stage3);
                }
                else{
                    next_state.write(stage6);
                }
            break;

            case stage6:
                if(i_REQ.read()[0]== "1"){
                    next_state.write(stage7);
                }
                else if(i_REQ.read()[3]== "1"){
                    next_state.write(stage1);
                }
                else if(i_REQ.read()[2] == "1"){
                    next_state.write(stage3);
                }
                else if(i_REQ.read()[1]== "1"){
                    next_state.write(stage5);
                }
                else{
                    next_state.write(stage6);
                }
            break;

            case stage7:
                if(i_REQ.read()[0]== "1"){
                    next_state.write(stage7);
                }
                else if(i_REQ.read()[3]== "1"){
                    next_state.write(stage1);
                }
                else if(i_REQ.read()[2] == "1"){
                    next_state.write(stage3);
                }
                else if(i_REQ.read()[1]== "1"){
                    next_state.write(stage5);
                }
                else{
                    next_state.write(stage0);
                }
            break;

            default:
                next_state.write(stage0);
            break;
        }
}

void Arbitration_RR_Moore::update_logic(){
      if(state.read() == stage1){
            w_GNT.write("1000");
        }
        else if(state.read() == stage3){
            w_GNT.write("0100");
        }
        else if(state.read() == stage5){
            w_GNT.write("0010");
        }
        else if(state.read() == stage7){
            w_GNT.write("0001");
        }
        else{
            w_GNT.write("0000");
        }
        o_GNT.write(w_GNT.read() & i_REQ.read());
}

inline Arbitration_RR_Moore::~Arbitration_RR_Moore() {}

#endif //__ARBITRATION_RR_H__
