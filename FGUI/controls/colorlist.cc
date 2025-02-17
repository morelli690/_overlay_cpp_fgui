/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

 // includes
#include "colorlist.hh"
#include "../handler/handler.hh"
#include "../dependencies/color.hh"
#include "../dependencies/aliases.hh"

fgui::colorlist::colorlist() {

	fgui::colorlist::m_width = 350;
	fgui::colorlist::m_height = 200;
	fgui::colorlist::m_selected = 0;
	fgui::colorlist::m_slider_top = 0;
	fgui::colorlist::m_title = "colorlist";
	fgui::colorlist::m_item_height = 20;
	fgui::colorlist::m_font = fgui::element::m_font;
	fgui::colorlist::m_family = fgui::element_family::COLORLIST_FAMILY;
	fgui::element::m_flags = fgui::element_flag::DRAWABLE | fgui::element_flag::CLICKABLE | fgui::element_flag::SAVABLE;
}

//---------------------------------------------------------
void fgui::colorlist::draw() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// get the window style
	auto style = handler::get_style();

	// get the control area
	fgui::rect area = { a.x, a.y, (m_width - 250) - 15, m_height };
				
	// get the number of displayed items
	unsigned int items_displayed = 0;

	// calculate the amount of items to be displayed
	int calculated_items = (m_height - 20) / m_item_height;

	// color list body
	fgui::render.outline(area.left, area.top, area.right, area.bottom, fgui::color(style.colorlist.at(0)));

	if (fgui::input.is_mouse_in_region(area))
		fgui::render.outline(area.left + 2, area.top + 2, (area.right - 15) - 4, area.bottom - 4, fgui::color(style.colorlist.at(3)));
	else
		fgui::render.outline(area.left + 2, area.top + 2, area.right - 4, area.bottom - 4, fgui::color(style.colorlist.at(1)));
	
	fgui::render.rect(area.left + 3, area.top + 3, (area.right - 15) - 6, area.bottom - 6, fgui::color(style.colorlist.at(2)));
	
	if (m_color_list.empty())
		return;

	for (std::size_t i = m_slider_top; (i < m_color_list.size() && items_displayed < calculated_items); i++) {

		int item_text_width, item_text_height;
		fgui::render.get_text_size(fgui::colorlist::get_font(), m_color_list[i].m_identificator, item_text_width, item_text_height);

		// get the item area
		fgui::rect item_area = { a.x, a.y + (m_item_height * static_cast<int>(items_displayed)), (m_width - 250) - 15, m_item_height };

		// color identificator
		if (m_color_list[i].m_identificator.length() > 30)
			fgui::render.text(item_area.left + 5, item_area.top + (item_area.bottom / 2) - (item_text_height / 2), fgui::color(style.text.at(0)), fgui::colorlist::get_font(), m_color_list[i].m_identificator.replace(m_color_list[i].m_identificator.begin() + 30, m_color_list[i].m_identificator.end(), "..."));
		else
			fgui::render.text(item_area.left + 5, item_area.top + (item_area.bottom / 2) - (item_text_height / 2), fgui::color(style.text.at(0)), fgui::colorlist::get_font(), m_color_list[i].m_identificator);

		// color button body
		fgui::render.outline((item_area.left + 150), item_area.top + 4, 20, 16, fgui::color(style.colorlist.at(0)));
		
		if (fgui::input.is_mouse_in_region(item_area) || m_selected == i)
			fgui::render.outline((item_area.left + 150) + 2, (item_area.top + 2) + 4, 20 - 4, 16 - 4, fgui::color(style.colorlist.at(3)));
		else
			fgui::render.outline((item_area.left + 150) + 1, (item_area.top + 1) + 4, 20 - 2, 16 - 2, fgui::color(style.colorlist.at(2)));

		fgui::render.rect((item_area.left + 150) + 3, (item_area.top + 3) + 4, 20 - 6, 16 - 6, fgui::color(style.colorlist.at(1)));
		fgui::render.colored_gradient((item_area.left + 150) + 3, (item_area.top + 3) + 4, 20 - 6, 16 - 6, fgui::color(m_color_list[i].m_first_color), fgui::color(style.colorlist.at(2), m_color_list[i].m_first_color.m_alpha), fgui::gradient_type::VERTICAL);

		// separator line
		fgui::render.line(item_area.left, item_area.top + item_area.bottom + 2, item_area.left + (item_area.right - 15) - 5, item_area.top + item_area.bottom + 2, fgui::color(style.colorlist.at(0)));

		if (m_color_list[i].m_second_color_added) {
			
			fgui::rect second_item_area = { a.x + 150, a.y + (m_item_height * static_cast<int>(items_displayed)), (m_width - 15) - 250, m_item_height };

			// second color button body
			fgui::render.outline((second_item_area.left + 25), second_item_area.top + 4, 20, 16, fgui::color(style.colorlist.at(0)));
		
			if (fgui::input.is_mouse_in_region(second_item_area) || m_selected == i)
				fgui::render.outline((second_item_area.left + 25) + 2, (second_item_area.top + 2) + 4, 20 - 4, 16 - 4, fgui::color(style.colorlist.at(3)));
			else
				fgui::render.outline((second_item_area.left + 25) + 1, (second_item_area.top + 1) + 4, 20 - 2, 16 - 2, fgui::color(style.colorlist.at(2)));

			fgui::render.rect((second_item_area.left + 25) + 3, (second_item_area.top + 3) + 4, 20 - 6, 16 - 6, fgui::color(style.colorlist.at(1)));
			fgui::render.colored_gradient((second_item_area.left + 25) + 3, (second_item_area.top + 3) + 4, 20 - 6, 16 - 6, fgui::color(m_color_list[i].m_second_color), fgui::color(style.colorlist.at(2), m_color_list[i].m_second_color.m_alpha), fgui::gradient_type::VERTICAL);
		}

		items_displayed++;
	}

	// picker area
	fgui::rect picker_area = {a.x + (m_width - 240), a.y, 150, 150};

	// color picker pixelation value
	int pixelation = 3;

	// alpha background
	// NOTE: (If you are crashing here, you probably don't have the "alpha" function, just remove this line or replace with a rectangle)
	fgui::render.alpha(picker_area.left, picker_area.top, picker_area.right, picker_area.bottom);

	for (std::size_t i = 0; i < static_cast<float>(picker_area.bottom); i += pixelation) {

		// color
		fgui::color hue_color = fgui::color::hsb_to_rgb(i / 150.f, 1, 1);
		
		// hue
		fgui::render.rect(picker_area.left + picker_area.right + 10, picker_area.top + i, 15, pixelation, fgui::color(hue_color));

		for (std::size_t j = 0; j < (static_cast<float>(picker_area.right)); j += pixelation) {

			// color
			fgui::color hsb_color = fgui::color::hsb_to_rgb(fgui::color::get_hue(m_color_list[m_selected].m_first_color), j / static_cast<float>(picker_area.right), i / static_cast<float>(picker_area.bottom), m_color_list[m_selected].m_first_color.m_alpha);
			
			// hsb
			fgui::render.rect(picker_area.left + j, picker_area.top + i, pixelation, pixelation, fgui::color(hsb_color));
		}
	}

	// color hsb body
	fgui::render.outline(picker_area.left - 1, picker_area.top - 1, picker_area.right + 2, picker_area.bottom + 2, fgui::color(style.colorlist.at(0)));

	// hue bar body
	fgui::render.outline(picker_area.left + (picker_area.right + 10) - 1, picker_area.top - 1, 15 + 2, picker_area.bottom + 2, fgui::color(style.colorlist.at(0)));
	fgui::render.rect(picker_area.left + picker_area.right + 5, picker_area.top + picker_area.bottom * fgui::color::get_hue(m_color_list[m_selected].m_first_color), 3, 3, fgui::color(style.colorlist.at(3)));

	// alpha slider
	m_color_list[m_selected].m_alpha_slider->set_position(picker_area.left, picker_area.top + (picker_area.bottom + 20));
	m_color_list[m_selected].m_alpha_slider->draw();
	m_color_list[m_selected].m_alpha_slider->tooltip();

	// plus button
	m_color_list[m_selected].m_plus_button->set_position(picker_area.left, picker_area.top + (picker_area.bottom) + 40);
	m_color_list[m_selected].m_plus_button->draw();
	m_color_list[m_selected].m_plus_button->tooltip();

	// minus button
	m_color_list[m_selected].m_minus_button->set_position(picker_area.left + 20, picker_area.top + (picker_area.bottom) + 40);
	m_color_list[m_selected].m_minus_button->draw();
	m_color_list[m_selected].m_minus_button->tooltip();

	// gradient checkbox
	m_color_list[m_selected].m_gradient_checkbox->set_position(picker_area.left + 50, picker_area.top + (picker_area.bottom) + 40);
	m_color_list[m_selected].m_gradient_checkbox->draw();
	m_color_list[m_selected].m_gradient_checkbox->tooltip();

	// calculate the slider position
	float calculated_position = static_cast<float>(m_slider_top) / static_cast<float>(m_color_list.size());

	if (calculated_position >= 1.f)
		calculated_position = 1.f;

	calculated_position *= m_height;

	// calculate the slider size
	float calculated_size = static_cast<float>(calculated_items) / static_cast<float>(m_color_list.size());

	if (calculated_size > 1.f)
		calculated_size = 1.f;

	calculated_size *= m_height;

	// scrollbar area
	fgui::rect scrollbar_area = { (area.left + 2) + (area.right - 15), area.top + 2, 15 - 4, area.bottom - 4 };

	// scrollbar body
	fgui::render.outline(scrollbar_area.left + 1, scrollbar_area.top + 1, scrollbar_area.right - 2, scrollbar_area.bottom - 2, fgui::color(style.colorlist.at(0)));
	fgui::render.rect(scrollbar_area.left, scrollbar_area.top, scrollbar_area.right, scrollbar_area.bottom, fgui::color(style.colorlist.at(1)));
	fgui::render.outline(scrollbar_area.left + 1, (scrollbar_area.top + calculated_position) + 1, scrollbar_area.right - 2, (calculated_size - 2) - 4, fgui::color(style.colorlist.at(3)));

	if (m_color_list.size() > 50)
		fgui::render.colored_gradient(scrollbar_area.left + 2, (scrollbar_area.top + calculated_position) + 2, scrollbar_area.right - 4, (calculated_size - 4) - 4, fgui::color(style.colorlist.at(1)), fgui::color(style.colorlist.at(2)), fgui::gradient_type::VERTICAL);
	else
		fgui::render.colored_gradient(scrollbar_area.left + 2, (scrollbar_area.top + calculated_position) + 2, scrollbar_area.right - 4, (calculated_size - 4) - 4, fgui::color(style.colorlist.at(1)), fgui::color(style.colorlist.at(2)), fgui::gradient_type::VERTICAL);

	// dots
	if (m_dragging) {
		
		fgui::render.rect(scrollbar_area.left + 5, (scrollbar_area.top + calculated_position) + 2 + (calculated_size / 2) - 1, 1, 1, fgui::color(style.colorlist.at(3)));
		fgui::render.rect(scrollbar_area.left + 5, (scrollbar_area.top + calculated_position) + 2 + (calculated_size / 2) - 3, 1, 1, fgui::color(style.colorlist.at(3)));
		fgui::render.rect(scrollbar_area.left + 5, (scrollbar_area.top + calculated_position) + 2 + (calculated_size / 2) - 5, 1, 1, fgui::color(style.colorlist.at(3)));
	}

	else if (!m_dragging) {
		
		fgui::render.rect(scrollbar_area.left + 5, (scrollbar_area.top + calculated_position) + 2 + (calculated_size / 2) - 1, 1, 1, fgui::color(style.text.at(0)));
		fgui::render.rect(scrollbar_area.left + 5, (scrollbar_area.top + calculated_position) + 2 + (calculated_size / 2) - 3, 1, 1, fgui::color(style.text.at(0)));
		fgui::render.rect(scrollbar_area.left + 5, (scrollbar_area.top + calculated_position) + 2 + (calculated_size / 2) - 5, 1, 1, fgui::color(style.text.at(0)));
	}
}

