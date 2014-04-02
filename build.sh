#!/bin/bash

SRC=(
	"src/appkey.c"
	"src/main.c"
	"src/ns_err.c"
	"src/nspotify.c"

	"src/graphics/draw_box.c"
	"src/graphics/widgets/button.c"
	"src/graphics/widgets/checkbox.c"
	"src/graphics/widgets/input_field.c"
	"src/graphics/widgets/utf8_char.c"
	"src/graphics/widgets/utf8_strlen.c"
)

OUT="bin/nspotify"
CFLAGS="-Wall -O3"
LDFLAGS="-lncursesw -std=c99"

gcc $CFLAGS ${SRC[@]} -o $OUT $LDFLAGS
