
#include <filesystem>
#include <fstream>
#include <string>
#include <iostream>

#include <tal/gtk.hpp>
#include <tal/xdg.hpp>
namespace fs = std::filesystem;

GtkWidget *tal_scollbox_new(GtkWidget *contents)
{
	GtkWidget *scrollBox = gtk_scrolled_window_new(NULL, NULL);

	GtkWidget *viewport = gtk_viewport_new(NULL, NULL);
	gtk_container_add(GTK_CONTAINER(scrollBox), contents);

	return scrollBox;
}

void exec_app(const char *cmd)
{
	std::cout << "exec_app: " << cmd << "\n";
	g_spawn_command_line_async(cmd, NULL);
}

void app_btn_clicked(GtkWidget *widget, gpointer data)
{
	//exec_app("konsole");
	exec_app((const char *)g_object_get_data(G_OBJECT(widget), "desktop_exec"));
	exit(0);
}

GtkWidget *tal_app_button_new(tal::DesktopFile app)
{
	if (app.NoDisplay || app.Hidden)
		return NULL;
	GtkWidget *button = gtk_button_new();

	// Content
	GtkWidget *content = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_container_add(GTK_CONTAINER(button), content);

	// Icon
	GtkWidget *icon = gtk_image_new();
	if (g_file_test(app.Icon, G_FILE_TEST_EXISTS))
	{
		gtk_image_set_from_file(GTK_IMAGE(icon), app.Icon);
	}
	else
	{
		gtk_image_set_from_icon_name(GTK_IMAGE(icon), app.Icon, GTK_ICON_SIZE_DIALOG);
	}
	gtk_image_set_pixel_size(GTK_IMAGE(icon), 50);
	gtk_box_pack_start(GTK_BOX(content), icon, FALSE, TRUE, 0);

	// Label
	GtkWidget *label = gtk_label_new(app.Name);
	gtk_box_pack_start(GTK_BOX(content), label, TRUE, TRUE, 0);

	gtk_widget_set_size_request(GTK_WIDGET(button), 320, 180);
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
			std::cout << "File: " << entry.path().c_str() << "\n";
			tal::DesktopFile desktopFile = tal::xdg_parse_desktop_file(entry.path().c_str());

			GtkWidget *button = tal_app_button_new(desktopFile);
			if (button)
			{
				if (GTK_IS_FLOW_BOX(container))
					gtk_flow_box_insert(GTK_FLOW_BOX(container), button, -1);
				if (GTK_IS_BOX(container))
					gtk_box_pack_start(GTK_BOX(container), button, FALSE, TRUE, 20);
			}
		}
	}
}

GtkWidget *tal_app_row_new()
{

	// Create Container
	GtkWidget *list = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
	tal::XDGConfigInfo info = tal::xdg_config_info();

	// Add Apps
	add_apps(list, info.dataHome);
	while (*info.dataDirs)
	{
		add_apps(list, *info.dataDirs);
		info.dataDirs++;
	}
	tal::xdg_clean();

	GtkWidget *scrollbox = tal_scollbox_new(list);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollbox), GTK_POLICY_ALWAYS, GTK_POLICY_NEVER);
	return scrollbox;
}

GtkWidget *tal_app_list_new()
{

	// Create Container
	GtkWidget *list = gtk_flow_box_new();
	gtk_flow_box_set_row_spacing(GTK_FLOW_BOX(list), 20);
	gtk_flow_box_set_column_spacing(GTK_FLOW_BOX(list), 20);
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

GtkWidget *tal_home_nav()
{
	GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);

	GtkWidget *search = gtk_search_bar_new();
	gtk_box_pack_start(GTK_BOX(box), search, TRUE, TRUE, 20);

	GtkWidget *time = gtk_label_new("Time");
	gtk_box_pack_start(GTK_BOX(box), time, FALSE, TRUE, 20);

	return box;
}

GtkWidget *tal_home_apps()
{
	GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);

	GtkWidget *appsLabel = gtk_label_new("Apps");
	gtk_box_pack_start(GTK_BOX(box), appsLabel, FALSE, TRUE, 20);

	GtkWidget *appList = tal_app_row_new();
	gtk_box_pack_start(GTK_BOX(box), appList, FALSE, FALSE, 20);

	return box;
}

GtkWidget *tal_page_main_new()
{
	GtkWidget *page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	gtk_widget_set_margin_top(GTK_WIDGET(page), 20);
	gtk_widget_set_margin_bottom(GTK_WIDGET(page), 20);
	gtk_widget_set_margin_start(GTK_WIDGET(page), 20);
	gtk_widget_set_margin_end(GTK_WIDGET(page), 20);

	GtkWidget *home_nav = tal_home_nav();
	gtk_box_pack_start(GTK_BOX(page), home_nav, FALSE, TRUE, 20);
	GtkWidget *home_content = tal_home_apps();
	gtk_box_pack_start(GTK_BOX(page), home_content, FALSE, TRUE, 20);

	return tal_scollbox_new(page);
}

int main(int argc, char **argv)
{
	GtkWidget *window = tal::create_window("Television Application Launcher", &argc, &argv);

	GtkWidget *page = tal_page_main_new();
	gtk_container_add(GTK_CONTAINER(window), page);

	gtk_widget_show_all(window);

	gtk_main();
	return 0;
}