//---------------------------------------------------------
void fgui::colorlist::add_color(std::string identificator, fgui::color color, fgui::state gradient_state) {

	m_color_list.push_back(fgui::color_info(identificator, color, gradient_state));
}

//---------------------------------------------------------
fgui::color fgui::colorlist::get_color(int index) {

	if (m_color_list[index].m_gradient_checkbox->get_bool()) {

		static float ttt1 = 0.f;

		ttt1 = std::fminf(ttt1 + 0.0005f, 1.f);

		if (ttt1 >= 1.f) {

			static float ttt2 = 0.f;

			// ghetto way to return back to the first color
			ttt2 = std::fminf(ttt2 + 0.0005f, 1.f);

			if (ttt2 >= 1.f) {
				ttt2 = 0.f;
				ttt1 = 0.f;
			}

			return fgui::color::interpolate(m_color_list[index].m_second_color, m_color_list[index].m_first_color, ttt2);
		}

		return fgui::color::interpolate(m_color_list[index].m_first_color, m_color_list[index].m_second_color, ttt1);
	}

	return m_color_list[index].m_first_color;
}

//---------------------------------------------------------
void fgui::colorlist::set_color(int index, fgui::color color) {

	m_color_list[index].m_first_color.m_red = color.m_red;
	m_color_list[index].m_first_color.m_green = color.m_green;
	m_color_list[index].m_first_color.m_blue = color.m_blue;
	m_color_list[index].m_first_color.m_alpha = color.m_alpha;
}

