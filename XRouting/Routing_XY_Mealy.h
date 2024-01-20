#ifndef __ROUTING_MEALY__
#define __ROUTING_MEALY__

#include <systemc>
#include "Routing.h"

#include <bitset>

//router identification and network data width
class Routing_XY_Mealy : public IRouting{

protected:
    //signal state finite state machine
    enum fsm_mealy_state {//Enumerador para identificarf o estado da máquina de estado.
        stage0, stage1, stage2, stage3, stage4, stage5, stage6
    };

    //Variables X and Y
    unsigned int ROUTER_X_DST;
    unsigned int ROUTER_Y_DST;
public:
    sc_signal<fsm_mealy_state> state;
    sc_signal<fsm_mealy_state> next_state;

    void routing_xy_mealy_logic();
    void update_logic();

    SC_HAS_PROCESS(Routing_XY_Mealy);
    Routing_XY_Mealy(sc_module_name mn,
                    unsigned int ROUTER_ID_X,
                    unsigned int ROUTER_ID_Y);

    const char* moduleName() const { return "Routing_XY_Mealy"; }

    ~Routing_XY_Mealy();

};

Routing_XY_Mealy::Routing_XY_Mealy(sc_module_name mn,
                                   unsigned int ROUTER_ID_X,
                                   unsigned int ROUTER_ID_Y)
                                    :IRouting(mn,ROUTER_ID_X,ROUTER_ID_Y)
{

        SC_METHOD(routing_xy_mealy_logic);
        sensitive <<i_CLK << i_RST;

        SC_METHOD(update_logic);
        sensitive <<  i_FRAME << i_ROK << i_RD << i_DATA << state;
}

void Routing_XY_Mealy::routing_xy_mealy_logic(){

        if(i_RST.read() == 1){
            state.write(stage0);
        }
        // Logic
        else if(i_CLK.posedge()){
            state.write(next_state.read());
        }
}

