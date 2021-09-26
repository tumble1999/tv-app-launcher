
#include <filesystem>
#include <fstream>
#include <string>
#include <iostream>

#include <tal/gtk.hpp>
#include <tal/xdg.hpp>
namespace fs = std::filesystem;

void exec_app(const char *cmd)
{
	std::cout << "exec_app: " << cmd << "\n";
	g_spawn_command_line_async(cmd, NULL);
}

void app_btn_clicked(GtkWidget *widget, gpointer data)
{
	//exec_app("konsole");
	exec_app((const char *)g_object_get_data(G_OBJECT(widget), "desktop_exec"));
}

GtkWidget *tal_app_button_new(tal::DesktopFile app)
{
	GtkWidget *button = gtk_button_new_with_label(app.Name);
	g_object_set_data(G_OBJECT(button), "desktop_exec", (gpointer)app.Exec);
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(app_btn_clicked), NULL);
	return button;
}

void add_apps(GtkWidget *container, const char *path)
{
	std::cout << "Folder: " << path << "\n";
	std::string pathstr = path;
	pathstr.append("/applications");
	if (!fs::exists(pathstr))
		return;
	for (const auto &entry : fs::directory_iterator(pathstr))
	{
		if (entry.path().extension() == ".desktop")
		{
			tal::DesktopFile desktopFile = tal::xdg_parse_desktop_file(entry.path().c_str());
			std::cout << "Name: " << desktopFile.Name << "\n";
			std::cout << "Exec: " << desktopFile.Exec << "\n";
			GtkWidget *button = tal_app_button_new(desktopFile);
			gtk_flow_box_insert(GTK_FLOW_BOX(container), button, -1);
		}
	}
}

GtkWidget *tal_app_list_new()
{

	// Create Container
	GtkWidget *list = gtk_flow_box_new();
	tal::XDGConfigInfo info = tal::xdg_config_info();

	// Add Apps
	add_apps(list, info.dataHome);
	while (*info.dataDirs)
	{
		add_apps(list, *info.dataDirs);
		info.dataDirs++;
	}
	tal::xdg_clean();

	return list;
}

int main(int argc, char **argv)
{
	GtkWidget *window = tal::create_window("Television Application Launcher", &argc, &argv);

	GtkWidget *scrollBox = gtk_scrolled_window_new(NULL, NULL);
	gtk_container_add(GTK_CONTAINER(window), scrollBox);

	GtkWidget *viewport = gtk_viewport_new(NULL, NULL);
	gtk_container_add(GTK_CONTAINER(scrollBox), viewport);

	GtkWidget *page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(viewport), page);

	GtkWidget *appList = tal_app_list_new();
	gtk_container_add(GTK_CONTAINER(page), appList);

	gtk_widget_show_all(window);

	gtk_main();
	return 0;
}
