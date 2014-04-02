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

unsigned char utf8_strlen(const char *s)
{
	unsigned char len = 0;

	while (*s) {
		++len;

		if (*s & 0x80) {
			if (!(*s & 0x20)) {
				s += 2;
			} else if (!(*s & 0x10)) {
				s += 3;
			} else if (!(*s & 0x08)) {
				s += 4;
			} else if (!(*s & 0x04)) {
				s += 5;
			} else if (!(*s & 0x02)) {
				s += 6;
			} else if (!(*s & 0x01)) {
				s += 7;
			}
		} else {
			++s;
		}
	}

	return len;
}
