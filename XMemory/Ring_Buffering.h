 #ifndef __RING_BUFFERING_H__
#define __RING_BUFFERING_H__

#include <systemc>
#include "math.h"
#include <cmath>

#include "Memory.h"

/////////////////////////////////////////////////////////////
/// Buffering Ring Class
/////////////////////////////////////////////////////////////
template<int FIFO_DEPTH>
class Ring_Buffering : public IMemory<FIFO_DEPTH>{
public:

    sc_vector< sc_signal<sc_bv<9> > >  fifo_r;
    sc_signal<sc_uint<FIFO_DEPTH>> rd_ptr_r;
    sc_signal<sc_uint<FIFO_DEPTH>> wr_ptr_r;
    sc_signal<sc_uint<FIFO_DEPTH+1> > n_pos_r;


    void ring_buffering_fifo();
    void output();

    SC_HAS_PROCESS(Ring_Buffering);
    Ring_Buffering<FIFO_DEPTH>(sc_module_name mn);

    //inline ModuleType moduleType() const { return  XINAModule::TMemory; }
    inline const char* moduleName() const { return "Ring_Buffering"; }

    ~Ring_Buffering();
};
template<int FIFO_DEPTH>
inline Ring_Buffering<FIFO_DEPTH>::Ring_Buffering(sc_module_name mn)
                                :IMemory<FIFO_DEPTH>(mn)
{
        SC_METHOD(ring_buffering_fifo);
        this->sensitive << this->i_CLK << this->i_RST << this->i_WR<< this->i_RD<< this->i_DATA << n_pos_r;

        SC_METHOD(output);
        this->sensitive << this->i_CLK <<n_pos_r;

        fifo_r.init(FIFO_DEPTH);

}
template<int FIFO_DEPTH>
void Ring_Buffering<FIFO_DEPTH>::ring_buffering_fifo(){
        if(this->i_RST.read() == 1){
            rd_ptr_r.write(0);
            wr_ptr_r.write(0);
            n_pos_r.write(0);
        }

        else if(this->i_CLK.posedge()){
            if(this->i_WR.read() == 1  && n_pos_r.read() != FIFO_DEPTH){
                wr_ptr_r.write((wr_ptr_r.read()+1)%FIFO_DEPTH);

                fifo_r[wr_ptr_r.read()].write(this->i_DATA.read());

                if(this->i_RD.read() == 1 && n_pos_r.read() != 0){

                    rd_ptr_r.write((rd_ptr_r.read()+1)%FIFO_DEPTH);
                }
                else {
                    n_pos_r.write((n_pos_r.read()+1)%(FIFO_DEPTH+1));
                }
            }
            else if(this->i_RD.read() == 1 && n_pos_r.read() != 0){

                rd_ptr_r.write((rd_ptr_r.read()+1)%FIFO_DEPTH);

                n_pos_r.write((n_pos_r.read()-1)%(FIFO_DEPTH+1));
            }

        }
}

template<int FIFO_DEPTH>
void Ring_Buffering<FIFO_DEPTH>::output(){

    this->o_ROK.write((n_pos_r.read() != 0) ? true : false);
    this->o_WOK.write((n_pos_r.read() != (FIFO_DEPTH+1)) ? true : false);
    this->o_DATA.write(fifo_r[rd_ptr_r.read()].read());
}

/// destructor of abstract class
template<int FIFO_DEPTH>
inline Ring_Buffering<FIFO_DEPTH>::~Ring_Buffering(){}



#endif // __RING_BUFFERING_H__
