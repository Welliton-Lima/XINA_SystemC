#ifndef __ROUTING_MOORE__
#define __ROUTING_MOORE__

#include <systemc>
#include "Routing.h"

#include <bitset>

//router identification and network data width
class Routing_XY_Moore : public IRouting{

protected:
    //signal state finite state machine
    enum fsm_moore_state {// Enumerador par indentificar o estado da máquina de estado.
        s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10,s11,s12,s13
    };

    //Variables X and Y
    unsigned int ROUTER_X_DST;
    unsigned int ROUTER_Y_DST;
public:
    sc_signal<fsm_moore_state> state;
    sc_signal<fsm_moore_state> next_state;

    void routing_xy_moore_logic();
    void clock_logic();
    void update_logic();

    SC_HAS_PROCESS(Routing_XY_Moore);
    Routing_XY_Moore(sc_module_name mn,
                     unsigned int ROUTER_ID_X,
                     unsigned int ROUTER_ID_Y);

    const char* moduleName() const { return "Routing_XY_Moore"; }

    ~Routing_XY_Moore();

};

inline Routing_XY_Moore::Routing_XY_Moore(sc_module_name mn,
                         unsigned int ROUTER_ID_X,
                         unsigned int ROUTER_ID_Y)
                         :IRouting(mn,ROUTER_ID_X,ROUTER_ID_Y){

        SC_METHOD(clock_logic);
        sensitive << i_RST << i_CLK;

        SC_METHOD(routing_xy_moore_logic);
        sensitive << i_FRAME << i_ROK << i_RD<< i_DATA << state;

        SC_METHOD(update_logic);
        sensitive <<state;

}


void Routing_XY_Moore::clock_logic(){

        //Reset Logic
        if(i_RST.read() == 1){
            state.write(s0);
        }
        // Logic
        else if(i_CLK.posedge()){
            state.write(next_state.read());
        }

}

void Routing_XY_Moore::routing_xy_moore_logic(){
    switch(state.read()){
        case s0:
        if(i_FRAME.read() == 1 && i_ROK.read() == 1){
                ROUTER_Y_DST = i_DATA.read().range((8/2)-1,0).to_uint();
                ROUTER_X_DST = i_DATA.read().range(8-1, 8/2).to_uint();

            if(ROUTER_X_DST != ROUTER_ID_X){
                if(ROUTER_X_DST > ROUTER_ID_X){
                    next_state.write(s1);
                }
                else{
                    next_state.write(s2);
                }
            }
            else if(ROUTER_Y_DST != ROUTER_ID_Y){
                if(ROUTER_Y_DST > ROUTER_ID_Y){
                    next_state.write(s3);
                }
                else{
                    next_state.write(s4);
                }
            }
            else{
                next_state.write(s5);
            }
// TRECHO DE CÓDIGO PARA SER UTILIZADO JUNTO AO SIMULADOR SNoCs, PARA CONTAR O NÚMERO DE SALTOS QUE O PACOTE TEVE AO PERCORRER A REDE.
//                     if( f.packet_ptr != NULL ) {
//                      f.packet_ptr->hops++;
//                     }
        }

        else{
            next_state.write(s0);
        }
        break;

        //ROUTER_X_DST > ROUTER_ID_X
        case s1:
            if(i_FRAME.read() == 0 && i_RD.read() == 1 && i_ROK.read() == 1){
                next_state.write(s9);
            }
            else{
                next_state.write(s1);
            }
        break;

        case s9:
            if(i_FRAME.read() == 1 && i_RD.read() == 1 && i_ROK.read() == 1 ){
                next_state.write(s0);
            }
            else{
                next_state.write(s9);
            }
        break;

        //ROUTER_X_DST < ROUTER_ID_X
        case s2:
            if(i_FRAME.read() == 0 && i_RD.read()== 1 && i_ROK.read() == 1){
                next_state.write(s10);
            }
            else{
                next_state.write(s2);
            }
        break;

        case s10:
            if(i_FRAME.read() == 1 && i_RD.read() == 1 && i_ROK.read() == 1 ){
                next_state.write(s0);
            }
            else{
                next_state.write(s10);
            }
        break;

        //ROUTER_Y_DST > ROUTER_ID_Y
        case s3:
            if(i_FRAME.read() == 0 && i_RD.read() == 1 && i_ROK.read() == 1){
                next_state.write(s11);
            }
            else{
                next_state.write(s3);
            }
        break;

        case s11:
            if(i_FRAME.read() == 1 && i_RD.read() == 1 && i_ROK.read() == 1){
                next_state.write(s0);

            }
            else{
                next_state.write(s11);
            }
        break;

        //ROUTER_Y_DST < ROUTER_ID_Y
        case s4:
            if(i_FRAME.read() == 0 && i_RD.read() == 1 && i_ROK.read() == 1 ){
                next_state.write(s12);
            }
            else{
                next_state.write(s4);

            }
            break;

        case s12:
            if(i_FRAME.read() == 1 && i_RD.read() == 1 && i_ROK.read() == 1 ){
                next_state.write(s0);
            }
            else{
                next_state.write(s12);
            }
        break;

        //ROUTER_X_DST = ROUTER_ID_X and ROUTER_Y_DST = ROUTER_ID_Y
        case s5:
            if(i_FRAME.read() == 0 && i_RD.read() == 1 && i_ROK.read() == 1 ){
                next_state.write(s13);
            }
            else{
                next_state.write(s5);
            }
        break;

        case s13:
            if(i_FRAME.read() == 1 && i_RD.read() == 1 && i_ROK.read() == 1 ){
                next_state.write(s0);
            }
            else{
                next_state.write(s13);
            }
        break;

        //others
        default:
            next_state.write(s0);
        break;

    }
}

void Routing_XY_Moore::update_logic(){

            //Local Channel
        if(state.read() == s5 or state.read() == s13 ){
            o_REQ_L.write(1);
        }
        else{
            o_REQ_L.write(0);
        }

        //Norh Channel
        if(state.read() == s3 or state.read() == s11){
            o_REQ_N.write(1);
        }
        else{
            o_REQ_N.write(0);
        }
        //East Channel
        if(state.read() == s1 or state.read() == s9 ){
            o_REQ_E.write(1);
        }
        else{
            o_REQ_E.write(0);
        }
        //South Chanennel
        if(state.read() == s4 or state.read() == s12 ){
            o_REQ_S.write(1);
        }
        else{
            o_REQ_S.write(0);
        }
        //West Channel
        if(state.read() == s2 or state.read() == s10 ){
            o_REQ_W.write(1);
        }
        else{
            o_REQ_W.write(0);
        }

}

inline Routing_XY_Moore::~Routing_XY_Moore() {}



#endif //__ROUTING_MOORE__