//---------------------------------------------------------
void fgui::colorlist::set_gradient(int index, fgui::state gradient_state) {

	m_color_list[index].m_gradient_checkbox->set_bool(gradient_state);
}

//---------------------------------------------------------
void fgui::colorlist::handle_input() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// get the control area
	fgui::rect area = { a.x, a.y, (m_width - 250) - 15, m_height };

	// scrollbar slider area
	fgui::rect scrollbar_area = { (area.left + 2) + (area.right - 15), area.top + 2, 15 - 4, area.bottom - 4 };

		if (fgui::input.is_mouse_in_region(scrollbar_area)) {
					
			if (fgui::input.get_key_state(MOUSE_LEFT)) 
				m_dragging = true;
	}

	if (m_color_list.size() > 0) {
		
		// color picker area
		fgui::rect picker_area = { a.x + (m_width - 240), a.y, 150, 150 };

		// gradient checkbox area
		fgui::rect gradient_checkbox_area = { picker_area.left + 50, (picker_area.top + picker_area.bottom) + 40, m_color_list[m_selected].m_gradient_checkbox->get_size().width, m_color_list[m_selected].m_gradient_checkbox->get_size().height };
		
		// handle input
		m_color_list[m_selected].m_gradient_checkbox->handle_input();
		m_color_list[m_selected].m_alpha_slider->handle_input();
		
		// plus button area
		fgui::rect plus_button_area = { picker_area.left, (picker_area.top + picker_area.bottom) + 40, m_color_list[m_selected].m_plus_button->get_size().width, m_color_list[m_selected].m_plus_button->get_size().height };

		if (fgui::input.is_mouse_in_region(plus_button_area)) {

			// check if we don't have a second color added
			if (!m_color_list[m_selected].m_second_color_added) {

				m_color_list[m_selected].m_second_color_added = true;

				m_color_list[m_selected].m_backup_color = m_color_list[m_selected].m_first_color; 
				m_color_list[m_selected].m_second_color = m_color_list[m_selected].m_first_color;
			}
		}

		// minus button area
		fgui::rect minus_button_area = { picker_area.left + 20, (picker_area.top + picker_area.bottom) + 40, m_color_list[m_selected].m_minus_button->get_size().width, m_color_list[m_selected].m_minus_button->get_size().height };

		if (fgui::input.is_mouse_in_region(minus_button_area)) {

			// check if we have something to remove
			if (m_color_list[m_selected].m_second_color_added) {

				m_color_list[m_selected].m_second_color_added = false;

				m_color_list[m_selected].m_first_color = m_color_list[m_selected].m_backup_color;
				m_color_list[m_selected].m_second_color = fgui::color(0, 0, 0);

				m_color_list[m_selected].m_gradient_checkbox->set_bool(false);
			}
		}

		// get the number of displayed items
		unsigned int item_displayed = 0;

		// calculate the amount of items to be drawned
		int calculated_items = (m_height - 20) / m_item_height;

		for (std::size_t i = m_slider_top; (i < m_color_list.size() && item_displayed < calculated_items); i++) {

			int text_width, text_height;
			fgui::render.get_text_size(fgui::colorlist::get_font(), m_color_list[i].m_identificator, text_width, text_height);

			// get the item area of the colorlist
			fgui::rect item_area = { a.x, a.y + (m_item_height * item_displayed), (m_width - 250) - 15, m_item_height };

			if (fgui::input.is_mouse_in_region(item_area)) {

				// select a color picker
				m_selected = i;
			}

			item_displayed++;
		}
	}
}

