#ifndef __CHANNEL_IN__H__
#define __CHANNEL_IN__H__

#include <systemc>
#include <bitset>

#include "../SoCINModule.h" //  Classe do do Simulador SNOCS para interação dos módulos

#include "../XSwitch/Switch.h" // Classe Switch

// Classe do controlador de Fluxo de entrada
#include "../XFlow_in/Flow_in.h"
#include "../XFlow_in/Flow_in_Moore.h"
#include "../XFlow_in/Flow_in_Mealy.h"

// Classe do contgrolador de Fluxo de Saída
#include "../XMemory/Memory.h"
#include "../XMemory/Ring_Buffering.h"
#include "../XMemory/Shift_Buffering.h"

// Classe de Roteamento XY
#include "../XRouting/Routing.h"
#include "../XRouting/Routing_XY_Moore.h"
#include "../XRouting/Routing_XY_Mealy.h"

// Definição do Tamanho do Buffer
#define FIFO_DEPTH 8

class Channel_in: public SoCINModule{

public:
    // Clock e Reset
    sc_in<bool> i_CLK;
    sc_in<bool> i_RST;

    //Link inerface
    sc_in<sc_bv<9>> i_DATA;
    sc_in<bool>  i_VAL;
    sc_out<bool> o_ACK;

    //Requests and Grants
    sc_out<bool> o_L_REQ;
    sc_out<bool> o_N_REQ;
    sc_out<bool> o_E_REQ;
    sc_out<bool> o_S_REQ;
    sc_out<bool> o_W_REQ;

    sc_in<sc_bv<4>> i_GNT;

    //Intra router signals
    sc_out<bool>     o_ROK;
    sc_in<sc_bv<4>>  i_RD;
    sc_out<sc_bv<9>> o_DATA;

    //----------------signals-------------------------------//
    sc_signal<bool>         w_ROK, w_RD, w_WOK, w_WR;
    sc_signal<sc_bv<9>>     w_DATA_IN, w_DATA_OUT;

    sc_signal<bool>         w_FRAME;
    sc_signal<sc_bv<8>>     w_DATA;
    sc_signal<bool>         w_RD3, w_RD2, w_RD1, w_RD0;

    //---------------MODULES-----------------------------------//
    IFlow_in            *u_FLOW_IN;
    IMemory<FIFO_DEPTH> *u_BUFFER_FIFO;
    IRouting            *u_ROUTING;
    Switch_module       *u_SWITCH;

    //----------------PARAMETERS---------------------------//
    int ENA;
    bool FLOW_MODE, ROUTING_MODE,BUFFER_MODE;
    unsigned int ROUTER_ID_X, ROUTER_ID_Y;

    // Função de ajustes dos sinais.
    void adjust();

    // Construtor da classe.
    SC_HAS_PROCESS(Channel_in);
    Channel_in(sc_module_name mn,
        int ENA,
        bool FLOW_MODE,
        bool ROUTING_MODE,
        bool BUFFER_MODE,
        unsigned int ROUTER_ID_X,
        unsigned int ROUTER_ID_Y);

    ModuleType moduleType() const { return SoCINModule::TInputModule; }
    const char* moduleName() const { return "Channel_in"; }

