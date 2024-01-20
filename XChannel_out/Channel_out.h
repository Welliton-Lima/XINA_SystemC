#ifndef __CHANNEL_OUT_H__
#define __CHANNEL_OUT_H__

#include <systemc>
#include "../SoCINModule.h" // Classe do Simulador SNoCs para instâncias os módulos de construção de uma REDE.

// Classe de controle de fluxo de sáida
#include "../XFlow_out/Flow_out.h"
#include "../XFlow_out/Flow_out_Moore.h"
#include "../XFlow_out/Flow_out_Mealy.h"

// Classe de Switch
#include "../XSwitch/Switch.h"
#include "../XSwitch/Switch_Data.h"

// Classe do Arbiter
#include "../XArbiter/Arbiter.h"
#include "../XArbiter/Arbitration_RR_Moore.h"
#include "../XArbiter/Arbitration_RR_Mealy.h"

class Channel_out: public SoCINModule{
// Variávies de parametrização
protected:
    bool ENA;
    bool FLOW_MODE;
    bool ARBITER_MODE;
public:
    sc_in<bool> i_CLK;
    sc_in<bool> i_RST;

    //Link inerface
    sc_out<sc_bv<9>> o_DATA;
    sc_out<bool>     o_VAL;
    sc_in<bool>      i_ACK;

    //Requeriments and grants
    sc_in<sc_bv<4>>  i_REQ;
    sc_out<sc_bv<4>> o_GNT;

    //Intra router signals
    sc_in<sc_bv<4>>  i_ROK;
    sc_out<bool>     o_RD;

    sc_in<sc_bv<9>> i_DATA3;
    sc_in<sc_bv<9>> i_DATA2;
    sc_in<sc_bv<9>> i_DATA1;
    sc_in<sc_bv<9>> i_DATA0;

    //----------------SIGNALS----------------------//
    sc_signal<bool>     w_ROK;
    sc_signal<sc_bv<9>> w_DATA;
    sc_signal<sc_bv<4>> w_GNT,w_GNT0;

    sc_signal<bool> w_ROK0, w_ROK1, w_ROK2, w_ROK3;

    //-----------------COMPONENTS-------------------------//
    IFlow_out        *u_Flow_out;
    IArbiter         *u_Arbiter;
    Switch_Data      *u_Data_switch;
    Switch_module    *u_ROK_switch;

    // Classe de ajustes dos sinais de saída.
    void logic_out();

    // Construtor
    SC_HAS_PROCESS(Channel_out);
    Channel_out(sc_module_name mn,
        int ENA,
        bool FLOW_MODE,
        bool ARBITER_MODE);

    ModuleType moduleType() const { return SoCINModule::TOutputModule; }
    const char* moduleName() const { return "Channel_out"; }

    ~Channel_out(){
        delete u_Flow_out;
        delete u_ROK_switch;
        delete u_Data_switch;
        delete u_Arbiter;
    }
};
// Função do construtor
inline Channel_out::Channel_out(sc_module_name mn,
                                int ENA,
                                bool FLOW_MODE,
                                bool ARBITER_MODE)
                                : SoCINModule(mn),ENA(ENA),
                                i_CLK("Channel_out_i_CLK"),
                                i_RST("Channel_in_i_RST"),
                                i_DATA0("Channel_out_i_DATA0"),
                                i_DATA1("Channel_out_i_DATA1"),
                                i_DATA2("Channel_out_i_DATA2"),
                                i_DATA3("Channel_out_i_DATA3"),
                                o_VAL("Channel_out_o_VAL"),
                                o_GNT("Channel_out_o_GNT"),
                                o_RD("Channel_out_o_RD"),
                                i_REQ("Channel_out_i_REQ"),
                                i_ACK("Channel_out_i_ACK"),
                                i_ROK("Channel_out_i_ROK"),
                                o_DATA("Channel_out_o_DATA")
{
        SC_METHOD(logic_out);
        sensitive << i_CLK<< i_RST << w_GNT << i_ROK;

        // Instâncias os móodulos de acordo com a parametrização.
        if(FLOW_MODE == 0){//Select Flow type
            u_Flow_out    = new Flow_out_Moore("u_Flow_out_Moore");// FLOW_MODE = 0, Select Flow Hand Shake FSM Moore
        }
        else{
            u_Flow_out    = new Flow_out_Mealy("u_Flow_out_Mealy");// FLOW_MODE = 1, Select Flow Hand Shake FSM Mealy
        }

        if(ARBITER_MODE == 0){
            u_Arbiter     = new Arbitration_RR_Moore("u_Arbiter_Moore",0,0,0);//ARBITER_MODE = 0, Select Arbiter Round Robin FSM Moore
        }
        else{
            u_Arbiter     = new Arbitration_RR_Mealy("u_Arbiter_Mealy",0,0,0);//ARBITER_MODE = 1, Select Arbiter Round Robin FSM Mealy
        }
            u_Data_switch = new Switch_Data("u_Data_switch");
            u_ROK_switch  = new Switch_module("u_ROK_switch");

            u_Flow_out->i_CLK(i_CLK);
            u_Flow_out->i_RST(i_RST);
            u_Flow_out->i_ACK(i_ACK);
            u_Flow_out->i_DATA(w_DATA);
            u_Flow_out->i_ROK(w_ROK);
            u_Flow_out->o_RD(o_RD);
            u_Flow_out->o_VAL(o_VAL);
            u_Flow_out->o_DATA(o_DATA);

            u_Arbiter->i_CLK(i_CLK);
            u_Arbiter->i_RST(i_RST);
            u_Arbiter->i_REQ(i_REQ);
            u_Arbiter->o_GNT(w_GNT);

            u_Data_switch->i_SEL(w_GNT);
            u_Data_switch->i_DATA3(i_DATA3);
            u_Data_switch->i_DATA2(i_DATA2);
            u_Data_switch->i_DATA1(i_DATA1);
            u_Data_switch->i_DATA0(i_DATA0);
            u_Data_switch->o_DATA(w_DATA);

            u_ROK_switch->i_SEL(w_GNT);
            u_ROK_switch->i_DATA3(w_ROK3);
            u_ROK_switch->i_DATA2(w_ROK2);
            u_ROK_switch->i_DATA1(w_ROK1);
            u_ROK_switch->i_DATA0(w_ROK0);
            u_ROK_switch->o_DATA(w_ROK);

    }

void Channel_out::logic_out(){

    if(ENA != 0){
        o_GNT.write(w_GNT.read());

        w_ROK0.write(i_ROK.read().get_bit(0));
        w_ROK1.write(i_ROK.read().get_bit(1));
        w_ROK2.write(i_ROK.read().get_bit(2));
        w_ROK3.write(i_ROK.read().get_bit(3));
    }
    else{
        o_GNT.write(0);

        w_ROK0.write(i_ROK.read().get_bit(0));
        w_ROK1.write(i_ROK.read().get_bit(1));
        w_ROK2.write(i_ROK.read().get_bit(2));
        w_ROK3.write(i_ROK.read().get_bit(3));
    }

}
#endif //__CHANNEL_OUT_H__
