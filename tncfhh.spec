%define build_attestation_imc_imv 1

Summary: An open source implementation of the Trusted Network Connect (TNC) framework
Name: tncfhh
Version: 0.8.3

Release: 14%{?dist}
License: GPLv2
Url: http://trust.inform.fh-hannover.de/joomla/index.php/projects/tncfhh
Source0: http://trust.inform.fh-hannover.de/download/tncfhh/tncfhh-%{version}.tar.gz

Group: Applications/System
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
BuildRequires: cmake log4cxx-devel xerces-c-devel trousers-devel libtnc-devel
BuildRequires: libtool-ltdl-devel boost-devel openssl-devel libxml2-devel

Patch1: tncfhh-0.8.3-issues.patch
Patch2: tncfhh-0.8.3-issues-2.patch
Patch3: tncutil-build-issue.patch
Patch4: tnc-platidimv-issue.patch
Patch5: tnc-hostscannerimv-issue.patch
Patch6: tncfhh-0.8.3-issues-3.patch
Patch7: tncfhh-985785.patch
Patch8: tncfhh-dlopen-support.patch

%description
The TNC@FHH project is an open source implementation of the Trusted Network
Connect (TNC) framework, which is specified by the Trusted Computing Group
(TCG). TNC@FHH allows you to provision access to a network based upon
factors like the user credentials and the requesting endpoint's integrity state.

The following TNC components and their respective interfaces are implemented by
TNC@FHH: IMCs (IF-IMC 1.2), IMVs (IF-IMV 1.2), TNCS (IF-TNCCS 1.1), 
NAA (IF-T EAP 1.1).

%package libs
Summary: Dynamic library for TNC
License: GPLv2
Group: Development/Libraries
Requires: %{name} = %{version}
Requires: boost-thread boost-system

%description libs
This package provides naaeap, tnsc, imunit, tncutil, and tncxacml 
dynamic libraries for using TNC client and server interfaces.

%package devel
Summary: Development files for TNC
License: GPLv2
Group: Development/Libraries
Requires: %{name}-libs = %{version}
Requires: %{name}-examples = %{version}
Requires: %{name}-utils = %{version}

%description devel
This package contains the header files needed for developing 
IMC and IMV pairs.

%package examples
Summary: Example IMC/IMV implementations
License: GPLv2
Group: Applications/System
Requires: %{name}-libs = %{version}

%description examples
This package provides some example implementations of several 
IMC/IMV pairs.

%package utils
Summary: Dynamic library for TNC utilities
License: GPLv2
Group: Development/Libraries

%description utils
A shared library that offers simple configuration file parsing.

%prep
%setup -q -n tncfhh-%{version}
%patch1 -p1
%patch2 -p1
%patch3 -p1
%patch4 -p1
%patch5 -p1
%patch6 -p1
%patch7 -p1
%patch8 -p1

%build
%cmake . -DCMAKE_INSTALL_LIBDIR:PATH=%{_libdir} -DCOMPONENT=all -DNAL=8021x \
%if %{build_attestation_imc_imv}
 -DTPM=on
%endif
make %{?_smp_mflags}

%install
rm -rf $RPM_BUILD_ROOT
#mkdir -p $RPM_BUILD_ROOT%{_libdir}
make install DESTDIR=${RPM_BUILD_ROOT} INSTALL='install -p'

%clean
rm -rf $RPM_BUILD_ROOT

%post -p /sbin/ldconfig
%postun -p /sbin/ldconfig

%post -n tncfhh-libs  -p /sbin/ldconfig
%postun -n tncfhh-libs  -p /sbin/ldconfig

%post -n tncfhh-utils  -p /sbin/ldconfig
%postun -n tncfhh-utils -p /sbin/ldconfig

%post -n tncfhh-examples  -p /sbin/ldconfig
%postun -n tncfhh-examples  -p /sbin/ldconfig

%files
%defattr(-,root,root,-)
%doc README LICENSE doc/tncfhh.pdf
%attr(0644,root,root) %config(noreplace) %{_sysconfdir}/tnc_config
%{_libdir}/libimunit.so.?
%{_libdir}/libimunit.so.?.?.?

