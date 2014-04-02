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
#include "utf8_char.h"

utf8_char *new_utf8_char(char *s)
{
	utf8_char *this = (utf8_char *)malloc(sizeof(utf8_char));

	if (!this) {
		return NULL;
	}

	this->s = s;
	this->next = NULL;
	this->prev = NULL;

	return this;
}

void destroy_utf8_char(utf8_char *this)
{
	if (!this) {
		return;
	}

	if (this->s) {
		free(this->s);
	}

	free(this);
}

utf8_char *utf8_char_clear_str(utf8_char *this)
{
	if (!this) {
		return NULL;
	}

	while (this->prev) {
		this = this->prev;
	}

	while (this->next) {
		this = this->next;
		destroy_utf8_char(this->prev);
	}

	this->prev = NULL;

	return this;
}

void utf8_char_destroy_str(utf8_char *this)
{
	destroy_utf8_char(utf8_char_clear_str(this));
}

void utf8_char_addch(utf8_char *this)
{
	if (!this || !this->s) {
		addch(' ');
	} else {
		addstr(this->s);
	}
}

void utf8_char_mvaddch(int ypos, int xpos, utf8_char *this)
{
	if (!this || !this->s) {
		mvaddch(ypos, xpos, ' ');
	} else {
		mvaddstr(ypos, xpos, this->s);
	}
}

unsigned char utf8_char_strlen(utf8_char *this)
{
	if (!this) {
		return 0;
	}

	int len = 0;

	while (this->prev) {
		this = this->prev;
	}

	while (this->s) {
		++len;
		this = this->next;
	}

	return len;
}

unsigned char utf8_char_nbytes(utf8_char *this)
{
	if (!this || !this->s) {
		return 0;
	}

	if (!(this->s[0] & 0x80)) {
		return 1;
	} else if (!(this->s[0] & 0x20)) {
		return 2;
	} else if (!(this->s[0] & 0x10)) {
		return 3;
	} else if (!(this->s[0] & 0x08)) {
		return 4;
	} else if (!(this->s[0] & 0x04)) {
		return 5;
	} else if (!(this->s[0] & 0x02)) {
		return 6;
	} else if (!(this->s[0] & 0x01)) {
		return 7;
	} else { /* this->s[0] == 0xFF */
		unsigned char len = 0, i;

		for (i = 0; this->s[i]; ++i) {
			++len;
		}

		return len;
	}
}

void copystr(char *dest, char *src)
{
	if (!dest || !src) {
		return;
	}

	while (*src) {
		*dest = *src;
		++src;
		++dest;
	}
}

char *utf8_char_to_str(struct utf8_char *this)
{
	if (!this) {
		return NULL;
	}

	int len = 0;
	char *str;

	while (this->prev) {
		this = this->prev;
	}

	while (this->s) {
		len += utf8_char_nbytes(this);
		this = this->next;
	}

	str = (char *)malloc(sizeof(char) * (len + 1));

	if (!str) {
		return NULL;
	}

	int i = 0;

	while (this->prev) {
		this = this->prev;
	}

	while (this->s) {
		copystr(str + i, this->s);
		i += utf8_char_nbytes(this);
		this = this->next;
	}

	str[i] = '\0';

	return str;
}

void utf8_char_insert(utf8_char *this, utf8_char *new)
{
	if (!this || !new) {
		return;
	}

	new->next = this;
	new->prev = this->prev;
	this->prev = new;

	if (new->prev) {
		new->prev->next = new;
	}
}

void utf8_char_remove(utf8_char *this)
{
	if (!this || !this->s) {
		return;
	}

	this->next->prev = this->prev;

	if (this->prev) {
		this->prev->next = this->next;
	}

	destroy_utf8_char(this);
}
