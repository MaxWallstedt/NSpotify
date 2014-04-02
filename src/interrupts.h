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

#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#define CTRL_A	0x01
#define CTRL_B	0x02
#define CTRL_C	0x03
#define CTRL_D	0x04
#define CTRL_E	0x05
#define CTRL_F	0x06
#define CTRL_G	0x07
#define CTRL_H	0x08
#define CTRL_I	0x09 /* Same as '\t' */
#define CTRL_J	0x0A /* Same as '\n' and CTRL_M */
#define CTRL_K	0x0B
#define CTRL_L	0x0C
#define CTRL_M	0x0A /* Not 0x0D? Same as '\n' and CTRL_J */
#define CTRL_N	0x0E
#define CTRL_O	0x0F
#define CTRL_P	0x10
#define CTRL_Q	0x11
#define CTRL_R	0x12
#define CTRL_S	0x13
#define CTRL_T	0x14
#define CTRL_U	0x15
#define CTRL_V	0x16
#define CTRL_W	0x17
#define CTRL_X	0x18
#define CTRL_Y	0x19
#define CTRL_Z	0x1A

#define CTRL_2	0x00
#define CTRL_3	0x1B /* Same as 'Esc' key */
#define CTRL_4	0x1C
#define CTRL_5	0x1D
#define CTRL_6	0x1E
#define CTRL_7	0x1F

#define F11	0x9A /* Not a proper UTF-8 character */

#endif
