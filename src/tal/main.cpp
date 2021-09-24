#include <gtk/gtk.h>
#include <ltv/window.h>

static void activate(GtkApplication *app, gpointer user_data)
{
	/*GtkWidget *window = gtk_application_window_new(app);
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

	// gtk_container_add(GTK_CONTAINER(box), button);
	// gtk_container_add(GTK_CONTAINER(box), button2);

	gtk_widget_show_all(window);

	GtkWidget *msgBox = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, "Hello World");
	gtk_window_set_position(GTK_WINDOW(msgBox), GTK_WIN_POS_CENTER_ON_PARENT);
	gtk_widget_show_now(msgBox);*/

	ltv::Window window(app, "Television Application Launcher - In Development");
	ltv::Container buttonRow(GTK_ORIENTATION_HORIZONTAL);
	window.addChild(&buttonRow);
	ltv::Container buttonRow2(GTK_ORIENTATION_HORIZONTAL);
	window.addChild(&buttonRow2);
	ltv::Container buttonRow3(GTK_ORIENTATION_HORIZONTAL);
	window.addChild(&buttonRow3);
	ltv::Container buttonRow4(GTK_ORIENTATION_HORIZONTAL);
	window.addChild(&buttonRow4);

	GtkWidget *button = gtk_button_new_with_label("Hello");
	buttonRow.addChild(button);
	GtkWidget *button2 = gtk_button_new_with_label("World");
	buttonRow.addChild(button2);
	GtkWidget *button3 = gtk_button_new_with_label("Foo");
	buttonRow.addChild(button3);
	GtkWidget *button4 = gtk_button_new_with_label("Bar");
	buttonRow.addChild(button4);
	GtkWidget *button5 = gtk_button_new_with_label("Hello");
	buttonRow2.addChild(button5);
	GtkWidget *button6 = gtk_button_new_with_label("World");
	buttonRow2.addChild(button6);
	GtkWidget *button7 = gtk_button_new_with_label("Foo");
	buttonRow2.addChild(button7);
	GtkWidget *button8 = gtk_button_new_with_label("Bar");
	buttonRow2.addChild(button8);
	GtkWidget *button9 = gtk_button_new_with_label("Hello");
	buttonRow3.addChild(button9);
	GtkWidget *button10 = gtk_button_new_with_label("World");
	buttonRow3.addChild(button10);
	GtkWidget *button11 = gtk_button_new_with_label("Foo");
	buttonRow3.addChild(button11);
	GtkWidget *button12 = gtk_button_new_with_label("Bar");
	buttonRow3.addChild(button12);
	GtkWidget *button13 = gtk_button_new_with_label("Hello");
	buttonRow4.addChild(button13);
	GtkWidget *button14 = gtk_button_new_with_label("World");
	buttonRow4.addChild(button14);
	GtkWidget *button15 = gtk_button_new_with_label("Foo");
	buttonRow4.addChild(button15);
	GtkWidget *button16 = gtk_button_new_with_label("Bar");
	buttonRow4.addChild(button16);

	window.show();
}

int main(int argc, char **argv)
{
	GtkApplication *app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	int status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);

	return status;
}
