#include <gtk/gtk.h>

#define TAL_FULLSCREEN false

static void activate(GtkApplication *app, gpointer user_data)
{
	GtkWidget *window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Television Application Launcher InDev");
	//gtk_window_set_default_size(GTK_WINDOW(window), 1200, 700);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

	GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
	gtk_container_add(GTK_CONTAINER(window), box);

	GtkWidget *button = gtk_button_new_with_label("Hello");
	gtk_box_pack_start(GTK_BOX(box), button, FALSE, FALSE, 50);

	GtkWidget *button2 = gtk_button_new_with_label("World");
	gtk_box_pack_start(GTK_BOX(box), button2, FALSE, TRUE, 50);

	GtkWidget *button3 = gtk_button_new_with_label("Foo");
	gtk_box_pack_start(GTK_BOX(box), button3, TRUE, FALSE, 50);

	GtkWidget *button4 = gtk_button_new_with_label("Bar");
	gtk_box_pack_start(GTK_BOX(box), button4, TRUE, TRUE, 50);

	gtk_container_add(GTK_CONTAINER(box), button);
	gtk_container_add(GTK_CONTAINER(box), button2);

	gtk_widget_show_all(window);

	GtkWidget *msgBox = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, "Hello World");
	gtk_window_set_position(GTK_WINDOW(msgBox), GTK_WIN_POS_CENTER_ON_PARENT);
	gtk_widget_show_now(msgBox);
}

int main(int argc, char **argv)
{
	GtkApplication *app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	int status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);

	return status;
}