void Routing_XY_Mealy::update_logic(){

        switch(state.read()){

            case stage0:
            if(i_FRAME.read() == 1 && i_ROK.read() == 1){

                    ROUTER_Y_DST = i_DATA.read().range((8/2)-1,0).to_uint();
                    ROUTER_X_DST = i_DATA.read().range(8-1, 8/2).to_uint();

                if(ROUTER_X_DST != ROUTER_ID_X){
                    if(ROUTER_X_DST > ROUTER_ID_X){
                        o_REQ_L.write(0);
                        o_REQ_N.write(0);
                        o_REQ_E.write(1);
                        o_REQ_S.write(0);
                        o_REQ_W.write(0);

                        if(i_RD.read() == 1){
                            next_state.write(stage1);
                        }
                        else{
                            next_state.write(stage0);
                        }
                    }
                    else{
                        o_REQ_L.write(0);
                        o_REQ_N.write(0);
                        o_REQ_E.write(0);
                        o_REQ_S.write(0);
                        o_REQ_W.write(1);
                        if(i_RD.read() == 1){
                            next_state.write(stage2);
                        }

                        else{
                            next_state.write(stage0);
                        }
                    }
                }

            else if(ROUTER_Y_DST != ROUTER_ID_Y){
                if(ROUTER_Y_DST > ROUTER_ID_Y){
                    o_REQ_L.write(0);
                    o_REQ_N.write(1);
                    o_REQ_E.write(0);
                    o_REQ_S.write(0);
                    o_REQ_W.write(0);

                    if(i_RD.read() == 1){
                        next_state.write(stage3);
                    }

                    else{
                        next_state.write(stage0);
                    }
                }
                else{
                    o_REQ_L.write(0);
                    o_REQ_N.write(0);
                    o_REQ_E.write(0);
                    o_REQ_S.write(1);
                    o_REQ_W.write(0);
                    if(i_RD.read() == 1){
                        next_state.write(stage4);
                    }

                    else{
                        next_state.write(stage0);
                    }
                }
            }
            else{
                o_REQ_L.write(1);
                o_REQ_N.write(0);
                o_REQ_E.write(0);
                o_REQ_S.write(0);
                o_REQ_W.write(0);

                if(i_RD.read() == 1){
                    next_state.write(stage5);
                }

                else{
                    next_state.write(stage0);
                }
            }
// TRECHO DE CÓDIGO PARA SER UTILIZADO JUNTO AO SIMULADOR SNoCs, PARA CONTAR O NÚMERO DE SALTOS QUE O PACOTE TEVE AO PERCORRER A REDE.
//                     if( f.packet_ptr != NULL ) {
//                      f.packet_ptr->hops++;
//                     }
        }
        else{
            o_REQ_L.write(0);
            o_REQ_N.write(0);
            o_REQ_E.write(0);
            o_REQ_S.write(0);
            o_REQ_W.write(0);
            next_state.write(stage0);
        }
            break;

            //ROUTER_X_DST > ROUTER_ID_X
            case stage1:
                o_REQ_L.write(0);
                o_REQ_N.write(0);
                o_REQ_E.write(1);
                o_REQ_S.write(0);
                o_REQ_W.write(0);

                if(i_FRAME.read() == 1 && i_RD.read() == 1 && i_ROK.read() == 1){
                    next_state.write(stage6);
                }
                else{
                    next_state.write(stage1);
                }
            break;
            //ROUTER_X_DST < ROUTER_ID_X
            case stage2:
                o_REQ_L.write(0);
                o_REQ_N.write(0);
                o_REQ_E.write(0);
                o_REQ_S.write(0);
                o_REQ_W.write(1);
                if(i_FRAME.read() == 1 && i_RD.read() == 1 && i_ROK.read() == 1 ){
                    next_state.write(stage6);
                }
                else{
                    next_state.write(stage2);
                }
            break;

            //ROUTER_Y_DST > ROUTER_ID_Y
            case stage3:
                o_REQ_L.write(0);
                o_REQ_N.write(1);
                o_REQ_E.write(0);
                o_REQ_S.write(0);
                o_REQ_W.write(0);
                if(i_FRAME.read() == 1 && i_RD.read() == 1 && i_ROK.read() == 1){
                    next_state.write(stage6);
                }
                else{
                    next_state.write(stage3);
                }
            break;
            //ROUTER_Y_DST < ROUTER_ID_Y
            case stage4:
                o_REQ_L.write(0);
                o_REQ_N.write(0);
                o_REQ_E.write(0);
                o_REQ_S.write(1);
                o_REQ_W.write(0);

                if(i_FRAME.read() == 1 && i_RD.read() == 1 && i_ROK.read() == 1 ){
                    next_state.write(stage6);
                }
                else{
                    next_state.write(stage4);
                }
            break;

            //ROUTER_X_DST = ROUTER_ID_X and ROUTER_Y_DST = ROUTER_ID_Y
            case stage5:
                o_REQ_L.write(1);
                o_REQ_N.write(0);
                o_REQ_E.write(0);
                o_REQ_S.write(0);
                o_REQ_W.write(0);
                if(i_FRAME == 1 && i_RD.read() == 1 && i_ROK.read() == 1 ){
                    next_state.write(stage6);
                }
                else{
                    next_state.write(stage5);
                }
            break;

            //others
            case stage6:
                o_REQ_L.write(0);
                o_REQ_N.write(0);
                o_REQ_E.write(0);
                o_REQ_S.write(0);
                o_REQ_W.write(0);
                next_state.write(stage0);
            break;

            default:
                o_REQ_L.write(0);
                o_REQ_N.write(0);
                o_REQ_E.write(0);
                o_REQ_S.write(0);
                o_REQ_W.write(0);

                next_state.write(stage0);
            break;
        }

}
inline Routing_XY_Mealy::~Routing_XY_Mealy() {}



#endif //__ROUTING_MEALY__
