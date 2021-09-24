#include <ltv/container.h>

ltv::Container::Container(GtkOrientation p_orientation, gint p_spacing)
	: m_pBox(gtk_box_new(p_orientation, p_spacing))
{
}

ltv::Container::~Container()
{
}

GtkBox *ltv::Container::getBox()
{
	return GTK_BOX(m_pBox);
}
void ltv::Container::addChild(
	GtkWidget *p_pWidget,
	bool p_addToEnd,
	gboolean p_expand,
	gboolean p_fill,
	guint p_padding)
{
	if (p_addToEnd)
	{
		gtk_box_pack_end(getBox(),
						 p_pWidget,
						 p_expand,
						 p_fill,
						 p_padding);
	}
	else
	{
		gtk_box_pack_start(getBox(),
						   p_pWidget,
						   p_expand,
						   p_fill,
						   p_padding);
	}
}

void ltv::Container::addChild(
	Container *p_pConatiener,
	bool p_addToEnd,
	gboolean p_expand,
	gboolean p_fill,
	guint p_padding)
{
	addChild(p_pConatiener->m_pBox, p_addToEnd, p_expand, p_fill, p_padding);
}