//---------------------------------------------------------
void fgui::colorlist::update() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// get the number of displayed items
	unsigned int item_displayed = 0;

	// calculate the amount of items to be drawned
	int calculated_items = (m_height - 20) / m_item_height;

	if (m_dragging) {

		if (fgui::input.get_key_state(MOUSE_LEFT)) {

			// get the cursor position
			fgui::point cursor;
			fgui::input.get_mouse_position(cursor.x, cursor.y);

			// move the scrollbar UP and DOWN according to the cursors position
			cursor.y -= a.y + 2;

			// ratio of how many visible to how many are hidden
			float calculated_size = static_cast<float>(calculated_items) / static_cast<float>(m_color_list.size());
			calculated_size *= m_height;

			// height delta
			float height_delta = (cursor.y + calculated_size) - m_height;

			if (height_delta >= 0)
				cursor.y -= height_delta;

			float new_position_ratio = static_cast<float>(cursor.y) / static_cast<float>(m_height);
			m_slider_top = new_position_ratio * m_color_list.size();

			if (m_slider_top <= 0)
				m_slider_top = 0;
		}

		else
			m_dragging = false;
	}

	if (m_color_list.size() > 0) {

		m_color_list[m_selected].m_alpha_slider->update();
		m_color_list[m_selected].m_minus_button->update();
		m_color_list[m_selected].m_plus_button->update();
		m_color_list[m_selected].m_gradient_checkbox->update();

		for (std::size_t i = m_slider_top; (i < m_color_list.size() && item_displayed < calculated_items); i++) {

			if (m_selected == i) {

				// color picker area
				fgui::rect picker_area = { a.x + (m_width - 240), a.y, 150, 150 };

				fgui::rect hsb_area = { picker_area.left, picker_area.top, picker_area.right, picker_area.bottom };
				fgui::rect hue_area = { picker_area.left + picker_area.right + 10, picker_area.top, 15, picker_area.bottom };

				static bool hue_selected = false;
				static bool hsb_selected = false;

				// get the cursor position
				fgui::point cursor;
				fgui::input.get_mouse_position(cursor.x, cursor.y);

				if (fgui::input.get_key_press(MOUSE_LEFT)) {

					hue_selected = fgui::input.is_mouse_in_region(hue_area);
					hsb_selected = fgui::input.is_mouse_in_region(hsb_area);
				}

				else if (!fgui::input.get_key_state(MOUSE_LEFT)) {

					hue_selected = false;
					hsb_selected = false;
				}

				if (hsb_selected) {

					fgui::precision_point relative_pos = { cursor.x - static_cast<float>(hsb_area.left), cursor.y - static_cast<float>(hsb_area.top) };
					m_color_list[i].m_first_color = fgui::color::hsb_to_rgb(fgui::color::get_hue(m_color_list[i].m_first_color), relative_pos.x / picker_area.right, relative_pos.y / picker_area.bottom, m_color_list[i].m_first_color.m_alpha);
				}

				if (hue_selected) {

					float hue = (cursor.y - hue_area.top) / 150.f;
					
					m_color_list[i].m_first_color = fgui::color::hsb_to_rgb(std::clamp(hue, 0.f, 1.f), 1, 1);
				}

				// color alpha
				m_color_list[i].m_first_color.m_alpha = (m_color_list[i].m_alpha_slider->get_value() * 2.55f);
			}
		}
	}
}

