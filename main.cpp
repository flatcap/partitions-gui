#include <gtkmm/main.h>

#include "dparted.h"
#include "container.h"

/**
 * create_data
 */
DPContainer * create_data (void)
{
	DPContainer *c = new DPContainer;

	DPContainer *p1 = new DPContainer;
	DPContainer *p2 = new DPContainer;
	DPContainer *p3 = new DPContainer;
	DPContainer *p4 = new DPContainer;
	DPContainer *p5 = new DPContainer;
	DPContainer *p6 = new DPContainer;
	DPContainer *p7 = new DPContainer;
	DPContainer *p8 = new DPContainer;
	DPContainer *p9 = new DPContainer;

	p1->name = "sdc1"; p1->type = "swap";     p1->size = 8;   p1->offset = 0;
	p2->name = "none"; p2->type = "free";     p2->size = 60;  p2->offset = 8;
	p3->name = "sdc2"; p3->type = "extended"; p3->size = 160; p3->offset = 68;
	p4->name = "sdc5"; p4->type = "lvm";      p4->size = 50;  p4->offset = 0;
	p5->name = "sdc6"; p5->type = "lvm";      p5->size = 40;  p5->offset = 50;
	p6->name = "sdc7"; p6->type = "lvm";      p6->size = 30;  p6->offset = 90;
	p7->name = "none"; p7->type = "free";     p7->size = 40;  p7->offset = 120;
	p8->name = "none"; p8->type = "free";     p8->size = 30;  p8->offset = 228;
	p9->name = "sdc3"; p9->type = "ext4";     p9->size = 40;  p9->offset = 258;

	c->add_child (p1);
	c->add_child (p2);
	c->add_child (p3);
		p3->add_child (p4);
		p3->add_child (p5);
		p3->add_child (p6);
		p3->add_child (p7);
	c->add_child (p8);
	c->add_child (p9);

	return c;
}

/**
 * main
 */
int main (int argc, char *argv[])
{
	DPContainer *c = NULL;

	Gtk::Main kit (argc, argv);

	c = create_data();
	DParted d;

	d.set_data (c);

	Gtk::Main::run (d);

	return 0;
}

