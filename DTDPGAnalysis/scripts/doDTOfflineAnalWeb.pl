#!/usr/bin/perl

$run = $ARGV[0];
$dir = $ARGV[1];

$pathweb = "/afs/cern.ch/cms/MUON/dt/sx5/Results/GlobalRuns/$dir/Run$run";

if (($run eq "") || ($dir eq "" )) {

print " Execute as::   \n";
print " > doDTOfflineAnalWeb  #RUN_NB  #GLOBAL_RUN_DIR   \n";
print "         #RUN_NB = Run number   \n";
print "         #GLOBAL_RUN_DIR = Directory where gifs are saved   \n";
print "  				(CRUZET09/CRAFT09)   \n";

}

elsif (!(-e "$pathweb")){

print "                                \n";
print "  Please select a valid directory  (CRUZET09/CRAFT09/...)   \n";
print "       $pathweb does not exist        \n";
print "                                \n";
print " Execute as::   \n";
print " > doDTOfflineAnalWeb  #RUN_NB  #GLOBAL_RUN_DIR   \n";
print "         #RUN_NB = Run number   \n";
print "         #GLOBAL_RUN_DIR = Directory where gifs are saved   \n";
print "                                 (CRUZET09/CRAFT09)   \n";


}

else{

################################################################################################
#
#		Root website (general)
#
################################################################################################


open(FILELIST,"/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DT/OfflineCode/Scripts/WebScripts/plotlistForWeb_Main.txt");
@gifs = <FILELIST>;
close(FILELIST);

## print $pathweb;

### Reference run 

open(REFRUN,"/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DT/OfflineCode/Scripts/referenceRun.txt");
@rrunv = <REFRUN>;
close(REFRUN);


$runref=@rrunv[0];
print "$runref\n";
$pathrefW =@rrunv[1];
print "$pathrefW\n";

#### $pathref = "/afs/cern.ch/cms/MUON/dt/sx5/Results/GlobalRuns/Beam2011/Collisions/Run177718/";
#--------------------


if (!(-e "$pathweb/webPlots/")){
system("mkdir $pathweb/webPlots/");
}

print " Producing main website ..................................... \n";

$pathcurrent = $pathweb;

$pathcurrentW = "";


open(OUTF,">$pathweb/Welcome.html");

&head; 

print OUTF <<EndofHtml1;

<BODY BGCOLOR="lightyellow">
<CENTER>
<IMG SRC="http://cern.ch/isr-muon/CMS-logo.gif" ALIGN=UP WIDTH=45 HEIGHT=45>
<font size=+5>
<B>DT run $run prompt offline plots</B></font>
<IMG SRC="http://cern.ch/isr-muon/CMS-logo.gif" ALIGN=UP WIDTH=45 HEIGHT=45>
<hr>
<CENTER>

<div class="highslide-gallery">

EndofHtml1


## Defined previously: $gif + $gifref + $runref + $giftitle

$count=0;



foreach $file (@gifs){

 if ($count==0){
	 print OUTF "<h2>Data Integrity plots and L1 GMT Trigger Ref</h2><TABLE><TR><TD>\n"
  }
   elsif ($count==3){
	 print OUTF "</TABLE><HR><h2>Chamber performance plots</h2>\n";
         print OUTF "<TABLE><TR><TD>\n";
  }	
   elsif (($count==7) || ($count==11)|| ($count==20) || ($count==24) || ($count==28)  ){
         print OUTF "<TR><TD>\n";
  }
   elsif ($count==16){
	 print OUTF "</TABLE><HR><h2>Trigger performance plots</h2>\n";
        print OUTF "<TABLE><TR><TD>\n";
   }
   else {
         print OUTF "<TD>\n";

   }


      ($gif,$giftitle) =  split(/\@\@/,$file);
      &doItem;
      $count++;
##         print OUTF "<BR>\n";

 }



print OUTF <<EndofHtml1;

</div>

</TABLE>
<h3>
Individual wheel results<BR>
<button onClick="window.location='Wheel+2/'">YB+2</button>
<button onClick="window.location='Wheel+1/'">YB+1</button>
<button onClick="window.location='Wheel+0/'">YB0</button>
<button onClick="window.location='Wheel-1/'">YB-1</button>
<button onClick="window.location='Wheel-2/'">YB-2</button>
<HR>
<button onClick="window.location='ExtraPlots/'">Extra Plots</button>
EndofHtml1

close(OUTF);

######## End of main page

################################################################################################
#  Pages for individual wheels
################################################################################################

open(FILELIST,"/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DT/OfflineCode/Scripts/WebScripts/plotlistForWeb_Wheel.txt");
@gifs = <FILELIST>;
close(FILELIST);


@wheel_names = ("-","+2","+1","+0","-1","-2");
@wheel_nb = ("-","2","1","0","-1","-2");

@sector_names = ("-","01","02","03","04","05","06","07","08","09","10","11","12","13","14");

for ($i=1;$i<=5;$i++){


$wheel = $wheel_names[$i];
$wn = $wheel_nb[$i];

print " Producing website wheel $wheel ..................................... \n";


open(OUTF,">$pathweb/Wheel$wheel/Welcome.html");

$pathcurrent = "$pathweb\/Wheel$wheel";
$pathcurrentW = "Wheel$wheel/";

if (!(-e "$pathcurrent/webPlots/")){
system("mkdir $pathcurrent/webPlots/");
}

&head; 

print OUTF <<EndofHtml1;

<BODY BGCOLOR="lightgreen">

<CENTER>
<IMG SRC="http://cern.ch/isr-muon/CMS-logo.gif" ALIGN=UP WIDTH=45 HEIGHT=45>
<font size=+5>
<B>DT run $run prompt offline plots for wheel $wheel</B>
<IMG SRC="http://cern.ch/isr-muon/CMS-logo.gif" ALIGN=UP WIDTH=45 HEIGHT=45>

<hr>
<CENTER>

EndofHtml1

## Defined previously: $gif + $gifref + $runref + $giftitle

$count=0;

foreach $file (@gifs){

  if ($count==0){
	 print OUTF "<h2>Data Integrity plots</h2><TABLE><TR><TD>\n"
  }
   elsif ($count==2){
	 print OUTF "</TABLE><HR><h2>Chamber performance plots</h2>\n";
         print OUTF "<TABLE><TR><TD>\n";
  }	
   elsif (($count==6) || ($count==10)|| ($count==18) || ($count==22) || ($count==28) || ($count==14) ){
         print OUTF "<TR><TD>\n";
  }

   elsif ($count==24){
	 print OUTF "</TABLE><HR><h2>Trigger performance plots</h2>\n";
         print OUTF "<TABLE><TR><TD>\n";
   }
   else {
         print OUTF "<TD>\n";

   }


      ($gif,$giftitle) =  split(/\@\@/,$file);
      &doItem;
      $count++;

 }



print OUTF <<EndofHtml1;

</TABLE>

<h2> Sectors data<BR>

EndofHtml1



for ($s=1;$s<=14;$s++){

$sector = $sector_names[$s];

print OUTF <<EndofHtml1;

<button onClick="window.location='Sect$sector/'">Sect $sector</button>

EndofHtml1

&createsectorweb($run,$wn,$sector,$s);

}

print OUTF <<EndofHtml1;
<BR>
<button onClick="window.location='ExtraPlots/'">Extra Plots</button>

<h3>

EndofHtml1

close(OUTF);

} ## Loop on sectors

} ## Loop on wheels