//---------------------------------------------------------
void fgui::colorlist::tooltip() {}

//---------------------------------------------------------
void fgui::colorlist::save(const std::string& file_name, nlohmann::json& json_module) {

	for (std::size_t i = 0; i < m_color_list.size(); i++) {

		// main color
		json_module[m_identificator][m_color_list[i].m_identificator]["primary_red"] = m_color_list[i].m_first_color.m_red;
		json_module[m_identificator][m_color_list[i].m_identificator]["primary_green"] = m_color_list[i].m_first_color.m_green;
		json_module[m_identificator][m_color_list[i].m_identificator]["primary_blue"] = m_color_list[i].m_first_color.m_blue;
		json_module[m_identificator][m_color_list[i].m_identificator]["primary_alpha"] = m_color_list[i].m_first_color.m_alpha;

		if (m_color_list[i].m_second_color_added) {

			// secondary color
			json_module[m_identificator][m_color_list[i].m_identificator]["secondary_red"] = m_color_list[i].m_second_color.m_red;
			json_module[m_identificator][m_color_list[i].m_identificator]["secondary_green"] = m_color_list[i].m_second_color.m_green;
			json_module[m_identificator][m_color_list[i].m_identificator]["secondary_blue"] = m_color_list[i].m_second_color.m_blue;
			json_module[m_identificator][m_color_list[i].m_identificator]["secondary_alpha"] = m_color_list[i].m_second_color.m_alpha;
		}

		// gradient
		json_module[m_identificator][m_color_list[i].m_identificator]["color_interpolation"] = m_color_list[i].m_gradient_checkbox->get_bool();
	}
}

