/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

// includes
#include "spinner.hh"
#include "../handler/handler.hh"
#include "../dependencies/color.hh"
#include "../dependencies/aliases.hh"

fgui::spinner::spinner() {

    fgui::spinner::m_width = 50;
	fgui::spinner::m_height = 30;
	fgui::spinner::m_title = "spinner";
    fgui::spinner::m_value = 0;
    fgui::spinner::m_min = 0;
    fgui::spinner::m_max = 0;
    fgui::spinner::m_holding_ticks = 00;
    fgui::spinner::m_normal_click = false;
    fgui::spinner::m_holding_click = false;
	fgui::spinner::m_font = fgui::element::m_font;
	fgui::spinner::m_family = fgui::element_family::SPINNER_FAMILY;
	fgui::element::m_flags = fgui::element_flag::DRAWABLE | fgui::element_flag::CLICKABLE;
}

//---------------------------------------------------------
void fgui::spinner::draw() {

    // get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// get the window style
	auto style = handler::get_style();

	// get the control area
	fgui::rect area = { a.x, a.y, m_width, m_height };

    int text_width, text_height;
	fgui::render.get_text_size(fgui::spinner::get_font(), m_title, text_width, text_height);

    // spinner body
    fgui::render.outline(area.left, area.top, area.right, area.bottom, fgui::color(style.spinner.at(0)));

	if (fgui::input.is_mouse_in_region(area))
		fgui::render.outline(area.left + 2, area.top + 2, area.right - 4, area.bottom - 4, fgui::color(style.spinner.at(3)));
	else
		fgui::render.outline(area.left + 1, area.top + 1, area.right - 2, area.bottom - 2, fgui::color(style.spinner.at(2)));

	fgui::render.rect(area.left + 3, area.top + 3, area.right - 6, area.bottom - 6, fgui::color(style.spinner.at(1)));
	fgui::render.rect((area.left + 3) + (area.right - 15), area.top + 3, 15 - 5, area.bottom - 6, fgui::color(style.spinner.at(2)));

	// keybinder label
	fgui::render.text(area.left, (area.top - text_height) - 2, fgui::color(style.text.at(0)), fgui::spinner::get_font(), m_title);

    int value_text_width, value_text_height;
	fgui::render.get_text_size(fgui::spinner::get_font(), std::to_string(m_value), value_text_width, value_text_height);

    // current value
    fgui::render.text(area.left + 10, area.top + (area.bottom / 2) - (value_text_height / 2), fgui::color(style.text.at(0)), fgui::spinner::get_font(), std::to_string(m_value));

    // up and down button area
	fgui::rect up_button_area = { a.x + (m_width - 6), a.y + 5, 10, 10 };
	fgui::rect down_button_area = { a.x + (m_width - 6), a.y + 15, 10, 10 };

    fgui::color up_color = { 0, 0, 0 };
    fgui::color down_color = { 0, 0, 0 };

    if (fgui::input.is_mouse_in_region(up_button_area))
        up_color = { style.spinner.at(3) };
    else
        up_color = { style.text.at(0) };

    if (fgui::input.is_mouse_in_region(down_button_area))
        down_color = { style.spinner.at(3) };
    else
        down_color = { style.text.at(0) };

    // up down
    fgui::render.rect(up_button_area.left - 3, up_button_area.top + (up_button_area.bottom / 2), 5, 1, fgui::color(up_color));
	fgui::render.rect(up_button_area.left - 2, up_button_area.top + (up_button_area.bottom / 2) - 1, 3, 1, fgui::color(up_color));
	fgui::render.rect(up_button_area.left - 1, up_button_area.top + (up_button_area.bottom / 2) - 2, 1, 1, fgui::color(up_color));

    // down button
    fgui::render.rect(down_button_area.left - 3, down_button_area.top + (down_button_area.bottom / 2), 5, 1, fgui::color(down_color));
	fgui::render.rect(down_button_area.left - 2, down_button_area.top + (down_button_area.bottom / 2) + 1, 3, 1, fgui::color(down_color));
	fgui::render.rect(down_button_area.left - 1, down_button_area.top + (down_button_area.bottom / 2) + 2, 1, 1, fgui::color(down_color));
}

