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

#pragma once

#include <atomic>
#include <functional>
#include <obs.hpp>
#include <obs-frontend-api.h>

#include "../obs-externalsourcecontrol.hpp"
#include "plugin-macros.generated.h"

class EventHandler {
public:
	EventHandler();
	~EventHandler();
	typedef std::function<void()> StartStreamingCallback;
	StartStreamingCallback _startStreamingCallback;
	typedef std::function<void()> EndStreamingCallback;
	EndStreamingCallback _endStreamingCallback;

private:
	// variables
	std::atomic<bool> _obsLoaded;

	// frontend
	static void frontendEventHandler(enum obs_frontend_event event,
					 void *data);
	void frontendLoadingFinishHandler();
	void frontendExitHandler();
};
