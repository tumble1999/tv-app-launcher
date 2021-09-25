#include <gtk/gtk.h>
#include <vector>
#include <iostream>

static void btnClicked(GtkWidget *widget, gpointer data)
{
	char *app = (char *)"konsole";
	char **cmd = &app;
	//g_spawn_async(NULL, cmd, NULL, G_SPAWN_SEARCH_PATH, NULL, NULL, NULL, NULL);
	g_spawn_command_line_async(app, NULL);
}

static void activate(GtkApplication *app, gpointer user_data)
{
	/*
	Tpodo
	Window>Serolled window>>viewport>box>flowbox> APP buttons
	*/

	GtkWidget *window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Television Application Launcher InDev");
	//gtk_window_set_default_size(GTK_WINDOW(window), 1200, 700);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

	GtkWidget *button = gtk_button_new_with_label("Hello World");
	gtk_container_add(GTK_CONTAINER(window), button);

	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(btnClicked), NULL);

	gtk_widget_show_all(window);
}

int main(int argc, char **argv)
{
	GtkApplication *app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	int status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);

	return status;
}