    ~Channel_in(){
        delete u_FLOW_IN;
        delete u_BUFFER_FIFO;
        delete u_SWITCH;
        delete u_ROUTING;
    }
};
// Função de Contsrução da classe.
inline Channel_in::Channel_in(sc_module_name mn,
        int ENA,
        bool FLOW_MODE,
        bool ROUTING_MODE,
        bool BUFFER_MODE,
        unsigned int ROUTER_ID_X,
        unsigned int ROUTER_ID_Y)
    : SoCINModule(mn),ENA(ENA),ROUTER_ID_X(ROUTER_ID_X),ROUTER_ID_Y(ROUTER_ID_Y),
      i_CLK("Channel_in_i_CLK"),
      i_RST("Channel_in_i_RST"),
      i_DATA("Channel_in_i_DATA"),
      i_VAL("Channel_in_i_VAL"),
      i_GNT("Channel_in_i_GNT"),
      i_RD("Channel_in_i_RD"),
      o_ACK("Channel_in_o_ACK"),
      o_L_REQ("Channel_in_o_L_REQ"),
      o_N_REQ("Channel_in_o_N_REQ"),
      o_E_REQ("Channel_in_o_E_REQ"),
      o_S_REQ("Channel_in_o_S_REQ"),
      o_W_REQ("Channel_in_o_W_REQ"),
      o_ROK("Channel_in_o_ROK"),
      o_DATA("Channel_in_o_DATA")
{

        SC_METHOD(adjust)
        sensitive << i_CLK<< i_RST<< w_DATA_OUT<< w_ROK << i_RD;

        if(ENA != 0){ // Instancias os componentes caso a vaiável de habilitação seja TRUE.

        if(FLOW_MODE == 0){ //Select Flow type
            u_FLOW_IN = new Flow_in_Moore("u_FLOW_IN_MOORE");// FLOW_MODE = 0, Select Flow Hand Shake FSM Moore.
        }
        else{
            u_FLOW_IN = new Flow_in_Mealy("u_FLOW_IN_MEALY");// FLOW_MODE = 1, Select Flow Hand Shake FSM Mealy.
        }
        if(ROUTING_MODE == 0){ //Select
            u_ROUTING = new Routing_XY_Moore("u_ROUTING_MOORE",ROUTER_ID_X,ROUTER_ID_Y);//ROUTING_MODE = 0, Select Routing XY FSM Moore.
        }
        else{
            u_ROUTING = new Routing_XY_Mealy("u_ROUTING_MEALY",ROUTER_ID_X,ROUTER_ID_Y); //ROUTING_MODE = 1, Select Routing XY FSM Mealy.
        }
        if(BUFFER_MODE == 0) {//Select Buffer FIFO type
            u_BUFFER_FIFO = new Ring_Buffering<FIFO_DEPTH> ("u_BUFFER_FIFO");//BUFFER_MODE = 0; FIFO RING.
        }
        else{
            u_BUFFER_FIFO = new Shift_Buffering<FIFO_DEPTH> ("u_BUFFER_SHIFT");//BUFFER_MODE = 1; FIFO SHIFT.
        }

        u_SWITCH = new Switch_module("u_SWITCH");//Switch READ

        u_FLOW_IN->i_CLK(i_CLK);
        u_FLOW_IN->i_RST(i_RST);
        u_FLOW_IN->i_DATA(i_DATA);
        u_FLOW_IN->i_VAL(i_VAL);
        u_FLOW_IN->i_WOK(w_WOK);
        u_FLOW_IN->o_ACK(o_ACK);
        u_FLOW_IN->o_DATA(w_DATA_IN);
        u_FLOW_IN->o_WR(w_WR);

        u_BUFFER_FIFO->i_CLK(i_CLK);
        u_BUFFER_FIFO->i_RST(i_RST);
        u_BUFFER_FIFO->i_RD(w_RD);
        u_BUFFER_FIFO->i_WR(w_WR);
        u_BUFFER_FIFO->i_DATA(w_DATA_IN);
        u_BUFFER_FIFO->o_ROK(w_ROK);
        u_BUFFER_FIFO->o_WOK(w_WOK);
        u_BUFFER_FIFO->o_DATA(w_DATA_OUT);

        u_ROUTING->i_CLK(i_CLK);
        u_ROUTING->i_RST(i_RST);
        u_ROUTING->i_FRAME(w_FRAME);
        u_ROUTING->i_DATA(w_DATA);
        u_ROUTING->i_ROK(w_ROK);
        u_ROUTING->i_RD(w_RD);
        u_ROUTING->o_REQ_L(o_L_REQ);
        u_ROUTING->o_REQ_N(o_N_REQ);
        u_ROUTING->o_REQ_E(o_E_REQ);
        u_ROUTING->o_REQ_S(o_S_REQ);
        u_ROUTING->o_REQ_W(o_W_REQ);

        u_SWITCH->i_SEL(i_GNT);
        u_SWITCH->i_DATA0(w_RD0);
        u_SWITCH->i_DATA1(w_RD1);
        u_SWITCH->i_DATA2(w_RD2);
        u_SWITCH->i_DATA3(w_RD3);
        u_SWITCH->o_DATA(w_RD);
    }

}

// Classe de Ajustes dos sinais
void Channel_in::adjust(){

        if(ENA != 0){
            w_FRAME.write(w_DATA_OUT.read().get_bit(8)); // Obtém o bit Frame, Bit mais significativo do Array.
            w_DATA.write(w_DATA_OUT.read().range(8-1, 0)); // Obtém o os bits de dados, excluido o bit mais siginificativo do FRAME.

            o_ROK.write(w_ROK.read());
            o_DATA.write(w_DATA_OUT.read());

            w_RD3.write(i_RD.read().get_bit(3));
            w_RD2.write(i_RD.read().get_bit(2));
            w_RD1.write(i_RD.read().get_bit(1));
            w_RD0.write(i_RD.read().get_bit(0));
        }
        else{// Lança zero nas sáidas caso o módulo seja desabilitado.
            w_FRAME.write(0);
            w_DATA.write(0);
            o_ROK.write(0);
            o_DATA.write(0);
            o_ACK.write(0);
            o_L_REQ.write(0);
            o_N_REQ.write(0);
            o_E_REQ.write(0);
            o_S_REQ.write(0);
            o_W_REQ.write(0);
        }
    }


#endif //__CHANNEL_IN__H__
