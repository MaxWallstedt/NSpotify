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

void draw_box(int ypos, int xpos, int height, int width)
{
	if (height < 2 || width < 2)
		return;

	int i;
	int yendpos = ypos + height - 1;
	int xendpos = xpos + width - 1;
	int maxy, maxx;
	getmaxyx(stdscr, maxy, maxx);

	if (ypos >= 0 && ypos < maxy && xpos >= 0 && xpos < maxx) {
		/* BOX DRAWINGS LIGHT DOWN AND RIGHT */
		//mvprintw(ypos, xpos, "\xE2\x94\x8C");
		mvaddstr(ypos, xpos, "\u250C");
	}

	for (i = ypos + 1; i < yendpos; ++i) {
		if (i >= 0 && i < maxy && xpos >= 0 && xpos < maxx) {
			/* BOX DRAWINGS LIGHT VERTICAL */
			//mvprintw(i, xpos, "\xE2\x94\x82");
			mvaddstr(i, xpos, "\u2502");
		}
	}

	if (yendpos >= 0 && yendpos < maxy && xpos >= 0 && xpos < maxx) {
		/* BOX DRAWINGS LIGHT UP AND RIGHT */
		//mvprintw(yendpos, xpos, "\xE2\x94\x94");
		mvaddstr(yendpos, xpos, "\u2514");
	}

	++xpos;

	for ( ; xpos < xendpos; ++xpos) {
		if (ypos >= 0 && ypos < maxy && xpos >= 0 && xpos < maxx) {
			/* BOX DRAWINGS LIGHT HORIZONTAL */
			//mvprintw(ypos, xpos, "\xE2\x94\x80");
			mvaddstr(ypos, xpos, "\u2500");
		}

		if (yendpos >= 0 && yendpos < maxy && xpos >= 0 && xpos < maxx) {
			/* BOX DRAWINGS LIGHT HORIZONTAL */
			//mvprintw(yendpos, xpos, "\xE2\x94\x80");
			mvaddstr(yendpos, xpos, "\u2500");
		}
	}

	if (ypos >= 0 && ypos < maxy && xpos >= 0 && xpos < maxx) {
		/* BOX DRAWINGS LIGHT DOWN AND LEFT */
		//mvprintw(ypos, xpos, "\xE2\x94\x90");
		mvaddstr(ypos, xpos, "\u2510");
	}

	for (i = ypos + 1; i < yendpos; ++i) {
		if (i >= 0 && i < maxy && xpos >= 0 && xpos < maxx) {
			/* BOX DRAWINGS LIGHT VERTICAL */
			//mvprintw(i, xpos, "\xE2\x94\x82");
			mvaddstr(i, xpos, "\u2502");
		}
	}

	if (yendpos >= 0 && yendpos < maxy && xpos >= 0 && xpos < maxx) {
		/* BOX DRAWINGS LIGHT UP AND LEFT */
		//mvprintw(yendpos, xpos, "\xE2\x94\x98");
		mvaddstr(yendpos, xpos, "\u2518");
	}
}