//---------------------------------------------------------
void fgui::spinner::set_value(int value) {

    m_value = value;
}

//---------------------------------------------------------
int fgui::spinner::get_value() {

    return m_value;
}

//---------------------------------------------------------
void fgui::spinner::set_boundaries(int min, int max) {

    m_min = min;
    m_max = max;
}

//---------------------------------------------------------
void fgui::spinner::handle_input() {
   
    // get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

    // up and down button area
    fgui::rect up_button_area = { a.x + (m_width - 15), a.y, 15, 10 };
	fgui::rect down_button_area = { a.x + (m_width - 15), a.y + 15, 15, 10 };

    // reset click state
    m_normal_click = true;

    if (fgui::input.is_mouse_in_region(up_button_area)) {
        m_value += 1;

        // tell the spinner that this was a normal click
        m_normal_click = false;
    }

    else if (fgui::input.is_mouse_in_region(down_button_area)) {
        m_value -= 1;
        
        // tell the spinner that this was a normal click
        m_normal_click = false;
    }
}

//---------------------------------------------------------
void fgui::spinner::update() {

    // get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

    // up and down button area
    fgui::rect up_button_area = { a.x + (m_width - 15), a.y, 15, 10 };
	fgui::rect down_button_area = { a.x + (m_width - 15), a.y + 15, 15, 10 };

    if (fgui::input.is_mouse_in_region(up_button_area)) {

        // check if the user is holding MOUSE 1
        if (fgui::input.get_key_state(MOUSE_LEFT) && !m_normal_click) {
            
            m_holding_ticks += 1;

            if (m_holding_ticks > 128) {
                m_value += 1;

                // tell the spinner that this wasn't a normal click
                m_holding_click = true;
            }
        }
                
        else // reset ticks
            m_holding_ticks = 0;
    }

    else if (fgui::input.is_mouse_in_region(down_button_area) && !m_normal_click) {
        
        // check if the user is holding MOUSE 1
        if (fgui::input.get_key_state(MOUSE_LEFT)) {
            
            m_holding_ticks += 1;

            if (m_holding_ticks > 128) {
                m_value -= 1;

                // tell the spinner that this wasn't a normal click
                m_holding_click = true;
            }
        }

        else // reset ticks
            m_holding_ticks = 0;
    }

    else // reset ticks
        m_holding_ticks = 0;

    if (m_value <= m_min) {
        m_value = m_min;
        return;
    }

    else if (m_value > m_max)
        m_value = m_min;

    // reset click state
    m_holding_click = false;

}

//---------------------------------------------------------
void fgui::spinner::tooltip() {

    // get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// get the window style
	auto style = handler::get_style();

	// get the control area
	fgui::rect area = { a.x, a.y, m_width, m_height };

	if (m_tooltip.length() > 0) {

		// tooltip text size
		int tooltip_text_width, tooltip_text_height;
		fgui::render.get_text_size(fgui::element::get_font(), m_tooltip, tooltip_text_width, tooltip_text_height);

		fgui::point cursor = { 0, 0 };
		fgui::input.get_mouse_position(cursor.x, cursor.y);

		if (fgui::input.is_mouse_in_region(area)) {
			fgui::render.rect(cursor.x + 10, cursor.y + 20, tooltip_text_width + 10, 20, fgui::color(style.spinner.at(3)));
			fgui::render.text(cursor.x + 10 + ((tooltip_text_width + 10) / 2) - (tooltip_text_width / 2), cursor.y + 20 + (20 / 2) - (tooltip_text_height / 2), fgui::color(style.text.at(3)), fgui::element::get_font(), m_tooltip);
		}
	}
}

//---------------------------------------------------------
void fgui::spinner::save(const std::string& file_name, nlohmann::json& json_module) {

    json_module[m_identificator] = m_value;
}

//---------------------------------------------------------
void fgui::spinner::load(const std::string& file_name) {

    nlohmann::json json_module;

	// open the file
	std::ifstream file_to_load(file_name, std::ifstream::binary);

	if (!file_to_load.good())
		return;

	// read config file
	json_module = nlohmann::json::parse(file_to_load);

	// change the element value to match the one stored on file
	m_value = json_module[m_identificator];
}