%files libs
%{_libdir}/libnaaeap.so.?
%{_libdir}/libnaaeap.so.?.?.?
%{_libdir}/libtncs.so.?
%{_libdir}/libtncs.so.?.?.?
%{_libdir}/libtncxacml.so.?
%{_libdir}/libtncxacml.so.?.?.?
%attr(0755,root,root) %dir %{_sysconfdir}/tnc
%attr(0755,root,root) %dir %{_sysconfdir}/tnc/xacml
%attr(0644,root,root) %config(noreplace) %{_sysconfdir}/tnc/xacml/*

%files devel
%defattr(-,root,root,-)
%{_includedir}/tncfhhConfig.h
%{_includedir}/naaeap/
%attr(0755, root, root) %{_libdir}/libnaaeap.so
%{_includedir}/tncs/
%attr(0755, root, root) %{_libdir}/libtncs.so
%{_includedir}/tcg/tnc/
%{_includedir}/imunit/
%attr(0755, root, root) %{_libdir}/libimunit.so
%{_includedir}/tncutil/
%attr(0755, root, root) %{_libdir}/libtncutil.so
%{_includedir}/tncxacml/
%attr(0755, root, root) %{_libdir}/libtncxacml.so
%attr(0755, root, root) %{_libdir}/libdummy*.so
%attr(0755, root, root) %{_libdir}/libhostscanner*.so
%attr(0755, root, root) %{_libdir}/libclamav*.so
%attr(0755, root, root) %{_libdir}/libexample*.so
%attr(0755, root, root) %{_libdir}/libplatid*.so
%if %{build_attestation_imc_imv}
%attr(0755, root, root) %{_libdir}/libattestation*.so
%endif
#tncsim module
%attr(0644,root,root) %config(noreplace) %{_sysconfdir}/tnc/tncsim_config
%{_bindir}/tncsim

%files examples
%defattr(-,root,root,-)
%attr(0644,root,root) %config(noreplace) %{_sysconfdir}/tnc/*.*
%{_libdir}/libdummy*.so.*
%{_libdir}/libhostscanner*.so.*
%{_libdir}/libclamav*.so.*
%{_libdir}/libexample*.so.*
%{_libdir}/libplatid*.so.*
%if %{build_attestation_imc_imv}
%{_libdir}/libattestation*.so.*
%endif

%files utils
%{_libdir}/libtncutil.so.?
%{_libdir}/libtncutil.so.?.?.?

%changelog
* Thu Sep 12 2013 Avesh Agarwal <avagarwa@redhat.com> - 0.8.3-14
- Rebuilding for rhel7 as due to unblocking of xerces-c build 
  was failing

* Thu Sep 12 2013 Avesh Agarwal <avagarwa@redhat.com> - 0.8.3-13
- Implemented support for dlopen
- Removed libtool support
- Fixed imv and imc build issues arising from a
  previous upstream patch
- Fixed a few coverity scan error issues

* Tue Jul 30 2013 Avesh Agarwal <avagarwa@redhat.com> - 0.8.3-12
- Fixes for rhbz #985785 to fix crash issue in Filecert manager
  in platidimv.
- Fixed crashing of attestation imv so while loading due to
  wrong static initialization order in attestation imv.
- Fixes some coverity scan errors.
- Fixed comilation when sysconf dir variable is not defined on a
  local system. Added some messaging outputs during compilations.
- Fixed erroneous data type conversion issues causing wrong outputs
  and with potential for data corruption.
- Fixes tncutil build issue from upstream commit
- Fixes typo in assignment in platidimv from upstream commit
- Fixes Fix typo in variable declaraction in hostscannerimv
  from upstream commit
- Fixes imcv shared library build issue from upstream commit

* Sun Feb 10 2013 Denis Arnaud <denis.arnaud_fedora@m4x.org> - 0.8.3-11
- Rebuild for Boost-1.53.0

* Sat Feb 09 2013 Denis Arnaud <denis.arnaud_fedora@m4x.org> - 0.8.3-10
- Rebuild for Boost-1.53.0

* Wed Oct 31 2012 Tom Callaway <spot@fedoraproject.org> - 0.8.3-9
- rebuild

* Mon Jul 23 2012 Avesh Agarwal <avagarwa@redhat.com> - 0.8.3-8
- Fix build failure in fedora rawhide. It was caused due to 
  removal of CMAKE_INSTALL_LIBDIR macro from /etc/rpm/cmake.macros 
  that was present in previous fedora releases.

* Sat Jul 21 2012 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 0.8.3-7
- Rebuilt for https://fedoraproject.org/wiki/Fedora_18_Mass_Rebuild

* Tue Feb 28 2012 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 0.8.3-6
- Rebuilt for c++ ABI breakage

* Sat Jan 14 2012 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 0.8.3-5
- Rebuilt for https://fedoraproject.org/wiki/Fedora_17_Mass_Rebuild

* Sat Nov 26 2011 Thomas Spura <tomspur@fedoraproject.org> - 0.8.3-4
- rebuild for https://fedoraproject.org/wiki/Features/F17Boost148

* Tue Sep 20 2011 Avesh Agarwal <avagarwa@redhat.com> - 0.8.3-3
- Fixed libxml2-devel issue in spec file

* Tue Sep 20 2011 Avesh Agarwal <avagarwa@redhat.com> - 0.8.3-2
- Fixed cmake issues
- added a new command tncsim for testing
- Fixed some implementation issues

* Fri Sep 2 2011 Avesh Agarwal <avagarwa@redhat.com> - 0.8.3-1
- New upstream release
- updated local patches

* Mon Aug 8 2011 Avesh Agarwal <avagarwa@redhat.com> - 0.8.2-2
- Fixed broken dependencies of boost-system and boost-thread
- Fixed some performance and implementation issues

* Mon Jul 18 2011 Avesh Agarwal <avagarwa@redhat.com> - 0.8.2-1
- Initial packaging of tncfhh-0.8.2
- Fixed cmake issues
- Fixed xerces issues
- Fixed memory leak and exception issue
