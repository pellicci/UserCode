min=$3
max=$4
NFILE=`rfdir $2 | grep root | awk '{print $9}' | awk -v mmin=$min '{ if (substr($1,13,6) >= mmin) print $1}' | awk -v mmax=$max '{ if (substr($1,13,6) <= mmax) print $1}' | wc -l `
rfdir $2 | grep root | awk '{print $9}' | awk -v mmin=$min '{ if (substr($1,13,6) >= mmin) print $1}' | awk -v mmax=$max '{ if (substr($1,13,6) <= mmax) print $1}' | sed "s|^| stager_get -M $2/|" | tr "\n" ";" > tmp.sh
source tmp.sh
rfdir $2 | grep root | awk '{print $9}' | awk -v mmin=$min '{ if (substr($1,13,6) >= mmin) print $1}' | awk -v mmax=$max '{ if (substr($1,13,6) <= mmax) print $1}' | sed "s|^| stager_qry -M $2/|" | tr "\n" ";" > tmp.sh
source tmp.sh
NSTAGED=`source tmp.sh | grep STAGED | wc -l `
echo "Found $NFILE files, of which $NSTAGED staged."
echo "stager_get was called, please try again later if you like"
#echo "now hadding staged files..."
#`source tmp.sh | grep STAGED | grep root | awk '{print $1}' | sed "s|^|rfio://|" | tr "\n" " " | sed "s|^|hadd $1 |"`

rm tmp.sh
echo "no further actions taken..."
