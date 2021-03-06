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

#include <stdint.h>
#include <stdlib.h>

const uint8_t g_appkey[] = {
	0x01, 0xD6, 0xDF, 0x50, 0x69, 0xCD, 0xC5, 0x8C, 0xF9, 0xA0, 0xDE, 0x81, 0xA0, 0xA5, 0x09, 0xF3,
	0x92, 0x3E, 0x14, 0x67, 0x38, 0x62, 0x17, 0x63, 0x21, 0xA7, 0x10, 0x2E, 0xF0, 0x86, 0x15, 0x4C,
	0x6A, 0x47, 0xC9, 0x35, 0xB2, 0xA4, 0xAF, 0x40, 0x9D, 0x6A, 0x38, 0x79, 0xA6, 0xD1, 0xE1, 0xDF,
	0x8F, 0x75, 0xEA, 0x9D, 0x98, 0x64, 0x01, 0x17, 0xB5, 0x96, 0x10, 0xA9, 0xE6, 0x30, 0xB0, 0x4A,
	0x1F, 0x3D, 0x60, 0x08, 0x1D, 0x44, 0x57, 0x87, 0x00, 0x70, 0xB4, 0xB5, 0x1A, 0xEB, 0xDC, 0xF6,
	0xAE, 0x75, 0x3E, 0x4A, 0x23, 0x61, 0xCD, 0x67, 0x26, 0x71, 0x3E, 0xC7, 0xBA, 0x8C, 0x2E, 0xCA,
	0x12, 0xDA, 0x8D, 0x0F, 0x77, 0x03, 0x7A, 0xC3, 0x63, 0x71, 0x38, 0xEE, 0x42, 0x26, 0x2E, 0x85,
	0x82, 0xCC, 0xE1, 0x75, 0x49, 0xD0, 0xD9, 0xA3, 0x32, 0x14, 0x53, 0xA2, 0x49, 0x00, 0xFC, 0x0F,
	0xDC, 0xAA, 0x9A, 0xD2, 0x85, 0x32, 0xB8, 0xD1, 0xA2, 0xBA, 0xB4, 0xB7, 0xC0, 0x61, 0xB1, 0x15,
	0xBD, 0xB0, 0xC6, 0xED, 0xBE, 0x5E, 0xB6, 0x17, 0x39, 0x13, 0xCB, 0x34, 0xDA, 0xB8, 0x03, 0x28,
	0x5D, 0xAF, 0xDC, 0x96, 0x0C, 0xBD, 0x52, 0x6A, 0xE7, 0x50, 0xEB, 0xC5, 0xAD, 0x7C, 0x09, 0xF5,
	0xA7, 0x0E, 0x21, 0xDA, 0x32, 0x2A, 0x15, 0x07, 0xC4, 0x94, 0xAA, 0x3F, 0x1F, 0x6D, 0x30, 0x41,
	0xC2, 0x42, 0x88, 0xFC, 0xF2, 0xE0, 0x88, 0x91, 0x6C, 0xDE, 0x8B, 0xA3, 0x9D, 0x77, 0x15, 0x7B,
	0x64, 0xA9, 0x77, 0x20, 0x7E, 0xD0, 0x63, 0x0A, 0x71, 0x83, 0xD3, 0x7C, 0xE9, 0x3E, 0x7C, 0xCA,
	0x52, 0xD2, 0x3D, 0x5A, 0xE4, 0x1D, 0xA7, 0x03, 0x1D, 0x5A, 0xBC, 0x48, 0x97, 0x0D, 0xD9, 0x3A,
	0x20, 0xEE, 0x07, 0x2A, 0x18, 0x75, 0xEE, 0x2E, 0xDA, 0xD7, 0xFD, 0xD0, 0x5C, 0xAA, 0xBA, 0x2C,
	0x28, 0xB0, 0x0E, 0x13, 0xAF, 0x12, 0x21, 0x0E, 0x90, 0xA5, 0xF2, 0xC0, 0xD1, 0x25, 0x8A, 0xCA,
	0x5F, 0x02, 0x9E, 0xC3, 0xEB, 0x5D, 0xBD, 0xF1, 0x89, 0x7E, 0x1B, 0x23, 0x29, 0xA7, 0x98, 0xC3,
	0x94, 0x6B, 0xFD, 0x2C, 0xE6, 0xF4, 0x0E, 0xF9, 0x3A, 0xEC, 0x0A, 0x8C, 0x85, 0xBD, 0x68, 0x52,
	0xE4, 0xB4, 0xC8, 0xCC, 0x66, 0xF1, 0x30, 0xD1, 0xDD, 0x74, 0x69, 0x9E, 0x3C, 0x6F, 0x8D, 0xA4,
	0x37,
};

const size_t g_appkey_size = sizeof(g_appkey);
