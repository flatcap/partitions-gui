#include <iostream>

#include "treeview.h"

/**
 * TreeView
 */
TreeView::TreeView()
{
	//Fill popup menu:
	Gtk::MenuItem* item = Gtk::manage(new Gtk::MenuItem("_Edit"));
	item->signal_activate().connect( sigc::mem_fun(*this, &TreeView::on_menu_file_popup_generic) );
	m_Menu_Popup.append(*item);

	item = Gtk::manage(new Gtk::MenuItem("_Process"));
	item->signal_activate().connect( sigc::mem_fun(*this, &TreeView::on_menu_file_popup_generic) );
	m_Menu_Popup.append(*item);

	item = Gtk::manage(new Gtk::MenuItem("_Remove"));
	item->signal_activate().connect( sigc::mem_fun(*this, &TreeView::on_menu_file_popup_generic) );
	m_Menu_Popup.append(*item);

	m_Menu_Popup.accelerate(*this);
	m_Menu_Popup.show_all();
}

/**
 * ~TreeView
 */
TreeView::~TreeView()
{
}

/**
 * on_button_press_event
 */
bool TreeView::on_button_press_event(GdkEventButton* event)
{
	bool return_value = false;

	//Call base class, to allow normal handling,
	//such as allowing the row to be selected by the right-click:
	return_value = Gtk::TreeView::on_button_press_event(event);

	//Then do our custom stuff:
	if( (event->type == GDK_BUTTON_PRESS) && (event->button == 3) )
	{
		m_Menu_Popup.popup(event->button, event->time);
	}

	return return_value;
}

/**
 * on_menu_file_popup_generic
 */
void TreeView::on_menu_file_popup_generic()
{
	std::cout << "A popup menu item was selected." << std::endl;

	Glib::RefPtr<Gtk::TreeView::Selection> refSelection = get_selection();
	if(refSelection)
	{
		Gtk::TreeModel::iterator iter = refSelection->get_selected();
		if(iter)
		{
			std::cout << "selected something" << std::endl;
		}
	}
}

