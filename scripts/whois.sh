#!/bin/sh
phonebook --terse ccid --terse firstname --terse surname $1 | sed 's/;/ /g'  | awk '{print "If you look for " $2" "$3 " click on\n" "http://cmsonline.cern.ch/portal/page/portal/CMS%20online%20system/Shiftlist/monthly?shift_type=9&year=2010&month=3&_piref815_525408_815_492858_492869.next_page=%2Fhtdocs%2Fshiftlist%2Fshifters_info.jsp&_piref815_525408_815_492858_492869.shifterID="$1}' ;
