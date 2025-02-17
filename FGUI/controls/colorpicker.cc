/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

 // includes
#include "colorpicker.hh"
#include "../handler/handler.hh"
#include "../dependencies/color.hh"
#include "../dependencies/aliases.hh"

fgui::colorpicker::colorpicker() {

	fgui::colorpicker::m_width = 20;
	fgui::colorpicker::m_height = 16;
	fgui::colorpicker::m_opened = false;
	fgui::colorpicker::m_title = "color picker";
	fgui::colorpicker::m_color = { 0, 0, 0 };
	fgui::colorpicker::m_font = fgui::element::m_font;
	fgui::colorpicker::m_original_width = fgui::colorpicker::m_width;
	fgui::colorpicker::m_original_height = fgui::colorpicker::m_height;
	fgui::colorpicker::m_family = fgui::element_family::COLORPICKER_FAMILY;
	fgui::element::m_flags = fgui::element_flag::DRAWABLE | fgui::element_flag::CLICKABLE | fgui::element_flag::FOCUSABLE | fgui::element_flag::SAVABLE;
}

//---------------------------------------------------------
void fgui::colorpicker::draw() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// get the window style
	auto style = handler::get_style();

	// color preview area
	fgui::rect area = { a.x, a.y, m_original_width, m_original_height };

	// color preview body
	fgui::render.outline(area.left, area.top, area.right, area.bottom, fgui::color(style.colorpicker.at(0)));

	if (fgui::input.is_mouse_in_region(area) || m_opened)
		fgui::render.outline(area.left + 2, area.top + 2, area.right - 4, area.bottom - 4, fgui::color(style.colorpicker.at(3)));
	else
		fgui::render.outline(area.left + 1, area.top + 1, area.right - 2, area.bottom - 2, fgui::color(style.colorpicker.at(2)));

	fgui::render.rect(area.left + 3, area.top + 3, area.right - 6, area.bottom - 6, fgui::color(style.colorpicker.at(1)));
	fgui::render.colored_gradient(area.left + 3, area.top + 3, area.right - 6, area.bottom - 6, fgui::color(m_color), fgui::color(style.colorpicker.at(2), m_color.m_alpha), fgui::gradient_type::VERTICAL);

	if (m_opened) {

		// cursor position
		fgui::point cursor = { 0, 0 };
		fgui::input.get_mouse_position(cursor.x, cursor.y);

		// picker area
		fgui::rect picker_area = { a.x + 25, a.y, 150, 150 };

		// color picker pixelation value
		static int pixelation = 3;

		// color picker body 
		fgui::render.outline(picker_area.left, picker_area.top, (picker_area.right + 47), (picker_area.bottom + 5), fgui::color(style.colorpicker.at(0)));
		fgui::render.rect(picker_area.left + 1, picker_area.top + 1, (picker_area.right + 47) - 2, (picker_area.bottom + 5) - 2, fgui::color(style.colorpicker.at(1)));

		for (std::size_t i = 0; i < static_cast<float>(picker_area.bottom); i += pixelation) {
			
			// colors
			fgui::color hue_color = fgui::color::hsb_to_rgb(i / 150.f, 1, 1);
			fgui::color alpha_color = fgui::color(m_color.m_red, m_color.m_green, m_color.m_blue, i / static_cast<float>(picker_area.bottom) * 255);

			// hue
			fgui::render.rect((picker_area.left + picker_area.right) + 10, (picker_area.top + 3) + i, 15, pixelation, fgui::color(hue_color));

			// alpha
			fgui::render.rect((picker_area.left + picker_area.right) + 30, (picker_area.top + 3) + i, 15, pixelation, fgui::color(alpha_color));

			for (std::size_t j = 0; j < static_cast<float>(picker_area.right); j += pixelation) {
			
				// color
				fgui::color hsb_color = fgui::color::hsb_to_rgb(fgui::color::get_hue(m_color), j / static_cast<float>(picker_area.right), i / static_cast<float>(picker_area.bottom), m_color.m_alpha);

				// hsb
				fgui::render.rect((picker_area.left + 3) + j, (picker_area.top + 3) + i, pixelation, pixelation, fgui::color(hsb_color));
			}
		}

		// color hsb body
		fgui::render.outline(picker_area.left + 2, picker_area.top + 2, picker_area.right + 1, picker_area.bottom + 1, fgui::color(style.colorpicker.at(0)));

		// hue bar body
		fgui::render.outline((picker_area.left + picker_area.right) + 9, (picker_area.top + 2), 15 + 1, picker_area.bottom + 1, fgui::color(style.colorpicker.at(0)));
		fgui::render.rect((picker_area.left + picker_area.right) + 5, (picker_area.top + 2) + picker_area.bottom * fgui::color::get_hue(m_color), 3, 3, fgui::color(style.colorlist.at(3)));
		
		// alpha bar body
		fgui::render.outline((picker_area.left + picker_area.right) + 29, (picker_area.top + 2), 15 + 1, picker_area.bottom + 1, fgui::color(style.colorpicker.at(0)));
		fgui::render.rect((picker_area.left + picker_area.right) + 25, (picker_area.top + 2) + picker_area.bottom * (m_color.m_alpha / 255.f), 3, 3, fgui::color(style.colorlist.at(3)));

		// draw color code
		if (fgui::input.is_mouse_in_region(picker_area) && fgui::input.get_key_state(MOUSE_LEFT))
			fgui::render.text(cursor.x - 8, cursor.y + 8, fgui::color(style.text.at(0)), fgui::colorpicker::get_font(), "rgba: " + std::to_string(m_color.m_red) + ", " + std::to_string(m_color.m_green) + ", " +
			std::to_string(m_color.m_blue) + ", " + std::to_string(m_color.m_alpha));
	}
}

