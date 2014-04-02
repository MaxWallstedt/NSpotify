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
#include "input_field.h"
#include "../draw.h"
#include "../../ns_err.h"
#include "../../interrupts.h"

#define max(a,b)	a > b ? a : b
#define min(a,b)	a < b ? a : b

input_field *new_input_field(int ypos,
                             int xpos,
                             unsigned char width,
                             const char *default_str,
                             unsigned char hide_input)
{
	input_field *this = (input_field *)malloc(sizeof(input_field));

	if (!this) {
		return NULL;
	}

	this->ypos = ypos;
	this->xpos = xpos;
	this->width = width;
	this->default_str = default_str;
	this->str = new_utf8_char(NULL);
	this->char_pos = 0;
	this->hide_input = hide_input;

	if (!this->str) {
		free(this);
		return NULL;
	}

	return this;
}

void destroy_input_field(input_field *this)
{
	if (!this) {
		return;
	}

	utf8_char_destroy_str(this->str);
	free(this);
}

void print_string(input_field *this)
{
	if (!this) {
		return;
	}

	utf8_char *tmp = this->str;
	utf8_char *start;

	int i;

	struct {
		unsigned left : 1;
		unsigned right : 1;
	} overflow = {0, 0};

	for (i = 0; i < this->char_pos; ++i) {
		tmp = tmp->prev;
	}

	start = tmp;

	if (start->prev) {
		overflow.left = 1;
	}

	for (i = 0; i < this->width - 1 && tmp->next; ++i) {
		tmp = tmp->next;
	}

	if (i == this->width - 1 && tmp->next && tmp->next->s) {
		overflow.right = 1;
	}

	move(this->ypos, this->xpos);

	for (i = 0; i < this->width && start->next; ++i) {
		if (this->hide_input) {
			addch('*');
		} else {
			utf8_char_addch(start);
		}

		start = start->next;
	}

	for ( ; i < this->width; ++i) {
		addch(' ');
	}

	if (overflow.left) {
		/* LEFT-POINTING DOUBLE ANGLE QUOTATION MARK */
		mvaddstr(this->ypos, this->xpos, "\u00AB");
	}

	if (overflow.right) {
		/* RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK */
		mvaddstr(this->ypos, this->xpos + this->width - 1, "\u00BB");
	}
}

void input_field_draw(input_field *this)
{
	if (!this) {
		return;
	}

	draw_box(this->ypos - 1, this->xpos - 1, 3, this->width + 2);

	if (!this->str->s && !this->str->prev) {
		mvaddnstr(this->ypos, this->xpos, this->default_str, this->width);

		if (utf8_strlen(this->default_str) > this->width) {
			/* RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK */
			mvaddstr(this->ypos, this->xpos + this->width - 1, "\u00BB");
		}
	} else {
		print_string(this);
	}
}

