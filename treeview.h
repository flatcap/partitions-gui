#ifndef _TREEVIEW_H_
#define _TREEVIEW_H_

#include <gtkmm/treeview.h>
#include <gtkmm.h>

class TreeView : public Gtk::TreeView
{
public:
	TreeView();
	virtual ~TreeView();

protected:
	// Override Signal handler:
	// Alternatively, use signal_button_press_event().connect_notify()
	virtual bool on_button_press_event(GdkEventButton *ev);

	//Signal handler for popup menu items:
	void on_menu_file_popup_generic();

	Gtk::Menu m_Menu_Popup;

private:

};

#endif // _TREEVIEW_H_

