#pragma once

using create_interface_fn = void* (*)(const char*, int*);

enum class InterfaceReturnStatus {
	OK,
	FAILED
};

static const char* interface_version_server_plugin_callbacks = "ISERVERPLUGINCALLBACKS003";
static const char* interface_version_engine_client = "VEngineClient014";
static const char* interface_version_client_entity_list = "VClientEntityList003";
static const char* interface_version_player_info_manager = "PlayerInfoManager002";
static const char* interface_version_engine_cvar = "VEngineCvar004";
