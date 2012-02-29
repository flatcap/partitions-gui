#include <iostream>

#include "dparted.h"

/**
 * Dparted
 */
DParted::DParted() :
	button1 ("hello"),
	button2 ("bye"),
	button3 ("wibble"),
	button4 ("hatstand")
{
	set_title ("DParted");
	set_default_size (1800, 900);

	add (grid);

	init_menubar();
	//init_toolbar();
	//init_scrolledwindow();
	init_treeview();

	grid.set_orientation (Gtk::ORIENTATION_VERTICAL);
	//grid.set_row_homogeneous (false);
	grid.add (button1);
	//grid.add (menubar);

	//Get the menubar and toolbar widgets, and add them to a container widget:
	Gtk::Widget* pMenubar = m_refUIManager->get_widget("/MenuBar");
	if(pMenubar)
		grid.add (*pMenubar);

	Gtk::Widget* pToolbar = m_refUIManager->get_widget("/ToolBar") ;
	if(pToolbar)
		grid.add (*pToolbar);

	grid.add (button2);
	//grid.add (toolbar);
	//grid.add (scrolledwindow);

	grid.add (drawingarea);
	grid.add (button3);

	grid.add (treeview);
	grid.add (button4);

	show_all();
}

/**
 * ~DParted
 */
DParted::~DParted()
{
}


/**
 * init_menubar
 */
void DParted::init_menubar (void)
{
	//Create actions for menus and toolbars:
	m_refActionGroup = Gtk::ActionGroup::create();

	//File|New sub menu:
	m_refActionGroup->add(Gtk::Action::create("FileNewStandard", Gtk::Stock::NEW, "_New", "Create a new file"), sigc::mem_fun(*this, &DParted::on_menu_file_new_generic));
	m_refActionGroup->add(Gtk::Action::create("FileNewFoo", Gtk::Stock::NEW, "New Foo", "Create a new foo"), sigc::mem_fun(*this, &DParted::on_menu_file_new_generic));
	m_refActionGroup->add(Gtk::Action::create("FileNewGoo", Gtk::Stock::NEW, "_New Goo", "Create a new goo"), sigc::mem_fun(*this, &DParted::on_menu_file_new_generic));

	//File menu:
	m_refActionGroup->add(Gtk::Action::create("FileMenu", "File"));
	//Sub-menu.
	m_refActionGroup->add(Gtk::Action::create("FileNew", Gtk::Stock::NEW));
	m_refActionGroup->add(Gtk::Action::create("FileQuit", Gtk::Stock::QUIT), sigc::mem_fun(*this, &DParted::on_menu_file_quit));

	//Edit menu:
	m_refActionGroup->add(Gtk::Action::create("EditMenu", "Edit"));
	m_refActionGroup->add(Gtk::Action::create("EditCopy", Gtk::Stock::COPY), sigc::mem_fun(*this, &DParted::on_menu_others));
	m_refActionGroup->add(Gtk::Action::create("EditPaste", Gtk::Stock::PASTE), sigc::mem_fun(*this, &DParted::on_menu_others));
	m_refActionGroup->add(Gtk::Action::create("EditSomething", "Something"), Gtk::AccelKey("<control><alt>S"), sigc::mem_fun(*this, &DParted::on_menu_others));


	//Choices menu, to demonstrate Radio items
	m_refActionGroup->add( Gtk::Action::create("ChoicesMenu", "Choices") );
	Gtk::RadioAction::Group group_userlevel;
	m_refChoiceOne = Gtk::RadioAction::create(group_userlevel, "ChoiceOne", "One");
	m_refActionGroup->add(m_refChoiceOne, sigc::mem_fun(*this, &DParted::on_menu_choices_one) );
	m_refChoiceTwo = Gtk::RadioAction::create(group_userlevel, "ChoiceTwo", "Two");
	m_refActionGroup->add(m_refChoiceTwo, sigc::mem_fun(*this, &DParted::on_menu_choices_two) );

	//Help menu:
	m_refActionGroup->add( Gtk::Action::create("HelpMenu", "Help") );
	m_refActionGroup->add( Gtk::Action::create("HelpAbout", Gtk::Stock::HELP), sigc::mem_fun(*this, &DParted::on_menu_others) );

	m_refUIManager = Gtk::UIManager::create();
	m_refUIManager->insert_action_group(m_refActionGroup);

	add_accel_group(m_refUIManager->get_accel_group());

	//Layout the actions in a menubar and toolbar:
	Glib::ustring ui_info =
		"<ui>"
		"	<menubar name='MenuBar'>"
		"		<menu action='FileMenu'>"
		"			<menu action='FileNew'>"
		"				<menuitem action='FileNewStandard'/>"
		"				<menuitem action='FileNewFoo'/>"
		"				<menuitem action='FileNewGoo'/>"
		"			</menu>"
		"			<separator/>"
		"			<menuitem action='FileQuit'/>"
		"		</menu>"
		"		<menu action='EditMenu'>"
		"			<menuitem action='EditCopy'/>"
		"			<menuitem action='EditPaste'/>"
		"			<menuitem action='EditSomething'/>"
		"		</menu>"
		"		<menu action='ChoicesMenu'>"
		"			<menuitem action='ChoiceOne'/>"
		"			<menuitem action='ChoiceTwo'/>"
		"		</menu>"
		"		<menu action='HelpMenu'>"
		"			<menuitem action='HelpAbout'/>"
		"		</menu>"
		"	</menubar>"
		"	<toolbar name='ToolBar'>"
		"		<toolitem action='FileNewStandard'/>"
		"		<toolitem action='FileQuit'/>"
		"	</toolbar>"
		"</ui>";

	try
	{
		m_refUIManager->add_ui_from_string(ui_info);
	}
	catch(const Glib::Error& ex)
	{
		std::cerr << "building menus failed: " << ex.what();
	}

#if 0
	//Get the menubar and toolbar widgets, and add them to a container widget:
	Gtk::Widget* pMenubar = m_refUIManager->get_widget("/MenuBar");
	if(pMenubar)
		m_Box.pack_start(*pMenubar, Gtk::PACK_SHRINK);

	Gtk::Widget* pToolbar = m_refUIManager->get_widget("/ToolBar") ;
	if(pToolbar)
		m_Box.pack_start(*pToolbar, Gtk::PACK_SHRINK);
#endif
}

