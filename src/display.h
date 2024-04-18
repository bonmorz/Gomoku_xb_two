#ifndef _DISPLAY_HH
#define _DISPLAY_HH

#include "../kmod/vga_gomoku.h"

class GMKDisplay{
	public:
		GMKDisplay(const char *dev_name):dev_name_(dev_name)
			{};
		// piece 0:No piece, 1:white piece, 2:black piece
		bool update_piece_info(int x,int y,int piece, int current=1);
		bool update_select(int x,int y);
		bool clear_board();
		bool sync();
		bool open_display();
	protected:
		vga_gomoku_arg_t arg_;
		int vga_gomoku_fd_=-1;
		const char *dev_name_;
};

#endif