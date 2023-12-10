#include "image_composer.h"

#include "editor/editor_scale.h"
#include "editor/editor_settings.h"

void ImageComposer::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_READY: {
			//connect("confirmed", callable_mp(this, &ImageComposer::_path_confirmed));
		} break;
	}
}

void ImageComposer::show_dialog(const String &path, bool p_exclusive) {
	set_flag(Window::FLAG_BORDERLESS, p_exclusive); // Avoid closing accidentally .
	set_close_on_escape(!p_exclusive);
	image_panel->set_texture_path(path);
	popup_centered(Size2(800, 600) * EDSCALE);
}

ImageComposer *ImageComposer::singleton = nullptr;

ImageComposer::ImageComposer() {
	singleton = this;

	set_title(TTR("Image Composer"));

	VBoxContainer *vb = memnew(VBoxContainer);

	image_panel = memnew(MultiTextureRect);

	image_panel->set_stretch_mode(MultiTextureRect::STRETCH_SCALE);
	image_panel->set_custom_minimum_size({800, 600});

	vb->add_child(image_panel);

	add_child(vb);

	get_ok_button()->set_text(TTR("Ok"));
}
