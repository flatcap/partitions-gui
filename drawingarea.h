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

private:

};

#endif // _DRAWINGAREA_

