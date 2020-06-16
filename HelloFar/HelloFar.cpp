#include "pch.h"

#include "version.hpp"
#include "guid.hpp"

static struct PluginStartupInfo Info;

void WINAPI GetGlobalInfoW(struct GlobalInfo* Info)
{
	Info->StructSize = sizeof(struct GlobalInfo);
	Info->MinFarVersion = FARMANAGERVERSION;
	Info->Version = PLUGIN_VERSION;
	Info->Guid = MainGuid;
	Info->Title = PLUGIN_NAME;
	Info->Description = PLUGIN_DESC;
	Info->Author = PLUGIN_AUTHOR;
}

void WINAPI SetStartupInfoW(const struct PluginStartupInfo* startupInfo)
{
	Info = *startupInfo;
}

void WINAPI GetPluginInfoW(struct PluginInfo* pluginInfo)
{
	pluginInfo->StructSize = sizeof(*pluginInfo);
	pluginInfo->Flags = PF_EDITOR;

	static const wchar_t* PluginMenuStrings[1];
	PluginMenuStrings[0] = Info.GetMsg(&MainGuid, 0);
	pluginInfo->PluginMenu.Guids = &MenuGuid;
	pluginInfo->PluginMenu.Strings = PluginMenuStrings;
	pluginInfo->PluginMenu.Count = ARRAYSIZE(PluginMenuStrings);
}

HANDLE WINAPI OpenW(const struct OpenInfo* OInfo)
{
	const wchar_t* MsgItems[] =
	{
		Info.GetMsg(&MainGuid, 0),
		Info.GetMsg(&MainGuid, 1),
		Info.GetMsg(&MainGuid, 2),
	};

	Info.Message(&MainGuid, NULL, FMSG_NONE, L"Contents", MsgItems, ARRAYSIZE(MsgItems), 1);
	return NULL;
}
