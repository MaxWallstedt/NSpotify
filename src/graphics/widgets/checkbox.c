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
#include <stdlib.h>
#include "checkbox.h"

checkbox *new_checkbox(int ypos, int xpos, unsigned char is_ticked)
{
	checkbox *this = (checkbox *)malloc(sizeof(checkbox));

	if (!this) {
		return NULL;
	}

	this->ypos = ypos;
	this->xpos = xpos;
	this->is_ticked = is_ticked;
	this->is_active = 0;

	return this;
}

void destroy_checkbox(checkbox *this)
{
	if (this) {
		free(this);
	}
}

void checkbox_draw(checkbox *this)
{
	if (this->is_active) {
		attron(A_STANDOUT);
	}

	mvaddstr(this->ypos, this->xpos, this->is_ticked ? "\u25A3" : "\u25A1");

	if (this->is_active) {
		attroff(A_STANDOUT);
	}
}

void checkbox_tick(checkbox *this)
{
	this->is_ticked = !(this->is_ticked);
	checkbox_draw(this);
}

void checkbox_set_active(checkbox *this)
{
	this->is_active = 1;
	checkbox_draw(this);
}

void checkbox_set_inactive(checkbox *this)
{
	this->is_active = 0;
	checkbox_draw(this);
}
