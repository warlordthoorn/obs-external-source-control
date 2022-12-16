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

#include <obs-module.h>
#include <obs.hpp>

#include "settingsdialog.hpp"
#include "../obs-externalsourcecontrol.hpp"

SettingsDialog::SettingsDialog(QWidget *parent)
	: QDialog(parent, Qt::Dialog), ui(new Ui::SettingsDialog)
{
	ui->setupUi(this);

	// Remove the ? button on dialogs on Windows (cause ugly)
	// setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	connect(ui->buttonBox, &QDialogButtonBox::clicked, this,
		&SettingsDialog::dialogButtonClicked);
}

SettingsDialog::~SettingsDialog()
{
	delete ui;
}

void SettingsDialog::dialogButtonClicked(QAbstractButton *button)
{
	if (button == ui->buttonBox->button(QDialogButtonBox::Ok))
		blog(LOG_INFO, "todo");
	else if (button == ui->buttonBox->button(QDialogButtonBox::Apply))
		blog(LOG_INFO, "todo");
	else if (button == ui->buttonBox->button(QDialogButtonBox::Cancel))
		setVisible(false);
}
