%define is_mandrake %(test -e /etc/mandrake-release && echo 1 || echo 0)
%define is_suse %(test -e /etc/SuSE-release && echo 1 || echo 0)
%define is_fedora %(test -e /etc/fedora-release && echo 1 || echo 0)

Name:           inspireremote
Version:        0.0.1
Release:        1%{?dist}
Summary:	A command line remote control application for the Inspire Browser

Group:          Productivity/Networking/Web/Browsers
License:        GPLv3
URL:            http://www.mikeditum.co.uk
Source0:        http://www.mikeditum.co.uk/inspireremote/inspireremote-%{version}.tar.gz
BuildRoot:      %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

BuildRequires:  qt-devel gcc-c++
Requires:       qt

%description
Inspire Remote allows the ability to remote control instances of the 
InspireBrowser across the network

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
