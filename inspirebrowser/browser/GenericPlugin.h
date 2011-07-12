#ifndef GENERIC_PLUGIN_H
#define GENERIC_PLUGIN_H

#include <QString>

class GenericPlugin
{
public:
	virtual ~GenericPlugin() {}

	virtual bool InitialisePlugin() = 0;
	virtual bool DeInitialisePlugin() { return true; }

	virtual QString GetId() = 0;
	virtual QString GetName() = 0;
	virtual QString GetDescription() = 0;
};

Q_DECLARE_INTERFACE(GenericPlugin, "org.inspirebrowser.Plugins.GenericPlugin/1.0");

#endif
