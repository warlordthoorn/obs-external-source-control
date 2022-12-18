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
#include <obs-frontend-api.h>

#include "config.hpp"

// define our parameters for global obs config store
#define CONFIG_NAME_SECTION "OBSExternalSourceControl"

#define CONFIG_PARAM_ENABLED "PluginEnabled"
#define CONFIG_PARAM_REFRESH "RefreshFrequency"
#define CONFIG_PARAM_TOPIC "ExternalTopic"
#define CONFIG_PARAM_SOURCE "SourceName"

Config::Config()
	: pluginEnabled(false),
	  refreshFrequency(60),
	  externalTopic(""),
	  sourceName("")
{
	reset();
}

void Config::reset()
{
	// get the obs configstore and check if it was succesful
	config_t *obsConfig = getConfigStore();

	if (!obsConfig) {
		blog(LOG_ERROR, "[Config::reset] Failed to fetch OBS config!");
		return;
	}

	// initialize to default, defined in the constructor
	config_set_default_bool(obsConfig, CONFIG_NAME_SECTION,
				CONFIG_PARAM_ENABLED, pluginEnabled);
	config_set_default_int(obsConfig, CONFIG_NAME_SECTION,
			       CONFIG_PARAM_REFRESH, refreshFrequency);
	config_set_default_string(obsConfig, CONFIG_NAME_SECTION,
				  CONFIG_PARAM_TOPIC,
				  externalTopic.toUtf8().constData());
	config_set_default_string(obsConfig, CONFIG_NAME_SECTION,
				  CONFIG_PARAM_SOURCE,
				  sourceName.toUtf8().constData());
}

void Config::save()
{
	// function get called after changing values
	// save all parameters in the config store
	config_t *obsConfig = getConfigStore();

	if (!obsConfig) {
		blog(LOG_ERROR, "[Config::save] Failed to fetch OBS config!");
		return;
	}

	config_set_bool(obsConfig, CONFIG_NAME_SECTION, CONFIG_PARAM_ENABLED,
			pluginEnabled);
	config_set_int(obsConfig, CONFIG_NAME_SECTION, CONFIG_PARAM_REFRESH,
		       refreshFrequency);
	config_set_string(obsConfig, CONFIG_NAME_SECTION, CONFIG_PARAM_TOPIC,
			  externalTopic.toUtf8().constData());
	config_set_string(obsConfig, CONFIG_NAME_SECTION, CONFIG_PARAM_SOURCE,
			  sourceName.toUtf8().constData());

	if (_savecallback)
		_savecallback();
}

void Config::load()
{
	config_t *obsConfig = getConfigStore();

	if (!obsConfig) {
		blog(LOG_ERROR, "[Config::load] Failed to fetch OBS config!");
		return;
	}

	this->pluginEnabled = config_get_bool(obsConfig, CONFIG_NAME_SECTION,
					      CONFIG_PARAM_ENABLED);
	this->refreshFrequency = config_get_int(obsConfig, CONFIG_NAME_SECTION,
						CONFIG_PARAM_REFRESH);
	this->externalTopic = QString::fromUtf8(config_get_string(
		obsConfig, CONFIG_NAME_SECTION, CONFIG_PARAM_TOPIC));
	this->sourceName = QString::fromUtf8(config_get_string(
		obsConfig, CONFIG_NAME_SECTION, CONFIG_PARAM_SOURCE));
}

config_t *Config::getConfigStore()
{
	// more convenient to use the global config instead of creating our own local data
	// user would have to copy this to data folder etc.
	return obs_frontend_get_global_config();
}
