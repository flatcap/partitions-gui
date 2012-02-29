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
		row[m_Columns.m_col_name] = x->name;
		row[m_Columns.m_col_type] = x->type;
		row[m_Columns.m_col_size] = x->size;
		if (x->children.size() > 0) {
			std::vector<DPContainer*>::iterator j;
			for (j = x->children.begin(); j != x->children.end(); j++) {
				DPContainer *y = (*j);
				//std::cout << "\tchild: " << y->name << std::endl;
				childrow = *(m_refTreeModel->append (row.children()));
				childrow[m_Columns.m_col_name] = y->name;
				childrow[m_Columns.m_col_type] = y->type;
				childrow[m_Columns.m_col_size] = y->size;

			}
		}
	}

	//Add the TreeView's view columns:
	append_column ("Name", m_Columns.m_col_name);
	append_column ("Type", m_Columns.m_col_type);
	append_column ("Size", m_Columns.m_col_size);

	//Connect signal:
	signal_row_activated().connect (sigc::mem_fun (*this, &TreeView::on_treeview_row_activated));
}

/**
 * on_treeview_row_activated
 */
void TreeView::on_treeview_row_activated (const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* /* column */)
{
#if 0
	Gtk::TreeModel::iterator iter = m_refTreeModel->get_iter (path);
	if (iter)
	{
		Gtk::TreeModel::Row row = *iter;
		std::cout << "Row activated: ID=" << row[m_Columns.m_col_id] << ", Name=" << row[m_Columns.m_col_name] << std::endl;
	}
#endif
}
