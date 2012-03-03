#include <iostream>
#include <stdlib.h>

#include "treeview.h"

/**
 * TreeView
 */
TreeView::TreeView()
{
	//Fill popup menu:
	Gtk::MenuItem* item = Gtk::manage(new Gtk::MenuItem("_Edit", true));
	item->signal_activate().connect( sigc::mem_fun(*this, &TreeView::on_menu_file_popup_generic) );
	m_Menu_Popup.append(*item);

	item = Gtk::manage(new Gtk::MenuItem("_Process", true));
	item->signal_activate().connect( sigc::mem_fun(*this, &TreeView::on_menu_file_popup_generic) );
	m_Menu_Popup.append(*item);

	item = Gtk::manage(new Gtk::MenuItem("_Remove", true));
	item->signal_activate().connect( sigc::mem_fun(*this, &TreeView::on_menu_file_popup_generic) );
	m_Menu_Popup.append(*item);

	m_Menu_Popup.accelerate(*this);
	m_Menu_Popup.show_all();

	set_has_tooltip (true);

	signal_popup_menu().connect (sigc::mem_fun (*this, &TreeView::on_popup_menu));
}

/**
 * ~TreeView
 */
TreeView::~TreeView()
{
}

/**
 * on_popup_menu
 */
bool TreeView::on_popup_menu (void)
{
	m_Menu_Popup.popup (0, 0);

	return true;
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


/**
 * get_color_as_pixbuf
 */
Glib::RefPtr<Gdk::Pixbuf> get_color_as_pixbuf (int width, int height)
{
	Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create (Gdk::COLORSPACE_RGB, false, 8, width, height);

	int r = random();
	pixbuf->fill (r);

	return pixbuf;
}

/**
 * init_treeview
 */
void TreeView::init_treeview (DPContainer *c)
{
	Gtk::TreeModel::Row row;
	Gtk::TreeModel::Row childrow;

	//Create the Tree model:
	m_refTreeModel = Gtk::TreeStore::create (m_Columns);
	set_model (m_refTreeModel);

	//All the items to be reordered with drag-and-drop:
	//set_reorderable();

	std::vector<DPContainer*>::iterator i;
	for (i = c->children.begin(); i != c->children.end(); i++) {
		DPContainer *x = (*i);
		//std::cout << "name: " << x->name << std::endl;
		row = *(m_refTreeModel->append());
		row[m_Columns.m_col_icon] = render_icon_pixbuf (Gtk::Stock::DND, Gtk::ICON_SIZE_MENU);
		row[m_Columns.m_col_name] = x->name;
		row[m_Columns.m_col_type] = x->type;
		row[m_Columns.m_col_size] = x->size;
		row[m_Columns.m_col_colour] = get_color_as_pixbuf (16, 16);

		if (x->children.size() > 0) {
			std::vector<DPContainer*>::iterator j;
			for (j = x->children.begin(); j != x->children.end(); j++) {
				DPContainer *y = (*j);
				//std::cout << "\tchild: " << y->name << std::endl;
				childrow = *(m_refTreeModel->append (row.children()));
				childrow[m_Columns.m_col_icon] = render_icon_pixbuf (Gtk::Stock::MEDIA_RECORD, Gtk::ICON_SIZE_MENU);
				childrow[m_Columns.m_col_name] = y->name;
				childrow[m_Columns.m_col_type] = y->type;
				childrow[m_Columns.m_col_size] = y->size;
				childrow[m_Columns.m_col_colour] = get_color_as_pixbuf (16, 16);
			}
		}
	}

	//Add the TreeView's view columns:
	Gtk::TreeView::Column* col = NULL;

	col = Gtk::manage (new Gtk::TreeView::Column ("Name"));
	col->pack_start(m_Columns.m_col_icon, false);
	col->pack_start(m_Columns.m_col_name, true);
	append_column(*col);

	//append_column ("Name", m_Columns.m_col_name);
	append_column ("Type", m_Columns.m_col_type);
	//append_column ("Size", m_Columns.m_col_size);

	col = Gtk::manage (new Gtk::TreeView::Column ("Size"));
	col->pack_start(m_Columns.m_col_colour, false);
	col->pack_start(m_Columns.m_col_size,   true);
	append_column(*col);


	//Connect signal:
	signal_row_activated().connect (sigc::mem_fun (*this, &TreeView::on_row_activated));
	signal_query_tooltip().connect (sigc::mem_fun (*this, &TreeView::on_query_tooltip));
}

/**
 * on_row_activated
 */
void TreeView::on_row_activated (const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn *col)
{
	std::cout << "Path: " << path.to_string() << std::endl;

	Gtk::TreeModel::iterator iter = m_refTreeModel->get_iter (path);
	if (iter)
	{
		DPContainer *c = NULL;
		Gtk::TreeModel::Row row = *iter;
		std::cout << "Row activated: Name=" << row[m_Columns.m_col_name] << ", Type=" << row[m_Columns.m_col_type] << std::endl;

		c = row[m_Columns.m_col_container];
		std::cout << typeid(row[m_Columns.m_col_container]).name() << std::endl;
		std::cout << typeid(c).name() << std::endl;
		std::cout << "Name=" << c->name << std::endl;
	}
}

/**
 * on_query_tooltip
 */
bool TreeView::on_query_tooltip (int x, int y, bool keyboard_tooltip, const Glib::RefPtr<Gtk::Tooltip>& tooltip)
{
	if (keyboard_tooltip)
		return false;

	int tx = 0;
	int ty = 0;

	convert_widget_to_tree_coords (x, y, tx, ty);

	//std::cout << "tooltip at (x,y) " << x << "," << y << "-- (tx,ty) " << tx << "," << ty << std::endl;

	Gtk::TreeModel::Path path;

	if (get_path_at_pos (tx, ty, path)) {
#if 0
		tooltip->set_text (path.to_string());
#else
		Gtk::TreeModel::iterator iter = m_refTreeModel->get_iter (path);
		Gtk::TreeModel::Row row = *iter;
		tooltip->set_text (row[m_Columns.m_col_name] + ":" + row[m_Columns.m_col_type]);
#endif
	} else {
		// implies mouse over non-data part of textview, e.g. headers
		tooltip->set_text ("wibble");
	}

	return true;
}
