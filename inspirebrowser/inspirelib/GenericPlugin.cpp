#include "GenericPlugin.h"

#include "PluginManager.h"

PluginManager* GenericPlugin::GetPluginManager()
{
	return qobject_cast<PluginManager*>(this->parent());
}