//---------------------------------------------------------
void fgui::colorpicker::set_color(int red, int green, int blue, int alpha) {

	m_color = fgui::color(red, green, blue, alpha);
}

//---------------------------------------------------------
void fgui::colorpicker::set_color(fgui::color color) {

	m_color = color;
}

//---------------------------------------------------------
fgui::color fgui::colorpicker::get_color() {

	return m_color;
}

//---------------------------------------------------------
void fgui::colorpicker::set_state(fgui::state state) {

	m_opened = state;
}

//---------------------------------------------------------
fgui::state fgui::colorpicker::get_state() {

	return m_opened;
}

//---------------------------------------------------------
void fgui::colorpicker::handle_input() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// get the control area
	fgui::rect area = { a.x, a.y, m_original_width, m_original_height };

	if (fgui::input.is_mouse_in_region(area))
		m_opened = !m_opened;
}

//---------------------------------------------------------
void fgui::colorpicker::update() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	if (m_opened) {

		// areas
		fgui::rect picker_area = { a.x + 25, a.y, 150, 150 };
		fgui::rect hsb_area = { picker_area.left, picker_area.top + 2, picker_area.right + 1, picker_area.bottom + 1 };
		fgui::rect hue_area = { picker_area.left + picker_area.right + 9, picker_area.top + 2, 15 + 1, picker_area.bottom + 1 };
		fgui::rect alpha_area = { picker_area.left + picker_area.right + 29, picker_area.top + 2, 15 + 1, picker_area.bottom + 1 };

		static bool hue_selected = false;
		static bool hsb_selected = false;
		static bool alpha_selected = false;

		// cursor position
		fgui::point cursor;
		fgui::input.get_mouse_position(cursor.x, cursor.y);

		if (fgui::input.get_key_press(MOUSE_LEFT)) {

			hue_selected = input.is_mouse_in_region(hue_area);
			alpha_selected = input.is_mouse_in_region(alpha_area);
			hsb_selected = input.is_mouse_in_region(hsb_area);
		}

		else if (!fgui::input.get_key_state(MOUSE_LEFT)) {

			hue_selected = false;
			alpha_selected = false;
			hsb_selected = false;
		}

		if (hsb_selected) {

			fgui::precision_point relative_pos = { cursor.x - static_cast<float>(hsb_area.left), cursor.y - static_cast<float>(hsb_area.top) };
			m_color = fgui::color::hsb_to_rgb(fgui::color::get_hue(m_color), relative_pos.x / picker_area.right, relative_pos.y / picker_area.bottom, m_color.m_alpha);
		}

		else if (hue_selected) {

			float hue = (cursor.y - hue_area.top) / 150.f;

			m_color = fgui::color::hsb_to_rgb(std::clamp(hue, 0.f, 1.f), 1, 1);
		}

		else if (alpha_selected) {

			int alpha = (cursor.y - alpha_area.top) / 150.f * 255;

			m_color.m_alpha = std::clamp(alpha, 0, 255);
		}
	}

	if (m_opened) {

		// get the control area
		fgui::rect area = { a.x, a.y, m_width, m_height };

		m_width = 25 /* picker_area.left */ + 197 /* picker_area.right + 47 */;
		m_height = 155 /* picker_area.bottom + 5 */;

		if (!fgui::input.is_mouse_in_region(area)) {

			if (fgui::input.get_key_press(MOUSE_LEFT))
				m_opened = false;
		}
	}

	else if (!m_opened) {

		// restore the width and height
		m_width = m_original_width;
		m_height = m_original_height;
	}
}

//---------------------------------------------------------
void fgui::colorpicker::tooltip() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// get the window style
	auto style = handler::get_style();

	// get the control area
	fgui::rect area = { a.x, a.y, m_width, m_original_height };

	if (m_tooltip.length() > 0) {

		// tooltip text size
		int tooltip_text_width, tooltip_text_height;
		fgui::render.get_text_size(fgui::element::get_font(), m_tooltip, tooltip_text_width, tooltip_text_height);

		fgui::point cursor = { 0, 0 };
		fgui::input.get_mouse_position(cursor.x, cursor.y);

		if (fgui::input.is_mouse_in_region(area)) {
			fgui::render.rect(cursor.x + 10, cursor.y + 20, tooltip_text_width + 10, 20, fgui::color(style.colorpicker.at(3)));
			fgui::render.text(cursor.x + 10 + ((tooltip_text_width + 10) / 2) - (tooltip_text_width / 2), cursor.y + 20 + (20 / 2) - (tooltip_text_height / 2), fgui::color(style.text.at(3)), fgui::element::get_font(), m_tooltip);
		}
	}
}

//---------------------------------------------------------
void fgui::colorpicker::save(const std::string& file_name, nlohmann::json& json_module) {

	json_module[m_identificator]["red"] = m_color.m_red;
	json_module[m_identificator]["green"] = m_color.m_green;
	json_module[m_identificator]["blue"] = m_color.m_blue;
	json_module[m_identificator]["alpha"] = m_color.m_alpha;
}

//---------------------------------------------------------
void fgui::colorpicker::load(const std::string& file_name) {

	nlohmann::json json_module;

	// open the file
	std::ifstream file_to_load(file_name, std::ifstream::binary);

	if (!file_to_load.good())
		return;

	// read config file
	json_module = nlohmann::json::parse(file_to_load);

	// change the element state to match the one stored on file
	m_color.m_red = json_module[m_identificator]["red"];
	m_color.m_green = json_module[m_identificator]["green"];
	m_color.m_blue = json_module[m_identificator]["blue"];
	m_color.m_alpha = json_module[m_identificator]["alpha"];
}