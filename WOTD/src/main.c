#include <pebble.h>
  
static Window *s_main_window;
static TextLayer *s_time_layer;
static TextLayer *s_word_layer;
static TextLayer *s_main_layer;
static TextLayer *s_def_layer;

static GFont s_time_font;
static GFont s_word_font;
static GFont s_main_font;
static GFont s_def_font;
static BitmapLayer *s_background_layer;
static GBitmap *s_background_bitmap;

static void update_time() {
  // Get a tm structure
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);

  // Create a long-lived buffer
  static char buffer[] = "00:00";

  // Write the current hours and minutes into the buffer
  if(clock_is_24h_style() == true) {
    //Use 2h hour format
    strftime(buffer, sizeof("00:00"), "%H:%M", tick_time);
  } else {
    //Use 12 hour format
    strftime(buffer, sizeof("00:00"), "%I:%M", tick_time);
  }

  // Display this time on the TextLayer
  text_layer_set_text(s_time_layer, buffer);
}

static void main_window_load(Window *window) {
  //Create GBitmap, then set to created BitmapLayer
   s_background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_BLACK_RECT);
   s_background_layer = bitmap_layer_create(GRect(0, 0, 144, 168));
   bitmap_layer_set_bitmap(s_background_layer, s_background_bitmap);
   layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_background_layer));
  
  // Create time TextLayer
  s_time_layer = text_layer_create(GRect(5, 136, 139, 50));
  text_layer_set_background_color(s_time_layer, GColorBlack);
  text_layer_set_text_color(s_time_layer, GColorClear);
  text_layer_set_text(s_time_layer, "00:00");
    
    // Create title TextLayer
    s_word_layer = text_layer_create(GRect(5, 0, 139, 50));
      text_layer_set_background_color(s_word_layer, GColorBlack);
  text_layer_set_text_color(s_word_layer, GColorClear);
  text_layer_set_text(s_word_layer, "Word of the Day:");
    
        // Create word TextLayer
    s_main_layer = text_layer_create(GRect(5, 0, 139, 50));
      text_layer_set_background_color(s_main_layer, GColorBlack);
  text_layer_set_text_color(s_main_layer, GColorClear);
  text_layer_set_text(s_main_layer, "Emblem:");
    
    
   //fonts_get_system_font(FONT_KEY_GOTHIC_24); 
    
        // Create def TextLayer
   s_def_layer = text_layer_create(GRect(5, 60, 139, 50));
    text_layer_set_background_color(s_def_layer, GColorBlack);
  text_layer_set_text_color(s_def_layer, GColorClear);
  text_layer_set_text(s_def_layer, "(n.) a sign, design, or figure that identifies or represents something");
    
  
  //Create GFont
  s_time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PERFECT_DOS_25));
s_word_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PERFECT_DOS_15));
    s_main_font = fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD); ;
        s_def_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PERFECT_DOS_15));
  //Apply to TextLayer
  text_layer_set_font(s_time_layer, s_time_font);
 text_layer_set_text_alignment(s_time_layer, GTextAlignmentRight);
    
      text_layer_set_font(s_word_layer, s_word_font);
  text_layer_set_text_alignment(s_word_layer, GTextAlignmentLeft);
    
    
    
         text_layer_set_font(s_main_layer, s_main_font);
  text_layer_set_text_alignment(s_main_layer, GTextAlignmentCenter);
    
             text_layer_set_font(s_def_layer, s_def_font);
 text_layer_set_text_alignment(s_def_layer, GTextAlignmentLeft);

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer));
    //layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_word_layer));
        layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_main_layer));
          layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_def_layer));
  
  // Make sure the time is displayed from the start
  update_time();
}

static void main_window_unload(Window *window) {
  //Unload GFont
  fonts_unload_custom_font(s_time_font);
  
  //Destroy GBitmap
  gbitmap_destroy(s_background_bitmap);

  //Destroy BitmapLayer
  bitmap_layer_destroy(s_background_layer);
  
  // Destroy TextLayer
  text_layer_destroy(s_time_layer);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
}
  
static void init() {
  // Create main Window element and assign to pointer
  s_main_window = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);
  
  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}

static void deinit() {
  // Destroy Window
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