######## End of wheel pages



################################################################################################
################################################################################################

sub doItem{

if ($issector==1){
 $filout = "OUTF2"
}
else{
 $filout = "OUTF"
}
;


$gifcurrent = $gif;
$gifref = $gif;

$gifcurrent =~ s/\$run/$run/;
$gifref =~ s/\$run/$runref/;

$gifcurrent =~ s/\$wn/$wn/;
$gifref =~ s/\$wn/$wn/;

$gifcurrent =~ s/\$sn/$s/;
$gifref =~ s/\$sn/$s/;

$gifcurrent =~ s/\\//g;
$gifref =~ s/\\//g;

$gifcurrent =~ s/ //g;
$gifref =~ s/ //g;


##system("convert $pathref/$pathcurrentW/$gifref -bordercolor green1 -border 20 -resize 80% /tmp/DTPromptplot.gif");
##system("montage $pathcurrent/$gifcurrent /tmp/DTPromptplot.gif -mode concatenate $pathcurrent/webPlots/Comp_$gifcurrent");

## <a href="webPlots/Comp_$gifcurrent" class="highslide" onclick="return hs.expand(this,config1)">
##    <!h4><!font color="orange">Pop-up plot (Run $run)<!/font><!/h4><!BR>
#   <h3><font color="orange">Left: Current run $run </font><br> <font color="green">Right: Reference run $runref</font></h3>
#   <hr>
#    <!div class='single-image'>
#    <!a href="$gifcurrent" class="highslide" onclick="return hs.expand(this)">
#    <!img src="$pathcurrentW\./$gifcurrent" alt="Highslide JS" height="120" width="107" /><!/a>
#    <!/div>

 print "                   *******   $gifcurrent\n";

##<div class="highslide-gallery">
print $filout <<endHtmHtm;

 <a href="$gifcurrent" class="highslide" onclick="return hs.expand(this,config1)">
  <img src="$gifcurrent" alt="Highslide JS" title="Click to enlarge" width="220"/></a>
 <div class='highslide-heading'><center>
     <h2><font color="white">$giftitle</font></h2>
 </div>
 <div class='highslide-caption' style="padding: 1px 10px 1px 10px"><center>
    <div class='single-image'>
    <h4><font color="green">Pop-up reference plot (Run $runref)</font></h4>
    <a href="$pathrefW/$pathcurrentW/$gifref" class="highslide" onclick="return hs.expand(this)">
    <img src="$pathrefW/$pathcurrentW/$gifref" alt="Highslide JS" width="450" /></a>
    </div>
 </div>

endHtmHtm

##</div>

}

