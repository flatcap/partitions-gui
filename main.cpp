#include <gtkmm/main.h>

#include "dparted.h"

/**
 * main
 */
int main (int argc, char *argv[])
{
	Gtk::Main kit (argc, argv);

	DParted d;

	Gtk::Main::run (d);

	return 0;
}

