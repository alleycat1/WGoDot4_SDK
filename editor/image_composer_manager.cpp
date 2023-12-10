#include "image_composer_manager.h"

#include "editor/editor_scale.h"
#include "editor/editor_settings.h"
#include "editor/editor_node.h"

void ImageComposerManager::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_READY: {
			connect("confirmed", callable_mp(this, &ImageComposerManager::_path_confirmed));
		} break;
	}
}

void ImageComposerManager::_path_confirmed() {
	String path = image_path->get_text();
	if(path.length() > 0)
	{
		EditorSettings::get_singleton()->set("filesystem/import/image_path", path);
		EditorSettings::get_singleton()->save();
		EditorNode::get_singleton()->show_image_composer(path);
	}
}

void ImageComposerManager::_browse_install() {
	if (image_path->get_text() != String()) {
		browse_dialog->set_current_dir(image_path->get_text());
	}
	browse_dialog->popup_file_dialog();
}

void ImageComposerManager::_select_dir(const String &p_path) {
	image_path->set_text(p_path);
}

void ImageComposerManager::show_dialog(bool p_exclusive) {
	set_flag(Window::FLAG_BORDERLESS, p_exclusive); // Avoid closing accidentally .
	set_close_on_escape(!p_exclusive);
	popup_centered(Size2(410, 105) * EDSCALE);
}

ImageComposerManager *ImageComposerManager::singleton = nullptr;

ImageComposerManager::ImageComposerManager() {
	singleton = this;

	set_title(TTR("Configure Image Composer"));

	VBoxContainer *vb = memnew(VBoxContainer);
	vb->add_child(memnew(Label(TTR("Please select the image path:"))));

	HBoxContainer *hb = memnew(HBoxContainer);

	image_path = memnew(LineEdit);
	image_path->set_h_size_flags(Control::SIZE_EXPAND_FILL);
	hb->add_child(image_path);
	path_browse = memnew(Button);
	hb->add_child(path_browse);
	path_browse->set_text(TTR("Browse"));
	path_browse->connect("pressed", callable_mp(this, &ImageComposerManager::_browse_install));
	hb->set_h_size_flags(Control::SIZE_EXPAND_FILL);
	hb->set_custom_minimum_size(Size2(400 * EDSCALE, 0));

	vb->add_child(hb);

	add_child(vb);

	get_ok_button()->set_text(TTR("Confirm"));

	browse_dialog = memnew(EditorFileDialog);
	browse_dialog->set_file_mode(EditorFileDialog::FILE_MODE_OPEN_DIR);
	browse_dialog->set_access(EditorFileDialog::ACCESS_FILESYSTEM);

	browse_dialog->connect("dir_selected", callable_mp(this, &ImageComposerManager::_select_dir));

	add_child(browse_dialog);
}
