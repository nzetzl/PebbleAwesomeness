#include <pebble.h>


static Window *window;
static TextLayer *heading_layer;
static TextLayer *text_layer;
static GFont word_font;
static GFont title_font;
static int x = 0;

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
	
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  	if (x < 0) {
		x++;
	}
	if (x < -2) {
		text_layer_set_text(text_layer, "Come back again tomorrow for more words!");
	} else if (x == -2) {
		text_layer_set_text(text_layer, "Butyraceous (adj.): of the nature of, resembling");
	} else if (x == -1) {
		text_layer_set_text(text_layer, 
							"Ad Hockery (n.): reliance on temporary solutions rather than on consistent, long-term plans");
	} else if (x == 0) {
		text_layer_set_text(text_layer, "Emblem (n.): a sign, design, or figure that identifies or represents something.");
	}
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
 	 x--;
	if (x < -2) {
		text_layer_set_text(text_layer, "Come back again tomorrow for more words!");
	} else if (x == -2) {
		text_layer_set_text(text_layer, "Butyraceous (adj.): of the nature of, resembling");
	} else if (x == -1) {
		text_layer_set_text(text_layer, 
							"Ad Hockery (n.): reliance on temporary solutions rather than on consistent, long-term plans");
	} else if (x == 0) {
		text_layer_set_text(text_layer, "Emblem (n.): a sign, design, or figure that identifies or represents something.");
	}
}

static void click_config_provider(void *context) {
  	window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  	window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  	window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void window_load(Window *window) {
  	Layer *window_layer = window_get_root_layer(window);
  	GRect bounds = layer_get_bounds(window_layer);
	heading_layer = text_layer_create(GRect(20, 5, 100, 100));
  	text_layer = text_layer_create(GRect(22, 80, 100, 60));
	title_font = fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD);
	word_font = fonts_get_system_font(FONT_KEY_GOTHIC_18);
	text_layer_set_font(heading_layer, title_font);
	text_layer_set_font(text_layer, word_font);
  	text_layer_set_text(heading_layer, "Word of the Day");
	text_layer_set_text(text_layer, "Emblem (n.): a sign, design, or figure that identifies or represents something.");
	text_layer_set_text_alignment(text_layer, GTextAlignmentLeft);
  	text_layer_set_text_alignment(heading_layer, GTextAlignmentCenter);
  	layer_add_child(window_layer, text_layer_get_layer(heading_layer));
	layer_add_child(window_layer, text_layer_get_layer(text_layer));
}

static void window_unload(Window *window) {
  	text_layer_destroy(text_layer);
	text_layer_destroy(heading_layer);
}

static void init(void) {
 	 window = window_create();
 	 window_set_click_config_provider(window, click_config_provider);
 	 window_set_window_handlers(window, (WindowHandlers) {
    	.load = window_load,
    	.unload = window_unload,
  	});
  	const bool animated = true;
  	window_stack_push(window, animated);
}

static void deinit(void) {
  	window_destroy(window);
}

int main(void) {
  	init();
  	app_event_loop();
  	deinit();
}
