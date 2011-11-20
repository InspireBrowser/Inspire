%define is_mandrake %(test -e /etc/mandrake-release && echo 1 || echo 0)
%define is_suse %(test -e /etc/SuSE-release && echo 1 || echo 0)
%define is_fedora %(test -e /etc/fedora-release && echo 1 || echo 0)

Name:           inspirebrowser
Version:        0.0.1
Release:        1%{?dist}
Summary:        A web browser designed for STB and Kiosk environments

Group:          Productivity/Networking/Web/Browsers
License:        GPLv3
URL:            http://www.mikeditum.co.uk
Source0:        http://www.mikeditum.co.uk/inspirebrowser/inspirebrowser-%{version}.tar.gz
BuildRoot:      %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

BuildRequires:  vlc-devel qt-webkit-devel gcc-c++
Requires:       vlc-core qt-webkit

%description
Inspire Browser is a Webkit based browser designed for STB and Kiosk based 
environments. It provides a powerful javascript API for controlling the 
browser and displaying video and audio content from numerous sources 
including igmp and rtsp.

%prep
%setup -q


%build
qmake-qt4
make %{?_smp_mflags}


%install
rm -rf $RPM_BUILD_ROOT
make install INSTALL_ROOT=$RPM_BUILD_ROOT 


%clean
rm -rf $RPM_BUILD_ROOT


%files
%defattr(-,root,root,-)
%doc

# the binary files
%{_bindir}/%{name}



%changelog
* Sat Jan 23 2011 - mike (at) mikeditum.co.uk
- Initial Implementation
