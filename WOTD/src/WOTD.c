#include <pebble.h>


static Window *window;
static TextLayer *heading_layer;
static TextLayer *text_layer;

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  	text_layer_set_text(text_layer, "Select");
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  	text_layer_set_text(text_layer, "Up");
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
 	 text_layer_set_text(text_layer, "Down");
}

static void click_config_provider(void *context) {
  	window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  	window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  	window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void window_load(Window *window) {
  	Layer *window_layer = window_get_root_layer(window);
  	GRect bounds = layer_get_bounds(window_layer);
	heading_layer = text_layer_create(GRect(5, 5, 50, 50));
  	text_layer = text_layer_create(GRect(0, 100, 144, 25));
  	text_layer_set_text(heading_layer, "Word of the Day");
	text_layer_set_font(heading_layer, GOTHIC_24_BOLD);
	text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
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
