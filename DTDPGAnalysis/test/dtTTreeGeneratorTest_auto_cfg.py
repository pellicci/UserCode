import os
import subprocess
import sys
import imp
from subprocess import Popen, PIPE, STDOUT

pathname = "/castor/cern.ch/cms/store/caf/user/pellicci/DPG/Dumper/auto/"
outpathname = "/castor/cern.ch/user/d/dtdqm/NTuples/RunBased/"

p1 = subprocess.Popen(["rfdir",pathname], stdout=PIPE)
p2 = subprocess.Popen(["awk", "{print $9}"], stdin=p1.stdout, stdout=PIPE)
p3 = subprocess.Popen(["sort", "-t_", "-k", "3"], stdin=p2.stdout, stdout=PIPE)
p4 = subprocess.Popen(["cut", "-d_", "-f", "3"], stdin=p3.stdout, stdout=PIPE)
raw_file_list = p4.communicate()[0]
file_list = raw_file_list.rsplit('\n')

p1 = subprocess.Popen(["rfdir",pathname], stdout=PIPE)
p2 = subprocess.Popen(["awk", "{print $9}"], stdin=p1.stdout, stdout=PIPE)
p3 = subprocess.Popen(["sort", "-t_", "-k", "3"], stdin=p2.stdout, stdout=PIPE)
raw_fileSONAME_list = p3.communicate()[0]
fileSONAME_list = raw_fileSONAME_list.rsplit('\n')

for runnumber in file_list:
    actual_number = runnumber + "\n"
    file_run_list = open('runlist.txt','r')
    run_list = file_run_list.readlines()
    file_run_list.close()
    if actual_number in run_list:
        outmessage = 'Run ' + runnumber + ' already processed'
        print outmessage
    else:
        print 'Processing run ' + runnumber

        num_index = file_list.index(runnumber)
        finalname = 'rfio:' + pathname + fileSONAME_list[num_index]
        outputname = 'DTTtree_' + runnumber + '.root'

        instring = open("dtTTreeGeneratorTest_TEMPLATE_cfg.py").read()
        instring = instring.replace('FINALNAME', finalname)
        instring = instring.replace('OUTPUTNAME', outputname)
        fout = open("dtTTreeGeneratorTest_AUTO_cfg.py", 'w')
        fout.write(instring)
        fout.close()

        os.system("cmsRun dtTTreeGeneratorTest_AUTO_cfg.py")

        os.system("rfcp " + outputname + " " + outpathname)
        os.system("rm " + outputname)
 
        new_file_run_list = open('runlist.txt','a')
        new_runnumber = "\n" + runnumber
        new_file_run_list.write(new_runnumber)
        new_file_run_list.close()

