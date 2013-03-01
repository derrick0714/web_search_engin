
#include "parser/parser.h"
#include "analysis_ctrl.h"


int main( char /* **argv */, int/* argc */)
{
	analysis_ctrl demo;
	demo.start();
	display::get_instance()->run();
	
	return 0;
}

