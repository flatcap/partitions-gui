#include <iostream>

#include "drawingarea.h"

/**
 * DrawingArea
 */
DrawingArea::DrawingArea()
{
	set_size_request (1024, 200);
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

	// coordinates for the center of the window
	int xc, yc;
	xc = width / 2;
	yc = height / 2;

	cr->set_line_width(10.0);

	// draw red lines out from the center of the window
	cr->set_source_rgb(0.8, 0.0, 0.0);
	cr->move_to(0, 0);
	cr->line_to(xc, yc);
	cr->line_to(0, height);
	cr->move_to(xc, yc);
	cr->line_to(width, yc);
	cr->stroke();

	return true;
}