#############################################################################################

sub head{

if ($issector==1){
 $filout = "OUTF2"
}
else{
 $filout = "OUTF"
}


print $filout <<EndofHtml1;
<html><head><title>DT run $run data summary</title>

<script type="text/javascript" src="https://dt-sx5.web.cern.ch/dt-sx5/styles/highslide/highslide-with-gallery.js"></script>
<!script type="text/javascript" src="https://dt-sx5.web.cern.ch/dt-sx5/styles/highslide/highslide.js">
<!/script>
<link rel="stylesheet" type="text/css" href="https://dt-sx5.web.cern.ch/dt-sx5/styles/highslide/highslide.css" />

<script type="text/javascript">
hs.graphicsDir = 'https://dt-sx5.web.cern.ch/dt-sx5/styles/highslide/graphics/';
hs.align = 'center';
hs.transitions = ['expand', 'crossfade'];
hs.wrapperClassName = 'dark borderless floating-caption';
hs.fadeInOut = true;
hs.dimmingOpacity = 0.8;
//hs.captionEval = 'this.thumb.alt';

//hs.outlineType = 'rounded-white';

hs.marginBottom = 105; // make room for the thumbstrip and the controls
hs.marginTop = 50; // make room for the heading

hs.numberPosition = 'caption bottom';
hs.captionEval = 'this.a.title';
hs.captionOverlay.position = 'rightpanel';

// Heading with button - this example uses the same heading for all images  
hs.headingId = 'my-heading';
hs.dragByHeading = false;
hs.headingOverlay = {
        position: 'top center',
        fade: false,
        relativeTo: 'viewport',
};


// Add the slideshow providing the controlbar and the thumbstrip
if (hs.addSlideshow) hs.addSlideshow({
	//slideshowGroup: 'group1',
	interval: 5000,
	repeat: false,
	useControls: true,
//	captionOverlay: { position: 'rightpanel', width: '600px'},
	fixedControls: 'fit',
	overlayOptions: {
		className: 'text-controls',
		position: 'bottom center',
		relativeTo: 'viewport',
		offsetY: -60
	},
	thumbstrip: {
		position: 'bottom center',
		mode: 'horizontal',
		relativeTo: 'viewport'
	}
});


var config1 = {

	slideshowGroup: 'group1',
//	thumbnailId: 'thumb1',
	transitions: ['expand', 'crossfade'],
	headingEval: 'this.a.title',
	align: 'left',
	captionOverlay: { position: 'rightpanel', width: '500px'},

};




// Make all images animate to the one visible thumbnail
var miniGalleryOptions1 = {
        thumbnailId: 'thumb1'
}
</script>


</HEAD>


EndofHtml1

}

