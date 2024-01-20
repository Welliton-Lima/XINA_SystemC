#ifndef __SHIFT_BUFFERING_H__
#define __SHIFT_BUFFERING_H__

#include <systemc>
#include "math.h"
#include <cmath>

#include "Memory.h"

/////////////////////////////////////////////////////////////
/// Buffering Shift Class
/////////////////////////////////////////////////////////////
template<int FIFO_DEPTH>
class Shift_Buffering : public IMemory<FIFO_DEPTH>{
public:

    sc_vector< sc_signal<sc_bv<9>> > fifo_r;
    sc_signal<sc_uint<FIFO_DEPTH>> rd_ptr_r;

    void shif_buffering_fifo();
    void output();

    SC_HAS_PROCESS(Shift_Buffering);
    Shift_Buffering<FIFO_DEPTH>(sc_module_name mn);

    //inline ModuleType moduleType() const { return  XINAModule::TMemory; }
    inline const char* moduleName() const { return "Shift_Buffering"; }

    ~Shift_Buffering();
};

template<int FIFO_DEPTH>
inline Shift_Buffering<FIFO_DEPTH>::Shift_Buffering(sc_module_name mn)
                            :IMemory<FIFO_DEPTH>(mn)
{
        SC_METHOD(shif_buffering_fifo);
        this->sensitive << this->i_CLK << this->i_RST << this->i_WR << this->i_RD<< this->i_DATA << rd_ptr_r;

        SC_METHOD(output);
        this->sensitive << this->i_CLK << this->i_DATA << rd_ptr_r;

        fifo_r.init(FIFO_DEPTH);
}
template<int FIFO_DEPTH>
void Shift_Buffering<FIFO_DEPTH>::shif_buffering_fifo(){
       if(this->i_RST.read() == 1){
            rd_ptr_r.write(0);
        }
        else if(this->i_CLK.posedge() ){
            if(this->i_WR.read() == 1 && rd_ptr_r.read() != FIFO_DEPTH){

                fifo_r[0].write(this->i_DATA.read());

                for(int i=1;i<FIFO_DEPTH; i++){

                    fifo_r[i].write(fifo_r[i-1].read());
                }

                if(!(this->i_RD.read() ==1 && rd_ptr_r.read() != 0)){
                    rd_ptr_r.write((rd_ptr_r.read()+1)%FIFO_DEPTH);
                }

            }
            else if(this->i_RD.read() == 1 && rd_ptr_r.read() != 0){
                    rd_ptr_r.write((rd_ptr_r.read()-1)%FIFO_DEPTH);
            }
        }
}

template<int FIFO_DEPTH>
void Shift_Buffering<FIFO_DEPTH>::output(){
    this->o_ROK.write((rd_ptr_r.read() != 0) ? 1 : 0);
    this->o_WOK.write((rd_ptr_r.read() != FIFO_DEPTH) ? 1 : 0);
    this->o_DATA.write((rd_ptr_r.read() == 0) ? fifo_r[0] : fifo_r[rd_ptr_r.read()- 1]);
}

/// destructor of abstract class
template<int FIFO_DEPTH>
inline Shift_Buffering<FIFO_DEPTH>::~Shift_Buffering(){}

#endif // __SHIFT_BUFFERING_H__
