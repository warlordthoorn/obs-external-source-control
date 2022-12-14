/*
obs-externalsourcecontrol
Copyright (C) 2022-2023 warlordthoorn warlordthoorn@gmail.com

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program. If not, see <https://www.gnu.org/licenses/>
*/

#include <QAction>
#include <QMainWindow>
#include <obs-module.h>
#include <obs-frontend-api.h>

#include "obs-externalsourcecontrol.hpp"
#include "ui/settingsdialog.hpp"

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE(PLUGIN_NAME, "en-US")

SettingsDialog *_settingsDialog = nullptr;

bool obs_module_load(void)
{
	blog(LOG_INFO, "initializing");

	// inspired by https://github.com/obsproject/obs-websocket/blob/master/src/obs-websocket.cpp
	// Request ui access from QT and initialize our dialog window
	obs_frontend_push_ui_translation(obs_module_get_string);
	QMainWindow *mainWindow =
		static_cast<QMainWindow *>(obs_frontend_get_main_window());
	_settingsDialog = new SettingsDialog(mainWindow);
	obs_frontend_pop_ui_translation();

	// Create Qt object and add it to the tools tab
	const char *menuActionText = obs_module_text(
		"OBSExternalSourceControl.Settings.ToolsItemTitle");
	QAction *menuAction =
		(QAction *)obs_frontend_add_tools_menu_qaction(menuActionText);
	QObject::connect(menuAction, &QAction::triggered,
			 [] { _settingsDialog->show(); });

	blog(LOG_INFO, "successfully loaded (version %s)",
	     PLUGIN_VERSION);

	return true;
}

void obs_module_unload()
{
	blog(LOG_INFO, "shutting down");

	blog(LOG_INFO, "plugin unloaded");
}