#############################################################################################

sub createsectorweb($run,$wn,$sector,$s)
{

$run = $_[0];
$wn = $_[1];
$sector = $_[2];
$sn= $_[3];


open(OUTF2,">$pathweb/Wheel$wheel/Sect$sector/Welcome.html");
         
$pathcurrent = "$pathweb\/Wheel$wheel/Sect$sector/";
$pathcurrentW = "Wheel$wheel/Sect$sector/";
   
if (!(-e "$pathcurrent/webPlots/")){
system("mkdir $pathcurrent/webPlots/"); 
}   

print "        -----  Producing website wheel $wheel sector $sector ..................................... \n";

       $issector =1;
        &head;   
       $issector =0;
    
print OUTF2 <<EndofHtml1;

<BODY BGCOLOR="lightblue">

<CENTER>
<IMG SRC="http://cern.ch/isr-muon/CMS-logo.gif" ALIGN=UP WIDTH=45 HEIGHT=45>
<font size=+5>
<B>DT run $run prompt offline plots for wheel $wheel sector $sector</B>
<IMG SRC="http://cern.ch/isr-muon/CMS-logo.gif" ALIGN=UP WIDTH=45 HEIGHT=45>

<hr>

EndofHtml1

open(FILELIST2,"/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DT/OfflineCode/Scripts/WebScripts/plotlistForWeb_Sector.txt");
@gifs2 = <FILELIST2>;
close(FILELIST2);

$count=0;

foreach $file2 (@gifs2){

  if ($count==0){
         print OUTF2 "<h2>Data Integrity plots</h2><TABLE><TR><TD>\n"
  }
   elsif ($count==2){
         print OUTF2 "</TABLE><HR><h2>Chamber performance plots</h2>\n";
         print OUTF2 "<TABLE><TR><TD>\n";
  }
   elsif (($count==4) || ($count==7) || ($count==10)|| ($count==13) || ($count==15) || ($count==18) || ($count==21) || ($count==24) || ($count==27) || ($count==29)   || ($count==32)   || ($count==35)   || ($count==38)   || ($count==40)   || ($count==44) || ($count==51) ){
         print OUTF2 "<TR><TD>\n";
  } 

   elsif ($count==47){
         print OUTF2 "</TABLE><HR><h2>Trigger performance plots</h2>\n";
         print OUTF2 "<TABLE><TR><TD>\n";
   }
   else {
         print OUTF2 "<TD>\n";

   }


      ($gif,$giftitle) =  split(/\@\@/,$file2);
       $issector =1;
        &doItem;   
       $issector =0;
      $count++;
   
 }

print OUTF2 "</TABLE><h3>";

close(OUTF2);


}
