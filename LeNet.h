#include "systemc.h"
#include "define.h"
#include <iostream>
#include <fstream>
using namespace std;
// vvvvv put your code here vvvvv
  SC_MODULE( Conv_pool ) {
  
 	sc_in_clk clk;
	sc_in < bool > rst;
	
  sc_out < bool > rom_rd;
	sc_out < sc_uint<16> > rom_addr;
	sc_in < DATA_TYPE > rom_data_out;
 
  sc_out < bool > dense_en;
  sc_in < bool > conv_pool_rd;
  sc_in < sc_uint<16> > conv_pool_addr;
  sc_out < DATA_TYPE > conv_pool_data_out;
	
	void run2();
  DATA_TYPE max(DATA_TYPE a,DATA_TYPE b,DATA_TYPE c,DATA_TYPE d) //find max among four elements
    {
        DATA_TYPE max=a;
        if(b>max)
        max=b;
        if(c>max)
        max=c;
        if(d>max)
        max=d;
        return max;
    }

  DATA_TYPE conv1[156]={0},conv2[2416]={0}; //some elements are biases
  DATA_TYPE dense1[30840]={0},dense2[10164]={0},dense3[850]={0};
  DATA_TYPE input[784]={0},output[3456]={0},output2[864]={0},output3[1024]={0},temp[6][64],output4[256]={0};
  DATA_TYPE total[42110]={0};
  int state=0,index=0;

	SC_CTOR( Conv_pool ) {
   for(int i=0;i<6;i++)
   {
     for(int j=0;j<64;j++)
     temp[i][j]=0;
   
   }
		SC_METHOD( run2 );
		sensitive << rst.pos() << clk.pos();
	}

};

  SC_MODULE( Dense ){
 
  sc_in_clk clk;
  sc_in < bool > dense_en;
  sc_out < bool > conv_pool_rd;
  sc_out < sc_uint<16> > conv_pool_addr;
  sc_in < DATA_TYPE > conv_pool_data_out;
  
 	sc_out < DATA_TYPE > result;
	sc_out < bool > output_valid;
  
  void run();
  
  int state=0;
  DATA_TYPE dense1[30840]={0},dense2[10164]={0},dense3[850]={0};
  DATA_TYPE input[256]={0},out1[120]={0},out2[84]={0},out3[10]={0};
  
  SC_CTOR( Dense ) {

		SC_METHOD( run );
		sensitive << clk.pos();
	}
  
  };
  
SC_MODULE( LeNet ) {	
	sc_in_clk clk;
	sc_in < bool > rst;
	
	sc_out < bool > rom_rd;
	sc_out < sc_uint<16> > rom_addr;
	sc_in < DATA_TYPE > rom_data_out;
	
	sc_out < bool > ram_wr;
	sc_out < sc_uint<16> > ram_addr;
	sc_in < DATA_TYPE > ram_data_out;
	sc_out < DATA_TYPE > ram_data_in;
	
	sc_out < DATA_TYPE > result;
	sc_out < bool > output_valid;
 
  
  
  sc_signal < bool > s1,s2;
  sc_signal < sc_uint<16> > s3;
  sc_signal < DATA_TYPE > s4;
  
  
  
	SC_CTOR( LeNet )
	{
	
   Conv_pool* a=new Conv_pool ("a");
   Dense *b = new Dense("b");
   
    a->clk(clk);
    a->rst(rst);
    a->rom_rd(rom_rd);
    a->rom_addr(rom_addr);
    a->rom_data_out(rom_data_out);
    a->dense_en(s1);
    a->conv_pool_rd(s2);
    a->conv_pool_addr(s3);
    a->conv_pool_data_out(s4);
    
    b->dense_en(s1);
    b->conv_pool_rd(s2);
    b->conv_pool_addr(s3);
    b->conv_pool_data_out(s4);
     b->clk(clk);
     b->result(result);
     b->output_valid(output_valid);
	}
};
// ^^^^^ put your code here ^^^^^
