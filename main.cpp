#include "LeNet.h"
#include "ROM.h"
#include "RAM.h"
#include "Monitor.h"
#include "clockreset.h"
#include <iostream>

using namespace std;

int sc_main( int argc, char* argv[] ) {
	
	sc_signal < bool > clk, rst;
 
  sc_signal < bool > rom_rd;
	sc_signal < sc_uint<16> > rom_addr;
	sc_signal < DATA_TYPE > rom_data_out;
	
	sc_signal < bool > ram_wr;
	sc_signal < sc_uint<16> > ram_addr;
	sc_signal < DATA_TYPE > ram_data_out;
	sc_signal < DATA_TYPE > ram_data_in;
	
	sc_signal < DATA_TYPE > data_in;
	sc_signal < bool > data_valid;
	
	
	Reset m_Reset( "m_Reset", 10 );
	Clock m_Clock( "m_Clock", 3, 200000000 );
	ROM m_ROM( "m_ROM" );
	LeNet m_LeNet( "m_LeNet" );
	Monitor m_Monitor( "m_Monitor" );
  RAM m_RAM( "m_RAM" );
	
	m_Reset( rst );
	m_Clock( clk );
	m_ROM( clk, rom_rd, rom_addr, rom_data_out );
	m_LeNet(clk, rst,rom_rd, rom_addr, rom_data_out , ram_wr, ram_addr, ram_data_out, ram_data_in, data_in, data_valid );
	m_Monitor(clk,rst, data_in, data_valid );
  m_RAM( clk, ram_wr, ram_addr, ram_data_out , ram_data_in);
		
	sc_start( 200000000, SC_NS );
	return 0;

}











