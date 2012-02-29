CC	= g++
RM	= rm -fr

SRC	= main.cpp dparted.cpp drawingarea.cpp treeview.cpp container.cpp

HDR	= dparted.h drawingarea.h treeview.h container.h

#PACKAGES = atk atkmm-1.6 cairo cairomm-1.0 freetype2 gdkmm-2.4 gdk-pixbuf-2.0 \
#	   giomm-2.4 glib-2.0 glibmm-2.4 gtkmm-2.4 gtk+-unix-print-2.0 \
#	   libparted libpng pangomm-1.4 pango pixman-1 sigc++-2.0 uuid

PACKAGES = gtkmm-3.0

OBJ	= $(SRC:%.cpp=%.o)

OUT	= dparted

CFLAGS	= -g -Wall
CFLAGS	+= -I..
CFLAGS	+= -DGTKMM_DISABLE_DEPRECATED

CFLAGS	+= $(shell pkg-config --cflags $(PACKAGES))
LDFLAGS += $(shell pkg-config --libs   $(PACKAGES))

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT):	$(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

all:	$(OBJ) $(OUT)

clean:
	$(RM) $(OBJ) $(OUT)

distclean: clean

