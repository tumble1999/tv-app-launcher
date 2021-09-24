#include <ltv/window.h>

ltv::Window::Window(
	GtkApplication *p_pApp,
	const gchar *p_pTitle,
	GtkOrientation p_orientation,
	gint p_spacing)
	: Container(p_orientation, p_spacing),
	  m_pWindow(gtk_application_window_new(p_pApp))
{
	gtk_window_set_title(getWindow(), p_pTitle);
	gtk_window_set_position(getWindow(), GTK_WIN_POS_CENTER);
	gtk_container_add(GTK_CONTAINER(m_pWindow), m_pBox);
}

ltv::Window::~Window()
{
}

GtkWindow *ltv::Window::getWindow()
{
	return GTK_WINDOW(m_pWindow);
}

void ltv::Window::show()
{
	gtk_widget_show_all(m_pWindow);
}