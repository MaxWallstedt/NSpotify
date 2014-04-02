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

#ifndef CHECKBOX_H
#define CHECKBOX_H

typedef struct {
	int ypos;
	int xpos;
	unsigned is_ticked : 1;
	unsigned is_active : 1;
} checkbox;

checkbox *new_checkbox(int ypos, int xpos, unsigned char is_ticked);
void destroy_checkbox(checkbox *this);

void checkbox_draw(checkbox *this);
void checkbox_tick(checkbox *this);
void checkbox_set_active(checkbox *this);
void checkbox_set_inactive(checkbox *this);

#endif
