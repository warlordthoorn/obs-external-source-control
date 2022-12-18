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

#include "EventHandler.hpp"

EventHandler::EventHandler() : _obsLoaded(false)
{
	obs_frontend_add_event_callback(frontendEventHandler, this);
}

EventHandler::~EventHandler()
{
	obs_frontend_remove_event_callback(frontendEventHandler, this);
}

void EventHandler::frontendEventHandler(enum obs_frontend_event event,
					void *data)
{
	auto eventHandler = static_cast<EventHandler *>(data);

	if (!eventHandler->_obsLoaded.load() &&
	    event != OBS_FRONTEND_EVENT_FINISHED_LOADING)
		return;

	switch (event) {
	case OBS_FRONTEND_EVENT_STREAMING_STARTING:
		// a choice to start connection here or the next one
		// we only will start listing to the server once the stream is fully started
		// not this
		break;
	case OBS_FRONTEND_EVENT_STREAMING_STARTED:
		// so we use this one
		if (getEventHandler()->_startStreamingCallback)
			getEventHandler()->_startStreamingCallback();
		break;
	case OBS_FRONTEND_EVENT_STREAMING_STOPPING:
		// a choice to start connection here or the next one
		// we will stop listing to the server if the streaming event is stopping
		// so we use this
		if (getEventHandler()->_endStreamingCallback)
			getEventHandler()->_endStreamingCallback();
		break;
	case OBS_FRONTEND_EVENT_STREAMING_STOPPED:
		// not this
		break;
	case OBS_FRONTEND_EVENT_RECORDING_STARTING:
		// recording should not influence us
		// if already streaming okay otherwise no live viewers anyway
		break;
	case OBS_FRONTEND_EVENT_RECORDING_STARTED:
		// N.A.
		break;
	case OBS_FRONTEND_EVENT_RECORDING_STOPPING:
		// N.A.
		break;
	case OBS_FRONTEND_EVENT_RECORDING_STOPPED:
		// N.A.
		break;
	case OBS_FRONTEND_EVENT_SCENE_CHANGED:
		// TODO::FEATURE => different source names for different scenes to be controlled
		break;
	case OBS_FRONTEND_EVENT_SCENE_LIST_CHANGED:
		// TODO::FEATURE => could be used to show in dropdown list for ui
		break;
	case OBS_FRONTEND_EVENT_TRANSITION_CHANGED:
		// not usefull (overruled by OBS_FRONTEND_EVENT_SCENE_CHANGED)
		break;
	case OBS_FRONTEND_EVENT_TRANSITION_STOPPED:
		// N.A.
		break;
	case OBS_FRONTEND_EVENT_TRANSITION_LIST_CHANGED:
		// N.A.
		break;
	case OBS_FRONTEND_EVENT_SCENE_COLLECTION_CHANGED:
		// TODO::FEATURE => also shown in ui
		break;
	case OBS_FRONTEND_EVENT_SCENE_COLLECTION_LIST_CHANGED:
		// maybe useful not sure yet
		break;
	case OBS_FRONTEND_EVENT_PROFILE_CHANGED:
		// for raw settings (not scenes) so
		// N.A.
		break;
	case OBS_FRONTEND_EVENT_PROFILE_LIST_CHANGED:
		// N.A.
		break;
	case OBS_FRONTEND_EVENT_EXIT:
		// about to exit clean up
		eventHandler->frontendExitHandler();
		break;
	case OBS_FRONTEND_EVENT_REPLAY_BUFFER_STARTING:
		// does anyone use this???
		// N.A.
		break;
	case OBS_FRONTEND_EVENT_REPLAY_BUFFER_STARTED:
		// N.A.
		break;
	case OBS_FRONTEND_EVENT_REPLAY_BUFFER_STOPPING:
		// N.A.
		break;
	case OBS_FRONTEND_EVENT_REPLAY_BUFFER_STOPPED:
		// N.A.
		break;
	case OBS_FRONTEND_EVENT_STUDIO_MODE_ENABLED:
		// we only want to impact the live stream
		// if issues arrive probably and some here
		break;
	case OBS_FRONTEND_EVENT_STUDIO_MODE_DISABLED:
		// idem
		break;
	case OBS_FRONTEND_EVENT_PREVIEW_SCENE_CHANGED:
		// idem
		break;
	case OBS_FRONTEND_EVENT_SCENE_COLLECTION_CLEANUP:
		// perhaps furture
		break;
	case OBS_FRONTEND_EVENT_FINISHED_LOADING:
		eventHandler->frontendLoadingFinishHandler();
		break;
	case OBS_FRONTEND_EVENT_RECORDING_PAUSED:
		// N.A.
		break;
	case OBS_FRONTEND_EVENT_RECORDING_UNPAUSED:
		// N.A.
		break;
	case OBS_FRONTEND_EVENT_TRANSITION_DURATION_CHANGED:
		// N.A.
		break;
	case OBS_FRONTEND_EVENT_REPLAY_BUFFER_SAVED:
		// N.A.
		break;
	case OBS_FRONTEND_EVENT_VIRTUALCAM_STARTED:
		// N.A.
		break;
	case OBS_FRONTEND_EVENT_VIRTUALCAM_STOPPED:
		// N.A.
		break;
	case OBS_FRONTEND_EVENT_TBAR_VALUE_CHANGED:
		// N.A.
		break;
	case OBS_FRONTEND_EVENT_SCENE_COLLECTION_CHANGING:
		// perhaps
		break;
	case OBS_FRONTEND_EVENT_PROFILE_CHANGING:
		// N.A.
		break;
	case OBS_FRONTEND_EVENT_SCRIPTING_SHUTDOWN:
		// N.A.
		break;
	case OBS_FRONTEND_EVENT_PROFILE_RENAMED:
		// N.A.
		break;
	case OBS_FRONTEND_EVENT_SCENE_COLLECTION_RENAMED:
		// perhaps
		break;
	default:
		// for most events we do nothing
		break;
	}
}

void EventHandler::frontendLoadingFinishHandler()
{
	_obsLoaded.store(true);
}

void EventHandler::frontendExitHandler()
{
	_obsLoaded.store(false);
}
