#include <pebble.h>

Window *window;
Layer *graphics_layer;

void graphics_proc(Layer *layer, GContext *ctx){
    //Sets the graphics context's current colour
    //Whatever the last set colour was with the colour set functions will be the one that
    //is applied when the stroke/fill functions are called (respectively)
    graphics_context_set_stroke_color(ctx, GColorRed);
    //Sets the line stroke to a width of 3 (pixels). The default is one
    graphics_context_set_stroke_width(ctx, 3);
    //Draws a line from (x: 0, y: 0) to (x: 60, y: 65) with the current context (colour red, stroke width 3)
    graphics_draw_line(ctx, GPoint(0, 0), GPoint(60, 65));

    //Sets the fill colour to blue
    graphics_context_set_fill_color(ctx, GColorBlue);
    //Fills in a circle with a radius of 10 pixels at point (x: 80, y: 80)
    graphics_fill_circle(ctx, GPoint(80, 80), 10);
}

//Called when the window loads
void window_load(Window *window){
    Layer *window_layer = window_get_root_layer(window);

    //Creates the graphics layer
    graphics_layer = layer_create(layer_get_bounds(window_layer));
    //Sets the update procedure so the system knows what to call on when it wants to draw stuff!!!
    layer_set_update_proc(graphics_layer, graphics_proc);
    //Adds the layer to the window itself
    layer_add_child(window_layer, graphics_layer);
}

//Called when the window unloads
void window_unload(Window *window){
    layer_destroy(graphics_layer);
}

//Initializes the app
void init(){
    window = window_create();
    window_set_window_handlers(window, (WindowHandlers) {
        .load = window_load,
        .unload = window_unload
    });
    window_stack_push(window, true);
}

//Deinitializes the app
void deinit(){
    window_destroy(window);
}

//The main function, seen in every C program
int main(){
    init();
    app_event_loop();
    deinit();
}
