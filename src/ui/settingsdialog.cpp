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

#include "../obs-externalsourcecontrol.hpp"
#include "settingsdialog.hpp"
#include "../util/config.hpp"

SettingsDialog::SettingsDialog(QWidget *parent)
	: QDialog(parent, Qt::Dialog), ui(new Ui::SettingsDialog)
{
	ui->setupUi(this);

	connect(ui->buttonBox, &QDialogButtonBox::clicked, this,
		&SettingsDialog::dialogButtonClicked);
}

SettingsDialog::~SettingsDialog()
{
	delete ui;
}

void SettingsDialog::dialogButtonClicked(QAbstractButton *button)
{
	if (button == ui->buttonBox->button(QDialogButtonBox::Ok)) {
		save();
		setVisible(false);
	} else if (button == ui->buttonBox->button(QDialogButtonBox::Apply))
		save();
	else if (button == ui->buttonBox->button(QDialogButtonBox::Cancel))
		setVisible(false);
}

void SettingsDialog::save()
{
	auto conf = getConfig();
	if (!conf) {
		blog(LOG_ERROR,
		     "[SettingsDialog::save] Unable to retreive config!");
		return;
	}

	conf->pluginEnabled = ui->enableExternalControlCheckBox->isChecked();
	conf->refreshFrequency = ui->sourceIntervalSpinBox->value();
	conf->externalTopic = ui->subscriptionTopicLineEdit->text();
	conf->sourceName = ui->namedSourceLineEdit->text();

	conf->save();
}

void SettingsDialog::loadUI()
{
	auto conf = getConfig();
	if (!conf) {
		blog(LOG_ERROR,
		     "[SettingsDialog::loadUI] Unable to retreive config!");
		return;
	}

	ui->enableExternalControlCheckBox->setChecked(conf->pluginEnabled);
	ui->sourceIntervalSpinBox->setValue(conf->refreshFrequency);
	ui->subscriptionTopicLineEdit->setText(conf->externalTopic);
	ui->namedSourceLineEdit->setText(conf->sourceName);
}

// called when the widget is shown
void SettingsDialog::showEvent(QShowEvent *)
{
	loadUI();
}
