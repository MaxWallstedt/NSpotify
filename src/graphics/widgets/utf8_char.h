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

#ifndef UTF8_CHAR_H
#define UTF8_CHAR_H

typedef struct utf8_char utf8_char;

struct utf8_char {
	char *s;
	utf8_char *next;
	utf8_char *prev;
};

utf8_char *new_utf8_char(char *s);
void destroy_utf8_char(utf8_char *this);

utf8_char *utf8_char_clear_str(utf8_char *this);
void utf8_char_destroy_str(utf8_char *this);

void utf8_char_addch(utf8_char *this);
void utf8_char_mvaddch(int ypos, int xpos, utf8_char *this);

unsigned char utf8_char_strlen(utf8_char *this);
unsigned char utf8_char_nbytes(utf8_char *this);
char *utf8_char_to_str(utf8_char *this);

void utf8_char_insert(utf8_char *this, utf8_char *new);
void utf8_char_remove(utf8_char *this);

#endif
