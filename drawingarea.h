#ifndef _DRAWINGAREA_
#define _DRAWINGAREA_

#include <gtkmm/drawingarea.h>

class DrawingArea : public Gtk::DrawingArea
{
public:
	DrawingArea();
	virtual ~DrawingArea();

protected:
	//Override default signal handler:
	virtual bool on_draw (const Cairo::RefPtr<Cairo::Context>& cr);

	void draw_box (const Cairo::RefPtr<Cairo::Context>& cr, double x, double y, double width, double height, double line_width, double red, double green, double blue);

private:

};

#endif // _DRAWINGAREA_

