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

#ifndef INPUT_FIELD_H
#define INPUT_FIELD_H

#include "utf8.h"

typedef struct {
	int ypos;
	int xpos;
	unsigned char width;
	const char *default_str;
	utf8_char *str;
	unsigned char char_pos;
	unsigned hide_input : 1;
} input_field;

input_field *new_input_field(int ypos,
                             int xpos,
                             unsigned char width,
                             const char *default_str,
                             unsigned char hide_input);
void destroy_input_field(input_field *this);

void input_field_draw(input_field *this);
int input_field_getstr(input_field *this, char **dest);

#endif
