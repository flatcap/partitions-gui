#ifndef _DPARTED_H_
#define _DPARTED_H_

#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm/menubar.h>
#include <gtkmm/toolbar.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/statusbar.h>
#include <gtkmm/button.h>

#include <gtkmm.h>

#include "drawingarea.h"
#include "treeview.h"

class DParted : public Gtk::Window
{
public:
	DParted();
	virtual ~DParted();

protected:
	Gtk::Button		button1;
	Gtk::Button		button2;
	Gtk::Button		button3;
	Gtk::Button		button4;
	// GUI
	Gtk::Grid		grid;
	Gtk::MenuBar		menubar;
	//Gtk::Toolbar		toolbar;
	//Gtk::ScrolledWindow	scrolledwindow;
	DrawingArea		drawingarea;
	TreeView		treeview;
	//Gtk::Statusbar		statusbar;

	Glib::RefPtr<Gtk::UIManager> m_refUIManager;
	Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup;
	Glib::RefPtr<Gtk::RadioAction> m_refChoiceOne, m_refChoiceTwo;

	//Signal handlers:
	void on_menu_file_new_generic();
	void on_menu_file_quit();
	void on_menu_others();

	void on_menu_choices_one();
	void on_menu_choices_two();

	//Signal handlers:
	void on_button_quit();
	void on_treeview_row_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);

	//Tree model columns:
	class ModelColumns : public Gtk::TreeModel::ColumnRecord
	{
	public:

		ModelColumns()
		{ add(m_col_id); add(m_col_name); }

		Gtk::TreeModelColumn<int> m_col_id;
		Gtk::TreeModelColumn<Glib::ustring> m_col_name;
	};

	ModelColumns m_Columns;
	Glib::RefPtr<Gtk::TreeStore> m_refTreeModel;

private:
	void init_menubar (void);
#if 0
	void init_toolbar (void);
	void init_scrolledwindow (void);
#endif
	void init_treeview (void);
};

#endif // _DPARTED_H_