#if 0
/**
 * init_toolbar
 */
void DParted::init_toolbar (void)
{
}

/**
 * init_scrolledwindow
 */
void DParted::init_scrolledwindow (void)
{
}

#endif
/**
 * init_treeview
 */
void DParted::init_treeview (void)
{
	//Create the Tree model:
	m_refTreeModel = Gtk::TreeStore::create(m_Columns);
	treeview.set_model(m_refTreeModel);

	//All the items to be reordered with drag-and-drop:
	treeview.set_reorderable();

	//Fill the TreeView's model
	Gtk::TreeModel::Row row = *(m_refTreeModel->append());
	row[m_Columns.m_col_id] = 1;
	row[m_Columns.m_col_name] = "Billy Bob";

	Gtk::TreeModel::Row childrow = *(m_refTreeModel->append(row.children()));
	childrow[m_Columns.m_col_id] = 11;
	childrow[m_Columns.m_col_name] = "Billy Bob Junior";

	childrow = *(m_refTreeModel->append(row.children()));
	childrow[m_Columns.m_col_id] = 12;
	childrow[m_Columns.m_col_name] = "Sue Bob";

	row = *(m_refTreeModel->append());
	row[m_Columns.m_col_id] = 2;
	row[m_Columns.m_col_name] = "Joey Jojo";


	row = *(m_refTreeModel->append());
	row[m_Columns.m_col_id] = 3;
	row[m_Columns.m_col_name] = "Rob McRoberts";

	childrow = *(m_refTreeModel->append(row.children()));
	childrow[m_Columns.m_col_id] = 31;
	childrow[m_Columns.m_col_name] = "Xavier McRoberts";

	//Add the TreeView's view columns:
	treeview.append_column("ID", m_Columns.m_col_id);
	treeview.append_column("Name", m_Columns.m_col_name);

	//Connect signal:
	treeview.signal_row_activated().connect(sigc::mem_fun(*this, &DParted::on_treeview_row_activated) );
}


/**
 * on_menu_file_quit
 */
void DParted::on_menu_file_quit()
{
	hide(); //Closes the main window to stop the Gtk::Main::run().
}

/**
 * on_menu_file_new_generic
 */
void DParted::on_menu_file_new_generic()
{
	 std::cout << "A File|New menu item was selected." << std::endl;
}

/**
 * on_menu_others
 */
void DParted::on_menu_others()
{
	std::cout << "A menu item was selected." << std::endl;
}

/**
 * on_menu_choices_one
 */
void DParted::on_menu_choices_one()
{
	Glib::ustring message;
	if(m_refChoiceOne->get_active())
		message = "Choice 1 was selected.";
	else
		message = "Choice 1 was deselected";

	std::cout << message << std::endl;
}

/**
 * on_menu_choices_two
 */
void DParted::on_menu_choices_two()
{
	Glib::ustring message;
	if(m_refChoiceTwo->get_active())
		message = "Choice 2 was selected.";
	else
		message = "Choice 2 was deselected";

	std::cout << message << std::endl;
}

/**
 * on_treeview_row_activated
 */
void DParted::on_treeview_row_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* /* column */)
{
	Gtk::TreeModel::iterator iter = m_refTreeModel->get_iter(path);
	if(iter)
	{
		Gtk::TreeModel::Row row = *iter;
		std::cout << "Row activated: ID=" << row[m_Columns.m_col_id] << ", Name=" << row[m_Columns.m_col_name] << std::endl;
	}
}
