Name: t-union-tairfileimporter
Version: %{_version}
Release: %(echo $RELEASE)%{?dist}
URL: %{_svn_path}

Summary: Athena module(AD matching post) for Yitao Union
Group: TBUnion/Engine
License: Commercial

AutoReqProv: no
BuildRequires: gcc >= 4.1.2
BuildRequires: t-union-tools >= 0.4.4-79.el5
Requires: t-union-tools >= 0.4.4

%description
%{_svn_path}
%{_svn_revision}
    The utilities of cps-trade.

%build
cd $OLDPWD/..
make -C src/ clean
make -C src/ release=yes

cd $OLDPWD

%install
# OLDPWD is the dir of rpm_create running
# _prefix is an inner var of rpmbuild,
# can set by rpm_create, default is "/home/a"
# _lib is an inner var, maybe "lib" or "lib64" depend on OS

# The below commands are for backtotair
# create dirs
mkdir -p .%{_prefix}/share/tools/tairFileImporter/bin/
mkdir -p .%{_prefix}/share/tools/tairFileImporter/conf/
# copy files
cp $OLDPWD/../bin/tairFileImporter				.%{_prefix}/share/tools/tairFileImporter/bin/
cp $OLDPWD/../conf/importer.conf		    	.%{_prefix}/share/tools/tairFileImporter/conf/
cp $OLDPWD/../conf/log4cpp.conf		    	.%{_prefix}/share/tools/tairFileImporter/conf/

%post
# The below command is for backtotair
chmod +x /home/a/share/tools/tairFileImporter/bin/tairFileImporter
rm -f /home/a/bin/tairFileImporter
ln -s %{_prefix}/share/tools/tairFileImporter/bin/tairFileImporter  /home/a/bin/tairFileImporter

%files
%defattr(-,ads,ads)
%{_prefix}

%changelog
* Thu Dec 27 2012 xiaoliang.zxl <xiaoliang.zxl@taobao.com> 0.0.3-0
- refactor tairFileImporter
* Tue Nov 15 2011 xiaoliang.zxl <xiaoliang.zxl@taobao.com> 0.0.2-0
* Mon Dec 29 2010 zhonghuan <zhonghuan@taobao.com> 0.0.1-0
- init version
