#include <iostream>

#include <gtkmm.h>

#include "drawingarea.h"

/**
 * DrawingArea
 */
DrawingArea::DrawingArea()
{
	set_size_request (400, 200);
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
 * on_draw
 */
bool DrawingArea::on_draw (const Cairo::RefPtr<Cairo::Context>& cr)
{
	//std::cout << __PRETTY_FUNCTION__ << std::endl;
	Gtk::Allocation allocation = get_allocation();
	const int width = allocation.get_width();
	const int height = allocation.get_height();

	cr->set_line_width(10.0);

	cr->set_source_rgb(1.0, 0.0, 0.0);
	cr->move_to(0, 5);
	cr->line_to(width-5, 5);
	cr->line_to(width-5, height-5);
	cr->line_to(5, height-5);
	cr->line_to(5, 0);
	cr->stroke();

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

