#include <gtk/gtk.h>
#include <tal/structs.hpp>
namespace tal
{

	GtkWidget *create_window(const gchar *title, int *argc, char ***argv);

	GtkWidget *create_app_btn(DesktopFile app);
}