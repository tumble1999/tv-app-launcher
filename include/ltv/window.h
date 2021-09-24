#pragma once
#include "container.h"

namespace ltv
{
	class Window : public Container
	{
	public:
		Window(
			GtkApplication *p_pApp,
			const gchar *p_pTitle,
			GtkOrientation p_orientation = GTK_ORIENTATION_VERTICAL,
			gint p_spacing = 0);

		~Window();

		GtkWindow *getWindow();
		void show();

	private:
		GtkWidget *m_pWindow;
	};
}