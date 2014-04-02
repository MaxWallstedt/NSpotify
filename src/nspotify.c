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
#include "ns_err.h"
#include "interrupts.h"
#include "graphics/draw.h"
#include "graphics/widgets.h"

#define	SPLASH_WIDTH	33

input_field *input_field_username;
input_field *input_field_password;
checkbox *checkbox_remember_me;
button *button_log_in;

void splash();
int init_widgets();
void free_widgets();
void free_strings(char *, char *);

ns_err start_nspotify()
{
	char *username = NULL, *password = NULL;
	int ret, key;

	if (init_widgets()) {
		goto malloc_fail;
	}

	splash();

	while (1) {
username_state:
		ret = input_field_getstr(input_field_username, &username);
		input_field_draw(input_field_username);

		switch (ret) {
		case NS_ERR_MALLOC:
			goto malloc_fail;
		case NS_ERR_REALLOC:
			goto realloc_fail;
		case KEY_UP:
			goto username_state;
		case CTRL_C:
			goto quit_ok;
		}

password_state:
		ret = input_field_getstr(input_field_password, &password);
		input_field_draw(input_field_password);

		switch (ret) {
		case NS_ERR_MALLOC:
			goto malloc_fail;
		case NS_ERR_REALLOC:
			goto realloc_fail;
		case KEY_UP:
			goto username_state;
		case CTRL_C:
			goto quit_ok;
		}

remember_me_state:
		checkbox_set_active(checkbox_remember_me);

		while (1) {
			switch (key = getch()) {
			case KEY_ENTER:
			case '\n':
			case '\r':
			case ' ':
				checkbox_tick(checkbox_remember_me);
				break;
			case KEY_UP:
				checkbox_set_inactive(checkbox_remember_me);
				goto password_state;
			case '\t':
			case KEY_RIGHT:
				checkbox_set_inactive(checkbox_remember_me);
				goto log_in_state;
			case CTRL_C:
				goto quit_ok;
			}
		}

log_in_state:
		button_set_active(button_log_in);

		while (1) {
			switch (key = getch()) {
			case KEY_ENTER:
			case '\n':
			case '\r':
			case ' ':
				goto quit_ok; /* Main-flöde här */
			case KEY_UP:
				button_set_inactive(button_log_in);
				goto password_state;
			case '\t':
				button_set_inactive(button_log_in);
				goto username_state;
			case KEY_LEFT:
				button_set_inactive(button_log_in);
				goto remember_me_state;
			case CTRL_C:
				goto quit_ok;
			}
		}
	}

quit_ok:
	free_widgets();
	free_strings(username, password);
	return NS_ERR_OK;

malloc_fail:
	free_widgets();
	free_strings(username, password);
	return NS_ERR_MALLOC;

realloc_fail:
	free_widgets();
	free_strings(username, password);
	return NS_ERR_REALLOC;
}

void splash()
{
	int maxy, maxx, xpos;
	getmaxyx(stdscr, maxy, maxx);

	xpos = (maxx - SPLASH_WIDTH) / 2;

	mvprintw(0, xpos + 2, "M  M  MMM         M  M  M");
	mvprintw(1, xpos + 2, "MM M M     M   M  M    M  M M");
	mvprintw(2, xpos + 2, "M MM  MM  M M M M MM M MM M M");
	mvprintw(3, xpos + 2, "M  M    M M M M M M  M M   MM");
	mvprintw(4, xpos + 2, "M  M MMM  MM   M   M M M    M");
	mvprintw(5, xpos + 2, "          M                M");

	mvprintw(7, xpos + 1, "Log in with          or");
	attron(A_BOLD);
	mvprintw(7, xpos + 13, "Facebook");
	mvprintw(7, xpos + 25, "Spotify");
	attroff(A_BOLD);

	input_field_username->xpos = xpos + 1;
	input_field_draw(input_field_username);

	input_field_password->xpos = xpos + 1;
	input_field_draw(input_field_password);

	checkbox_remember_me->xpos = xpos + 1;
	checkbox_draw(checkbox_remember_me);
	mvprintw(18, xpos + 3, "Remember me");

	button_log_in->xpos = xpos + 23;
	button_draw(button_log_in);

	draw_box(maxy - 2, -1, 3, 19);
	mvprintw(maxy - 1, 1, "Ctrl+'Q' - Quit");
}

int init_widgets()
{
	input_field_username = new_input_field(10, 0, 31, "Username", 0);

	if (!input_field_username) {
		return 1;
	}

	input_field_password = new_input_field(14, 0, 31, "Password", 1);

	if (!input_field_password) {
		return 1;
	}

	checkbox_remember_me = new_checkbox(18, 0, 0);

	if (!checkbox_remember_me) {
		return 1;
	}

	button_log_in = new_button(18, 0, 8, "Log in");

	if (!button_log_in) {
		return 1;
	}

	return 0;
}

void free_widgets()
{
	destroy_input_field(input_field_username);
	destroy_input_field(input_field_password);
	destroy_checkbox(checkbox_remember_me);
	destroy_button(button_log_in);
}

void free_strings(char *s1, char *s2)
{
	if (s1) {
		free(s1);
	}

	if (s2) {
		free(s2);
	}
}
