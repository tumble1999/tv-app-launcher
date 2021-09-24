#pragma once
#include <gtk/gtk.h>

namespace ltv
{
	class Container
	{
	public:
		/**
		 * @brief Construct a new Container object
		 *
		 * @param p_spacing Spacing of items in the container
		 * @param p_orientation Direction of the list
		 */
		Container(
			GtkOrientation p_orientation = GTK_ORIENTATION_HORIZONTAL,
			gint p_spacing = 0);
		~Container();

		/**
		 * @brief Get the GTK Box object
		 *
		 * @return GtkBox*
		 */
		GtkBox *getBox();

		/**
		 * @brief Add a widget to the conatiner
		 *
		 * @param p_pWidget Widget to add
		 * @param p_addToEnd Weather or not to add to the end
		 * @param p_expand to expand
		 * @param p_fill to fill
		 * @param p_padding how much to padd
		 */
		void addChild(
			GtkWidget *p_pWidget,
			bool p_addToEnd = false,
			gboolean p_expand = TRUE,
			gboolean p_fill = TRUE,
			guint p_padding = 0);

		/**
		 * @brief Add a container to the conatiner
		 *
		 * @param p_pConatiener Container to add
		 * @param p_addToEnd Weather or not to add to the end
		 * @param p_expand to expand
		 * @param p_fill to fill
		 * @param p_padding how much to padd
		 */
		void addChild(
			Container *p_pConatiener,
			bool p_addToEnd = false,
			gboolean p_expand = TRUE,
			gboolean p_fill = TRUE,
			guint p_padding = 0);

	protected:
		/**
	 * @brief The GTKBox this class represents
	 *
	 */
		GtkWidget *m_pBox;
	};

}