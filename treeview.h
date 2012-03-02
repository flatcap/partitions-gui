#ifndef _TREEVIEW_H_
#define _TREEVIEW_H_

#include <gtkmm/treeview.h>
#include <gtkmm.h>

#include "container.h"

class TreeView : public Gtk::TreeView
{
public:
	TreeView();
	virtual ~TreeView();

	void init_treeview (DPContainer *c);

protected:
	// Override Signal handler:
	// Alternatively, use signal_button_press_event().connect_notify()
	virtual bool on_button_press_event(GdkEventButton *ev);

	//Signal handler for popup menu items:
	void on_menu_file_popup_generic();

	Gtk::Menu m_Menu_Popup;

	//Tree model columns:
	class ModelColumns : public Gtk::TreeModel::ColumnRecord
	{
	public:
		ModelColumns()
		{
			add(m_col_container);
			add(m_col_name);
			add(m_col_type);
			add(m_col_size);
		}

		Gtk::TreeModelColumn<DPContainer*>  m_col_container;
		Gtk::TreeModelColumn<Glib::ustring> m_col_name;
		Gtk::TreeModelColumn<Glib::ustring> m_col_type;
		Gtk::TreeModelColumn<long long>     m_col_size;
	};

	ModelColumns m_Columns;
	Glib::RefPtr<Gtk::TreeStore> m_refTreeModel;

	void on_row_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);
	bool on_query_tooltip (int x, int y, bool keyboard_tooltip, const Glib::RefPtr<Gtk::Tooltip>& tooltip);
	bool on_popup_menu (void);

private:

};

#endif // _TREEVIEW_H_

