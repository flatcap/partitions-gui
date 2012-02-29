/* Copyright (c) 2012 Richard Russon (FlatCap)
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Library General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place - Suite 330, Boston, MA 02111-1307, USA.
 */


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <string>
#include <typeinfo>
#include <sstream>

#include "container.h"

/**
 * DPContainer
 */
DPContainer::DPContainer (void) :
	offset (0),
	size (0)
{
}

/**
 * ~DPContainer
 */
DPContainer::~DPContainer()
{
	for (std::vector<DPContainer*>::iterator i = children.begin(); i != children.end(); i++) {
		delete *i;
	}
}

/**
 * add_child
 */
void DPContainer::add_child (DPContainer *child)
{
	/* Check:
	 *	available space
	 *	alignment type
	 *	size (restrictions)
	 *	valid type within this parent
	 */
#if 0
	if (children.size() > 0) {
		DPContainer *last = children.back();

		last->next = child;
		child->prev = last;
	}
#endif
	bool inserted = false;

	for (std::vector<DPContainer*>::iterator i = children.begin(); i != children.end(); i++) {
		if ((*i)->offset > child->offset) {
			children.insert (i, child);
			inserted = true;
			break;
		}
	}

	if (!inserted) {
		children.push_back (child);
	}

	//log_debug ("insert: %s (%s)\n", this->name.c_str(), child->name.c_str());
}


