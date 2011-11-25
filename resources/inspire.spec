
Name:           inspire
Version:        0.0.1
Release:        1%{?dist}
Summary:        A web browser designed for STB and Kiosk environments

Group:          Productivity/Networking/Web/Browsers
License:        GPLv3
URL:            http://www.mikeditum.co.uk
Source0:        http://www.mikeditum.co.uk/inspire/inspire-%{version}.tar.gz
BuildRoot:      %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

BuildRequires:  libqxt-devel
%if 0%{?suse_version} == 1140
BuildRequires:  patterns-openSUSE-devel_C_C++
BuildRequires:  libqt4-devel
BuildRequires:  libQtWebKit-devel
%endif
%if 0%{?fedora} == 14
BuildRequires:  qt-webkit-devel
BuildRequires:  gcc-c++
%endif

Requires:       libqxt
%if 0%{?suse_version} == 1140
Requires:       libqt4
Requires:       libQtWebKit
%endif
%if 0%{?fedora} == 14
Requires:       qt-webkit
requires:       redhat-lsb
%endif

%description
Inspire is a Webkit based browser designed for STB and Kiosk based 
environments. The basic browser is extended by plugins that can, among other 
things, provide a powerful javascript API for controlling the browser, querying
the system and displaying video and audio content from numerous sources 
including igmp and rtsp.

%package browser
Summary: The Inspire Browser executable
Group: Productivity/Networking/Web/Browsers
Requires: libinspire
%description browser
A Webkit based browser designed for STB and Kiosk based environments.

%package remote
Summary: The Inspire Remote executable
Group: Productivity/Networking/Web/Browsers
Requires: libinspire
%description remote
The inspireremote application that allows sending of commands across the network
to clients running the inspirebrowser with the commandserver plugin

%package -n libinspire
Summary: The inspire library used by inspire-browser and inpire-remote
Group: Productivity/Networking/Web/Browsers
%description -n libinspire
The inspire library that powers the inspire browser and inspire remote applications

%package plugin-systemjs
Summary: An inspire plugin that allows interacting with the system from Javascript
Group: Productivity/Networking/Web/Browsers
Requires: libinspire inspire-browser
%description plugin-systemjs
A plugin for the inspire browser that allows querying and controlling of the system
through a JavaScript API

%package plugin-browserjs
Summary: An inspire plugin that allows interacting with the browser from Javascript
Group: Productivity/Networking/Web/Browsers
Requires: libinspire inspire-browser
%description plugin-browserjs
A plugin for the inspire browser that allows interaction with the browser window
through a JavaScript API

%package plugin-videojs
Summary: An inspire plugin that allows playback of video through a Javascript API
Group: Productivity/Networking/Web/Browsers
BuildRequires:  vlc-devel
Requires: libinspire inspire-browser
%if 0%{?suse_version} == 1140
Requires:       libvlc5
%endif
%if 0%{?fedora} == 14
Requires: vlc-core
%endif
%description plugin-videojs
A plugin for the inspire browser that allows playback of video and audio from different
sources through a JavaScript API

%package plugin-commandserver
Summary: An inspire plugin that allows controlling of the inspire browser from the network
Group: Productivity/Networking/Web/Browsers
Requires: libinspire inspire-browser
%description plugin-commandserver
A plugin for the inspire browser that allows controlling of clients running the inspire browser
from other networked machines

%package desktop
Summary: Meta-Package that includes the browser and all plugins designed for a desktop machine
Group: Productivity/Networking/Web/Browsers
Requires: libinspire inspire-browser 
Requires: inspire-plugins-desktop
%description desktop
Meta-Package that just includes the browser and all plugins designed for a desktop machine. Includes
systemjs, browserjs, videosjs and commandserver plugins

%package plugins-desktop
Summary: Meta-Package that just includes all plugins designed for a desktop machine
Group: Productivity/Networking/Web/Browsers
Requires: inspire-plugin-systemjs
Requires: inspire-plugin-browserjs
Requires: inspire-plugin-videojs
Requires: inspire-plugin-commandserver
%description plugins-desktop
Meta-Package that just includes all plugins designed for a desktop machine. Includes
systemjs, browserjs, videosjs and commandserver plugins

%prep
%setup -n inspire-%{version}

%build
%configure
make %{?_smp_mflags}

%install
rm -rf $RPM_BUILD_ROOT
make install INSTALL_ROOT=$RPM_BUILD_ROOT 

%clean
rm -rf $RPM_BUILD_ROOT

%files browser
%{_bindir}/inspirebrowser

%files remote
%{_bindir}/inspireremote

%files -n libinspire
%{_libdir}/libinspirelib.so
%{_libdir}/libinspirelib.so.0
%{_libdir}/libinspirelib.so.0.0
%{_libdir}/libinspirelib.so.0.0.1

%files plugin-systemjs
%{_libdir}/inspirebrowser/plugins/libsystemjs.so

%files plugin-browserjs
%{_libdir}/inspirebrowser/plugins/libbrowserjs.so

%files plugin-videojs
%{_libdir}/inspirebrowser/plugins/libvideojs_vlc.so

%files plugin-commandserver
%{_libdir}/inspirebrowser/plugins/libcommandserver.so

%files desktop

%files plugins-desktop

%changelog
* Tue Nov 22 2011 - mike (at) mikeditum.co.uk
- Combined inspirebrowser and inspireremote spec files into one file and
  had it generate multiple packages for each executable, plugin and the 
  inspire library. In addition create some meta-packages for quick installing.

* Sat Jan 23 2011 - mike (at) mikeditum.co.uk
- Initial Implementation