//---------------------------------------------------------
void fgui::colorlist::load(const std::string& file_name) {

	nlohmann::json json_module;

	// open the file
	std::ifstream file_to_load(file_name, std::ifstream::binary);

	if (!file_to_load.good())
		return;

	// read config file
	json_module = nlohmann::json::parse(file_to_load);

	// change the element state to match the one stored on file
	for (std::size_t i = 0; i < m_color_list.size(); i++) {

		// primary color
		m_color_list[i].m_first_color.m_red = json_module[m_identificator][m_color_list[i].m_identificator]["primary_red"];
		m_color_list[i].m_first_color.m_green = json_module[m_identificator][m_color_list[i].m_identificator]["primary_green"];
		m_color_list[i].m_first_color.m_blue = json_module[m_identificator][m_color_list[i].m_identificator]["primary_blue"];
		m_color_list[i].m_first_color.m_alpha = json_module[m_identificator][m_color_list[i].m_identificator]["primary_alpha"];

		if (m_color_list[i].m_second_color_added) {

			// secondary color
			m_color_list[i].m_second_color.m_red = json_module[m_identificator][m_color_list[i].m_identificator]["secondary_red"];
			m_color_list[i].m_second_color.m_green = json_module[m_identificator][m_color_list[i].m_identificator]["secondary_green"];
			m_color_list[i].m_second_color.m_blue = json_module[m_identificator][m_color_list[i].m_identificator]["secondary_blue"];
			m_color_list[i].m_second_color.m_alpha = json_module[m_identificator][m_color_list[i].m_identificator]["secondary_alpha"];
		}

		// gradient
		m_color_list[i].m_gradient_checkbox->set_bool(json_module[m_identificator][m_color_list[i].m_identificator]["color_interpolation"]);
	}
}