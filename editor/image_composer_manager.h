#ifndef IMAGE_COMPOSER_MANAGER_H
#define IMAGE_COMPOSER_MANAGER_H

#include "editor/editor_file_dialog.h"
#include "scene/gui/dialogs.h"
#include "scene/gui/line_edit.h"
#include "scene/gui/texture_rect.h"

class ImageComposerManager : public ConfirmationDialog {
	GDCLASS(ImageComposerManager, ConfirmationDialog)

	Label *message = nullptr;
	LineEdit *image_path = nullptr;
	Button *path_browse = nullptr;
	EditorFileDialog *browse_dialog = nullptr;

	void _select_dir(const String &p_path);
	void _path_confirmed();
	void _browse_install();

	static ImageComposerManager *singleton;

protected:
	void _notification(int p_what);

public:
	static ImageComposerManager *get_singleton() { return singleton; }

	void show_dialog(bool p_exclusive = false);

	ImageComposerManager();
};

#endif // IMAGE_COMPOSER_MANAGER_H