int input_field_getstr(input_field *this, char **dest)
{
	int key = 0, i;
	unsigned char ins_mode = 0;

	while (1) {
		if (*dest) {
			free(*dest);
		}

		*dest = utf8_char_to_str(this->str);

		if (*dest == NULL) {
			return NS_ERR_MALLOC;
		}

		print_string(this);

		if (ins_mode) {
			curs_set(2);
		} else {
			curs_set(1);
		}

		move(this->ypos, this->xpos + this->char_pos);

		key = getch();

		if (key == F11) {
			/* TODO Define behaviour here */
		} else if (key >= 0x20 && key <= 0xFF) {
			char *tmp_s = NULL;

			if (!(key & 0x80)) {
				tmp_s = (char *)malloc(sizeof(char) * 2);
			} else if (!(key & 0x20)) {
				tmp_s = (char *)malloc(sizeof(char) * 3);
			} else if (!(key & 0x10)) {
				tmp_s = (char *)malloc(sizeof(char) * 4);
			} else if (!(key & 0x08)) {
				tmp_s = (char *)malloc(sizeof(char) * 5);
			} else if (!(key & 0x04)) {
				tmp_s = (char *)malloc(sizeof(char) * 6);
			} else if (!(key & 0x02)) {
				tmp_s = (char *)malloc(sizeof(char) * 7);
			} else if (!(key & 0x01)) {
				tmp_s = (char *)malloc(sizeof(char) * 8);
			}

			if (!tmp_s) {
				return NS_ERR_MALLOC;
			}

			tmp_s[0] = key;
			int i = 1;

			if (tmp_s[0] & 0x80) {
				unsigned char bitmask = 0x40;

				while (tmp_s[0] & bitmask) {
					tmp_s[i] = getch();
					bitmask >>= 1;
					++i;
				}
			}

			tmp_s[i] = '\0';

			if (ins_mode && this->str->s) {
				free(this->str->s);
				this->str->s = tmp_s;
				this->str = this->str->next;
			} else {
				utf8_char *tmp_c = new_utf8_char(tmp_s);

				if (!tmp_c) {
					free(tmp_c);
					return NS_ERR_MALLOC;
				}

				utf8_char_insert(this->str, tmp_c);

				if (this->char_pos != this->width - 1
				    && (this->char_pos != this->width - 2
				        || !(this->str->s)
				        || (this->str->next
				            && !(this->str->next->s)))) {
					++(this->char_pos);
				}
			}
		} else {
			switch (key) {
			case KEY_LEFT:
				if (this->str->prev) {
					if (this->char_pos != 1
					    || !(this->str->prev->prev)) {
						--(this->char_pos);
					}

					this->str = this->str->prev;
				}

				break;

			case KEY_RIGHT:
				if (this->str->next) {
					if (this->char_pos != this->width - 1
					    && (this->char_pos != this->width - 2
					        || (this->str->next->next
					            && !(this->str->next->next->s)))) {
						++(this->char_pos);
					}

					this->str = this->str->next;
				}

				break;

			case KEY_BACKSPACE:
				if (this->str->prev) {
					utf8_char *tmp_c = this->str;

					for (i = 0; i < this->char_pos; ++i) {
						tmp_c = tmp_c->prev;
					}

					if (!(tmp_c->prev)) {
						--(this->char_pos);
					}

					utf8_char_remove(this->str->prev);
				}

				break;

			case KEY_DC:
				if (this->str->s) {
					utf8_char *tmp_c = this->str;

					for (i = 0; i < this->char_pos; ++i) {
						tmp_c = tmp_c->prev;
					}

					if (tmp_c->prev) {
						++(this->char_pos);
					}

					this->str = this->str->next;
					utf8_char_remove(this->str->prev);
				}

				break;

			case KEY_IC:
				ins_mode = !ins_mode;
				break;

			case KEY_HOME:
				while (this->str->prev) {
					this->str = this->str->prev;
				}

				this->char_pos = 0;
				break;

			case KEY_END:
				while (this->str->next) {
					this->str = this->str->next;
				}

				this->char_pos = min(utf8_char_strlen(this->str), this->width - 1);
				break;

			case CTRL_X:
				this->str = utf8_char_clear_str(this->str);
				this->char_pos = 0;

				break;

			default:
				curs_set(0);
				return key;
			}
		}

		/*
		switch (key) {
		case KEY_BACKSPACE:
			if (this->str->prev) {
				struct utf8_char *tmp = this->str;
				int tmp_count = this->char_pos;

				while (tmp_count) {
					tmp = tmp->prev;
					--tmp_count;
				}

				if (!tmp->prev) {
					--(this->char_pos);
				}

				tmp = this->str->prev;

				if (this->str->prev->prev) {
					this->str->prev->prev->next = this->str;
					this->str->prev = this->str->prev->prev;
				} else {
					this->str->prev = NULL;
				}

				destroy_utf8_char(tmp);
			}

			break;
		case KEY_DC:
			if (this->str->c) {
				struct utf8_char *tmp = this->str;
				int tmp_count = this->char_pos;

				while (tmp_count) {
					tmp = tmp->prev;
					--tmp_count;
				}

				if (tmp->prev) {
					while (tmp_count < this->width - 1
					       && tmp->next) {
						tmp = tmp->next;
						++tmp_count;
					}

					if (tmp_count == this->width - 1
					    && !(tmp->c)) {
						++(this->char_pos);
					}
				}

				tmp = this->str;

				if (this->str->prev) {
					this->str->prev->next = this->str->next;
					this->str->next->prev = this->str->prev;
				} else {
					this->str->next->prev = NULL;
				}

				this->str = this->str->next;
				destroy_utf8_char(tmp);
			}

			break;
		}
		*/
	}
}
