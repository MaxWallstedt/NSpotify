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
#include <string.h>
#include "button.h"
#include "../draw.h"
#include "utf8.h"

#define max(a,b)	a > b ? a : b
#define min(a,b)	a < b ? a : b

button *new_button(int ypos, int xpos, int width, const char *label)
{
	button *this = (button *)malloc(sizeof(button));

	if (!this) {
		return NULL;
	}

	this->ypos = ypos;
	this->xpos = xpos;
	this->width = width;
	this->label = label;
	this->is_active = 0;

	return this;
}

void destroy_button(button *this)
{
	if (this) {
		free(this);
	}
}

void button_draw(button *this)
{
	draw_box(this->ypos - 1, this->xpos - 1, 3, this->width + 2);

	unsigned char label_len = utf8_strlen(this->label);
	int pre_space = max((this->width - label_len) / 2, 0);
	int post_space = max(this->width - pre_space - label_len, 0);

	move(this->ypos, this->xpos);

	if (this->is_active) {
		attron(A_STANDOUT);
	}

	while (pre_space) {
		addch(' ');
		--pre_space;
	}

	addnstr(this->label, this->width);

	while (post_space) {
		addch(' ');
		--post_space;
	}

	if (utf8_strlen(this->label) > this->width) {
		/* RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK */
		mvaddstr(this->ypos, this->xpos + this->width - 1, "\u00BB");
	}

	if (this->is_active) {
		attroff(A_STANDOUT);
	}
}

void button_set_active(button *this)
{
	this->is_active = 1;
	button_draw(this);
}

void button_set_inactive(button *this)
{
	this->is_active = 0;
	button_draw(this);
}
