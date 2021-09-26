#include <tal/gtk.hpp>

#include <iostream>

/**
 * @brief This function exists to create a GTK window so the code is not filling up main.cpp
 *
 * @param title
 * @param argc
 * @param argv
 * @return GtkWidget*
 */
GtkWidget *tal::create_window(const gchar *title, int *argc, char ***argv)
{
	gtk_init(argc, argv);

	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(window), title);
	// Adds the functionality where the program exits when the window is closed
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	return window;
}
