#ifndef __ARBITRATION_RR_Mealy_H__
#define __ARBITRATION_RR_Mealy_H__

#include <systemc>
#include "Arbiter.h"

/////////////////////////////////////////////////////////////
/// Arbitration Round Robin Class
/////////////////////////////////////////////////////////////

class Arbitration_RR_Mealy : public IArbiter{
protected:
    enum fsm_state{ // Enumarador para identificação dos estados da máquina de estados.
        stage0,stage1,stage2,stage3
    };
public:
    sc_signal<fsm_state> r_STATE;
    sc_signal<fsm_state> r_NEXT_STATE;

    void Arbitration_Mealy();

    SC_HAS_PROCESS(Arbitration_RR_Mealy);
    Arbitration_RR_Mealy(sc_module_name mn,
             unsigned short nPorts,
             unsigned short ROUTER_ID,
             unsigned short PORT_ID);
    const char* moduleName() const { return "Arbiter_RR_Mealy"; }

    ~Arbitration_RR_Mealy();
};

/////////////////////////////////////////////////////////////
/// End of Arbitration Round Robin Class
/////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////
/// Constructor
/////////////////////////////////////////////////////////////

// Nota: Construtor baseado no Arbter da SOCIN, nPorts, ROUTER_ID e PORT_ID não foram utilizados na rede XINA.
inline Arbitration_RR_Mealy::Arbitration_RR_Mealy(sc_module_name mn,
                                                  unsigned short nPorts,
                                                  unsigned short ROUTER_ID,
                                                  unsigned short PORT_ID)
                                                  :IArbiter(mn,nPorts,ROUTER_ID,PORT_ID)
{
 SC_METHOD(Arbitration_Mealy);
        sensitive << i_CLK << i_RST  << i_REQ;

}

/////////////////////////////////////////////////////////////
/// Arbitration Round Robin FSM MOORE XINA
/////////////////////////////////////////////////////////////

void Arbitration_RR_Mealy::Arbitration_Mealy(){
    if(i_RST.read() == 1){
        r_STATE.write(stage0);
    }

    else if(i_CLK.posedge()){
        r_STATE.write(r_NEXT_STATE.read());
    }

    switch(r_STATE.read()){
        case stage0:
            if(i_REQ.read()[3] == "1"){
                o_GNT.write("1000");
                r_NEXT_STATE.write(stage0);
            }
            else if(i_REQ.read()[2] == "1"){
                o_GNT.write("0100");
                r_NEXT_STATE.write(stage1);
            }
            else if(i_REQ.read()[1] == "1"){
                o_GNT.write("0010");
                r_NEXT_STATE.write(stage2);
            }
            else if(i_REQ.read()[0] == "1"){
                o_GNT.write("0001");
                r_NEXT_STATE.write(stage3);
            }
            else{
                o_GNT.write("0000");
                r_NEXT_STATE.write(stage0);
            }
        break;

        case stage1:

            if(i_REQ.read()[2] == "1"){
                o_GNT.write("0100");
                r_NEXT_STATE.write(stage1);
            }
            else if(i_REQ.read()[1]== "1"){
                o_GNT.write("0010");
                r_NEXT_STATE.write(stage2);
            }
            else if(i_REQ.read()[0]== "1"){
                o_GNT.write("0001");
                r_NEXT_STATE.write(stage3);
            }
            else if(i_REQ.read()[3]== "1"){
                o_GNT.write("1000");
                r_NEXT_STATE.write(stage0);
            }
            else{
                o_GNT.write("0000");
                r_NEXT_STATE.write(stage1);
            }
        break;

        case stage2:
            if(i_REQ.read()[1]== "1"){
                o_GNT.write("0010");
                r_NEXT_STATE.write(stage2);
            }
            else if(i_REQ.read()[0]== "1"){
                o_GNT.write("0001");
                r_NEXT_STATE.write(stage3);
            }
            else if(i_REQ.read()[3]== "1"){
                o_GNT.write("1000");
                r_NEXT_STATE.write(stage0);
            }
            else if(i_REQ.read()[2] == "1"){
                o_GNT.write("0100");
                r_NEXT_STATE.write(stage1);
            }
            else{
                o_GNT.write("0000");
                r_NEXT_STATE.write(stage2);
            }
        break;

        case stage3:

            if(i_REQ.read()[0]== "1"){
                o_GNT.write("0001");
                r_NEXT_STATE.write(stage3);
            }
            else if(i_REQ.read()[3]== "1"){
                o_GNT.write("1000");
                r_NEXT_STATE.write(stage0);
            }
            else if(i_REQ.read()[2] == "1"){
                o_GNT.write("0100");
                r_NEXT_STATE.write(stage1);
            }
            else if(i_REQ.read()[1]== "1"){
                o_GNT.write("0010");
                r_NEXT_STATE.write(stage2);
            }
            else{
                o_GNT.write("0000");
                r_NEXT_STATE.write(stage3);
            }
        break;

        default:
            o_GNT.write("0000");
            r_NEXT_STATE.write(stage0);
        break;
    }
}

inline Arbitration_RR_Mealy::~Arbitration_RR_Mealy() {}

#endif //__ARBITRATION_RR_Mealy_H__
