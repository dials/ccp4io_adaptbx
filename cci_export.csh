#! /bin/csh -f
set echo
cd ../ccp4io
if ($status != 0) exit $status
set ccp4io="`pwd`"
setenv CVSROOT /net/cci/cvs
cd /var/tmp
mkdir cvs_export_$$
cd cvs_export_$$
set target="`pwd`"
cvs export -rHEAD ccp4io_adaptbx
cvs export -rHEAD ccp4io
cd $ccp4io
cvs -q diff -r1.1.1.1 > $target/ccp4io/CCI_PATCHES
cd $target
tar cf ccp4io.tar ccp4io ccp4io_adaptbx
gzip ccp4io.tar
zip -q -r ccp4io.zip ccp4io ccp4io_adaptbx
mv ccp4io.tar.gz ccp4io.zip $HOME
cd /var/tmp
rm -rf cvs_export_$$
