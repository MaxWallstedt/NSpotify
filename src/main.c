/* NSpotify is an ncurses based Spotify client.
 * Copyright © 2014 Max Wällstedt
 *
 * This file is part of NSpotify.
 *
 * NSpotify is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * NSpotify is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with NSpotify. If not, see <http://www.gnu.org/licenses/>.
 *
 * You can contact me by email at <max.wallstedt@gmail.com>.
 */

#include <curses.h>
#include <locale.h>
#include "ns_err.h"
#include "nspotify.h"

int main(int argc, char **argv)
{
	setlocale(LC_ALL, "");

	initscr();
	raw();
	noecho();
	keypad(stdscr, TRUE);
	meta(stdscr, TRUE);
	curs_set(0);

	ns_err err = start_nspotify();

	endwin();

	if (err) {
		ns_err_print(err);
		return 1;
	}

	return 0;
}
