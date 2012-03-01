#include <iostream>

#include <gtkmm.h>

#include "drawingarea.h"

/**
 * DrawingArea
 */
DrawingArea::DrawingArea()
{
	set_size_request (400, 400);
	set_hexpand (true);
	set_vexpand (false);
}

/**
 * ~DrawingArea
 */
DrawingArea::~DrawingArea()
{
}


/**
 * draw_box
 */
void DrawingArea::draw_box (const Cairo::RefPtr<Cairo::Context>& cr, double x, double y, double width, double height, double line_width, double red, double green, double blue)
{
	cr->set_line_width(line_width);
	cr->set_source_rgb(red, green, blue);

	double half = line_width/2;

	Cairo::Antialias a = cr->get_antialias();
	cr->set_antialias (Cairo::ANTIALIAS_NONE);

	cr->move_to (x,                y + half);
	cr->line_to (x + width - half, y + half);
	cr->line_to (x + width - half, y + height - half);
	cr->line_to (x + half,         y + height - half);
	cr->line_to (x + half,         y);

	cr->stroke();
	cr->set_antialias (a);
}

/**
 * on_draw
 */
bool DrawingArea::on_draw (const Cairo::RefPtr<Cairo::Context>& cr)
{
	//std::cout << __PRETTY_FUNCTION__ << std::endl;
	Gtk::Allocation allocation = get_allocation();

	int width  = allocation.get_width();
	int height = allocation.get_height();

	double x = 0;
	double y = 0;

	double line_width = 10;

	double red   = 1.0;
	double green = 0.0;
	double blue  = 0.0;

#if 1
	for (int i = 0; i < 4; i++) {
		if (i % 2) {
			red = 1.0; green = 0.0;
		} else {
			red = 0.0; green = 1.0;
		}

		draw_box (cr, x, y, width, height, line_width, red, green, blue);

		x += 1*line_width;
		y += 1*line_width;

		width  -= (2 * line_width);
		height -= (2 * line_width);
	}
#endif

#if 0
	cr->set_line_width(10.0);
	cr->set_source_rgb(1.0, 0.0, 0.0);
	cr->move_to(0, 5);
	cr->line_to(width-5, 5);
	cr->line_to(width-5, height-5);
	cr->line_to(5, height-5);
	cr->line_to(5, 0);
	cr->stroke();
#endif

#if 0
	Gtk::StockID id ("gtk-dialog-warning");
	Gtk::Image image (id, Gtk::IconSize (64));
	Glib::RefPtr<Gdk::Pixbuf> pb = image.get_pixbuf();
	Gdk::Cairo::set_source_pixbuf (cr, pb, 100, 80);
	cr->fill();
#endif

	Glib::RefPtr<Pango::Layout> layout = Pango::Layout::create(cr);

	Pango::FontDescription font; // ("Wingdings 48");
	font.set_family ("Liberation Sans");
	font.set_size (48 * Pango::SCALE);

	//font = layout->get_font_description();
	//std::cout << font.get_family() << std::endl;
	//std::cout << (font.get_size() / Pango::SCALE) << std::endl;

	layout->set_font_description (font);
	layout->set_text("hello world");

#if 1
	int stringWidth = 0;
	int stringHeight = 0;
	layout->get_pixel_size(stringWidth, stringHeight);
	//std::cout << "text: " << stringWidth << "x" << stringHeight << std::endl;
	cr->move_to ((width-stringWidth)/2, (height-stringHeight)/2);
#endif

	//cr->move_to (20, 100);
	cr->set_source_rgb(0.0, 1.0, 0.0);

	layout->update_from_cairo_context (cr);
	layout->show_in_cairo_context (cr);

	return true;
}

